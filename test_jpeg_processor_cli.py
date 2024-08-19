#!/usr/bin/env python3
import subprocess

jpeg_file_path = 'test.jpeg'

# Command to invoke the tool with the JPEG file path
command = ['./jpeg_processor_cli', jpeg_file_path]

# Run the command
subprocess.run(command)
