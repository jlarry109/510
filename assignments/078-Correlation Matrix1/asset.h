#ifndef __T_ASSET_H___
#define __T_ASSET_H___
#include <string>
#include <vector>
#include "matrix.h"

class Asset {
private:
    std::string name;
    size_t numEntries;
    std::vector<double> timeSeriesRateOfReturn;
    double avgRateOfReturn;
    double standardDeviation;

public:
    Asset();
    Asset(const std::string name);
    //Asset(const std::string name, const size_t _numEntries);
    ~Asset();

    double calculateAvgReturn();
    double calculateRateOfReturn(const double currEntry, const double prevEntry);
    double calculateStandardDeviation();
    double calculateCovariance(const Asset& rhs);
    double calculateCorrelation(Asset& rhs);
    Matrix<double>& createCovarianceMatrix(std::vector<Asset>& assets);
    void updateAsset(const double currEntry, double prevEntry = 1.0);
    std::string getName() const;
    double getAvgRateOfReturn() const;
    double getStandardDeviation() const;
    size_t getNumEntries() const;
};

#endif
