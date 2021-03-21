#SCALES IMAGES
import PIL
from PIL import Image

sizex = int(input("X size -> "))
sizey = int(input("Y size -> "))

location = str(input("Folder dir -> "))
number = int(input("Number of files (0, n(inclusive)) -> "))

size = (sizex, sizey)
for i in range(0, number + 1):
    image = Image.open(location + "\\" + str(i) + ".png")
    image = image.resize(size, Image.BILINEAR)
    image = image.save(location + "\\" + str(i) + ".png")