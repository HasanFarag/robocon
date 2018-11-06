# Arduino Weather Station CSV Data Logging
import csv
import serial
from serial import SerialException
from msvcrt import kbhit, getch
from time import sleep
import tkinter as tk
import tkinter.messagebox
from PIL import Image, ImageTk

# ______________________________________Classes_________________________________________ #
class dataLog():

    # The populateFile method opens the .csv file specified by the file_name and appends information from the arduino.
    def populateFile(self, directory, file_name):
        with open(directory + file_name, 'a', newline='') as csv_file:
            sensorData = self.takeReading()
            csv_writer = csv.writer(csv_file)
            csv_writer.writerow([sensorData[0], sensorData[1], sensorData[2], sensorData[3], sensorData[4]])
            sleep(2)

    def takeReading(self, ser):
        data = str(ser.readline(), 'utf-8').strip('\r \n')
        sensorData = data.split()
        return sensorData

class WeatherGUI(tk.Tk, dataLog):
    # This is the controller class

    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.create_widgets()
        self.title("Weather Logging Software")
        self.resizable(0,0)
        tkinter.messagebox.showinfo("Welcome", "Welcome to the Weather Station Data Software this software allows you to"
                                               " monitor "
                                               "the readings from the arduino weather station and save them to a csv file")
    def create_widgets(self):
        self.container = tk.Frame(self)
        self.container.pack(side="top", fill="both", expand=True)
        self.container.grid(row=0, column = 0, sticky = tk.W + tk.E)


        self.frames = {}

        for F in (CommandPage, DisplayPage):
            frame = F(self.container, self)
            frame.grid(column = 0, row = 0, sticky=tk.NW+tk.SE)
            self.frames[F] = frame

        self.show_frame(CommandPage)

    def show_frame(self, cls, COM = 0, Directory = 0, fileName = 0):
        if cls == DisplayPage:
            while True:
                try:
                    ser = serial.Serial('COM' + COM, 9600)  # Establish the connection on a specific port
                    self.frames[cls].generateLabels(ser)
                    self.frames[cls].tkraise()
                    break
                except SerialException:
                    tkinter.messagebox.showinfo("Error", "Unable to connect to weather station. Please check the COM Port and try again")
                    break
        else:
            self.frames[cls].tkraise()

    def fileSetUp(self, directory, file_name):
        with open(directory + file_name, 'a') as csv_file:
            csv_writer = csv.writer(csv_file)
            csv_writer.writerow(["Weather Station Project"])
            csv_writer.writerow(["Day", "Hour", "Temperature", "Pressure", "Humidity", "\n"])
            sleep(2)

class BaseFrame(tk.Frame):
    # This is the template master class to allow for the easy creation of new frames to stack in the main container
    def __init__(self, master, controller):
        tk.Frame.__init__(self, master)
        self.container = master
        self.controller = controller
        self.create_widgets()

    def create_widgets(self):
        raise NotImplementedError


class CommandPage(BaseFrame):

    def create_widgets(self):
        comLabel = tk.Label(self, text = "Please Enter COM Port:")
        comLabel.grid(row = 0, column = 0)

        self.entryCOM = tk.Entry(self, bd=2)
        self.entryCOM.grid(row=1, column=0)

        directLabel = tk.Label(self, text = "Please copy & paste the directory you wish to save any data to")
        directLabel.grid(row = 2, column= 0)

        self.entryDirect = tk.Entry(self, bd=2)
        self.entryDirect.grid(row = 3, column = 0)

        fileLabel = tk.Label(self, text = "Please name the file you wish to create.")
        fileLabel.grid(row = 4, column = 0)

        self.entryFile = tk.Entry(self, bd=2)
        self.entryFile.grid(row = 5, column = 0)

        navigationButton = tk.Button(self, pady = 5,padx = 5, text = "Use COM Port", command = lambda: self.readEntries(), anchor = tk.W)
        navigationButton.grid(row = 6, column = 0, padx= 5, pady= 5, sticky = tk.E + tk.W)

    def readEntries(self):
        COM = self.entryCOM.get()
        Directory = self.entryDirect.get()
        fileName = self.entryFile.get()
        self.controller.show_frame(DisplayPage, COM, Directory, fileName)

class DisplayPage(BaseFrame, dataLog):

    def create_widgets(self):
        #Images
        self.tempImg = tk.PhotoImage(file="Temperature.png")
        tempImage = tk.Label(self, image=self.tempImg)
        tempImage.grid(row=0, column = 0)

        self.pressureImg = tk.PhotoImage(file="Pressure1.png")
        pressureImage = tk.Label(self, image=self.pressureImg)
        pressureImage.grid(row=0, column=1)

        self.humidityImg = tk.PhotoImage(file = "Humidity1.png")
        humidityImage = tk.Label(self, image = self.humidityImg)
        humidityImage.grid(row = 0, column = 2)

        navigationButton = tk.Button(self, text="Log Data", command=lambda: self.fileSetUp("C://Users/arran/OneDrive/Documents/Weather Station Data/", "test.csv"),
                                     padx=5, pady=5, anchor=tk.W)
        navigationButton.grid(row=2, column=0, padx=5, pady=5, sticky=tk.E + tk.W)

    def generateLabels(self, ser):
        # Station Readings
        sensorData = self.takeReading(ser)

        self.tempLabel = tk.Label(self, text=sensorData[2] + " Degrees")
        self.tempLabel.grid(row=1, column=0)

        self.pressLabel = tk.Label(self, text=sensorData[3] + " Pa")
        self.pressLabel.grid(row=1, column=1)

        self.humidityLabel = tk.Label(self, text=sensorData[4] + " %")
        self.humidityLabel.grid(row=1, column=2)


# _________________________Functions____________________________#
# This is a test.

def kbdScan(Command):
    if kbhit():
        unichr = ord(getch())
        if unichr != 0xe0:
            asciichr = chr(unichr).lower()
        if asciichr == ' ':
            Command = "STOP"
    else:
        Command = "RUN"
    return Command


# _____________________Program Introduction_______________________________#

GUI = WeatherGUI()
GUI.mainloop()

# ________________________Main Program___________________________________#

# Each time the program a command is entered and the process finishes the program returns to this point to request
# another Command from the user.
get_sample = False
screen = False
first_run = True
main = True
logger = dataLog()

'''
while main:
    directory = input(
        "Please copy and paste the directory you wish to save the files to here: ")
    Command = input("Type commands here all in upper-case (Type HELP for a list of commands): ")
    while Command == "RUN":
        Command = kbdScan(Command)
        if Command == "STOP":
            first_run = True
            break
        if first_run:
            New_Old = input("Would you like to create a new file? ")
            if New_Old == "YES":
                # defFile is the name of the file the user would like to create
                defFile = input("Enter the file name that you would like to use: ")
                # File_name is the UserDef variable combined with .csv
                file_name = defFile + ".csv"
                first_run = False
                logger.fileSetUp(directory, file_name)
                print("Press Space at any time to stop the sample.")
            elif New_Old == "NO":
                file_name = input("Please type the file name exactly followed by .csv: ")
                logger.populateFile(directory, file_name)
                print("Press Space at any time to stop the sample")
            else:
                print("Invalid command please answer YES or NO: ")
        if not first_run:
            logger.populateFile(directory, file_name)
        # Prints list of the commands available
    if Command == "READ":
        sensorData = logger.takeReading()
        print("Temperature       Pressure         Humidity")
        print(sensorData)
    if Command == "HELP":
        print(
            "RUN Starts the program, or continues it if it has been paused. READ takes an instant reading. EXIT exits "
            "the program.")
        # Pauses the program
    if Command == "EXIT":
        main = False

print("Program Exiting...")
sleep(5)
'''