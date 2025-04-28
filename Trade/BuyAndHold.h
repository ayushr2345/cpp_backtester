#pragma once

#include "ITrade.h"
#include "../StockQuote.h"

namespace trade
{
    class BuyAndHold : public ITrade
    {
    private:
    public:
        BuyAndHold(const StockQuote& stockQuote, double initialCapital);
        ~BuyAndHold();
        void ExecuteTrade() override;
        std::vector<Position> GetPositions() override;
    };
} // namespace trade