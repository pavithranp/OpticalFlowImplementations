// Copyright [2020] <Pavithran Pandiyan>
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION   // use of stb functions once and for all
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
typedef Eigen::Matrix<unsigned char, -1, -1> matrixc;
typedef Eigen::Map<matrixc > map_mat;
bool Image::ReadFromDisk(const char* file_name) {
    // std::cout << file_name;
    unsigned char *img = stbi_load(file_name, &rows_, &cols_, &channels_, 0);
    if ( img == NULL ) {
        std::cout << " Error loading image please check the path!"
            << std::endl;
        return 0;
    } else {
        std::cout << rows_ << std::endl << cols_ <<
            std::endl << channels_ << std::endl;
    }
    if (channels_ == 1) {
        image_data = Eigen::Map<matrixc > (img, rows_, cols_).cast<float>();
    } else {
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
    unsigned char *img = temp.data();
    stbi_write_jpg(file_name, rows_, cols_, 1, img, rows_*1);
    // stbi_image_free(img);
}
