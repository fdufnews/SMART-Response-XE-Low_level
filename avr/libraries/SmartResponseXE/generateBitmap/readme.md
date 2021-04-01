Bitmap generator
---------------
A Python application that generates a .h file from a raw bitmap.

Syntaxe:
genbitmapRLE.py --help
usage: genbitmapRLE.py [-h] filein fileout width height

process a raw bitmap

positional arguments:
  filein      bitmap file in raw format to convert
  fileout     .h file
  width       width of bitmap
  height      height of bitmap

optional arguments:
  -h, --help  show this help message and exit

As the display in the terminal is modifying 3 points at a time the width of the image at the input shall be a multiple of 3.
As a convenient way to manage images of any size by the final application, the image and information on its size are stored in the data.
The image data are compacted and ordered as expected by the display they are then RLE compressed.
The only task of the software is reading the size of the image, initializing the transfert, decoding and sending the data.

The source image is made using GIMP
1. Picture is converted to indexed palette mode with 4 colors.
2. Picture is exported in RAW format (.data extension). The export generate 2 files one .data and one .data.pal. The second is of no use it can be discarded.
3. Using the script the .data file is converted to a .h file that can be included in the software.
