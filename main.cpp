#include <iostream>
#include <cstdlib>
#include "cargs.h"
#include "image_handler.h"

using namespace std;

static struct cag_option options[] = {
        {.identifier = 's',
         .access_letters = "s",
         .access_name = "src",
         .value_name = "VALUE",
         .description = "Source directory containing images to process."},

        {.identifier = 'g',
                .access_letters = "g",
                .access_name = "src-gamma",
                .value_name = "GAMMA",
                .description = "The known source gamma of the images to process."},

        {.identifier = 't',
                .access_letters = "t",
                .access_name = "dest-gamma",
                .value_name = "DEST_GAMMA",
                .description = "The desired destination gamma of the images to process."},

        {.identifier = 'h',
                .access_letters = "h",
                .access_name = "help",
                .description = "Shows the command help"}};

struct configuration
{
    std::filesystem::path src;
    float source_gamma = 0.0;
    float dest_gamma = 0.0;
};

int main(int argc, char * argv[]) {
    char identifier;
    cag_option_context context;
    struct configuration config;

    cag_option_prepare(&context, options, CAG_ARRAY_SIZE(options), argc, argv);
    while (cag_option_fetch(&context)) {
        identifier = cag_option_get(&context);
        switch (identifier) {
            case 's':
                config.src = cag_option_get_value(&context);
                break;
            case 'g':
                config.source_gamma = atof(cag_option_get_value(&context));
                break;
            case 't':
                config.dest_gamma = atof(cag_option_get_value(&context));
                break;
            case 'h':
                printf("Usage: gamma_shift [OPTION]...\n");
                printf("Batch gamma corrects images in a folder..\n\n");
                cag_option_print(options, CAG_ARRAY_SIZE(options), stdout);
                return EXIT_SUCCESS;
            default:
                cout << "ERROR: Invalid option flags.\n";
                return EXIT_FAILURE;
        }
    }

    std::cout << "Processing: " << config.src << "\n";

    Image_Handler processor;

    int total_files = processor.populate_image_queue(config.src);
    if(total_files > 0) {
       cout << "Total .jpg's found: " << total_files << "\n";
    }
    else {
       cout << "ERROR: No files found, please ensure you have supplied a path to a directory\n";
       return EXIT_FAILURE;
    }

    if (processor.process_images(config.source_gamma, config.dest_gamma) == -1) {
        cout << "Error applying transformation.\n";
        return EXIT_FAILURE;
    }

    return 0;
}

