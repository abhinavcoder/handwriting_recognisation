import cv2.cv as cv
import tesseract

'''
pagesegmode values are:
0 = Orientation and script detection (OSD) only.
1 = Automatic page segmentation with OSD.
2 = Automatic page segmentation, but no OSD, or OCR
3 = Fully automatic page segmentation, but no OSD. (Default)
4 = Assume a single column of text of variable sizes.
5 = Assume a single uniform block of vertically aligned text.
6 = Assume a single uniform block of text.
7 = Treat the image as a single text line.
8 = Treat the image as a single word.
9 = Treat the image as a single word in a circle.
10 = Treat the image as a single character.
-l lang and/or -psm pagesegmode must occur before anyconfigfile.

'''
api = tesseract.TessBaseAPI()
api.Init(".","eng",tesseract.OEM_DEFAULT)
api.SetPageSegMode(10)    
image=cv.LoadImage("image.jpg", cv.CV_LOAD_IMAGE_GRAYSCALE)
tesseract.SetCvImage(image,api)
text=api.GetUTF8Text()
conf=api.MeanTextConf()
file = open("tess_output.txt", "w")
file.write('%s' % text)
file.close();
