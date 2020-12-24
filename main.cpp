
#include <Eigen/Dense>
#include <iostream>
#include "lib/Image.h"

int main() {
  Image x(10, 10);
  const char* file_ppm = "../data/tsu1.pgm";
  x.ReadFromDisk(file_ppm);
  std::cout << x.image_data;
  // Matrix3d m = Matrix3d::Random();
  // m = (m + Matrix3d::Constant(1.2)) * 50;
  // cout << "m =" << endl << m << endl;
  // Vector3d v(1, 2, 3);

  // cout << "m * v =" << endl << m * v << endl;
}
