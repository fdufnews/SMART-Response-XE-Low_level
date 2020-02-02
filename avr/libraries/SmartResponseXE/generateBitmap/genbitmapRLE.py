#!/usr/bin/python2

# Generate a bitmap for the SMART Response XE
# RLE variant
from array import array
import argparse

#list defining the 4 colors for any of the 3 pixels
# The color list is inverted comparing to the one in the SMART Response library
# that's because "min" and "max" has a different meaning in the two applications
color = [0xFF, 0x92, 0x49, 0x00]
#list defining the mask to access the 3 pixels
mask = [0xE0, 0x1C, 0x03]

#define a parser for the command line
parser = argparse.ArgumentParser(description='process a raw bitmap')
parser.add_argument('filein', help='bitmap file in raw format to convert')
parser.add_argument('fileout', help='.h file')
parser.add_argument('width',type=int, nargs=1, help='width of bitmap')
parser.add_argument('height',type=int, nargs=1, help='height of bitmap')
parser.add_argument('--version', action='version', version='%(prog)s 1.0')

#parse the command line
result = parser.parse_args()
dict = vars(result)
width = dict['width'][0]
height = dict['height'][0]
infilename= dict['filein']
outfilename= dict['fileout']

fileout = open(outfilename,'w')
# let's write a header with the name of the image source
fileout.write('// Original file {}\n\n#include <avr/pgmspace.h>\n\n'.format(infilename))
# name the bitmap with the name of the output file
name = outfilename.split('.')
fileout.write('const uint8_t bitmap_{0}[{1}/3*{2}+4+1] PROGMEM ='.format(name[0], width, height))
fileout.write('{\n\t')

#put size of the picture as a header of the bitmap
fileout.write('0x{0:02x}, 0x{1:02x}, // image width={2}\n\t'.format(width & 0xff, width>>8 & 0xFF, width))
fileout.write('0x{0:02x}, 0x{1:02x}, // image height={2}\n\t'.format(height & 0xff, height>>8 & 0xFF, height))

with open( infilename, 'rb' ) as filein:
	data = array( 'B', filein.read() ) # buffer the file

# count of byte processed
count = 0
# count byte written
countw = 0

first = 1 # Flag telling that we have just started
countRLE = 0 # count number of same bytes
prev_char = 4 # hold value of current running length (4 is an impossible value in the context)

# bytearray used to hold 3 pixels at a time
ba = bytearray()
for byte in data:
	ba.insert(0,byte) # push the pixel in the array
	count = count + 1
	if(count%3==0):  # every 3 pixels concatenate them into one byte
		pix = color[ba.pop()] & mask[0] | color[ba.pop()] & mask[1] | color[ba.pop()] & mask[2]
		if pix != prev_char:
			if countRLE!=0: # if we are not starting encoding write the previous running length
				fileout.write('0X{0:02X},0x{1:02x},'.format(countRLE, prev_char)) # write the byte to the file in ascii hex
				if(countw%8==7):
					fileout.write('\n\t')  # every 16 bytes written newline
				countw +=1
			countRLE = 1 # restart RLE count
			prev_char = pix # new pix we are counting
			first = 0
		else:
			countRLE +=1
			if countRLE==254: # if running length is to roll over write value and reset count
				fileout.write('0X{0:02X},0x{1:02x},'.format(countRLE, prev_char)) # write the byte to the file in ascii hex
				if(countw%8==7):
					fileout.write('\n\t')  # every 16 bytes written newline
				countw +=1
				countRLE = 0
		
		
fileout.write('0X{0:02X},0x{1:02x},'.format(countRLE, prev_char))
fileout.write('0X00,0x00\n};')
fileout.close()

