
#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"
#include "src/conv_lib.h"


MatrixXf block_matching( MatrixXf A,  MatrixXf V)
{
  //make functor

  int P = V.cols() > V.rows() ? V.cols()/2 : V.rows()/2;

  MatrixXf B = MatrixXf::Zero(A.rows()+(2*P),A.cols()+(2*P));

  B.block(P, P, A.rows(), A.cols()) = A;
  return MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B,&V] (Index i,Index j) {
        return (V.array() * B.block (i,j, V.rows(),V.cols()).array()).sum();
        });
}

MatrixXf pad1 (MatrixXf input, int pad) {

int rl=input.rows(),cl=input.cols();

MatrixXf B(rl+pad,cl+pad);
B.block(pad/2,pad/2,rl,cl) = input;
cout<<input.row(0).replicate(2,1)<<endl;
//row and column fill
B.block(0,pad/2,pad/2,cl) = input.row(0).replicate(pad/2,1);
B.block(rl+pad/2,pad/2,pad/2,cl) = input.row(rl-1).replicate(pad/2,1);
B.block(pad/2,0,rl,pad/2) = input.col(0).replicate(1,pad/2);
B.block(pad/2,cl+pad/2,rl,pad/2) = input.col(cl-1).replicate(1,pad/2);
// corner squares
B.block(0,0,pad/2,pad/2) = MatrixXf::Constant(pad/2, pad/2, input.coeff(0,0));
B.block(0,cl+pad/2,pad/2,pad/2) = MatrixXf::Constant(pad/2, pad/2, input.coeff(0,cl-1));
B.block(rl+pad/2,0,pad/2,pad/2) = MatrixXf::Constant(pad/2, pad/2, input.coeff(rl-1,0));
B.block(rl+pad/2,cl+pad/2,pad/2,pad/2) = MatrixXf::Constant(pad/2, pad/2, input.coeff(rl-1,cl-1));;

return B;
}

struct pad {
  Index size() const { return m_out_size; }
  Index operator[] (Index i) const { return std::max<Index>(0,i);}//(m_out_size-m_in_size)); }
  Index m_in_size, m_out_size;
};

int main()
{
   MatrixXf A(3,4);
  A.reshaped() = VectorXf::LinSpaced(12,1,12);
  cout << A << "\n\n";
  int N = 5;
  MatrixXf B= pad1(A,4);
  // B = A(pad{2,5}, pad{2,5});
  cout << B << "\n\n";
//  RowVectorXf kernel = GaussianFilter(2.0,3);
//   VectorXf kernelY = kernel.transpose();
  // Image x, y;
  // const char* file_ppm1 = "../data/tsu1.pgm";
  // x.ReadFromDisk(file_ppm1);
  // const char* file_ppm2 = "../data/tsu2.pgm";
  // y.ReadFromDisk(file_ppm2);

  // cout << x.image_data.topLeftCorner(5, 5) << endl << endl;
  // cout << x.image_data.topLeftCorner(5, 5) << endl << endl;
  // x.WriteToDisk("test.jpg");
}
