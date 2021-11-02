import PIL
from PIL import Image
from math import ceil

ASCII_CHARS = ['@', '#', '$', 'S', '%', '?', '!', '=', '*', '+', ';', ':', '~', '-', ',', '.']
pixel_to_ascii_coef = 17

def resize_image (image, new_width=100):
    width, height = image.size
    ratio = height / (width * 2.7)

    new_height = int (new_width * ratio)
    resized_image = image.resize ((new_width, new_height))
    return resized_image

def grayify (image):
    grayscale_image = image.convert("L")
    return grayscale_image

def pixels_to_ascii (image):
    pixels = image.getdata()
    characters = "".join (ASCII_CHARS[pixel // pixel_to_ascii_coef] for pixel in pixels)
    return characters

def get_asm_code(filename, img_array_data, new_width, new_height):
    img_array_data = list(map (lambda x: ord(x), img_array_data))

    with open(filename, 'w') as file:
        file.write(f"vrsetx {new_width}\n")
        file.write(f"vrsety {new_height}\n")
        file.write(f"vrsetstart 0\n")
    
        for index, byte in enumerate(img_array_data):
            file.write(f"push {byte}\n")
            file.write(f"pop [{index}]\n")
        
        file.write("scrupd\n")
        file.write("hlt\n")

    
def main():
    path = input("Enter path to image ")
    out_path = path.split('.')[0] + '.asm'

    new_width = int (input("Enter new width "))
    image = Image.open(path)
    
    resized_image = resize_image(image, new_width=new_width)
    new_width, new_height = resized_image.size

    new_image_data = pixels_to_ascii(grayify(resized_image))
    
    get_asm_code (out_path, new_image_data, new_width, new_height)

if __name__ == "__main__":
    main()