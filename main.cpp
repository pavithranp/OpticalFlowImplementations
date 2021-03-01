// Copyright [2020] <Pavithran Pandiyan>
#include <Eigen/Dense>
#include <iostream>
#include <math.h>
#include "block_matching/block_matching.h"
#include <chrono> 
#include "HornSchunck/HornSchunck.h"
#include "util/Image.h"
using namespace std::chrono;

using namespace Eigen;
using namespace std;

int main() {
  // VectorXf kernelY= kernel.transpose();
  Image x, y, z;

  const char* file_ppm1 = "../data/yos2.pgm";
  const char* file_ppm2 = "../data/yos1.pgm";

  x.ReadFromDisk(file_ppm1);
  y.ReadFromDisk(file_ppm2);
  // RowVectorXf v = RowVectorXf::LinSpaced(20, 0, 19);
  // cout << "Input:" << endl << v << endl;
  // Map<RowVectorXf, 0, InnerStride<2> > v2(v.data(), v.size());
  // cout << "Even:" << v2 << endl;

  // y.ReadFromDisk(file_ppm2);
  int block_size = 5;
  // MatrixXf m;
  int s = 1;
  // z = BlockMatching(x, y, s, block_size);

  auto start = high_resolution_clock::now();
  HornSchunck hs(s);
  z = hs(x, y);
  // BlockMatching bm(7, 3);
  // z = bm(x, y);
  auto stop = high_resolution_clock::now();

  z.Write3ToDisk("test.jpg");

  auto duration = duration_cast<milliseconds>(stop - start);

  cout << "Time taken by function: "
    << duration.count() << " milliseconds" << endl;

  // y.Write3ToDisk("test.jpg");
  // cout << "done";
}

