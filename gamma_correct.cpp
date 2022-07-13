//
// Created by Howard Colin on 10/07/2022.
//

#include "gamma_correct.h"

int Gamma_Correct::calc_inverse_gamma(const Mat &src, Mat &dest, const float gamma) {
    float inverse_gamma = 1 / gamma;
    Mat table(1, 256, CV_8U);
    uchar *p = table.ptr();
    for (int i = 0; i<256; ++i) {
        p[i] = (uchar) (pow(i/255.0, inverse_gamma) * 255);
    }
    LUT(src, table, dest);
    return 0;
}

int Gamma_Correct::apply_gamma(const Mat &src, Mat &dest, const float gamma){
    Mat table(1, 256, CV_8U);
    uchar *p = table.ptr();
    for (int i = 0; i<256; ++i){
        p[i] = (uchar) (pow(i/255.0, gamma) * 255);
    }
    LUT(src, table, dest);
    return 0;
}