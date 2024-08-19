#include <iostream>
#include <vector>
#include <jpeglib.h>
#include <jerror.h>


// reference: https://github.com/LuaDist/libjpeg/blob/master/example.c
extern "C" void process_image(const unsigned char* image_data, size_t data_size) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    jpeg_mem_src(&cinfo, image_data, data_size);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int channels = cinfo.output_components;

    // The code below gets rid of the "Application transferred too few scanlines" error

    // Skip all scanlines
    jpeg_skip_scanlines(&cinfo, height);

    // Process scanlines (if we do not want to skip them)
    // int row_stride = cinfo.output_width * cinfo.output_components;
    // JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    // while (cinfo.output_scanline < cinfo.output_height) {
    //     (void) jpeg_read_scanlines(&cinfo, buffer, 1);
    //     // Do something with the scanlines here
    // }

    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Channels: " << channels << std::endl;

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
}
