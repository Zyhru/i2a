#include "image.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "fmt: ./ascii <image_path>";
    return -1;
  }

  char *file_name = argv[1];
  Image image(file_name);
  image.processImage();

  return 0;
}
