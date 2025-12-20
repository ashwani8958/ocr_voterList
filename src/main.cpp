#include <iostream>
#include "ExtractImage.h"

using namespace std;

int main(int argc, char *argv[]){
    
    // cout << "hello" << endl;

    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0]
                  << " <input_pdf> <output_dir>\n";
        return 1;
    }

    const std::string pdfPath   = argv[1];
    const std::string outputDir = argv[2];

    try
    {
        // 300 DPI is recommended for Hindi OCR
        ExtractImage converter(300);

        vector<PageImage> images = converter.convert(pdfPath, outputDir);

        std::cout << "Conversion successful!\n";
        std::cout << "Total pages converted: " << images.size() << "\n\n";

        for (const auto& img : images)
        {
            std::cout << "Page " << img.pageIndex
                      << " -> " << img.imagePath
                      << " (" << img.width << "x"
                      << img.height << " @ "
                      << img.dpi << " DPI)\n";
        }
    }
    catch (const std::exception& ex){
        std::cerr << "ERROR: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}