//
// Created by Howard Colin on 10/07/2022.
//

#ifndef GAMMA_SHIFT_IMAGE_HANDLER_H
#define GAMMA_SHIFT_IMAGE_HANDLER_H

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <deque>

#include "gamma_correct.h"

using namespace cv;

class Image_Handler {
private:
    Mat src_image, linear_image, corrected_image;
    Gamma_Correct corrector;
    std::deque<std::filesystem::path> image_queue;
    int save_corrected_image(std::filesystem::path dest);
public:
    int populate_image_queue(std::filesystem::path src);
    int process_images(const float src_gamma, const float dest_gamma);
};


#endif //GAMMA_SHIFT_IMAGE_HANDLER_H
