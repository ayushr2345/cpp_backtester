#pragma once

#include "../StockQuote.h"

namespace indicators
{
    class IIndicator
    {
    public:
        virtual ~IIndicator() = default;
        virtual void Calculate(const StockQuote&) = 0;
    };
} // namespace indicators
