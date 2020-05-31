#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#ifdef USE_PNG
#include <png++/png.hpp>
typedef png::rgb_pixel image_color;
typedef png::image<image_color> image_type;
#endif

class Image {
 public:
  void loadBmp(std::string filename) {
    std::ifstream textureFile(filename, std::ios::in | std::ios::binary);
    if (textureFile) {
      std::copy(std::istreambuf_iterator<char>(textureFile), std::istreambuf_iterator<char>(),
                std::back_inserter(buffer_));
    } else {
      throw std::runtime_error("Texture file not accessable");
    }

    if ((buffer_[0] != 'B') || (buffer_[1] != 'M')) {
      throw std::runtime_error("File is no bmp");
    }

    // read image sizes
    width_ = *((uint32_t*)&buffer_[18]);
    height_ = *((uint32_t*)&buffer_[22]);
    bits_per_pixel_ = *((uint32_t*)&buffer_[28]);

    // remove header an footer
    uint32_t size = (width_ * height_ * bits_per_pixel_) / 8;
    uint32_t pos_data = *((uint32_t*)&buffer_[10]);
    buffer_.erase(buffer_.begin(), buffer_.begin() + pos_data);
    buffer_.erase(buffer_.begin() + size, buffer_.end());
  }

#ifdef USE_PNG
  void loadPng(std::string filename) {
    image_type texture_image(filename);
    width_ = texture_image.get_width();
    height_ = texture_image.get_height();
    bits_per_pixel_ = 24;

    // copy image to the buffer vector
    for (uint32_t x = 0; x < texture_image.get_width(); x++) {
      for (uint32_t y = 0; y < texture_image.get_height(); y++) {
        buffer_.push_back(texture_image[x][y].red);
        buffer_.push_back(texture_image[x][y].green);
        buffer_.push_back(texture_image[x][y].blue);
      }
    }
  }
#endif

  uint32_t width() { return width_; }

  uint32_t height() { return height_; }

  uint16_t bits_per_pixel() { return bits_per_pixel_; }

  std::vector<GLubyte>& data() { return buffer_; }

 private:
  uint32_t width_;
  uint32_t height_;
  uint16_t bits_per_pixel_;
  std::vector<GLubyte> buffer_;
};