
#include<algorithm>
using namespace Eigen;
using namespace std;
// MatrixXf Cost(MatrixXf A,  MatrixXf B)
// {
//   int P = V.cols() > V.rows() ? V.cols()/2 : V.rows()/2;

//   MatrixXf B = MatrixXf::Zero(A.rows()+(2*P), A.cols()+(2*P));

//   B.block(P, P, A.rows(), A.cols()) = A;
//   return MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B, &V] (Index i, Index j) {
//         return (V.array() * B.block (i, j, V.rows(), V.cols()).array()).sum();
//         });
// }

MatrixXf padding(MatrixXf image_data, int padX, int padY) {
int rl = image_data.rows(), cl = image_data.cols();

Eigen::MatrixXf B(rl+padX, cl+padY);
B.block(padX/2, padY/2, rl, cl) = image_data;
// cout << input.row(0).replicate(2, 1) << endl;
// top-bot row and left-right column fill
B.block(0, padY/2, padX/2, cl) = image_data.row(0).replicate(padX/2, 1);
B.block(rl+padX/2, padY/2, padX/2, cl) = image_data.row(rl-1).replicate(padX/2, 1);
B.block(padX/2, 0, rl, padY/2) = image_data.col(0).replicate(1, padY/2);
B.block(padX/2, cl+padY/2, rl, padY/2) = image_data.col(cl-1).replicate(1, padY/2);
// corner squares
B.block(0, 0, padX/2, padY/2) =
            Eigen::MatrixXf::Constant(padX/2, padY/2, image_data.coeff(0, 0));
B.block(0, cl+padY/2, padX/2, padY/2) =
            Eigen::MatrixXf::Constant(padX/2, padY/2, image_data.coeff(0, cl-1));
B.block(rl+padX/2, 0, padX/2, padY/2) =
            Eigen::MatrixXf::Constant(padX/2, padY/2, image_data.coeff(rl-1, 0));
B.block(rl+padX/2, cl+padY/2, padX/2, padY/2) =
            Eigen::MatrixXf::Constant(padX/2, padY/2, image_data.coeff(rl-1, cl-1));

return B;
}
struct Distance
{
     int x;
     int y;
};
//Algorithm
  // check size of matrix are same
  // loop through each pixel on image 1
    // loop through search window size on 2nd image
        // locate blocks around two imgs
        // calculate cost of two blocks (sub square sum)
    // find distance with minimum cost

Distance SearchSpace(MatrixXf A,  MatrixXf V)
{
  // check pad
  int Py = V.cols()/2 , Px = V.rows()/2;

  MatrixXf B = MatrixXf::Zero(A.rows()+(2*Px), A.cols() + (2*Py));
  B.block(Px, Py, A.rows(), A.cols()) = A;
  cout<<B<<endl<<endl;
  MatrixXf C = MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B, &V] (Index i, Index j) {
        return pow((V.array() - B.block(i, j, V.rows(),V.cols()).array()),2).sum();
        });
  Distance D;
  cout << "cost :" <<C.minCoeff(&D.x, &D.y) << endl;
  return D;
}

void BlockMatching(MatrixXf A, MatrixXf B, int sx, int sy, int block = 3) {
    // MatrixXf Apad = padding(A, block/2, block/2);
    // MatrixXf Bpad = padding(B, block/2, block/2);
    cout<< "print";
    MatrixXf::NullaryExpr(A.rows(), A.cols(), [&A, &B, &sx,&sy,&block](Index i, Index j) {
        // sx += ;
        // sy += (block/2);
cout<< "print";
        int xmax = std::min((int)i+sx+(block/2), 10);
        int ymax = std::min((int)j+sy+(block/2), 10);
        int xmin = std::max(0, (int)j-sx-(block/2));
        int ymin = std::max(0, (int)j-sy-(block/2));

        // cout<<xmax<<endl<<ymax<<endl<<xmin<<endl<<ymin<<endl;
        // cout << K.block(xmin,ymin,xmax-xmin+1,ymax-ymin+1) << endl;
        Distance D =
            SearchSpace(B.block(xmin, ymin, xmax-xmin+1, ymax-ymin+1),
                        A.block(i, j, block, block));
        cout << D.x << " " << D.y << endl;
        });
    
}



