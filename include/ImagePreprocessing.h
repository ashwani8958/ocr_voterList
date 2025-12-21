#pragma once

#include <opencv2/core.hpp>

#include <string>
#include <vector>

/**
 * @class ImagePreprocessing
 * @brief Performs image preprocessing for OCR pipelines.
 *
 * This class applies a fixed preprocessing pipeline on document images
 * to make them suitable for OCR engines (e.g., Tesseract).
 */
class ImagePreprocessing{
private:
    std::vector<std::string> rawPngPaths;

    void validateInputFilePath(const std::string & rawPngPath) const;
    void checkOutputFilePath(const std::string & preprocessImage) const;
    void getAllRawImageNames(const std::string & rawPngPath);

    cv::Mat removeNoiseAndBackground(const cv::Mat& inputImage);
    cv::Mat improveTextContrast(const cv::Mat& inputImage);
    cv::Mat normalizeOrientationAndScale(const cv::Mat& inputImage);
    cv::Mat separateTextFromNonText(const cv::Mat& inputImage);
    
    public:
    ImagePreprocessing() = default;
    void preprocess(const std::string& rawPngPath, const std::string& preprocessImagePath);
};