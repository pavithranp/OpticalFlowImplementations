// Copyright [2020] <Pavithran Pandiyan>
#pragma once

#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class Image {
 public:
  // Constructors
  Image(int rows, int cols) : rows_{rows}, cols_{cols} {
    // function to read
    Eigen ::MatrixXd x(rows, cols);
    std::cout << "x:" << std::endl << x;
  }

  // Getter functions
  int get_rows() { return rows_; }
  int get_cols() { return cols_; }

  // Dowscaling and Upscaling functions
  // void DownScale(int scale);
  // void UpScale(int scale);

  // Reading & Writing Images from disk
  bool ReadFromDisk(const char* file_name);
  void WriteToDisk(const std::string &file_name);

 private:
  // Private member variables
  int rows_ = 0;
  int cols_ = 0;
  int channels_ = 0;
  int max_val_ = 255;
};
