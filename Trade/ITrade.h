#pragma once

#include <memory>
#include <vector>
#include "../StockQuote.h"

namespace trade
{
    struct Position
    {
        double m_buyPrice;
        int    m_numShares;
        double m_sellPrice;
        double m_netProfit;
        double m_totalValue;
    };

    class ITrade
    {
    protected:
        double                      m_initialCapital;
        std::vector<Position>       m_positions;
        std::unique_ptr<StockQuote> m_stockQuote;
    public:
        virtual ~ITrade() = default;
        virtual void ExecuteTrade() = 0;
        virtual std::vector<Position> GetPositions() = 0;
    };
} // namespace trade