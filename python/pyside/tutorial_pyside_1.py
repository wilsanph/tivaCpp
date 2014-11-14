import PySide
from PySide import QtGui
from PySide import QtCore
import pyqtgraph as pg
import numpy as np
import serial
import sys



class MainWindow(QtGui.QMainWindow):


    def __init__(self,parent=None):
        QtGui.QMainWindow.__init__(self,parent)

        self.mGraph = pg.GraphicsWindow()
        self.setCentralWidget(self.mGraph)

        self.mPort = serial.Serial("/dev/ttyACM0",1000000)

        self.mBuffSize = 200
        self.mSampleTime = 0.025

        self.mPlotBuff = np.zeros(self.mBuffSize)
        self.mPlotBuff2 = np.zeros(self.mBuffSize)
        self.mPlotBuff3 = np.zeros(self.mBuffSize)
        self.mTimeBuff = np.zeros(self.mBuffSize)#np.array([q*0.025 for q in range(self.mBuffSize)])

        self.mTimer = QtCore.QTimer()
        self.connect(self.mTimer,QtCore.SIGNAL("timeout()"),self.onUpdateGraph)
        self.mTimer.start(25)

        self.mSimTime = 0

        self.mPlot1 = self.mGraph.addPlot(title="test plot")
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff2)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff3)


    def sliceBuffer(self,buff,newVal):
        for i in range(len(buff)-1):
            buff[i] = buff[i+1]
        buff[len(buff)-1] = newVal

    def onUpdateGraph(self):
        self.mSimTime += 25./1000.

        # Pedir datos por puerto serie
        self.mPort.write('s')
        buff = self.mPort.read(6)

        data = map(ord,buff)

        print "data: " , data

        x1 = (data[0] << 8) + data[1]
        x2 = (data[2] << 8) + data[3]
        x3 = (data[4] << 8) + data[5]

        x1 = (x1 / 4095.) * 1.0
        x2 = (x2 / 4095.) * 1.0
        x3 = (x3 / 4095.) * 1.0

        self.sliceBuffer(self.mTimeBuff,self.mSimTime)
        self.sliceBuffer(self.mPlotBuff,x1)
        self.sliceBuffer(self.mPlotBuff2,x2)
        self.sliceBuffer(self.mPlotBuff3,x3)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff,clear=True)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff2)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff3)
        self.mPlot1.enableAutoRange('y',False)

        print "x1: " , x1
        print "x2: " , x2
        print "x3: " , x3

        """

        self.mGraph.plot(self.mSimTime,x1,clear=True)
        """
        pass

print "sys.argv: " , sys.argv
app = QtGui.QApplication(sys.argv)

window = MainWindow()
window.show()

app.exec_()
