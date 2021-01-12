// Copyright [2020] <Pavithran Pandiyan>
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION   // use of stb functions once and for all
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
using namespace Eigen;
using namespace std;

typedef Eigen::Matrix<unsigned char, -1, -1> matrixc;
typedef Eigen::Map<matrixc > map_mat;
bool Image::ReadFromDisk(const char* file_name) {
    // std::cout << file_name;
    unsigned char* img = stbi_load(file_name, &rows_, &cols_, &channels_, 0);
    if (img == NULL) {
        std::cout << " Error loading image please check the path!"
            << std::endl;
        return 0;
    }
    else {
        std::cout << rows_ << std::endl << cols_ <<
            std::endl << channels_ << std::endl;
    }
    if (channels_ == 1) {
        image_data = Eigen::Map<matrixc >(img, rows_, cols_).cast<float>();
    }
    else {
        std::cout << "image has " << channels_ <<
            " channels, currently not supported" << std::endl;
    }
    return 1;
}

void Image::WriteToDisk(const char* file_name)
{
    if (image_data.isZero(0)) {
        std::cout << " image matrix is empty" << std::endl;
        return;
    }
    image_data = image_data.cwiseAbs();
    std::cout << image_data.size();
    Eigen::Matrix<unsigned char, Eigen::Dynamic,
        Eigen::Dynamic> temp = image_data.cast<unsigned char>();
    unsigned char* img = temp.data();
    stbi_write_jpg(file_name, rows_, cols_, 1, img, rows_ * 1);
    // stbi_image_free(img);
}

void Image::Write3ToDisk(const char* file_name)
{
    // if (image_data.isZero(0)) {
    //     std::cout << " image matrix is empty" << std::endl;
    //     return;
    // }
    // G = Eigen::MatrixXf::Zero(image_data.rows(), image_data.cols());
    // B = Eigen::MatrixXf::Zero(image_data.rows(), image_data.cols());
    R = image_data;
    G = image_data;
    B = image_data;
    rows_ = R.rows();
    cols_ = R.cols();
    Eigen::MatrixXf RGB = Eigen::MatrixXf::NullaryExpr(R.rows() * 3, R.cols(), [R_v = R, G_v = G, B_v = B](Eigen::Index i, Eigen::Index j) {
        // std::cout << i << j << std::endl;
        int r = i % 3;
        if (r == 0) {
            return R_v.coeff(i / 3, j);
        }
        else if (r == 1)
        {
            return G_v.coeff(i / 3, j);
        }
        else if (r == 2)
        {
            return B_v.coeff(i / 3, j);
        }


        // return A.coeff(i % A.rows(), j);
        });

    Eigen::Matrix<unsigned char, Eigen::Dynamic,
        Eigen::Dynamic> temp = RGB.cast<unsigned char>();
    unsigned char* img = temp.data();
    stbi_write_jpg(file_name, rows_, cols_, 3, img, rows_ * 3);
}

void Image::add_padding(int padX, int padY) {
    // look for a better way to do this
    int rl = rows_, cl = cols_;

    Eigen::MatrixXf B(rl + padX, cl + padY);
    B.block(padX / 2, padY / 2, rl, cl) = image_data;
    // cout << input.row(0).replicate(2, 1) << endl;
    // top-bot row and left-right column fill
    B.block(0, padY / 2, padX / 2, cl) = image_data.row(0).replicate(padX / 2, 1);
    B.block(rl + padX / 2, padY / 2, padX / 2, cl) = image_data.row(rl - 1).replicate(padX / 2, 1);
    B.block(padX / 2, 0, rl, padY / 2) = image_data.col(0).replicate(1, padY / 2);
    B.block(padX / 2, cl + padY / 2, rl, padY / 2) = image_data.col(cl - 1).replicate(1, padY / 2);
    // corner squares
    B.block(0, 0, padX / 2, padY / 2) =
        Eigen::MatrixXf::Constant(padX / 2, padY / 2, image_data.coeff(0, 0));
    B.block(0, cl + padY / 2, padX / 2, padY / 2) =
        Eigen::MatrixXf::Constant(padX / 2, padY / 2, image_data.coeff(0, cl - 1));
    B.block(rl + padX / 2, 0, padX / 2, padY / 2) =
        Eigen::MatrixXf::Constant(padX / 2, padY / 2, image_data.coeff(rl - 1, 0));
    B.block(rl + padX / 2, cl + padY / 2, padX / 2, padY / 2) =
        Eigen::MatrixXf::Constant(padX / 2, padY / 2, image_data.coeff(rl - 1, cl - 1));

    image_data = B;
}
