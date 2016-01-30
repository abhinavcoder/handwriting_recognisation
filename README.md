# Handwriting_recognisation

#### Description :

- Handwriting recognition for Cursive and Non-cursive using Tesseract-OCR .
- Image Processing techniques(method of histograms) for cursive segmentation .
- Spline curves for smooth data points interpolation.
- Simulator made from Tkinter GUI in Python .
- Processing and OpenCV code in C++ which is executed through Python wrapper

#### User Manual : 
1. Install tesseract , PIL and OpenCV in Ubuntu (follow SETUP_LINKS.docx)
2. To run GUI :
   > python tkinter_image.py
    i .  Draw the image 
    ii.  Click "Save" to save the image and coordinates ::
          a. Image saved as "Image.jpg" 
          b. Coordinates saved in "letter_sampleNew.txt"
    iii.  Click "Clear" to clear the image (Optional)
3. To refactor the coordinates and display it :
   i. Click "Factor $ Save"
          a. Factored coordinates saved in "letter_factor.txt"

4. // To be run only for cursive writing 
   To run the OpenCV- segmentation code 
   i. Click "Segment_OpenCV" 

The final segmented image is saved as "ImageFinal.jpg"

6. To show the recognisation using Tesseract 
   i.  Click "Cursive" for recognisation of cursive word(after step4)
   ii. Click "Character" for recognisation of single charact(ignore4)
   iii. For non-cursive word :
       a. In new terminal goto required directory :
          > tesseract Image.jpg out -l eng -psm 6
       b. Open "out.txt" , ignore step 7 
  
7. Open Output terminal to get the recognised word 
              or
   Open file "tess_output.txt" to get the recognised word 

8. Click "Clear" to remove everything and redraw

#### Simulator :

![Simulator](https://raw.githubusercontent.com/abhinavcoder/handwriting_recognisation/master/README_PICS/Tkinter.png)

Segmented word from OpenCV :

![Image](https://raw.githubusercontent.com/abhinavcoder/handwriting_recognisation/master/README_PICS/segmented.png)
