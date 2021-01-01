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
  Image() = default;

  // Getter functions
  int get_rows() { return rows_; }
  int get_cols() { return cols_; }

  // Reading & Writing Images from disk
  bool ReadFromDisk(const char* file_name);
  void WriteToDisk(const char* file_name);

 private:
  // Private member variables
  int rows_ = 0;
  int cols_ = 0;
  int channels_ = 0;
  int max_val_ = 255;
  Eigen::MatrixXf image_data;
};
