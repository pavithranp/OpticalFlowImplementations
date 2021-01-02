
#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"
#include "src/conv_lib.h"




int main()
{
 RowVectorXf kernel = GaussianFilter(2.0,3);
  VectorXf kernelY= kernel.transpose();
  Image x;
  const char* file_ppm = "../data/tsu1.pgm";
  x.ReadFromDisk(file_ppm);
  cout << x.image_data.topLeftCorner(5,5)<<endl<<endl;
  x.image_data = Conv1D(x.image_data,kernel);
  x.image_data = Conv1D(x.image_data,kernelY);
  cout << x.image_data.topLeftCorner(5,5)<<endl<<endl;
  x.WriteToDisk("test.jpg");
}
