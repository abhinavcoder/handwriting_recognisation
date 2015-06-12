
from Tkinter import *
import Image, ImageDraw

"""paint.py: not exactly a paint program.. just a smooth line drawing demo."""

b1 = "up"
xold, yold = None, None
file = open("letter_sample.txt", "w")
file.close()
points = []
def main():
    root = Tk()
    drawing_area = Canvas(root)
    drawing_area.pack()
    drawing_area.bind("<Motion>", motion)
    drawing_area.bind("<ButtonPress-1>", b1down)
    drawing_area.bind("<ButtonRelease-1>", b1up)
    drawing_area.bind("<Button-3>",reset)
    width = 400
    height = 300
    center = height//2
    white = (255, 255, 255)
    green = (0,128,0)
    cv = Canvas(root, width=width, height=height, bg='white')
    cv.pack()
    root.mainloop()



def b1down(event):
    global b1
    b1 = "down"           # you only want to draw when the button is down
                          # because "Motion" events happen -all the time-

def b1up(event):
    global b1, xold, yold
    b1 = "up"
    xold = None           # reset the line when you let go of the button
    yold = None

def reset(event):
    file = open("letter_sample.txt", "w")
    file.close()
    event.widget.delete("all")
    #drawing_area.create_line(points, tags="theline")
     # = open("letter_sample.txt", "w")


def motion(event):
    if b1 == "down":
        global xold, yold
        if xold is not None and yold is not None:
            event.widget.create_line(xold,yold,event.x,event.y,smooth=TRUE)
            file = open("letter_sample.txt", "a")
            file.write('%d' % event.x)
            file.write(" ")
            file.write('%d' %event.y)
            file.write("\n")
            file.close()
            points.append(event.x)
            points.append(event.y)
   
            #print event.x 
                          # here's where you draw it. smooth. neat.
        xold = event.x
        yold = event.y
    

if __name__ == "__main__":
    main()