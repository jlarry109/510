/**
 * Asset class implementation.
 */

#include "asset.h"
#include <cmath>
#include "matrix.h"
#include <numeric>
#include <assert.h>
#include "utility.h"

/*
 * Default constructor for Asset class.
 * Initializes name, numEntries, timeSeriesRateOfReturn, avgRateOfReturn, and standardDeviation.
 */
Asset::Asset() : name(""), numEntries(1), timeSeriesRateOfReturn(), avgRateOfReturn(0.00), standardDeviation(0.00) {}

/*
 * Constructor for Asset class.
 * Initializes name, numEntries, timeSeriesRateOfReturn, avgRateOfReturn, and standardDeviation with the given name.
 * @param name The name of the asset.
 */
Asset::Asset(const std::string name) : name(name), numEntries(1), timeSeriesRateOfReturn(), avgRateOfReturn(0.00), standardDeviation(0.00) {}

/**
 * Destructor for Asset class: Plain-old data (POD): Don't need to delete anything 
 */
Asset::~Asset() {}

/*
 * Calculate the average rate of return for the asset.
 * @return The average rate of return.
 */
double Asset::calculateAvgReturn() {
    double sum = std::accumulate(timeSeriesRateOfReturn.begin(), timeSeriesRateOfReturn.end(), decltype(timeSeriesRateOfReturn)::value_type(0.0));
    exitWithFailure(timeSeriesRateOfReturn.size() == 0, "Can't compute Average Rate of Return: Division by zero is undefined");
    return sum / timeSeriesRateOfReturn.size();
}

/*
 * Calculate the rate of return for the asset.
 * @param currEntry The current entry.
 * @param prevEntry The previous entry.
 * @return The rate of return.
 */
double Asset::calculateRateOfReturn(const double currEntry, const double prevEntry) {
    assert(numEntries >= 2);
    exitWithFailure(prevEntry == 0, "Can't compute Rate of Return: Division by zero is undefined");
    return currEntry / prevEntry - 1;
}

/*
 * Calculate the standard deviation for the asset.
 * @return The standard deviation.
 */
double Asset::calculateStandardDeviation() {
    assert(timeSeriesRateOfReturn.size() > 1);
    double running_diff = 0.00;
    for (double rate_of_return : timeSeriesRateOfReturn) {
        running_diff += std::pow(rate_of_return - avgRateOfReturn, 2);
    }
    return std::sqrt(running_diff / (timeSeriesRateOfReturn.size() - 1));
}

/*
 * Calculate the covariance between two assets.
 * @param rhs The other asset.
 * @return The covariance.
 */
double Asset::calculateCovariance(const Asset & rhs) {
    exitWithFailure(timeSeriesRateOfReturn.size() == 0, "Can't compute Covariance for zero entities: Division by zero is undefined");
    assert(timeSeriesRateOfReturn.size() == rhs.timeSeriesRateOfReturn.size());
    double running_diffA = 0.0;
    double running_diffB = 0.0;
    double sum_of_products = 0.0;
    for (size_t i = 0; i < timeSeriesRateOfReturn.size(); i++) {
        running_diffA = this->timeSeriesRateOfReturn[i] - this->avgRateOfReturn;
        running_diffB = rhs.timeSeriesRateOfReturn[i] - rhs.avgRateOfReturn;
        sum_of_products += running_diffA * running_diffB;
    }
    return sum_of_products / timeSeriesRateOfReturn.size();
}

/*
 * Calculate the correlation between two assets.
 * @param rhs The other asset.
 * @return The correlation.
 */
double Asset::calculateCorrelation(Asset& rhs) {
    if (this == &rhs) {
        return 1.0;
    }
    double covariance = this->calculateCovariance(rhs);
    double standDeviationLhs = standardDeviation;
    double standDeviationRhs = rhs.standardDeviation;
    exitWithFailure(standDeviationLhs == 0 || standDeviationRhs == 0, "Neither of the two SDs may be of value zero: Division by zero prohibited!");
    return covariance / standDeviationLhs * standDeviationRhs;
}

/*
 * Update the asset with the current and previous entries.
 * @param currEntry The current entry.
 * @param prevEntry The previous entry.
 */
void Asset::updateAsset(const double currEntry, const double prevEntry) {
    numEntries++;
    if (numEntries >= 2) {
        timeSeriesRateOfReturn.push_back(calculateRateOfReturn(currEntry, prevEntry));
        avgRateOfReturn = calculateAvgReturn();
    }
    
    if (timeSeriesRateOfReturn.size() > 1) {
        this->standardDeviation = this->calculateStandardDeviation();
    }
}

/**
 * Get the name of the asset.
 * @return The name of the asset.
 */
std::string Asset::getName() const {
    return name;
}

/**
 * Get the average rate of return for the asset.
 * @return The average rate of return.
 */
double Asset::getAvgRateOfReturn() const {
    return avgRateOfReturn;
}

/**
 * Get the standard deviation for the asset.
 * @return The standard deviation.
 */
double Asset::getStandardDeviation() const {
    return standardDeviation;
}

/**
 * Get the number of entries for the asset.
 * @return The number of entries.
 */
size_t Asset::getNumEntries() const {
    return numEntries;
}
