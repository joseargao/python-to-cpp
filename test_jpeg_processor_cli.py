#!/usr/bin/env python3
import subprocess
import time

jpeg_file_path = 'test.jpeg'

# Command to invoke the tool with the JPEG file path
command = ['./jpeg_processor_cli', jpeg_file_path]

start_time = time.time()

# Run the command
subprocess.run(command)

end_time = time.time()
elapsed_time = end_time - start_time
print(f"Time taken: {elapsed_time:.4f} seconds")
