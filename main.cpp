
#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"
#include "math.h"
using namespace Eigen;
using namespace std;


MatrixXf Conv( MatrixXf A,  RowVectorXf V)
{
  //make functor
  int P = V.cols()/2;

  MatrixXf B = MatrixXf::Zero(A.rows(),A.cols()+(2*P));
  B.block (0,P,A.rows(),A.cols())=A;
  return MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B,&V] (Index i,Index j) {
        return (V.array() * B.block (i,j, V.rows(),V.cols()).array()).sum();
        });
}
RowVectorXf GaussianFilter(float sigma, int kernel_size){

//assert odd kernel size
RowVectorXf kernel = 
          RowVectorXf::LinSpaced(kernel_size,-(kernel_size-1)/2,(kernel_size-1)/2);

kernel = (1/(sigma*sqrt(2.0*3.14)))*
            exp(pow(kernel.array(),2)/(-2.0*sigma*sigma));

kernel = kernel/kernel.sum();

return kernel;

}

int main()
{
 RowVectorXf kernel = GaussianFilter(2,3);

  Image x;
  const char* file_ppm = "../data/tsu1.pgm";
  x.ReadFromDisk(file_ppm);
  cout << x.image_data.topLeftCorner(5,5)<<endl<<endl;
  x.image_data = Conv(x.image_data,kernel);
  cout << x.image_data.topLeftCorner(5,5)<<endl<<endl;
  x.WriteToDisk("test.pgm");
}
