"""Library file for rover Hardware.

Created by Bill Crawford <bill.crawford@forthvalley.ac.uk>

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
    """Docstring."""

    def __init__(self):
        """Init."""
        self._boardInfo = {}
        self.overclocked = False
        self._piInfo()

    def type(self):
        """Type of board."""
        rev = []
        for key, value in self._boardInfo.items():
            if key == 'revision':
                rev = value
            if rev[0:2] == '100':
                self.overclocked = True
        return

    def _readFile(self, filePath):
        """Docstring."""
        try:
            infoFile = open(filePath, 'r')
            infoLines = infoFile.readlines().strip()
            infoFile.close()
        except Exception as e:
            # TODO log error
            return None
        return infoLines

    def _piInfo(self):
        """Docstring."""
        infolines = self._readFile('/proc/device-tree/model')
        if infolines:
            self.model = infolines.strip()
        infolines = self._readFile('/proc/cpuinfo')
        if infolines:
            for infoline in infolines:
                if infoline.find(':') > 0:
                    delimiter = infoline.find(':')
                    key = infoline[0:delimiter-1].strip().lower()
                    value = infoline[delimiter+1:].strip().lower()
                    self._boardInfo[key] = value
        if self.model is None:
            # TODO extract the board model
            pass
        return


class PortExpander:
    """Port Expander."""
    def __init__(self, address,
                 dataDirectionsA=0, dataDirectionsB=0
                 ):
        self.address = address
        self.dataDirectionsA = dataDirectionsA
        self.dataDirectionsB = dataDirectionsB


class StepperMotor:
    """26DBMXXD1U-L Stepper Motor Control.

    The 26DBMXXD1U-L is a 5 volt unipolar stepper motor with
    48 steps per revolution (7.5 degrees per step).

    TODO - Disuss mechanism with Mech Eng.
    """

    def __init__(self):
        """Stepper Motor Initialisation."""
        self.model = '26DBMXXD1U-L'
        self.mode = 'unipolar'
        # Sequence based on wiring of pins in the order
        # yellow, orange, brown, black
        # red and green assumed to be connected to 5v
        self.sequence = [[1, 0, 1, 0],
                         [1, 0, 0, 1],
                         [0, 1, 0, 1],
                         [0, 1, 1, 0]]
