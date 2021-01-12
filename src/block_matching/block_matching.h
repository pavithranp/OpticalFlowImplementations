// Copyright [2020] <Pavithran Pandiyan>
#include<algorithm>
#include"util/Image.h"
#include "util/color_lib.h"
using namespace Eigen;
using namespace std;

struct Distance
{
  int x;
  int y;
};
// Algorithm
  // check size of matrix are same
  // loop through each pixel on image 1
    // loop through search window size on 2nd image
        // locate blocks around two imgs
        // calculate cost of two blocks (sub square sum)
    // find distance with minimum cost

Distance SearchSpace(const MatrixXf A, const MatrixXf V, Distance& D)
{
  // make functor
  int Py = V.cols() / 2, Px = V.rows() / 2;

  MatrixXf B = MatrixXf::Zero(A.rows() + (2 * Px), A.cols() + (2 * Py));
  B.block(Px, Py, A.rows(), A.cols()) = A;
  // cout<<B<<endl<<endl;
  MatrixXf::NullaryExpr(A.rows(), A.cols(),
    [&B, &V](Index i, Index j) {
      return pow((V.array()
        - B.block(i, j, V.rows(), V.cols()).array()), 2).sum();
    }).minCoeff(&D.x, &D.y);
    return D;
}
Image BlockMatching(Image img1, Image img2, int s, int block_size = 3) {
  Image y;
  y.R = MatrixXf(img1.get_rows(), img1.get_cols());
  y.G = MatrixXf(img1.get_rows(), img1.get_cols());
  y.B = MatrixXf(img1.get_rows(), img1.get_cols());

  img2.add_padding(block_size - 1, block_size - 1);
  MatrixXf m;
  Distance D;
  int xmax, ymax, xmin, ymin, R = 0, G = 0, B = 0;
  for (int i = 0; i < img1.get_rows(); i++)
    for (int j = 0; j < img1.get_cols(); j++) {
      m = img2.image_data.block(i, j, block_size, block_size);
      // cout<<m;
      // cout<<i<<" :"<<j;
      xmax = min(i + s, img1.get_rows() - 1);
      ymax = min(j + s, img1.get_cols() - 1);

      xmin = max(0, i - s);
      ymin = max(0, j - s);

      SearchSpace(img1.image_data.block(xmin, ymin, xmax - xmin + 1, ymax - ymin + 1), m, D);
      // cout << D.x - s << " " << D.y - s;

      vector_to_RGB(D.x - s, D.y - s, R, G, B);
      y.R(i, j) = R;
      y.G(i, j) = G;
      y.B(i, j) = B;



    }
  return y;
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



