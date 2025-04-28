#include <stdexcept>
#include <iostream>
#include "IndicatorBasedTrade.h"

namespace trade
{
    IndicatorBasedTrade::IndicatorBasedTrade(const StockQuote& stockQuote, double initialCapital)
    {
        m_initialCapital = initialCapital;
        m_stockQuote = std::make_unique<StockQuote>(stockQuote);
    }

    IndicatorBasedTrade::~IndicatorBasedTrade()
    {
    }

    void IndicatorBasedTrade::ExecuteTrade()
    {
        std::cout << "This method should never be called for IndicatorBasedTrade" << std::endl;
    }

    std::vector<Position> IndicatorBasedTrade::GetPositions()
    {
        return m_positions;
    }

    void IndicatorBasedTrade::ExecuteIndicatorBasedTrade(const eIndicator indicator)
    {
        m_positions.clear();
        m_executionArray.clear();
        
        switch (indicator)
        {
            case SMA_SUPPORT:
            {
                int period = 44;
                // std::cin >> period; 
                ExecuteSimpleMovingAverageTrade(period);
                break;
            }
            case EMA_SUPPORT:
            {
                int period = 20;
                // std::cin >> period; 
                ExecuteExponentialMovingAverageTrade(period);
                break;
            }
            case SMA_CROSSOVER:
                // Implement SMA crossover strategy
                break;
            case EMA_CROSSOVER:
                // Implement EMA crossover strategy
                break;
            case SMA_EMA_CROSSOVER:
                // Implement SMA and EMA crossover strategy
                break;
            case RSI:
                // Implement RSI strategy
                break;
            case MACD:
                // Implement MACD strategy
                break;
            default:
                throw std::invalid_argument("Invalid indicator type");
        }
    }

    void IndicatorBasedTrade::ExecuteSimpleMovingAverageTrade(const int period)
    {
        // Create a strategy object
        strategies::SMASupportStrategy smaSupportStrategy(period);
        // Execute the strategy on the stock quote
        std::vector<strategies::ePosition> executionArray = smaSupportStrategy.GetExecutionArray(*m_stockQuote);
        m_executionArray = executionArray;

        // Execute the trade based on the execution array
        double buyPrice = 0.0;
        double sellPrice = 0.0;
        int numShares = 0;
        double netProfit = 0.0;
        double totalValue = m_initialCapital;
        for (size_t i = 0; i < executionArray.size(); ++i)
        {
            switch (executionArray[i])
            {
                case strategies::BUY:
                {
                    buyPrice = m_stockQuote->GetClosePrice()[i];
                    numShares = totalValue / buyPrice;
                    break;
                }
                case strategies::SELL:
                {
                    sellPrice = m_stockQuote->GetClosePrice()[i];
                    netProfit = (sellPrice - buyPrice) * numShares;
                    totalValue += netProfit;
                    Position position = { buyPrice, numShares, sellPrice, netProfit, totalValue };
                    m_positions.push_back(position);
                    break;
                }
                case strategies::HOLD:
                case strategies::NOT_ENOUGH_DATA:
                {
                    // Do nothing
                    break;
                }
                default:
                {
                    throw std::invalid_argument("Invalid position type in execution array");
                }
            }
        }
    }

    void IndicatorBasedTrade::ExecuteExponentialMovingAverageTrade(const int period)
    {
        // Create a strategy object
        strategies::EMASupportStrategy emaSupportStrategy(period);
        // Execute the strategy on the stock quote
        std::vector<strategies::ePosition> executionArray = emaSupportStrategy.GetExecutionArray(*m_stockQuote);
        m_executionArray = executionArray;

        // Execute the trade based on the execution array
        double buyPrice = 0.0;
        double sellPrice = 0.0;
        int numShares = 0;
        double netProfit = 0.0;
        double totalValue = m_initialCapital;
        for (size_t i = 0; i < executionArray.size(); ++i)
        {
            switch (executionArray[i])
            {
                case strategies::BUY:
                {
                    buyPrice = m_stockQuote->GetClosePrice()[i];
                    numShares = totalValue / buyPrice;
                    break;
                }
                case strategies::SELL:
                {
                    sellPrice = m_stockQuote->GetClosePrice()[i];
                    netProfit = (sellPrice - buyPrice) * numShares;
                    totalValue += netProfit;
                    Position position = { buyPrice, numShares, sellPrice, netProfit, totalValue };
                    m_positions.push_back(position);
                    break;
                }
                case strategies::HOLD:
                case strategies::NOT_ENOUGH_DATA:
                {
                    // Do nothing
                    break;
                }
                default:
                {
                    throw std::invalid_argument("Invalid position type in execution array");
                }
            }
        }
    }
} // namespace trade