#pragma once

#include "IIndicator.h"
#include <vector>

namespace indicators
{
    class ExponentialMovingAverage : public IIndicator
    {
    private:
        int                 m_period;
        double              m_multiplier;
        std::vector<double> m_values;
        void Calculate(const StockQuote&) override;
    public:
        ExponentialMovingAverage(const int period=20);
        std::vector<double> CalculateMovingAverage(const StockQuote&);
    };
};
