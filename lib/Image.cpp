// Copyright [2020] <Pavithran Pandiyan>
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION   // use of stb functions once and for all
#include "stb_image.h"
typedef Eigen::Map<Eigen::Matrix<unsigned char, Eigen::Dynamic,
        Eigen::Dynamic>> Img_mat;

bool Image::ReadFromDisk(const char* file_name) {
    // std::cout << file_name;
    unsigned char *img = stbi_load(file_name, &rows_, &cols_, &channels_, 0);
    if ( img == NULL ) {
        std::cout << " Error loading image please check the path !";
    } else {
        std::cout << rows_ << std::endl << cols_ <<
            std::endl << channels_ << std::endl;
    }
    
    Img_mat image(img, rows_, cols_);
    std::cout << image << std::endl;
    if (channels_ == 3) {
    Img_mat red(img, rows_, cols_), green(img+1, rows_, cols_),
        blue(img+2, rows_, cols_);
    }
    return 1;
}
