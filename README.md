# braille-draw
converts images into braille ascii art

Made in Visual Studio 2017.
All native functions, excluding Opencv (x64).
Input images, for simplicity's sake, should be placed in the same directory as the source code file.
You can tweak the sensitivity of the binarization of the image into exclusively black/white pixels.
The output files are formatted in UTF-16.

TODO:

Add support for compressing more pixels into single character cells. This will likely look awful, but it would be nice
to add nonetheless - this would require repeating the arduous task of mapping ~250 binary inputs to Unicode outputs.
