#pragma once

#include "IIndicator.h"
#include <vector>

namespace indicators
{
    class SimpleMovingAverage : public IIndicator
    {
    private:
        u_int16_t           m_period;
        std::vector<double> m_values;
        void Calculate(const StockQuote&) override;
    public:
        SimpleMovingAverage(const int period=44);
        std::vector<double> CalculateMovingAverage(const StockQuote&);
    };
};
