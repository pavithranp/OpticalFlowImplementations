
#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"

using namespace Eigen;
using namespace std;


template<class ArgType>
class circulant_functor {
  const ArgType &m_mat;
  const ArgType &m_vec;
public:
  circulant_functor(const ArgType& arg1, const ArgType& arg2 ) : m_vec(arg1) ,m_mat(arg2) {}
 
  const typename ArgType::Scalar& operator() (Index row, Index col) const {
    Index index = row - col;
    if (index < 0) index += m_vec.size();
    return m_vec(index);
  }
};


template <class ArgType>
MatrixXd
makeCirculant(const Eigen::MatrixBase<ArgType>& arg,const Eigen::MatrixBase<ArgType>& arg1)
{
  return MatrixXd::NullaryExpr(arg.size(), arg.size(), circulant_functor<ArgType>(arg.derived()));
}

int main()
{
  Eigen::VectorXd vec(4);
  vec << 1, 2, 4, 8;
  Eigen::MatrixXd mat;
  mat = makeCirculant(vec,mat);
  std::cout << mat << std::endl;
//-----------------------------------------
// Matrix3i A;
// RowVectorXi V(3);
// V << -1, 2, -1;
//   A.reshaped() = VectorXi::LinSpaced(9,1,9);
//   cout << A << "\n\n";
//   cout << V << "\n\n";
//   int P = 1;
//   const int S =3;
//   MatrixXi B = MatrixXi::Zero(S,S+(2*P));
//   B.block<S,S>(0,P)=A;

//   MatrixXi C = MatrixXi::NullaryExpr(S, S, [&B,&V,S] (Index i,Index j) {
//         return (V.array() * B.block<1,3>(i,j).array()).sum();
      
//         });
//   cout << C << "\n\n";

//-----------------------
  // Image x;
  // const char* file_ppm = "../data/tsu1.pgm";
  // x.ReadFromDisk(file_ppm);
  // x.WriteToDisk("test.jpg");
}
