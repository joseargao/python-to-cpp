#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <jpeglib.h>
#include <jerror.h>

extern "C" void process_image(const unsigned char* image_data, size_t data_size);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_jpeg_file>" << std::endl;
        return 1;
    }

    // Get the file path
    std::string file_path = argv[1];

    // Read the contents of the JPEG into a vector
    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return 1;
    }
    std::vector<unsigned char> image_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Check if the file is empty
    if (image_data.empty()) {
        std::cerr << "Error: File " << file_path << " is empty or could not be read." << std::endl;
        return 1;
    }

    // Process the image
    process_image(image_data.data(), image_data.size());

    return 0;
}
