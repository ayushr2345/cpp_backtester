#pragma once

#include <vector>
#include "../StockQuote.h"

namespace strategies
{
    enum ePosition
    {
        BUY,
        SELL,
        HOLD,
        NOT_ENOUGH_DATA
    };
    class IStrategy
    {
    public:
        virtual ~IStrategy() = default;
        virtual std::vector<ePosition> GetExecutionArray(const StockQuote&) = 0;
    };
} // namespace strategies
