#include <iostream>
#include "SimpleMovingAverage.h"

namespace indicators
{
    SimpleMovingAverage::SimpleMovingAverage(const int period):
        m_period (period),
        m_values ()
    {
    }

    void SimpleMovingAverage::Calculate(const StockQuote& stockQuote)
    {
        m_values.clear();
        if (stockQuote.IsValid() == false)
        {
            std::cerr << "Invalid stock quote" << std::endl;
            return;
        }
        // Initial values will be 0 for the first period days
        for (u_int16_t i = 0; i < m_period - 1; i++)
        {
            m_values.push_back(0);
        }

        // Using Sliding Window Technique
        // Calculate the moving average for the first period days
        double sum = 0.0;
        const std::vector<double>& closePrices = stockQuote.GetClosePrice();
        for (u_int16_t i = 0; i < m_period; i++)
        {
            sum += closePrices[i];
        }
        m_values.push_back(sum / m_period);

        size_t pricesSize = closePrices.size();
        // Calculate the moving average for rest of the days
        for (size_t i = m_period; i < pricesSize; i++)
        {
            sum -= closePrices[i - m_period];
            sum += closePrices[i];
            m_values.push_back(sum / m_period);
        }
    }

    std::vector<double> SimpleMovingAverage::CalculateMovingAverage(const StockQuote& stockQuote)
    {
        Calculate(stockQuote);
        return m_values;
    }
} // namespace indicators
