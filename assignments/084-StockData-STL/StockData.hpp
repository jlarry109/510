#ifndef STOCKDATA_HPP
#define STOCKDATA_HPP

#include <string>

class StockData {
public:
    const std::string date;
    const double openingPrice;
    const double closingPrice;
    const double lowPrice;
    const double highPrice;
    const long volume;

    StockData(const std::string &date, double openingPrice, double closingPrice, double lowPrice, double highPrice, int volume);

    double rateOfReturn(const StockData &previous);
    
    // Factory function to create an instance from a line of text
    static StockData fromString(const std::string& line);


private:
    // Utility function to transform date from mm/dd/yyyy to yyyymmdd
    static std::string transformDate(const std::string& oldDate);


friend std::ostream& operator<<(std::ostream& out, const StockData& stockData);


};

#endif
