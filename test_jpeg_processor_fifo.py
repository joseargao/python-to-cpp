#!/usr/bin/env python3
import os

def write_jpeg_to_fifo(jpeg_path, fifo_path):
    # Open the jpeg and FIFO, then write the jpeg data into the FIFO
    with open(jpeg_path, 'rb') as jpeg_file:
        with open(fifo_path, 'wb') as fifo:
            while chunk := jpeg_file.read(1024):
                fifo.write(chunk)
            fifo.flush()

if __name__ == "__main__":
    jpeg_path = 'test.jpeg'
    fifo_path = 'jpeg_fifo'

    if not os.path.exists(fifo_path):
        print(f"Error: FIFO {fifo_path} does not exist.")
    else:
        write_jpeg_to_fifo(jpeg_path, fifo_path)
