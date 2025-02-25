#include <iostream>
#include <string>
#include <vector>
#include <zlib.h> // zlib 的头文件

// 压缩数据
std::vector<unsigned char> compressData(const std::string& input) {
    uLong sourceSize = input.size();
    uLong destSize = compressBound(sourceSize); // 获取压缩后的最大可能长度

    std::vector<unsigned char> compressedData(destSize);

    // 调用 zlib 的 compress 函数
    if (compress(compressedData.data(), &destSize,
                 reinterpret_cast<const unsigned char*>(input.data()), sourceSize) != Z_OK) {
        throw std::runtime_error("Compression failed!");
    }

    compressedData.resize(destSize); // 调整大小为实际压缩数据长度
    return compressedData;
}

// 解压数据
std::string decompressData(const std::vector<unsigned char>& compressedData, uLong originalSize) {
    std::vector<unsigned char> decompressedData(originalSize);

    // 调用 zlib 的 uncompress 函数
    if (uncompress(decompressedData.data(), &originalSize,
                   compressedData.data(), compressedData.size()) != Z_OK) {
        throw std::runtime_error("Decompression failed!");
    }

    return std::string(decompressedData.begin(), decompressedData.begin() + originalSize);
}

int main() {
    try {
        // 原始数据
        std::string input = "Hello, zlib! This is a test string for compression and decompression.";

        // 压缩
        std::cout << "Original data: " << input << std::endl;
        auto compressedData = compressData(input);
        std::cout << "Compressed data size: " << compressedData.size() << " bytes" << std::endl;

        // 解压
        auto decompressedData = decompressData(compressedData, input.size());
        std::cout << "Decompressed data: " << decompressedData << std::endl;

        // 验证结果
        if (input == decompressedData) {
            std::cout << "Decompressed data matches the original!" << std::endl;
        } else {
            std::cout << "Decompressed data does not match the original!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
