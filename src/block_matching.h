  // make functor
  // check size of matrix are same

  //loop through each pixel on image 1
    // loop through search window size on 2nd image
        // locate blocks around two imgs
        // calculate cost of two blocks (sub square sum)
    // find distance with minimum cost

MatrixXf Cost( MatrixXf A,  MatrixXf B)
{

  int P = V.cols() > V.rows() ? V.cols()/2 : V.rows()/2;

  MatrixXf B = MatrixXf::Zero(A.rows()+(2*P), A.cols()+(2*P));

  B.block(P, P, A.rows(), A.cols()) = A;
  return MatrixXf::NullaryExpr(A.rows(), A.cols(), [&B, &V] (Index i, Index j) {
        return (V.array() * B.block (i, j, V.rows(), V.cols()).array()).sum();
        });
}

MatrixXf BlockMatching(MatrixXf A, MatrixXf B, int sx, int sy, int block = 3){
    
    MatrixXf Apad = padding(A,block,block)

    MatrixXf Bpad = padding(B,block,block)


    MatrixXf::NullaryExpr(A.rows(), A.cols(), [&Apad, &Bpad] (Index i, Index j) {
        MatrixXf A_block = A.block(i,j,block,block)


        // loop through search window size on 2nd image
            // locate blocks around two imgs
            // calculate cost of two blocks (sub square sum)
        // find distance with minimum cost


        });

}

MatrixXf SearchSpace(MatrixXf A_block, MatrixXf B, int sx, int sy, int block = 3){
    
    MatrixXf::NullaryExpr(A.rows(), A.cols(), [&Apad, &Bpad] (Index i, Index j) {

    }
}