#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image_resize.h"

Image::~Image() { 
  stbi_image_free(data); 
  delete[] output;
}

bool Image::loadImage() {
  default_channels = STBI_rgb;
  data = stbi_load(file_name.c_str(), &width, &height, &channels, default_channels);
  if (!data) {
    return false;
  }

  // setting the format
  if (channels == 3) {
    format = "rgb";
  } else if (channels == 4) {
    format = "rgba";
  } else if (channels == 1) {
    format = "grayscale";
  }

  imageInfo();
  return true;
}

void Image::imageInfo() {
  std::string img_info = std::format("Image Information\n"
                                     "------------------\n"
                                     "-File Name: {}\n"
				     "-Width: {}\n"
                                     "-Height: {}\n"
                                     "-Format: {}",
                                     file_name, width, height, format);

  std::cout << img_info << std::endl;
}

void Image::imageResize() {
	user_height = height / (width / user_width);
	if(!stbir_resize_uint8(
	data, width, height, width * default_channels, 
	data, user_width, user_height, user_width * default_channels, default_channels)) {
	        std::cerr << "Failed to resize image: " << file_name << std::endl;
		return;
	}
}

void Image::processImage() {
	imageResize();

        int wh = user_width * user_height;
	std::string ascii_table = "@#S%?*+;:,. ";
	const float scale = 255.0f / static_cast<float>(ascii_table.length());
	output = new char[wh];

	int index = 0;
	for (int i = 0; i < wh; ++i) {
		uint8_t r = data[i * 3];
		uint8_t g = data[i * 3 + 1];
		uint8_t b = data[i * 3 + 2];

		// convert rgb to greyscale
		float intensity = rgbToGrayScale(r, g, b);
		output[index] = ascii_table[intensity / scale];
		
		// print a new line once index reaches width input
		if((i+1) % user_width == 0) {
			output[++index] = '\n';
		}
		++index;
	}
	
	output[index] = '\0';
	printImage();
	
}

void Image::printImage() {
  printf("%s", output);

}

float Image::rgbToGrayScale(uint8_t r, uint8_t g, uint8_t b) {
	return 0.21f * r + 0.72f * g + 0.007f * b; // luminosity grayscale algorithm
}
