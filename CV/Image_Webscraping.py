import os
import time
import requests
from selenium import webdriver
from selenium.webdriver.safari.service import Service
from selenium.webdriver.common.by import By

# Setup Safari WebDriver
service = Service('/usr/bin/safaridriver')  # Path to SafariDriver
driver = webdriver.Safari(service=service)

# Create a directory to save images
os.makedirs('trash_images', exist_ok=True)

# List of trash-related search terms
trash_terms = ['trash', 'garbage']

def scroll_down(driver):
    """Scrolls down the page to load more images."""
    last_height = driver.execute_script("return document.body.scrollHeight")
    while True:
        driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
        time.sleep(2)  # Wait for new images to load
        new_height = driver.execute_script("return document.body.scrollHeight")
        if new_height == last_height:
            break
        last_height = new_height

# Loop through each trash term
for term in trash_terms:
    # Open Google Images for each trash term
    driver.get(f'https://www.google.com/search?hl=en&tbm=isch&q={term}')
    
    # Scroll down to load more images
    scroll_down(driver)
    
    # Find image elements
    images = driver.find_elements(By.TAG_NAME, "img")
    image_count = 0
    max_images = 500

    # Loop through images and download them
    for img in images:
        if image_count >= max_images:
            break

        try:
            img_url = img.get_attribute('srcset') or img.get_attribute('src')
            print(f'Image URL: {img_url}')  # Debugging line

            if img_url and 'http' in img_url:  # Ensure the URL is valid
                img_data = requests.get(img_url).content
                img_name = os.path.join('trash_images', f'{term.replace(" ", "_")}_{image_count}.jpg')
                with open(img_name, 'wb') as handler:
                    handler.write(img_data)
                    print(f'Downloaded {img_name}')
                    image_count += 1
        except Exception as e:
            print(f'Error downloading image: {e}')

# Clean up
driver.quit()
print('Image download complete.')
