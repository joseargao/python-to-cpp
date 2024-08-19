CXX = g++
CXXFLAGS = -std=c++17 -Wall
LIBS = -L. -ljpeg_processor -ljpeg

# Source and Object files
LIB_SRC = jpeg_processor.cpp
LIB_OBJ = jpeg_processor.o
TEST_SRC = test_jpeg_processor.cpp
TEST_OBJ = test_jpeg_processor.o
FIFO_READER_SRC = test_jpeg_processor_fifo.cpp
FIFO_READER_OBJ = test_jpeg_processor_fifo.o
CLI_SRC = jpeg_processor_cli.cpp
CLI_OBJ = jpeg_processor_cli.o

# FIFO path
FIFO_PATH = ./jpeg_fifo

# Targets
all: lib

# Build the shared library
lib: $(LIB_SRC)
	$(CXX) $(CXXFLAGS) -shared -fPIC $(LIB_SRC) -o libjpeg_processor.so -ljpeg

# Build and run the test program
test: $(TEST_SRC) lib
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o test_jpeg_processor $(LIBS)
	./test_jpeg_processor

# Build the command line tool
cli: $(CLI_SRC) lib
	$(CXX) $(CXXFLAGS) $(CLI_SRC) -o jpeg_processor_cli $(LIBS)

# Create or recreate the FIFO
fifo_create:
	@if [ -e $(FIFO_PATH) ]; then rm -f $(FIFO_PATH); fi
	mkfifo $(FIFO_PATH)

# Build and run the FIFO reader program
fifo: fifo_create lib
	$(CXX) $(CXXFLAGS) $(FIFO_READER_SRC) -o test_jpeg_processor_fifo -L. -ljpeg_processor -ljpeg
	./test_jpeg_processor_fifo &

# Clean up build artifacts and FIFO
clean:
	rm -f *.o *.so test_jpeg_processor test_jpeg_processor_fifo jpeg_processor_cli
	rm -f /tmp/jpeg_fifo

# Run the Python script to transfer jpeg data via ctypes
python_ctypes: lib
	python3 test_jpeg_processor_ctypes.py

# Run the Python script to write to FIFO
python_fifo:
	python3 test_jpeg_processor_fifo.py

# Run the Python script that invokes the command line tool
python_cli: cli
	python3 test_jpeg_processor_cli.py
