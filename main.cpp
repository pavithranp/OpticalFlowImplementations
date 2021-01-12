// Copyright [2020] <Pavithran Pandiyan>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include "block_matching/block_matching.h"
#include "util/Image.h"


using namespace Eigen;
using namespace std;

int main() {
  // VectorXf kernelY= kernel.transpose();
  Image x, y, z;

  const char* file_ppm1 = "../data/yos1.pgm";
  const char* file_ppm2 = "../data/yos2.pgm";
  x.ReadFromDisk(file_ppm1);
  y.ReadFromDisk(file_ppm2);
  // RowVectorXf v = RowVectorXf::LinSpaced(20, 0, 19);
  // cout << "Input:" << endl << v << endl;
  // Map<RowVectorXf, 0, InnerStride<2> > v2(v.data(), v.size());
  // cout << "Even:" << v2 << endl;

  // y.ReadFromDisk(file_ppm2);
  int block_size = 3;
  // MatrixXf m;
  int s = 7 + 1;
  z = BlockMatching(x, y, s, block_size);
  z.Write3ToDisk("test.jpg");
  // y.Write3ToDisk("test.jpg");
  // cout << "done";
}
