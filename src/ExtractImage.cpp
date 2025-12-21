#include "ExtractImage.h"


#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-image.h>
#include <poppler/cpp/poppler-page-renderer.h>


#include <filesystem>
#include <stdexcept>
#include <sstream>

namespace fs = std::filesystem;


ExtractImage::ExtractImage(int dpi)
    : m_dpi(dpi){
    if (dpi < 150){
        throw std::invalid_argument("DPI too low for OCR");
    }
}

void ExtractImage::validatePaths( const std::string& pdfPath, const std::string& outputDir) const{
    if (!fs::exists(pdfPath)){
        throw std::runtime_error("PDF file does not exist");
    }

    if (!fs::exists(outputDir)){
        fs::create_directories(outputDir);
    }
}

std::vector<PageImage> ExtractImage::convert(const std::string& pdfPath, const std::string& outputDir){
   
    validatePaths(pdfPath, outputDir);

    // Load PDF document
    std::unique_ptr<poppler::document> doc ( poppler::document::load_from_file(pdfPath) );

    if (!doc)
        throw std::runtime_error("Failed to load PDF document");

    int pageCount = doc->pages();

    if (pageCount <= 0){
        throw std::runtime_error("PDF has no pages");
    }

    std::vector<PageImage> results;
    results.reserve(pageCount);

    // Renderer
    poppler::page_renderer renderer;
    renderer.set_render_hint(poppler::page_renderer::antialiasing, true);
    renderer.set_render_hint(poppler::page_renderer::text_antialiasing, true);

    for (int pageIndex = 0; pageIndex < pageCount; ++pageIndex)
    {
        std::unique_ptr<poppler::page> page(doc->create_page(pageIndex));
        if (!page){
            continue; // skip broken page safely
        }

        // Render page → image
        poppler::image img = renderer.render_page(page.get(), m_dpi, m_dpi);

        if (!img.is_valid()){
            continue;
        }

        // Create output filename
        std::ostringstream filePath;
        filePath << outputDir << "page_" << std::setw(4) << std::setfill('0') << pageIndex << ".png";

        // Save image
        if (!img.save(filePath.str(), "png")){
            throw std::runtime_error("Failed to save image: " + filePath.str());
        }

        // Collect metadata
        PageImage pageImage;
        pageImage.pageIndex = pageIndex;
        pageImage.imagePath = filePath.str();
        pageImage.width = img.width();
        pageImage.height = img.height();
        pageImage.dpi = m_dpi;

        results.push_back(pageImage);
    }

    return results;
}

