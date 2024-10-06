import os

# Path to your positive images directory
positive_images_dir = '/Users/pparakala/Personal/Projects/Trac/CV/trash_images'  # Replace with your actual path
output_file = 'negatives.txt'

# Open the output file in write mode
with open(output_file, 'w') as f:
    for filename in os.listdir(positive_images_dir):
        if filename.endswith(('.jpg', '.jpeg', '.png')):  # Add more extensions if needed
            image_path = os.path.join(positive_images_dir, filename)
            width, height = 24, 24  # Set the desired dimensions
            f.write(f"{image_path} 1 {width} {height}\n")  # Write the line in the required format

print(f'Positive samples written to {output_file}')
