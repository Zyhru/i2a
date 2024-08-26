#pragma once

#include <iostream>
#include <fstream>
#include <format>
#include <vector>
#include <cstdint>

class Image {
public:
	Image(std::string file, int w) : file_name(file), user_width(w) {
		if(!loadImage()) {
			throw std::runtime_error("failed to load image: " + file_name);
		}

	};
	
	~Image();

	bool loadImage();
	void processImage();

private:
	// original image info
	std::string file_name;
	int width;
	int height;
	int channels;
	uint8_t* data;

	char* output;
	std::string format;
	int default_channels;
	int user_width;
	int user_height;

	void imageInfo();
	void imageResize();
	void printImage();
	float rgbToGrayScale(uint8_t r, uint8_t g, uint8_t b);

};
