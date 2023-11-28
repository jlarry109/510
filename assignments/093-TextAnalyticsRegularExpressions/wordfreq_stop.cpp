#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cctype>
#include <set>

using std::string, std::set, std::regex, std::map;

string toLower(const string& str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}

set<string> readStopWords(const string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    set<string> result;

    string line;
    while (getline(file, line)) {
        result.insert(toLower(line)); 
    }

    file.close();
    return result;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " stopWords inputFile\n";
        return EXIT_FAILURE;
    }

    map<string, int> wordFreq;
    regex wordRegex("\\b[a-zA-Z]+\\b"); // Regular expression for words

    set<string> stopWords = readStopWords(argv[1]);

    // Open file
    std::ifstream file(argv[2]);
    if (!file.is_open()) {
        std::cerr << "Error opening file:" << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    string line;
    while (getline(file, line)) {
        line = toLower(line);

        // Use regex to split line into words
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), wordRegex);
        auto words_end = std::sregex_iterator();

        for (auto i = words_begin; i != words_end; ++i) {
            string word = i->str();
            if (stopWords.find(word) != stopWords.end()) { continue; } // C++20 adds "contains"
            ++wordFreq[word]; // Increase frequency count
        }
    }
    file.close();

    // Copy map to vector for sorting
   std::vector<std::pair<string, int>> freqVector(wordFreq.begin(), wordFreq.end());

    // Sort vector by frequency
    std::sort(freqVector.begin(), freqVector.end(), [](const std::pair<string, int>& a, const std::pair<string, int>& b) {
        if (a.second == b.second) { return a.first < b. first; }
        return a.second > b.second;
    });

    // Print top 20 words
    int count = 0;
    for (const auto& pair : freqVector) {
        if (count++ >= 20) break;
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    return EXIT_SUCCESS;
}
