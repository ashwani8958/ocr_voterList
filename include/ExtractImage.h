#pragma once
#include <string>
#include <vector>

struct PageImage{
    int pageIndex;                 // 0-based page number
    std::string imagePath;         // saved PNG path
    int width;                     // pixels
    int height;                    // pixels
    int dpi;
};

class ExtractImage{
public:
    ExtractImage(int dpi = 300);
    std::vector<PageImage> convert(const std::string& pdfPath, const std::string& outputDir);

private:
    int m_dpi;
    void validatePaths(const std::string& pdfPath, const std::string& outputDir) const;
};