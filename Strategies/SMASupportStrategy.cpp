#include "SMASupportStrategy.h"
#include <iostream>

namespace strategies
{
    SMASupportStrategy::SMASupportStrategy(const int period)
        : m_sma(period)
    {
    }

    SMASupportStrategy::~SMASupportStrategy()
    {
        // Destructor
        // Free any dynamically allocated memory if needed
        // No dynamic memory allocation in this class, so nothing
    }

    std::vector<ePosition> SMASupportStrategy::GetExecutionArray(const StockQuote& stockQuote)
    {
        if (stockQuote.IsValid() == false)
        {
            std::cerr << "Invalid stock quote" << std::endl;
            return std::vector<ePosition>();
        }

        // Calculate the moving average
        std::vector<double> movingAverage = m_sma.CalculateMovingAverage(stockQuote);
        std::vector<ePosition> executionArray(movingAverage.size(), HOLD);

        // Implement the strategy logic here
        // Buy when the price is above the moving average and sell when it's below
        const std::vector<double>& closePrices = stockQuote.GetClosePrice();
        bool positionOpen = false;
        for (size_t i = 0; i < closePrices.size(); i++)
        {
            if (movingAverage[i] == 0)
            {
                executionArray[i] = NOT_ENOUGH_DATA; // Not enough data to calculate moving average
                continue; // Skip if moving average is not available
            }

            if (closePrices[i] > movingAverage[i] and not positionOpen)
            {
                positionOpen = true;
                executionArray[i] = BUY;
            }
            else if (closePrices[i] < movingAverage[i] and positionOpen)
            {
                positionOpen = false;
                executionArray[i] = SELL;
            }
        }
        return executionArray;
    }
} // namespace strategies