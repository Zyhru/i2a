#include "image.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "usage: ./ascii <image_path> <width>";
    return -1;
  }

  char *file_name = argv[1];
  int width = std::atoi(argv[2]);

  Image image(file_name, width);
  image.processImage();

  return 0;
}
