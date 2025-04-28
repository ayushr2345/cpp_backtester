#pragma once

#include "IStrategy.h"
#include "../Indicators/ExponentialMovingAverage.h"
#include "../StockQuote.h"

namespace strategies
{
    class EMASupportStrategy : public IStrategy
    {
    private:
        indicators::ExponentialMovingAverage m_ema;
    public:
        EMASupportStrategy(const int period=20);
        ~EMASupportStrategy() override;
        std::vector<ePosition> GetExecutionArray(const StockQuote& quote) override;
    };
} // namespace strategies