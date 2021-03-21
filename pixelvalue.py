import os
from PIL import Image

a = str(input("Images Dir -> ")) + "\\"
b = a + "pixelvalues\\"
x = int(input("num images (n(inclusive)) -> "))


if not os.path.exists(b):
    os.makedirs(b)

for i in range(0, x + 1):
    img = Image.open(a + str(i) + ".png").convert('L')
    img.save(a + str(i) + ".png")

for i in range(0, x + 1):
    im = Image.open(a + str(i) + '.png')
    height, width = im.size
    data = []

    for ecs in range(im.width):
        for why in range(im.height):
            data.append(str(im.getpixel((ecs, why))))

    #WRITING DATA TO TEXT FILE
    try:
        f = open(b + str(i) + ".txt", 'x') #Create new file if a file does not exist
        f.close()
    except: #If file exists
        pass
    
    f = open(b + str(i) + ".txt", 'w')
    f.write(",".join(data)) #Write data
    f.close() #Close 'f' for next loop