#include <Eigen/Dense>
#include <iostream>
#include "src/Image.h"
// #include "src/block_matching.h"
#include "math.h"
using namespace Eigen;
using namespace std;

struct Distance
{
     int x;
     int y;
};
Distance search( MatrixXf A,  MatrixXf V)
{
  //make functor

  int Py = V.cols()/2 , Px = V.rows()/2;

  MatrixXf B = MatrixXf::Zero(A.rows()+(2*Px),A.cols()+(2*Py));
  B.block (Px,Py,A.rows(),A.cols())=A;
  // cout<<B<<endl<<endl;
  MatrixXf C =  MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B,&V] (Index i,Index j) {
                return pow((V.array() - B.block(i,j, V.rows(),V.cols()).array()),2).sum();
        });
  Distance D;
  cout << "cost :" <<C.minCoeff(&D.x, &D.y)<<endl;
  return D;
  
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
 Matrix3f m;
  m << 9, 14, 20,
     11, 18, 20,
    10, 16, 17;
  // VectorXf kernelY= kernel.transpose();
  Image x;
  
  const char* file_ppm = "../data/tsu1.pgm";
  x.ReadFromDisk(file_ppm);
  MatrixXf K = x.image_data.block(50,50,10,10);
  MatrixXf B = x.image_data.block(52,53,12,12);
  // BlockMatching(A,B,3,3);
    cout<< K<<endl<<endl;
    cout<< B<<endl<<endl;
    
  for(int i=0;i<10;i++)
  for(int j=0;j<10;j++){
      m= B.block(i,j,3,3);
      cout<<m;
      cout<<i<<" :"<<j;
      // int i=0,j=9;
      int s=3+1;

      int xmax = min(i+s,9);
      int ymax = min(j+s,9);

      int xmin = max(0,i-s);
      int ymin = max(0,j-s);
      // cout << xmax << endl << ymax << endl << xmin << endl << ymin << endl;
      // cout << K.block(xmin,ymin,xmax-xmin+1,ymax-ymin) << endl;
    Distance D = search(K.block(xmin,ymin,xmax-xmin+1,ymax-ymin+1),m);
 cout<< D.x << " " <<D.y<<endl<<endl;

  }
        // cout<< D.x << " " <<D.y<<endl<<endl;

}