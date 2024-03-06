from PyQt6 import QtWidgets, uic
from PyQt6.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt6.QtCore import QIODevice, QIODeviceBase

app = QtWidgets.QApplication([])
ui = uic.loadUi("workDeck.ui")
ui.setWindowTitle("workDeck")

serial = QSerialPort()
serial.setBaudRate(115200)
portList = []
ports = QSerialPortInfo().availablePorts()
for port in ports:
    portList.append(port.portName())

ui.comL.addItems(portList)

def onOpen():
    serial.setPortName(ui.comL.currentText())
    serial.open(QIODeviceBase.OpenModeFlag.ReadWrite)

def onClose():
    serial.close()

def serialSend(data):
    txs = ""
    for val in data:
        txs += str(val)
        txs += ','
    txs = txs[:-1]
    txs += ';'
    serial.write(txs.encode())
def onRead():
    rx = serial.readLine()
    rxs = str(rx,'utf-8').strip()
    data = rxs.split(',')
    print(data)
    match data[0]:
         case "1":
            openPage(data[1])
         case "2":
            onCheck(data[1])
         case "3":
            ui.dialLED.setValue(int(data[1]))
            ui.labelModeInt.setText(str(data[1]))
         case "4":
            ui.sliderBRT.setValue(int(data[1]))
            ui.labelBRTInt.setText(str(data[1]))

def onCheck(tmp):
    match tmp:
        case "1":
            ui.checkL.setChecked(True)
        case "0":
            ui.checkL.setChecked(False)

def onCheckPC():
    serialSend([2])

def onTurnPC():
    serialSend([3,ui.dialLED.value()])
    ui.labelModeInt.setText(str(ui.dialLED.value()))

def onTurnPCH():
    serialSend([4,ui.sliderBRT.value()])
    ui.labelBRTInt.setText(str(ui.sliderBRT.value()))

def openPage(tmp):
    match tmp:
        case "1":
            print("Youtube")
            serialSend([1,1])
        case "2":
            print("Wikipedia")
            serialSend([1, 2])
        case "3":
            print("Arduino")
            serialSend([1, 3])

ui.openB.clicked.connect(onOpen)
ui.closeB.clicked.connect(onClose)
serial.readyRead.connect(onRead)
ui.checkL.clicked.connect(onCheckPC)
ui.dialLED.sliderReleased.connect(onTurnPC)
ui.sliderBRT.sliderReleased.connect(onTurnPCH)
ui.btn1.clicked.connect(lambda: openPage("1"))
ui.btn2.clicked.connect(lambda: openPage("2"))
ui.btn3.clicked.connect(lambda: openPage("3"))

ui.show()
app.exec()