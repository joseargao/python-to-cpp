#include <iostream>
#include <vector>
#include <fstream>

extern "C" void process_image(const unsigned char* image_data, size_t data_size);

std::vector<unsigned char> read_file_to_vector(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return {};
    }

    return std::vector<unsigned char>(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
}

int main() {
    const char* filename = "test.jpeg";

    // Load the JPEG image into memory
    std::vector<unsigned char> image_data = read_file_to_vector(filename);
    if (image_data.empty()) {
        std::cerr << "Failed to load JPEG image." << std::endl;
        return 1;
    }

    // Process the image
    process_image(image_data.data(), image_data.size());

    std::cout << "Test Complete";

    return 0;
}
