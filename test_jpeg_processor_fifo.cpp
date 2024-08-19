#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

extern "C" void process_image(const unsigned char* image_data, size_t data_size);

int main() {
    const char* fifo_path = "jpeg_fifo";
    bool timing_started = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    int fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Failed to open FIFO" << std::endl;
        return 1;
    }

    // Read the jpeg data from the FIFO
    std::vector<unsigned char> buffer;
    const size_t chunk_size = 4096;
    unsigned char chunk[chunk_size];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, chunk, chunk_size)) > 0) {
        if (!timing_started) {
            // Start timing after the first successful read
            start = std::chrono::high_resolution_clock::now();
            timing_started = true;
        }
        buffer.insert(buffer.end(), chunk, chunk + bytes_read);
    }
    close(fd);

    if (bytes_read == -1) {
        std::cerr << "Error reading from FIFO" << std::endl;
        return 1;
    }

    // Process the image
    process_image(buffer.data(), buffer.size());

    // End timing
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;

    std::cout << "Time taken (read): " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
