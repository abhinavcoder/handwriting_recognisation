# handwriting_recognisation
# cursive segmentation done using opencv in c++
#Using Tkinter GUI in Python and processing code in C++ .
1. Install tesseract , PIL and OpenCV in Ubuntu
2. > python tkinter_image.py
3. Draw the image 
4. Click "Save" to save the image and coordinates ::
   a. Image saved as "temp.jpg" 
   b. Coordinates saved in "letter_sampleNew.txt"
5. Compile the code in openCV ::
     a. g++ -o segOpenCV  segOpenCV.cpp `pkg-config opencv --cflags --libs`
     b. ./segOpenCV
6. Go to location where it is cloned then type :: tesseract ImageFinal.jpg out -l eng -psm 6
7. Open "out.txt" to get the desired result
8. Click "Clear" to remove everything and redraw

# change the -psm number in the .py file according to necessity (line 72)
