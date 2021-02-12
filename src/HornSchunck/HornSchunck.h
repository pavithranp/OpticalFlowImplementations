#include<algorithm>
#include"util/Image.h"
#include "util/color_lib.h"
using namespace Eigen;
using namespace std;

// Algorithm
  // compute Motion tensor 
  // iteratively solve using jacobian to minimize Functional

    // loop through each pixel on image 1

Image HornSchunck(Image img1, Image img2, int s, int block_size = 3, int alpha_i = 100) {
    Image y;
    y.R = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    y.G = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    y.B = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    img1.add_padding(2 * s, 2 * s);
    img2.add_padding(2 * s, 2 * s);
    // img2.add_padding(block_size - 1, block_size - 1);
    MatrixXf J_11 = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf J_22 = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf J_33 = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf J_12 = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf J_13 = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf J_23 = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf u_old = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);
    MatrixXf v_old = MatrixXf(img1.get_rows() + 2 * s, img1.get_cols() + 2 * s);

    float fx, fy, ft;
    for (int i = s; i < img1.get_rows() + s; i++)
        for (int j = s; j < img1.get_cols() + s; j++) {

            fx = 0.5 * (img1.image_data(i + 1, j) - img1.image_data(i - 1, j) + img2.image_data(i + 1, j) - img2.image_data(i - 1, j));
            fy = 0.5 * (img1.image_data(i, j + 1) - img1.image_data(i, j - 1) + img2.image_data(i, j + 1) - img2.image_data(i, j - 1));

            ft = img2.image_data(i, j) - img1.image_data(i, j);

            J_11(i, j) = fx * fx;
            J_22(i, j) = fy * fy;
            J_33(i, j) = ft * ft;
            J_12(i, j) = fx * fy;
            J_13(i, j) = fx * ft;
            J_23(i, j) = fy * ft;
        }
    float xp, xm, yp, ym, hx_2, hy_2, sum, u, v;
    hx_2 = alpha_i;
    hy_2 = alpha_i;
    int R, G, B;
    for (int g = 0;g < 1;g++)
        for (int i = s; i < img1.get_rows() + s; i++)
            for (int j = s; j < img1.get_cols() + s; j++)
            {

                xp = (i < img1.get_rows() + s - 1) * hx_2;
                xm = (i > s) * hx_2;
                yp = (j < img1.get_cols() + s - 1) * hy_2;
                ym = (j > s) * hy_2;

                /* compute the sum of weights */
                sum = -(xp + xm + yp + ym);

                /* perform iteration */

                // cout << J_23(i, j) << sum << endl;
                u = (J_13(i, j) + J_12(i, j) * v_old(i, j)
                    - xm * u_old(i - 1, j)
                    - xp * u_old(i + 1, j)
                    - ym * u_old(i, j - 1)
                    - yp * u_old(i, j + 1)) / (sum - J_11(i, j));

                v = (J_23(i, j) + J_12(i, j) * u_old(i, j)
                    - xm * v_old(i - 1, j)
                    - xp * v_old(i + 1, j)
                    - ym * v_old(i, j - 1)
                    - yp * v_old(i, j + 1)) / (sum - J_22(i, j));
                vector_to_RGB(u, v, R, G, B);
                y.R(i, j) = R;
                y.G(i, j) = G;
                y.B(i, j) = B;
            }

    return y;
}
