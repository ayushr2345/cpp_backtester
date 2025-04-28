#include <iostream>
#include "ExponentialMovingAverage.h"

namespace indicators
{
    ExponentialMovingAverage::ExponentialMovingAverage(const int period):
        m_period     (period),
        m_values     ()
    {
        m_multiplier = 2.0 / (m_period + 1);
    }

    void ExponentialMovingAverage::Calculate(const StockQuote& stockQuote)
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

        // Calculate the simple moving average for the first period
        double sum = 0.0;
        const std::vector<double>& closePrices = stockQuote.GetClosePrice();
        u_int16_t i = 0;
        for (i = 0; i < m_period; i++)
        {
            sum += closePrices[i];
        }
        m_values.push_back((sum + closePrices[i]) / m_period);

        // Calculate the exponential moving average for the rest of the days
        for (size_t i = m_period; i < closePrices.size(); i++)
        {
            double ema = (closePrices[i] * m_multiplier) + (m_values.back() * (1 - m_multiplier));
            m_values.push_back(ema);
        }
    }

    std::vector<double> ExponentialMovingAverage::CalculateMovingAverage(const StockQuote& stockQuote)
    {
        Calculate(stockQuote);
        return m_values;
    }
} // namespace indicators
