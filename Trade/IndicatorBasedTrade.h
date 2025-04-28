#pragma once

#include "ITrade.h"
#include "../Strategies/SMASupportStrategy.h"
#include "../Strategies/EMASupportStrategy.h"

namespace trade
{
    enum eIndicator
    {
        SMA_SUPPORT,
        EMA_SUPPORT,
        SMA_CROSSOVER,
        EMA_CROSSOVER,
        SMA_EMA_CROSSOVER,
        RSI,
        MACD
    };

    class IndicatorBasedTrade : public ITrade
    {
    private:
        strategies::SMASupportStrategy     m_smaSupportStrategy;
        strategies::EMASupportStrategy     m_emaSupportStrategy;
        std::vector<strategies::ePosition> m_executionArray;
    public:
        IndicatorBasedTrade(const StockQuote& stockQuote, double initialCapital);
        ~IndicatorBasedTrade();
        void ExecuteTrade() override;
        std::vector<Position> GetPositions() override;
        void ExecuteIndicatorBasedTrade(const eIndicator indicator);
        void ExecuteSimpleMovingAverageTrade(const int period);
        void ExecuteExponentialMovingAverageTrade(const int period);
    };
} // namespace trade
