
#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"

int main() {
  Image x;
  const char* file_ppm = "../data/tsu1.pgm";
  x.ReadFromDisk(file_ppm);
  x.WriteToDisk("test.jpg");
}
