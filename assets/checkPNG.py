from PIL import Image
im = Image.open("1.png")
print(im.mode)  # 'RGB' or 'RGBA' or 'P'
print(list(im.getdata())[:10])

