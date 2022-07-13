//
// Created by Howard Colin on 10/07/2022.
//

#ifndef GAMMA_SHIFT_GAMMA_CORRECT_H
#define GAMMA_SHIFT_GAMMA_CORRECT_H

#include <opencv2/opencv.hpp>

using namespace cv;

class Gamma_Correct {
public:
    int calc_inverse_gamma(const Mat &src, Mat &dest, const float gamma);
    int apply_gamma(const Mat &src, Mat &dest, const float gamma);
};


#endif //GAMMA_SHIFT_GAMMA_CORRECT_H
