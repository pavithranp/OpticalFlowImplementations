
#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"

using namespace Eigen;
using namespace std;


MatrixXi Conv( MatrixXi A,  RowVectorXi V)
{
  int P = V.cols()/2;

  MatrixXi B = MatrixXi::Zero(5,6+(2*P));
  B.block (0,P,A.rows(),A.cols())=A;
  return MatrixXi::NullaryExpr(A.rows(), A.cols(), [&B,&V] (Index i,Index j) {
        return (V.array() * B.block (i,j, V.rows(),V.cols()).array()).sum();
        });
}

int main()
{
  
MatrixXi A(5,6);
RowVectorXi V(3);
V << -1, 2, -1;
  A.reshaped() = VectorXi::LinSpaced(30,1,30);
  cout << A << "\n\n";
  cout << V << "\n\n";
  

  MatrixXi C = Conv(A,V);
  cout << C << "\n\n";

//-----------------------
  // Image x;
  // const char* file_ppm = "../data/tsu1.pgm";
  // x.ReadFromDisk(file_ppm);
  // x.WriteToDisk("test.jpg");
}
