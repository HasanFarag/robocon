"""Functions to help interface with harware
Processor       : ARMv6-compatible processor rev 7 (v6l)
BogoMIPS        : 847.05
Features        : swp half thumb fastmult vfp edsp java tls
CPU implementer : 0x41
CPU architecture: 7
CPU variant     : 0x0
CPU part        : 0xb76
CPU revision    : 7
Hardware        : BCM2708
Revision        : 0002
Serial          : 000000000abc0ab1

GPIO 0 and GPIO 1 are reserved for SD card - DO NOT CONNECT.

Stepper motor requires 4 GPIO pins

For the Utrasonic sensors we will connect to a MCP23017A Port
Expander. This uses I2C to communicate with the Raspberry Pi.

Laser rangefinder for target distance uses I2C or PWM input
(could use an interrupt pin for this).

Main drive motors each require 2 GPIO for forward reverse
and 2 PWM speed signals also 2 or 1 GPIO for inhibits.
Wheel Speed sensors 2 GPIO

Possibly need a motor for cannon charge system. 1 GPIO or PWM

GPIO Count

"""
class Board:

    def __init__(self):
        self._boardInfo = {}
        self.overclocked = False
        self._piInfo()

    def type():
        """
        """
        if 'revision' in self._boardInfo:
            rev = self._boardInfo['revision']
            if rev[0:2] = '100':
                self.overclocked = True

    def _readFile(self, filePath):
        try:
            infoFile = open(filePath,'r')
            infoLines = infoFile.readlines().strip()
            infoFile.close()
        except Exception as e:
            #TODO log error
            return None
        return infoLines

    def _piInfo(self):
        infolines = self._readFile('/proc/device-tree/model')
        if infolines:
            self.model = infolines.strip()
        infolines = self._readFile('/proc/cpuinfo')
        if infolines:
            for infoline in infolines:
                if infoLine.find(:) > 0:
                    delimiter = infoLine.find(:)
                    key = infoLine[0:delimiter-1].strip().lower()
                    value = infoLine[delimiter+1:].strip().lower()
                    self._boardInfo[key] = value
        if not self.model:
            #TODO extract the board model
            pass
        return

class StepperMotor:
    """26DBMXXD1U-L Stepper Motor Control
    The 26DBMXXD1U-L is a 5 volt unipolar stepper motor with
    48 steps per revolution (7.5 degrees per step).
    """
    def __init__(self):
        self.model = '26DBMXXD1U-L'
        self.mode = 'unipolar'
        #Sequence based on wiring of pins in the order
        #yellow, orange, brown, black
        #red and green assumed to be connected to 5v
        self.sequence = [[1,0,0,1],
                         [1,0,0,0],
                         [1,1,0,0],
                         [0,1,0,0],
                         [0,1,1,0],
                         [0,0,1,0],
                         [0,0,1,1],
                         [0,0,0,1]]
