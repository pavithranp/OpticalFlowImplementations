// Copyright [2020] <Pavithran Pandiyan>
#include "Image.h"

bool Image::ReadFromDisk(const std::string &file_name) {
    // std::cout << file_name;
    std::string line;
    std::ifstream myfile(file_name, std::ios::binary);
    std::cout << "well at least this works";
    if (std::cout << myfile.is_open()) {
        while (getline(myfile, line)) {
        std::cout << line << '\n';
        }
        myfile.close();
    }
    return 1;
}
