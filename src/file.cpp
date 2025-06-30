#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include "language_detector.hpp"

const std::array<std::string, 16> langCodes = {
    "ar", "zh", "de", "en", "fr", "hi", "it", "ja",
    "ko", "nl", "pt", "ru", "es", "sv", "tr", "vi"
};

const std::array<Lang, 16> langEnums = {
    Lang::Ara, Lang::Cmn, Lang::Deu, Lang::Eng, Lang::Fra, Lang::Hin,
    Lang::Ita, Lang::Jpn, Lang::Kor, Lang::Nld, Lang::Por, Lang::Rus,
    Lang::Spa, Lang::Swe, Lang::Tur, Lang::Vie
};

Lang codeToLang(const std::string& code) {
    for (size_t i = 0; i < langCodes.size(); ++i) {
        if (langCodes[i] == code) {
            return langEnums[i];
        }
    }
    return Lang::Eng; // default
}

std::vector<std::string> readLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "ERROR: Cannot open " << filename << std::endl;
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    
    return lines;
}

int main() {
    std::vector<std::string> labels = readLines("../data/labels.txt");
    std::vector<std::string> texts = readLines("../data/text.txt");
    
    if (labels.empty() || texts.empty() || labels.size() != texts.size()) {
        std::cerr << "Error loading files or size mismatch" << std::endl;
        return 1;
    }
    
    int total = 0, correct = 0, unknown = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (size_t i = 0; i < labels.size(); ++i) {
        Lang expected = codeToLang(labels[i]);
        Lang detected = LanguageDetector::detectLanguage(texts[i]);
        
        if (expected == Lang::Eng && labels[i] != "en") {
            unknown++;
        } else if (detected == expected) {
            correct++;
        }
        
        total++;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    double accuracy = (double)correct / total * 100.0;
    double totalTime = duration.count() / 1000.0;
    double avgTime = totalTime / total;
    
    std::cout << "Samples: " << total << std::endl;
    std::cout << "Correct: " << correct << std::endl;
    std::cout << "Accuracy: " << std::fixed << std::setprecision(2) << accuracy << "%" << std::endl;
    std::cout << "Total time: " << std::fixed << std::setprecision(2) << totalTime << " ms" << std::endl;
    std::cout << "Avg time: " << std::fixed << std::setprecision(4) << avgTime << " ms/sample" << std::endl;
    
    return 0;
}
