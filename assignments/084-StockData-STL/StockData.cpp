#include "StockData.hpp"
#include "stringutility.hpp"
#include <iomanip>
#include <vector>
#include <iostream>

StockData::StockData(const std::string &date, double openingPrice, double closingPrice, double lowPrice, double highPrice, int volume)
    : date{date}, openingPrice{openingPrice}, closingPrice{closingPrice}, lowPrice{lowPrice}, highPrice{highPrice}, volume{volume} {}

//date, open, high low close, volume
StockData StockData::fromString(const std::string& line) {
    std::vector<std::string> fields = splitLine(line,",");
    std::string date = transformDate(fields[0]);
    double opening = std::stod(fields[1]);
    double high    = std::stod(fields[2]);    
    double low     = std::stod(fields[3]);
    double closing = std::stod(fields[4]);
    long volume    = std::stol(fields[5]);

    return StockData(date, opening, closing, low,  high, volume);
}

double StockData::rateOfReturn(const StockData &previous) {
    return (closingPrice / previous.closingPrice - 1) * 100.0;
}

std::string StockData::transformDate(const std::string& oldDate) {
    std::string result  = oldDate.substr(6,4)+oldDate.substr(0,2) + oldDate.substr(3,2);
    return result;
}

std::ostream& operator<<(std::ostream& out, const StockData& stockData) {
    // Save the stream state
    std::ios oldState(nullptr);
    oldState.copyfmt(out);

    out << std::fixed << std::setprecision(2);
    out << "Date: " << stockData.date
        << ", Opening Price: " << stockData.openingPrice
        << ", High: " << stockData.highPrice
        << ", Low: " << stockData.lowPrice
        << ", Closing Price: " << stockData.closingPrice
        << ", Volume: " << stockData.volume;

    // restore the stream state
    out.copyfmt(oldState);

    return out;
}