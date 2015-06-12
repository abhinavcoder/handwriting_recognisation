# handwriting_recognisation using Tkinter GUI in Python and processing code in C++ .
# Cursive and Non-cursive done

# Inorder to recognise the single character change the "mode" variable in "tkinter_image.py" to 10 ::
1. Install tesseract , PIL and OpenCV in Ubuntu
2. To run GUI :
   > python tkinter_image.py
GUI :
    i .  Draw the image 
    ii.  Click "Save" to save the image and coordinates ::
          a. Image saved as "Image.jpg" 
          b. Coordinates saved in "letter_sampleNew.txt"
   iii.  Click "Clear" to clear the image (Optional)
3. To refactor the coordinates :
   > g++ letter_factor.cpp 
   > ./a.out
4. GUI :: to show and save the factored image
   i . Click "Factor"
   ii. Click "Draw $ Save"
5. To run the OpenCV- segmentation code 
   > g++ -o segOpenCV  segOpenCV.cpp `pkg-config opencv --cflags --libs`
   > ./segOpenCV
The final segmented image is saved as "ImageFinal,jpg"
6. GUI :: to show the tesseract out 
   i . Click "tesseract-ocr" for recognisation
7. Open Output terminal to get the recognised word 
              or
   Open file "tess_output.txt" to get the recognised word 
8. Click "Clear" to remove everything and redraw

# change the mode variable in the "tkinter_image.py" file according to necessity (line 28)
