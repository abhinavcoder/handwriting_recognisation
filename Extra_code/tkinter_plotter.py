
from Tkinter import *

"""paint.py: not exactly a paint program.. just a smooth line drawing demo."""

points = []
root = Tk()
drawing_area = Canvas(root)
drawing_area.pack()

def main():
    drawing_area.bind("<Button-1>", update)
    drawing_area.bind("<Button-3>",reset)
    root.mainloop()



def reset(event):
    print "reset"
    drawing_area.create_line(points, tags="theline")
     # = open("letter_sample.txt", "w")

def update(event):
      print "updating"
      file = open("letter_segment.txt", "r")
      for line in file:
          for word in line.split():
             points.append(word)


    

if __name__ == "__main__":
    main()