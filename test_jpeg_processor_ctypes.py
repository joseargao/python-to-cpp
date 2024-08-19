#!/usr/bin/env python3
import ctypes
import time

# Load the shared library
lib = ctypes.CDLL('./libjpeg_processor.so')

# Function prototype for process_image
lib.process_image.argtypes = (ctypes.POINTER(ctypes.c_ubyte), ctypes.c_size_t)
lib.process_image.restype = None

# Load a file into a byte array
def read_file_to_bytes(file_path):
    with open(file_path, 'rb') as file:
        return file.read()

# Load the JPEG file into memory
image_data = read_file_to_bytes('test.jpeg')

# Convert image data to a ctypes array
image_data_ctypes = (ctypes.c_ubyte * len(image_data)).from_buffer_copy(image_data)

start_time = time.time()

# Call the process_image function from the shared library
lib.process_image(image_data_ctypes, len(image_data))

end_time = time.time()
elapsed_time = end_time - start_time
print(f"Time taken: {elapsed_time:.4f} seconds")
