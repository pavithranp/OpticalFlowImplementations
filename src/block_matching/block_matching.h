// Copyright [2020] <Pavithran Pandiyan>
#include<algorithm>
#include"util/Image.h"
//#include "util/color_lib.h"
#include "../OpticalFlow.h"
using namespace Eigen;
using namespace std;

// Algorithm
  // check size of matrix are same
  // loop through each pixel on image 1
    // loop through search window size on 2nd image
        // locate blocks around two imgs
        // calculate cost of two blocks (sub square sum)
    // find distance with minimum cost


class BlockMatching : public OpticalFlowMethod {
public:
  BlockMatching(int s, int block_size) : s(s), block_size(block_size) {};
  Image operator()(Image img1, Image img2);
  void SearchSpace(const MatrixXf A, const MatrixXf V, int& x, int& y);

private:
  int block_size;
  int s;

};

Image BlockMatching::operator()(Image img1, Image img2) {
  y.R = MatrixXf(img1.get_rows(), img1.get_cols());
  y.G = MatrixXf(img1.get_rows(), img1.get_cols());
  y.B = MatrixXf(img1.get_rows(), img1.get_cols());

  img2.add_padding(block_size - 1, block_size - 1);
  MatrixXf m;
  int _x, _y;
  int xmax, ymax, xmin, ymin, R = 0, G = 0, B = 0;

  // for every pixel find the closest block
  for (int i = 0; i < img1.get_rows(); i++)
    for (int j = 0; j < img1.get_cols(); j++) {
      m = img2.image_data.block(i, j, block_size, block_size);

      // set boundaries for search 
      xmax = min(i + s, img1.get_rows() - 1);
      ymax = min(j + s, img1.get_cols() - 1);

      xmin = max(0, i - s);
      ymin = max(0, j - s);

      SearchSpace(img1.image_data.block(xmin, ymin, xmax - xmin + 1, ymax - ymin + 1), m, _x, _y);

      distance_to_RGB(_x - s, _y - s, R, G, B);
      y.R(i, j) = R;
      y.G(i, j) = G;
      y.B(i, j) = B;
    }
  return y;
}

void BlockMatching::SearchSpace(const MatrixXf A, const MatrixXf V, int& x, int& y)
{
  // make functor
  int Py = V.cols() / 2, Px = V.rows() / 2;

  MatrixXf B = MatrixXf::Zero(A.rows() + (2 * Px), A.cols() + (2 * Py));
  B.block(Px, Py, A.rows(), A.cols()) = A;

  MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B, &V](Index i, Index j) {
    return pow((V.array()
      - B.block(i, j, V.rows(), V.cols()).array()), 2).sum();
    }).minCoeff(&x, &y);

}


// void BlockMatching(MatrixXf A, MatrixXf B, int sx, int sy, int block = 3) {
//     // MatrixXf Apad = padding(A, block/2, block/2);
//     // MatrixXf Bpad = padding(B, block/2, block/2);
//     cout<< "print";
//     MatrixXf::NullaryExpr(A.rows(), A.cols(), [&A, &B, &sx,&sy,&block](Index i, Index j) {
//         // sx += ;
//         // sy += (block/2);
//         cout<< "print";
//         int xmax = std::min((int)i+sx+(block/2), 10);
//         int ymax = std::min((int)j+sy+(block/2), 10);
//         int xmin = std::max(0, (int)j-sx-(block/2));
//         int ymin = std::max(0, (int)j-sy-(block/2));

//         // cout<<xmax<<endl<<ymax<<endl<<xmin<<endl<<ymin<<endl;
//         // cout << K.block(xmin,ymin,xmax-xmin+1,ymax-ymin+1) << endl;
//         Distance D =
//             SearchSpace(B.block(xmin, ymin, xmax-xmin+1, ymax-ymin+1),
//                         A.block(i, j, block, block));
//         cout << D.x << " " << D.y << endl;
//         });

// }



