#include "lve_pipeline.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace lve {

    LvePipeline::LvePipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
        createGraphicsPipeline(vertFilepath, fragFilepath);
    }


    std::vector<char> LvePipeline::readFile(const std::string& filepath) {

        // std::ios::ate - when file is open, we seek to the end immediately
        // std::ios::binary - read as a binary
        std::ifstream file{filepath, std::ios::ate | std::ios::binary};
        if (!file.is_open()) {
            throw std::runtime_error("failed to open file: " + filepath);
        }

        // istream::tellg - returns the position of the current character.
        // cause whe used ios::ate - we are in the end of the file, so tellg gives us a file's size
        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);

        file.seekg(0); // returns to the begining of a file
        file.read(buffer.data(), fileSize); // read data to buffer
        file.close();
        return buffer;
    }

    void LvePipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
        auto vertCode = readFile(vertFilepath);
        auto fragCode = readFile(fragFilepath);

        std::cout << "Vertext Shader Code Size: " << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << '\n';
    }
}