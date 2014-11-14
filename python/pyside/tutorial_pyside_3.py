import PySide
from PySide import QtGui
from PySide import QtCore
import pyqtgraph as pg
import numpy as np
import serial
import sys
import csv


class MainWindow(QtGui.QMainWindow):


    def __init__(self,parent=None):
        QtGui.QMainWindow.__init__(self,parent)

        self.mGraph = pg.GraphicsWindow()
        self.setCentralWidget(self.mGraph)

        self.mPort = serial.Serial("/dev/ttyACM0",1000000)

        self.mBuffSize = 200
        self.mSampleTime = 0.050

        self.mPlotBuff = np.zeros(self.mBuffSize)
        self.mTimeBuff = np.zeros(self.mBuffSize)#np.array([q*0.025 for q in range(self.mBuffSize)])

        self.mTimer = QtCore.QTimer()
        self.connect(self.mTimer,QtCore.SIGNAL("timeout()"),self.onUpdateGraph)
        self.mTimer.start(50)

        self.mSimTime = 0

        self.mPlot1 = self.mGraph.addPlot(title="test plot")
        self.mPlot1.setYRange(0,600)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff)

        self.mBuffData_xt   = [0]
        self.mBuffData_xt_1 = []
        self.mBuffData_ut   = [0]

    def sliceBuffer(self,buff,newVal):
        for i in range(len(buff)-1):
            buff[i] = buff[i+1]
        buff[len(buff)-1] = newVal

    def onUpdateGraph(self):
        self.mSimTime += self.mSampleTime

        # Pedir datos por puerto serie
        self.mPort.write('s')
        buff = self.mPort.read(4)

        data = map(ord,buff)

        print "data: " , data

        x1 = (data[0] << 8) + data[1]
        #rpm = x1 * 20. * 60. / 1200.
        rpm = x1
        x2 = (data[2] << 8) + data[3]
        u = x2 / 65535.0

        self.sliceBuffer(self.mTimeBuff,self.mSimTime)
        self.sliceBuffer(self.mPlotBuff,rpm)
        self.mPlot1.plot(self.mTimeBuff,self.mPlotBuff,clear=True)
        self.mPlot1.enableAutoRange('y',False)

        self.mBuffData_xt_1.append(self.mBuffData_xt[-1])
        self.mBuffData_xt.append(rpm)
        self.mBuffData_ut.append(u)

        print "x1: " , x1
        print "x2: " , x2
        print "rpm: " , rpm
        print "u: " , u


print "sys.argv: " , sys.argv
app = QtGui.QApplication(sys.argv)

window = MainWindow()
window.show()

app.exec_()

print "finishing application"

print "saving data"

# Add an extra element to the mBuffData_xt_1
window.mBuffData_xt_1.append(window.mBuffData_xt[-1])

with open('data.csv', 'wb') as f:
    writer = csv.writer(f)
    for i in range(len(window.mBuffData_xt)):
        writer.writerow([window.mBuffData_xt_1[i],
                         window.mBuffData_xt[i],
                         window.mBuffData_ut[i]])


print "finished application"

