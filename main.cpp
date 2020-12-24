
#include <Eigen/Dense>
#include <iostream>
#include "lib/Image.h"

int main() {
  Image x(10, 10);
  const char* file_ppm = "../data/tsu1.pgm";
  x.ReadFromDisk(file_ppm);
  // Eigen::MatrixXf f =  x.image_data.cast <float> ();
  std::cout << x.image_data;
  x.WriteToDisk("trest.jpg");
}
