
import cv2.cv as cv
import tesseract
from Tkinter import *
import Tkinter as tk
import Image,ImageDraw

'''
1. Run C++ code from python 
2. Save the image drawn using create_line
3. More better segmetnation 
'''
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
mode = 6
xold, yold = None, None
file1 = open("letter_sampleNew.txt", "w")
file1.close()
points = []
pointsFactor = [] 

class ImageGenerator:
    def __init__(self,parent,posx,posy,*kwargs):
        self.parent = parent
        self.posx = posx
        self.posy = posy
        self.sizex = 650
        self.sizey = 500
        self.b1 = "up"
        self.xold = None
        self.yold = None 
        self.drawing_area=tk.Canvas(self.parent,width=self.sizex,height=self.sizey)
        self.drawing_area.place(x=self.posx,y=self.posy)
        self.drawing_area.bind("<Motion>", self.motion)
        self.drawing_area.bind("<ButtonPress-1>", self.b1down)
        self.drawing_area.bind("<ButtonRelease-1>", self.b1up)
        self.button=tk.Button(self.parent,text="Save",width=10,bg='white',command=self.save)
        self.button.place(x=self.sizex/10,y=self.sizey+20)
        self.button1=tk.Button(self.parent,text="Clear",width=10,bg='white',command=self.clear)
        self.button1.place(x=(self.sizex/10)+200,y=self.sizey+20)
        self.button1=tk.Button(self.parent,text="Tesseract-OCR",width=10,bg='white',command=self.ocr)
        self.button1.place(x=(self.sizex/10)+400,y=self.sizey+20)
        self.button1=tk.Button(self.parent,text="Factor",width=10,bg='white',command=self.factor)
        self.button1.place(x=(self.sizex/10),y=self.sizey+70)
        self.button1=tk.Button(self.parent,text="Draw $ Save",width=10,bg='white',command=self.draw_save)
        self.button1.place(x=(self.sizex/10)+200,y=self.sizey+70)

        self.image=Image.new("RGB",(650,500),(255,255,255))
        self.draw=ImageDraw.Draw(self.image)

    def save(self):
        filename = "Image.jpg"
        self.image.save(filename)


    def clear(self):
        file1= open("letter_sampleNew.txt", "w")
        file1.close()
        self.drawing_area.delete("all")
        self.image=Image.new("RGB",(650,500),(255,255,255))
        self.draw=ImageDraw.Draw(self.image)

    def ocr(self):
        api = tesseract.TessBaseAPI()
        api.Init(".","eng",tesseract.OEM_DEFAULT)
        #setup the page segment number ... choose from the list at top ..
        api.SetPageSegMode(mode)    #set the -psm number ..
        image=cv.LoadImage("ImageFinal.jpg", cv.CV_LOAD_IMAGE_GRAYSCALE)
        tesseract.SetCvImage(image,api)
        text=api.GetUTF8Text()
        conf=api.MeanTextConf()
        file = open("tess_output.txt", "w")
        file.write('%s' % text)
        file.close()
        print(text)
       
    def factor(self):
        file = open("letter_factor.txt", "r")
        for line in file:
          for word in line.split():
             pointsFactor.append(word)

    def draw_save(self):
        self.drawing_area.delete("all")
        self.image=Image.new("RGB",(650,500),(255,255,255))
        self.draw=ImageDraw.Draw(self.image)        
        self.drawing_area.create_line(pointsFactor,smooth = 'true' , width=2 ,tags="theline")
        filename = "ImageFactor.jpg"
        self.image.save(filename) #the file being saved is the blank file 
    
    def b1down(self,event):
        self.b1 = "down"

    def b1up(self,event):
        self.b1 = "up"
        self.xold = None
        self.yold = None

    def motion(self,event):
        if self.b1 == "down":
            if self.xold is not None and self.yold is not None:
                event.widget.create_line(self.xold,self.yold,event.x,event.y,smooth='true',width=2,fill='black')
                file1 = open("letter_sampleNew.txt", "a")
                file1.write('%d' % event.x)
                file1.write(" ")
                file1.write('%d' %event.y)
                file1.write("\n")
                file1.close()
                points.append(event.x)
                points.append(event.y)
                self.draw.line(((self.xold,self.yold),(event.x,event.y)),(0,0,0),width=2)

        self.xold = event.x
        self.yold = event.y

if __name__ == "__main__":
    root=tk.Tk()
    root.wm_geometry("%dx%d+%d+%d" % (700, 700, 10, 10))
    root.config(bg='white')
    ImageGenerator(root,10,10)
    root.mainloop()