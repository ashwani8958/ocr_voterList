#include <iostream>
#include "ExtractImage.h"
#include "ImagePreprocessing.h"

using namespace std;

int main(int argc, char *argv[]){
    
    // cout << "hello" << endl;

    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <input_pdf> <raw_image_path> <preprocess_image_path>\n";
        return 1;
    }

    const std::string pdfPath   = argv[1];
    const std::string rawPngDir = argv[2];
    const std::string preProcessPngDir = argv[3];


    try
    {
        // 300 DPI is recommended for Hindi OCR
        ExtractImage converter(300);

        vector<PageImage> images = converter.convert(pdfPath, rawPngDir);

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

        ImagePreprocessing preProcessImages;
        preProcessImages.preprocess(rawPngDir, preProcessPngDir);
        // const vector<string> rawFiles = preProcessImages.GetAllRawImageNames(rawPngDir);

        // for(int i = 0; i < rawFiles.size(); i++){
        //     cout << rawFiles[i] << endl;
        // }
    }
    catch (const std::exception& ex){
        std::cerr << "ERROR: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}