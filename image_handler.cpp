//
// Created by Howard Colin on 10/07/2022.
//
#include "image_handler.h"

int Image_Handler::populate_image_queue(std::filesystem::path src) {
    int total_files = 0;

    if(!is_directory(src)){
        return -1;
    }

    try {
        std::filesystem::create_directory(src / "Processed");
    }
    catch(std::filesystem::filesystem_error const& ex) {
        return -1;
    };

    try {
        for (auto const &dir_entry: std::filesystem::directory_iterator{src}) {
            if (dir_entry.is_regular_file()) {
                if (dir_entry.path().extension() == ".jpg") {
                    image_queue.push_back(dir_entry);
                    total_files++;
                }
            }
        }
    }
    catch (std::filesystem::filesystem_error const& ex) {
        return -1;
    }
    return total_files;
}

int Image_Handler::process_images(const float src_gamma, const float dest_gamma) {
    for(auto &p: image_queue) {
        try {
            src_image = imread(p.generic_string());
        }
        catch(cv::Exception &e) {
            return -1;
        }

        if(corrector.calc_inverse_gamma(src_image, linear_image, src_gamma) == -1) {
            return -1;
        }

        corrector.apply_gamma(linear_image, corrected_image, dest_gamma);

        std::filesystem::path output {p.parent_path() / "Processed" / p.filename()};

        if(save_corrected_image(output) == -1) {
            return  -1;
        }
    }
    return 0;
}

int Image_Handler::save_corrected_image(std::filesystem::path dest) {
    try {
        imwrite(dest.generic_string(), corrected_image);
    }
    catch(cv::Exception &e) {
        return -1;
    }
    return 0;
}
