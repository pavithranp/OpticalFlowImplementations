
#include <Eigen/Dense>
#include <iostream>
#include "lib/Image.h"

int main() {
  Image x;
  const char* file_ppm = "../data/tsu1.pgm1";
  x.ReadFromDisk(file_ppm);
  x.WriteToDisk("test.jpg");
}
