#pragma once

#include "IStrategy.h"
#include "../Indicators/SimpleMovingAverage.h"
#include "../StockQuote.h"

namespace strategies
{
    class SMASupportStrategy : public IStrategy
    {
    private:
        indicators::SimpleMovingAverage m_sma;
    public:
        SMASupportStrategy(const int period=44);
        ~SMASupportStrategy() override;
        std::vector<ePosition> GetExecutionArray(const StockQuote& quote) override;
    };
} // namespace strategies