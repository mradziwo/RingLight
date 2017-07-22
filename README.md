# RingLight

## Supported comands
  
###     COMMAND_ERROR = 0x00
###    COMMAND_ECHO = 0x01
replies with data
###    COMMAND_READ_SIGNATURE = 0x02
not implemented
###    COMMAND_DEMO = 0x03
ignores data - launches demo. device is not responsive during demo
###    COMMAND_WHITE_LEVEL = 0x04
sets white fight of brightness from 0 to 255
data[1] = brighntess
###    COMMAND_COLOR_LEVEL = 0x05
data[1] = hue
data[2] = intensity

hue is wrapped from classic 0-360  to 0-255 values
intensity is 0-255

## Links
### arduhdlc
https://github.com/jarkko-hautakorpi/arduhdlc-qt-gui-example/blob/master/Arduino_sketch/Arduino_sketch.ino

When HDLC frame is being built around user data (say, "ABCD"), user defined function is called for each byte of the frame. For "ABCD" 8 bytes are sent out, frame being "~ABCD??~" where the two characters before end flag ~ are two non printable bytes/characters from 16bit CRC function. CRC for "ABCD" is 53965, or 0xCD and 0xD2 in Hexadecimal representation.

HDLC frame containing "ABCD":

		packet	"~ABCDÍÒ~"	char
			[0]	126 '~'	char
			[1]	65 'A'	char
			[2]	66 'B'	char
			[3]	67 'C'	char
			[4]	68 'D'	char
			[5]	205 / 205	char
			[6]	210 / 210	char
			[7]	126 '~'	char
      
      
### NeoPixel
https://github.com/adafruit/Adafruit_NeoPixel

##Arduino
Remove reset on DTR!
https://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection
