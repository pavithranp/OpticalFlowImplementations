
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include "block_matching/block_matching.h"
#include "util/Image.h"


using namespace Eigen;
using namespace std;

int main() {
  // VectorXf kernelY= kernel.transpose();
  Image x, y;

  const char* file_ppm1 = "../data/tsu1.pgm";
  // const char* file_ppm2 = "../data/tsu2.pgm";
  x.ReadFromDisk(file_ppm1);
  // RowVectorXf v = RowVectorXf::LinSpaced(20, 0, 19);
  // cout << "Input:" << endl << v << endl;
  // Map<RowVectorXf, 0, InnerStride<2> > v2(v.data(), v.size());
  // cout << "Even:" << v2 << endl;
  x.Write3ToDisk("test.jpg");
  // y.ReadFromDisk(file_ppm2);
  // int block_size = 3;
  // MatrixXf m;
  // int s = 2 + 1;
  // BlockMatching(x, y, s, block_size);
  cout << "done";
}
