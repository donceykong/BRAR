'''
@Author: Doncey Albin

Convinience Function for converting jpg to bmp
'''
from PIL import Image

def convert_jpg_to_bmp(input_path, output_path):
    try:
        # Open the image
        img = Image.open(input_path)

        # Convert the image to RGB mode if it's not already
        if img.mode != "RGB":
            img = img.convert("RGB")

        # Display some info about the image
        print(f"Image format: {img.format}")
        print(f"Image mode: {img.mode}")
        print(f"Image size: {img.size}")

        # Save the image in BMP format
        img.save(output_path, "BMP")

    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage:
convert_jpg_to_bmp("wooden_crate.jpg", "wooden_crate.bmp")
