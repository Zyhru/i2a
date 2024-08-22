#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../include/stb_image_resize.h"

Image::~Image() { stbi_image_free(data); }

bool Image::loadImage() {
  _desired_channels = STBI_rgb;
  data = stbi_load(_file_name.c_str(), &_width, &_height, &_nrChannels, _desired_channels);
  if (!data) {
    return false;
  }

  // set format
  if (_nrChannels == 3) {
    _format = "rgb";
  } else if (_nrChannels == 4) {
    _format = "rgba";
  } else if (_nrChannels == 1) {
    _format = "grayscale";
  } else {
    std::cerr << "invalid format!" << std::endl;
    return false;
  }

  //imageInfo();
  return true;
}

void Image::imageInfo() {
  #if 0
  std::string img_info = std::format("Image Information\n\n"
                                     "------------------\n\n"
                                     "-File Name: {}\n\n"
                                     "-Width: {}\n\n"
                                     "-Height: {}\n\n"
                                     "-Format: {}",
                                     _file_name, _width, _height, _format);

  std::cout << img_info << std::endl;
  #endif
}

void Image::processImage() {
	std::cout << "Number of channels: " << _nrChannels << std::endl;
	int new_width = 80;
	int new_height = _height / (_width / new_width);
	if(!stbir_resize_uint8(data, _width, _height, _width * _desired_channels, 
			       data, new_width, new_height, new_width * _desired_channels, 
			      _desired_channels)) {

	        std::cerr << "Failed to resize image: " << _file_name << std::endl;
		return;
	}

        int wh = new_width * new_height;
	std::string ascii = "@#S%?*+;:,. ";
	const float mapping = 255.0f / static_cast<float>(ascii.length());
	char* pixels = new char[wh];
	int ptr = 0;
	for (int i = 0; i < wh; ++i) {
		uint8_t r = data[i * 3];
		uint8_t g = data[i * 3 + 1];
		uint8_t b = data[i * 3 + 2];

		// convert rgb to greyscale
		float intensity = rgbToGrayScale(r, g, b);
		pixels[ptr] = ascii[intensity / mapping];
		

		// for each row, print out a new line and continue
		if((i+1) % new_width == 0) {
			pixels[++ptr] = '\n';
		}
		++ptr;
	}

	pixels[ptr] = '\0';
	printf("%s", pixels);
	delete[] pixels;
}

float Image::rgbToGrayScale(uint8_t r, uint8_t g, uint8_t b) {
	return 0.21f * r + 0.72f * g + 0.007f * b;
}
