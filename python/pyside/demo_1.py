from PySide import QtGui, QtCore
import serial
import pyqtgraph as pg
import sys
import glob
import numpy as np

class MCUInterface( object ):

    COMMAND_READ_COUNT  = "read_count"
    COMMAND_READ_SPEED  = "read_speed"
    COMMAND_SET_DUTY    = "set_duty"
    COMMAND_SET_SPEED   = "set_speed"    

    CODES = { "start" : 's',
              "error" : 'e',
              "read_encoder" : 'q',
              "read_speed" : 'r',
              "read_all" : 'a',
              "set_speed" : 'w',
              "set_direction" : 'd' }

    def __init__( self, port = "/dev/ttyACM0", baudrate= 1000000 ):
        self.mPort = None
        self.mPortName = port
        self.mBaudRate = baudrate

        self.continuousReading = False
        self.m_currentCommand = ""
        self.isPortOpen = False
        self.m_currentValue = 0        

    def open( self ):
        if self.mPort is not None:
            print "MCUInterface::open> The port is already openend, closing it first"
            self.close()
        try:
            self.mPort = serial.Serial( self.mPortName, self.mBaudRate )            
        except:
            self.mPort = None
            print "MCUInterface::open> Couldn't open serial port"
        
        if self.mPort is not None:
            self.isPortOpen = True
            print "MCUInterface::open> Open the serial port"

    def setparams( self, portname = "/dev/ttyACM0", baudrate = 1000000 ):
        self.mPortName = portname
        self.mBaudRate = baudrate

    def close( self ):
        if self.mPort is not None :
            self.mPort.close()
            self.mPort = None
            self.isPortOpen = False

    def onStartReading( self, readCommandIndx ):
        if readCommandIndx == 0: # Read encoder counts
            self.m_currentCommand = "read_encoder"
            
        elif readCommandIndx == 1:# Read the speed reg
            self.m_currentCommand = "read_speed"
            
        self.continuousReading = True

    def onStopReading( self ):
        self.continuousReading = False
        self.close()

    def update( self, dt ):
        if not self.continuousReading:
            return

        if command == "read_encoder":
            self.m_currentValue = self.onReadEncoder()
        elif command == "read_speed":
            self.m_currentValue = self.onReadSpeed()

    def value( self ):
        return self.m_currentValue        

    def executeCommand( self, command, sendData ):        
        if self.isPortOpen == False or self.mPort == None:
            print "MCUInterface::executeCommand> Please, open a port before trying to send something"
            return None

        buffTx = []
        buffTx.append( MCUInterface.CODES[ 'start' ] )
        buffTx.append( MCUInterface.CODES[ command ] )
        for i in range( len( sendData ) ):
            buffTx.append( sendData[i] )

        for byte in buffTx :
            self.mPort.write( byte )

        # One all bytes from the txBuffer have been send ...
        # ... wait for a 
        buffRx = self.mPort.read( 11 )
        data = map( ord, buffRx )

        return data

    def onReadEncoder( self ):
        bytesRx = self.executeCommand( self.m_currentCommand, [0,0,0,0] )
        encValue = ( bytesRx[0] << 24 ) + ( bytesRx[1] << 16 ) + ( bytesRx[2] << 8 ) + bytesRx[3]
        return encValue
        
    def onReadSpeed( self ):
        bytesRx = self.executeCommand( self.m_currentCommand, [0,0,0,0] )        
        encSpeed = ( bytesRx[0] << 24 ) + ( bytesRx[1] << 16 ) + ( bytesRx[2] << 8 ) + bytesRx[3]
        return encSpeed
        
    def onSetSpeed( self ):
        pass

    def onSetDirection( self ):
        pass


class MainWindow( QtGui.QMainWindow ):

    BAUDRATES = ["9600", "19200", "38400", "115200", "230400", "1000000", "2000000"]
    READ_OPTIONS = [ "Counts (Enc Counts)", "Speed (RPM)" ]
    SET_OPTIONS = [ "Duty [0-1]", "Speed (RPMs)" ]

    DUTY_RANGES = { "min" : 0, "max" : 1 }
    RPM_RANGES = { "min" : 0, "max" : 500 }

    SAMPLE_TIME = 50

    COMMANDS = ["read_encoder",
                "read_speed",
                "set_speed",
                "set_direction"]

    def __init__( self, parent = None ):
        QtGui.QMainWindow.__init__( self,parent )

        self.mCentralWidget = QtGui.QWidget()
        self.setCentralWidget( self.mCentralWidget )

        self.mLblPortSettings = QtGui.QLabel( "COM port settings" )
        self.mCbPortsList = QtGui.QComboBox()
        self.mCbPortBaud = QtGui.QComboBox()
        self.mBtnOpenPort = QtGui.QPushButton( "Open port" )
        self.mBtnClosePort = QtGui.QPushButton( "Close port" )

        self.mLblReadSettings = QtGui.QLabel( "Read settings" )
        self.mCbReadOptions = QtGui.QComboBox()
        self.mBtnReadStart = QtGui.QPushButton( "Start" )
        self.mBtnReadStop = QtGui.QPushButton( "Stop" )

        self.mLblSetSettings = QtGui.QLabel( "Set value settings" )
        self.mCbSetOptions = QtGui.QComboBox()
        self.mInputSetValue = QtGui.QLineEdit( "Enter a value here" )
        self.mBtnSetSend = QtGui.QPushButton( "Send data" )
        self.mDSpBxSetDuty1 = QtGui.QDoubleSpinBox()
        self.mDSpBxSetDuty2 = QtGui.QDoubleSpinBox()
        self.mDSpBxSetRPM1 = QtGui.QDoubleSpinBox()
        self.mDSpBxSetRPM2 = QtGui.QDoubleSpinBox()

        self.mLblPlotArea = QtGui.QLabel( "Plotting Area" )
        self.mPlotArea = PlotArea()
        self.mPlotArea.setCaller( self )

        self.mLblLogSettings = QtGui.QLabel( "Logging Area" )
        self.mBtnStartLogging = QtGui.QPushButton( "Start logging" )
        self.mBtnStopLogging  = QtGui.QPushButton( "Stop logging" )
        self.mBtnShowLogs = QtGui.QPushButton( "Show logs" )

        # Creating the layouts for our items
        self.mLytMainLayout = QtGui.QHBoxLayout()

        self.mLytSettingsLayout = QtGui.QVBoxLayout()
        self.mLytPortLayout = QtGui.QVBoxLayout()
        self.mLytReadLayout = QtGui.QVBoxLayout()
        self.mLytSetLayout 	= QtGui.QVBoxLayout()

        self.mLytPlotLogLayout	= QtGui.QVBoxLayout()
        self.mLytLogLayout		= QtGui.QVBoxLayout()

        self.mLytViewLayout		= QtGui.QVBoxLayout()
        self.mLytCalibLayout 	= QtGui.QVBoxLayout()

        """
            CREATING OUR INSTANCE VARIABLES USED IN THE APPLICATION
        """
        self.mMCUInterface = MCUInterface()
        self.mTimer = QtCore.QTimer()

        self.mPlot = self.mPlotArea.addPlot( title = "test plot" )



        self.initializeElements()
        self.initializeLayout()
        self.initializeSignals()

    def initializeElements( self ):
        list_of_ports = self.list_ports()
        self.mCbPortsList.addItems( list_of_ports )
        self.mCbPortBaud.addItems( MainWindow.BAUDRATES )

        self.mCbReadOptions.addItems( MainWindow.READ_OPTIONS )

        self.mCbSetOptions.addItems( MainWindow.SET_OPTIONS )
        self.mDSpBxSetDuty1.setMinimum( MainWindow.DUTY_RANGES["min"] )
        self.mDSpBxSetDuty1.setMaximum( MainWindow.DUTY_RANGES["max"] )
        self.mDSpBxSetDuty2.setMinimum( MainWindow.DUTY_RANGES["min"] )
        self.mDSpBxSetDuty2.setMaximum( MainWindow.DUTY_RANGES["max"] )
        self.mDSpBxSetRPM1.setMinimum( MainWindow.RPM_RANGES["min"] )
        self.mDSpBxSetRPM1.setMaximum( MainWindow.RPM_RANGES["max"] )
        self.mDSpBxSetRPM2.setMinimum( MainWindow.RPM_RANGES["min"] )
        self.mDSpBxSetRPM2.setMaximum( MainWindow.RPM_RANGES["max"] )

    def initializeLayout( self ):
        self.mCentralWidget.setLayout( self.mLytMainLayout )

        self.mLytMainLayout.addLayout( self.mLytSettingsLayout )

        self.mLytPortLayout.addWidget( self.mLblPortSettings )
        self.mLytPortLayout.addWidget( self.mCbPortsList )
        self.mLytPortLayout.addWidget( self.mCbPortBaud )
        self.mLytPortLayout.addWidget( self.mBtnOpenPort )
        self.mLytPortLayout.addWidget( self.mBtnClosePort )

        self.mLytSettingsLayout.addLayout( self.mLytPortLayout )

        self.mLytReadLayout.addWidget( self.mLblReadSettings )
        self.mLytReadLayout.addWidget( self.mCbReadOptions )
        self.mLytReadLayout.addWidget( self.mBtnReadStart )
        self.mLytReadLayout.addWidget( self.mBtnReadStop )

        self.mLytSettingsLayout.addLayout( self.mLytReadLayout )

        self.mLytSetLayout.addWidget( self.mLblSetSettings )
        self.mLytSetLayout.addWidget( self.mCbSetOptions )
        self.mLytSetLayout.addWidget( self.mInputSetValue )
        self.mLytSetLayout.addWidget( self.mDSpBxSetDuty1 )
        self.mLytSetLayout.addWidget( self.mDSpBxSetDuty2 )
        self.mLytSetLayout.addWidget( self.mDSpBxSetRPM1 )
        self.mLytSetLayout.addWidget( self.mDSpBxSetRPM2 )

        self.mLytSettingsLayout.addLayout( self.mLytSetLayout )

        self.mLytMainLayout.addLayout( self.mLytPlotLogLayout )

        self.mLytPlotLogLayout.addWidget( self.mLblPlotArea )
        self.mLytPlotLogLayout.addWidget( self.mPlotArea )
        self.mLytPlotLogLayout.addLayout( self.mLytLogLayout )

        self.mLytLogLayout.addWidget( self.mBtnStartLogging )
        self.mLytLogLayout.addWidget( self.mBtnStopLogging )
        self.mLytLogLayout.addWidget( self.mBtnShowLogs )

    def initializeSignals( self ):

        self.connect( self.mBtnOpenPort, QtCore.SIGNAL( "clicked()" ), self.onOpenPort )
        self.connect( self.mBtnClosePort, QtCore.SIGNAL( "clicked()" ), self.onClosePort )
        self.connect( self.mBtnReadStart, QtCore.SIGNAL( "clicked()" ), self.onReadStart )
        self.connect( self.mBtnReadStop, QtCore.SIGNAL( "clicked()" ), self.onReadStop )
        self.connect( self.mBtnSetSend, QtCore.SIGNAL( "clicked()"), self.onSendSingleSpeedValue )
        self.connect( self.mBtnStartLogging, QtCore.SIGNAL( "clicked()" ), self.onStartLogging )
        self.connect( self.mBtnStopLogging, QtCore.SIGNAL( "clicked()" ), self.onStopLogging )
        self.connect( self.mBtnShowLogs, QtCore.SIGNAL( "clicked()" ), self.onShowLogs )
        self.connect( self.mTimer, QtCore.SIGNAL( "timeout()" ), self.onTick )

    def onOpenPort( self ):
        print "MainWindow::onOpenPort>"
        baudRate = int( self.mCbPortBaud.currentText() )
        portName = self.mCbPortsList.currentText()
        self.mMCUInterface.setparams( portName, baudRate )
        self.mMCUInterface.open()

    def onClosePort( self ):
        print "MainWindow::onClosePort>"
        self.mMCUInterface.close()

    def onTick( self ):
        print "MainWindow::onTick>"
        self.mMCUInterface.update( MainWindow.SAMPLE_TIME )

    def onReadStart( self ):
        print "MainWindow::onReadStart>"
        currentReadCommandIndx = self.mCbReadOptions.currentIndex()
        self.mMCUInterface.onStartReading( currentReadCommandIndx )
        self.mTimer.start( MainWindow.SAMPLE_TIME )

    def onReadStop( self ):
        print "MainWindow::onReadStop>"
        self.mMCUInterface.onStopReading()
        self.mTimer.stop()

    def onSendSingleSpeedValue( self ):
        print "MainWindow::onSendSingleSpeedValue>"

    def onStartLogging( self ):
        print "MainWindow::onStartLogging>"

    def onStopLogging( self ):
        print "MainWindow::onStopLogging>"

    def onShowLogs( self ):
        print "MainWindow::onShowLogs>"        

    # Returns a list of the available ports
    def list_ports( self ):
        """"From StackOverflow post
            http://stackoverflow.com/questions/12090503/listing-available-com-ports-with-python
        """
        """Lists serial ports

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of available serial ports
        """
        if sys.platform.startswith('win'):
            ports = ['COM' + str(i + 1) for i in range(256)]

        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this is to exclude your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty[A-Za-z]*')

        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')

        else:
            raise EnvironmentError('Unsupported platform')

        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result



class PlotArea( pg.GraphicsWindow ):

    BUFF_SIZE = 200

    def __init__( self ):
        super( PlotArea, self ).__init__()

        self.caller = None        

        self.m_simTime = 0
        self.m_value = 0

        self.m_timeBuff = np.zeros( PlotArea.BUFF_SIZE )
        self.m_plotBuff = np.zeros( PlotArea.BUFF_SIZE )

        self.m_plot = self.addPlot( title = "test plot" )

    def setCaller( self, caller ):
        self.caller = caller

    def sliceBuffer( self, buff, newVal ):
        for i in range( len(buff)-1 ):
            buff[i] = buff[i+1]
        buff[len(buff)-1] = newVal

    def onReset( self ):
        self.m_timeBuff = np.zeros( PlotArea.BUFF_SIZE )
        self.m_plotBuff = np.zeros( PlotArea.BUFF_SIZE )
        self.m_simTime = 0
        self.m_value = 0

    def setValue( self, value ):
        self.m_value = value

    def onUpdateGraph( self, dt ):
        self.m_simTime += dt

    def onSetMode( self, mode ):
        if mode == 0: ## read encoders
            self.m_plot.setYRange( 0, 1000 )
        elif mode == 1:
            self.m_plot.setYRange( 0, 600 )


app = QtGui.QApplication( sys.argv )
window = MainWindow()
window.show()
sys.exit( app.exec_() )