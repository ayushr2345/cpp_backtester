#include "BuyAndHold.h"

namespace trade
{
    BuyAndHold::BuyAndHold(const StockQuote& stockQuote, double initialCapital)
    {
        m_initialCapital = initialCapital;
        m_stockQuote = std::make_unique<StockQuote>(stockQuote);
    }

    BuyAndHold::~BuyAndHold()
    {
    }

    void BuyAndHold::ExecuteTrade()
    {
        // Buy at the first price
        double buyPrice = m_stockQuote->GetClosePrice()[0];
        int numShares = m_initialCapital / buyPrice;
        double sellPrice = m_stockQuote->GetClosePrice().back();
        double netProfit = (sellPrice - buyPrice) * numShares;
        Position position = { buyPrice, numShares, sellPrice, netProfit, m_initialCapital + netProfit };
        m_positions.push_back(position);
    }

    std::vector<Position> BuyAndHold::GetPositions()
    {
        return m_positions;
    }
} // namespace trade