#include <iostream>
#include <memory>
#include "StockQuote.h"
#include "QuoteGenerator.h"
#include "Strategies/SMASupportStrategy.h"
#include "Trade/BuyAndHold.h"
#include "Trade/IndicatorBasedTrade.h"

int main()
{
    // Create a stock quote object
    QuoteGenerator quoteGenerator("NIFTY");
    quoteGenerator.OpenFile("/home/ayushr2345/code/trading-related/cpp_backtester/nifty_35_yrs.csv");
    auto niftyStockQuote = quoteGenerator.CreateStockQuote();
    if (!niftyStockQuote)
    {
        std::cerr << "Error creating stock quote." << std::endl;
        return 1;
    }

    // Check if the stock quote is valid
    if (!niftyStockQuote->IsValid())
    {
        std::cerr << "Invalid stock quote." << std::endl;
        return 1;
    }

    // Implement the Buy and Hold strategy
    trade::BuyAndHold buyAndHoldStrategy(*niftyStockQuote, 100000);
    buyAndHoldStrategy.ExecuteTrade();
    std::vector<trade::Position> positions = buyAndHoldStrategy.GetPositions();
    for (const auto& position : positions)
    {
        std::cout << "Buy Price: " << position.m_buyPrice << ", "
                  << "Number of Shares: " << position.m_numShares << ", "
                  << "Sell Price: " << position.m_sellPrice << ", "
                  << "Net Profit: " << position.m_netProfit << ", "
                  << "Total Value: " << position.m_totalValue << std::endl;
    }
    double buyAndHoldTotalValue = positions.back().m_totalValue;

    trade::IndicatorBasedTrade indicatorBasedTrade(*niftyStockQuote, 100000);
    indicatorBasedTrade.ExecuteIndicatorBasedTrade(trade::SMA_SUPPORT);
    std::vector<trade::Position> indicatorPositions = indicatorBasedTrade.GetPositions();
    double indicatorTotalValueSMASupport = 100000;
    for (const auto& position : indicatorPositions)
    {
        // std::cout << "Buy Price: " << position.m_buyPrice << ", "
        //           << "Number of Shares: " << position.m_numShares << ", "
        //           << "Sell Price: " << position.m_sellPrice << ", "
        //           << "Net Profit: " << position.m_netProfit << ", "
        //           << "Total Value: " << position.m_totalValue << std::endl;
                  indicatorTotalValueSMASupport += position.m_netProfit;
    }

    trade::IndicatorBasedTrade indicatorBasedTradeEMA(*niftyStockQuote, 100000);
    indicatorBasedTradeEMA.ExecuteIndicatorBasedTrade(trade::EMA_SUPPORT);
    std::vector<trade::Position> indicatorPositionsema = indicatorBasedTradeEMA.GetPositions();
    double indicatorTotalValueEMASupport = 100000;
    for (const auto& position : indicatorPositionsema)
    {
        // std::cout << "Buy Price: " << position.m_buyPrice << ", "
        //           << "Number of Shares: " << position.m_numShares << ", "
        //           << "Sell Price: " << position.m_sellPrice << ", "
        //           << "Net Profit: " << position.m_netProfit << ", "
        //           << "Total Value: " << position.m_totalValue << std::endl;
                  indicatorTotalValueEMASupport += position.m_netProfit;
    }
    std::cout << "Total Value after Indicator Based Trading: " << indicatorTotalValueEMASupport << std::endl;
    std::cout << "Total Value after Indicator Based Trading: " << indicatorTotalValueSMASupport << std::endl;
    std::cout << "Total Value after Buy and Hold: " << buyAndHoldTotalValue << std::endl;

    // WE ARE DOING BUY AND SELL INSTANTLY NEED TO CHANGE THE LOGIC FOR GENERATING EXECUTION ARRAY NEED TO GENERATE AFTER THE PERIOD OF MOVING AVERAGE

    // // Create a strategy object
    // strategies::SMASupportStrategy smaSupportStrategy(44);
    // // Execute the strategy on the stock quote
    // std::vector<strategies::ePosition> executionArray = smaSupportStrategy.GetExecutionArray(*niftyStockQuote);
    // for (const auto& position : executionArray)
    // {
    //     switch (position)
    //     {
    //         case strategies::BUY:
    //             std::cout << "BUY" << std::endl;
    //             break;
    //         case strategies::SELL:
    //             std::cout << "SELL" << std::endl;
    //             break;
    //         case strategies::HOLD:
    //             std::cout << "HOLD" << std::endl;
    //             break;
    //     }
    // }

    // Close the file after reading
    quoteGenerator.CloseFile();
    return 0;
}
