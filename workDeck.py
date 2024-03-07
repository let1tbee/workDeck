from PyQt6 import QtWidgets, uic
from PyQt6.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt6.QtCore import QIODevice, QIODeviceBase
from selenium import webdriver
from selenium.webdriver.chrome.service import Service as ChromeService
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from webdriver_manager.chrome import ChromeDriverManager

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

def openYT():
    driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()))
    chrome_options = Options()
    chrome_options.add_experimental_option("detach", True)
    driver = webdriver.Chrome(options=chrome_options)
    driver.maximize_window()
    driver.get("https://www.youtube.com/")
    driver.find_element(By.NAME, "search_query").send_keys("never gonna give you up")
    driver.find_element(By.ID, "search-icon-legacy").click()

def openWK():
    driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()))
    chrome_options = Options()
    chrome_options.add_experimental_option("detach", True)
    driver = webdriver.Chrome(options=chrome_options)
    driver.maximize_window()
    driver.get("https://uk.wikipedia.org/wiki/%D0%93%D0%BE%D0%BB%D0%BE%D0%B2%D0%BD%D0%B0_%D1%81%D1%82%D0%BE%D1%80%D1%96%D0%BD%D0%BA%D0%B0")
    driver.find_element(By.XPATH, "// input[ @ id = 'searchInput']").send_keys("Arduino")
    driver.find_element(By.XPATH,"// input[ @ id = 'searchButton']").click()

def openAr():
    driver = webdriver.Chrome(service=ChromeService(ChromeDriverManager().install()))
    chrome_options = Options()
    chrome_options.add_experimental_option("detach", True)
    driver = webdriver.Chrome(options=chrome_options)
    driver.maximize_window()
    driver.get("https://doc.arduino.ua/")

def openPage(tmp):
    match tmp:
        case "1":
            serialSend([1, 1])
            openYT()
        case "2":
            serialSend([1, 2])
            openWK()
        case "3":
            serialSend([1, 3])
            openAr()

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