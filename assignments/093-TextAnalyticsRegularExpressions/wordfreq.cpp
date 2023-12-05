#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cctype>

using std::string, std::map, std::pair, std::vector, std::cerr, std::cout;

string toLower(const string& str) {
    string lowerStr;
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " inputFile\n";
        return EXIT_FAILURE;
    }

    map<string, int> wordFreq;
    std::regex wordRegex("\\b[a-zA-Z]+\\b"); // Regular expression for words
    std::regex wordRegex1("\\b\\w*zz\\w*\\b");//containing zz 
    std::regex wordRegex2("\\b\\w*x\\b");//Find all words that end in 'x'
    std::regex wordRegex3("\\b\\w*cie\\w*\\b|\\b\\w*[^c]ei\\w*\\b");//"i before e except after c"
    std::regex wordRegex4("\\b(?:\\w*[^aeiouyAEIOUY\\d\\W]{4}\\w*)\\b");// matches four or more consecutive consonants.
    std::regex wordRegex5("\\b\\d{5}(?:-\\d{4})?\\b");//zip code
    std::regex wordRegex6("\\b\\d{2}/\\d{2}/(\\d{4})\\b"); //mm/dd/yyyy
    std::regex wordRegex7("\\b4\\d{3}\\s\\d{4}\\s\\d{4}\\s\\d{4}\\b");//starts with 4, and has 4 groups of numbers, separated by a space.
    // Open file
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error opening file" << std::endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        line = toLower(line);

        // Use regex to split line into words
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), wordRegex4);
        auto words_end = std::sregex_iterator();

        for (auto i = words_begin; i != words_end; ++i) {
            string word = i->str();
            ++wordFreq[word]; // Increase frequency count
        }
    }
    file.close();

    // Copy map to vector for sorting
    vector<pair<string, int>> freqVector(wordFreq.begin(), wordFreq.end());

    // Sort vector by frequency
    std::sort(freqVector.begin(), freqVector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second == b.second) { return a.first < b. first; }
        return a.second > b.second;
    });

    // Print top 20 words
    int count = 0;
    for (const auto& pair : freqVector) {
        if (count++ >= 20) break;
        cout << pair.first << ": " << pair.second << "\n";
    }

    return EXIT_SUCCESS;
}
