#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // for std::transform

namespace fs = std::filesystem;

// Function to process images
void create_samples(const std::string& pos_folder, const std::string& output_vec_file) {
    std::vector<std::string> image_paths;

    // List all image files in the directory
    for (const auto& entry : fs::directory_iterator(pos_folder)) {
        std::cout << "Checking: " << entry.path() << std::endl; // Print each path being checked
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // Convert to lowercase
            std::cout << "Found file: " << entry.path() << " with extension: " << ext << std::endl; // Check the extension
            if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".heic") {
                image_paths.push_back(entry.path().string());
            }
        }
    }

    // Print current working directory
    std::cout << "Current working directory: " << fs::current_path() << std::endl;

    // Open the output vector file
    std::ofstream vec_file(output_vec_file);
    if (!vec_file.is_open()) {
        std::cerr << "Error: Could not open output vector file!" << std::endl;
        return;
    }

    // Process images and write to vector file
    for (const auto& img_path : image_paths) {
        std::cout << "Writing to vec: " << img_path << std::endl; // Debug output
        vec_file << img_path << std::endl; // Write each image path to the vector file
    }

    vec_file.close();
    std::cout << "Samples processed into " << output_vec_file << std::endl;
}

int main() {
    create_samples("dataset/Amulya", "positives.vec");
    return 0;
}
