#!/usr/bin/env python

"""PySide port of the opengl/hellogl example from Qt v4.x"""

import sys
import math
from PySide import QtCore, QtGui, QtOpenGL
import serial

try:
    from OpenGL import GL
except ImportError:
    app = QtGui.QApplication(sys.argv)
    QtGui.QMessageBox.critical(None, "OpenGL hellogl",
                            "PyOpenGL must be installed to run this example.",
                            QtGui.QMessageBox.Ok | QtGui.QMessageBox.Default,
                            QtGui.QMessageBox.NoButton)
    sys.exit(1)


class Window(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.glWidget = GLWidget()

        self.xSlider = self.createSlider(QtCore.SIGNAL("xRotationChanged(int)"),
                                         self.glWidget.setXRotation)
        self.ySlider = self.createSlider(QtCore.SIGNAL("yRotationChanged(int)"),
                                         self.glWidget.setYRotation)
        self.zSlider = self.createSlider(QtCore.SIGNAL("zRotationChanged(int)"),
                                         self.glWidget.setZRotation)

        mainLayout = QtGui.QHBoxLayout()
        mainLayout.addWidget(self.glWidget)
        mainLayout.addWidget(self.xSlider)
        mainLayout.addWidget(self.ySlider)
        mainLayout.addWidget(self.zSlider)
        self.setLayout(mainLayout)

        self.xSlider.setValue(15 * 16)
        self.ySlider.setValue(345 * 16)
        self.zSlider.setValue(0 * 16)



        self.setWindowTitle(self.tr("Hello GL"))



    def createSlider(self, changedSignal, setterSlot):
        slider = QtGui.QSlider(QtCore.Qt.Vertical)

        slider.setRange(0, 360 * 16)
        slider.setSingleStep(16)
        slider.setPageStep(15 * 16)
        slider.setTickInterval(15 * 16)
        slider.setTickPosition(QtGui.QSlider.TicksRight)

        self.glWidget.connect(slider, QtCore.SIGNAL("valueChanged(int)"), setterSlot)
        self.connect(self.glWidget, changedSignal, slider, QtCore.SLOT("setValue(int)"))

        return slider


class GLWidget(QtOpenGL.QGLWidget):
    def __init__(self, parent=None):
        QtOpenGL.QGLWidget.__init__(self, parent)

        self.mPort = serial.Serial("/dev/ttyACM0",1000000)

        self.mTimer = QtCore.QTimer()
        self.connect(self.mTimer,QtCore.SIGNAL("timeout()"),self.onReceiveData)
        self.mTimer.start(25)

        self.object = 0
        self.xRot = 0
        self.yRot = 0
        self.zRot = 0

        self.lastPos = QtCore.QPoint()

        self.trolltechGreen = QtGui.QColor.fromCmykF(0.40, 0.0, 1.0, 0.0)
        self.trolltechPurple = QtGui.QColor.fromCmykF(0.39, 0.39, 0.0, 0.0)

    def onReceiveData(self):
        self.mPort.write('s')
        buff = self.mPort.read(2)

        data = map(ord,buff)

        angle = (data[0] << 8) + data[1]

        angle = ( angle / 4095.0 ) * 360.0

        self.setZRotation(angle*16)
        print "angle: " , angle

    def xRotation(self):
        return self.xRot

    def yRotation(self):
        return self.yRot

    def zRotation(self):
        return self.zRot

    def minimumSizeHint(self):
        return QtCore.QSize(50, 50)

    def sizeHint(self):
        return QtCore.QSize(400, 400)

    def setXRotation(self, angle):
        angle = self.normalizeAngle(angle)
        if angle != self.xRot:
            self.xRot = angle
            self.emit(QtCore.SIGNAL("xRotationChanged(int)"), angle)
            self.updateGL()

    def setYRotation(self, angle):
        angle = self.normalizeAngle(angle)
        if angle != self.yRot:
            self.yRot = angle
            self.emit(QtCore.SIGNAL("yRotationChanged(int)"), angle)
            self.updateGL()

    def setZRotation(self, angle):
        angle = self.normalizeAngle(angle)
        if angle != self.zRot:
            self.zRot = angle
            self.emit(QtCore.SIGNAL("zRotationChanged(int)"), angle)
            self.updateGL()

    def initializeGL(self):
        self.qglClearColor(self.trolltechPurple.darker())
        self.object = self.makeObject()
        GL.glShadeModel(GL.GL_FLAT)
        GL.glEnable(GL.GL_DEPTH_TEST)
        #GL.glEnable(GL.GL_CULL_FACE)

    def paintGL(self):

        GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT)
        GL.glLoadIdentity()
        GL.glTranslated(0.0, 0.0, -10.0)
        GL.glRotated(self.xRot / 16.0, 1.0, 0.0, 0.0)
        GL.glRotated(self.yRot / 16.0, 0.0, 1.0, 0.0)
        GL.glRotated(self.zRot / 16.0, 0.0, 0.0, 1.0)
        GL.glCallList(self.object)

    def resizeGL(self, width, height):
        side = min(width, height)
        GL.glViewport((width - side) / 2, (height - side) / 2, side, side)

        GL.glMatrixMode(GL.GL_PROJECTION)
        GL.glLoadIdentity()
        GL.glOrtho(-0.5, +0.5, +0.5, -0.5, 4.0, 15.0)
        GL.glMatrixMode(GL.GL_MODELVIEW)

    def mousePressEvent(self, event):
        self.lastPos = QtCore.QPoint(event.pos())

    def mouseMoveEvent(self, event):
        dx = event.x() - self.lastPos.x()
        dy = event.y() - self.lastPos.y()

        if event.buttons() & QtCore.Qt.LeftButton:
            self.setXRotation(self.xRot + 8 * dy)
            self.setYRotation(self.yRot + 8 * dx)
        elif event.buttons() & QtCore.Qt.RightButton:
            self.setXRotation(self.xRot + 8 * dy)
            self.setZRotation(self.zRot + 8 * dx)

        self.lastPos = QtCore.QPoint(event.pos())

    def makeObject(self):
        genList = GL.glGenLists(1)
        GL.glNewList(genList, GL.GL_COMPILE)

        GL.glBegin(GL.GL_QUADS)

        GL.glColor3f(0, 1, 0)
        #front
        GL.glVertex3d(-0.1, -0.1, 0.1)
        GL.glVertex3d( 0.1, -0.1, 0.1)
        GL.glVertex3d( 0.1,  0.1, 0.1)
        GL.glVertex3d(-0.1,  0.1, 0.1)
        # back
        GL.glVertex3d(-0.1, -0.1, -0.1)
        GL.glVertex3d( 0.1, -0.1, -0.1)
        GL.glVertex3d( 0.1,  0.1, -0.1)
        GL.glVertex3d(-0.1,  0.1, -0.1)
        # right
        GL.glColor3f(1, 0, 0)
        GL.glVertex3d(0.1, -0.1,  0.1)
        GL.glVertex3d(0.1, -0.1, -0.1)
        GL.glVertex3d(0.1,  0.1, -0.1)
        GL.glVertex3d(0.1,  0.1,  0.1)
        # left
        GL.glVertex3d(-0.1, -0.1,  0.1)
        GL.glVertex3d(-0.1, -0.1, -0.1)
        GL.glVertex3d(-0.1,  0.1, -0.1)
        GL.glVertex3d(-0.1,  0.1,  0.1)
        # top
        GL.glColor3f(0, 0, 1)
        GL.glVertex3d(-0.1, 0.1,  0.1)
        GL.glVertex3d( 0.1, 0.1,  0.1)
        GL.glVertex3d( 0.1, 0.1, -0.1)
        GL.glVertex3d(-0.1, 0.1, -0.1)
        # bottom
        GL.glVertex3d(-0.1, -0.1,  0.1)
        GL.glVertex3d( 0.1, -0.1,  0.1)
        GL.glVertex3d( 0.1, -0.1, -0.1)
        GL.glVertex3d(-0.1, -0.1, -0.1)

        GL.glEnd()
        GL.glEndList()

        return genList

    def normalizeAngle(self, angle):
        while angle < 0:
            angle += 360 * 16
        while angle > 360 * 16:
            angle -= 360 * 16
        return angle


if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv)
    window = Window()
    window.show()
    sys.exit(app.exec_())