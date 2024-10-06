import cv2
import os

# Set your directories
POSITIVE_IMAGES_DIR = '/Users/pparakala/Personal/Projects/Trac/CV/battery_images'
NEGATIVE_IMAGES_DIR = '/Users/pparakala/Personal/Projects/Trac/CV/trash_images'
VEC_FILE = 'positives.vec'
WIDTH = 24  # Width of samples
HEIGHT = 24  # Height of samples

# Collect positive images and create samples
positive_samples = []
for img_name in os.listdir(POSITIVE_IMAGES_DIR):
    img_path = os.path.join(POSITIVE_IMAGES_DIR, img_name)
    positive_samples.append(img_path)

# Create vector file
os.system(f"opencv_createsamples -info positives.txt -num {len(positive_samples)} -w {WIDTH} -h {HEIGHT} -vec {VEC_FILE}")
