#pragma once

#include <iostream>
#include <fstream>
//#include <format>
#include <vector>
#include <cstdint>


class Image {
public:
	Image(std::string filename) : _file_name(filename) {
		if(!loadImage()) {
			//std::cerr << std::format("failed to load image {}", filename);
			return;
		}
	};
	
	~Image();


	bool loadImage();
	void processImage();

private:
	std::string _file_name;
	std::string _format;
	int _width;
	int _height;
	int _nrChannels;
	int _desired_channels;
	unsigned char *data;

	void imageInfo();
	float rgbToGrayScale(uint8_t r, uint8_t g, uint8_t b);
	
};
