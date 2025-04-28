#pragma once

#include <string>
#include <vector>

class StockQuote
{
private:
    enum eTimeFrame
    {
        _1m,
        _5m,
        _15m,
        _30m,
        _1h,
        _4h,
        _1d,
        _1w,
        _1M,
    };

    bool                     m_isValid { false };
    std::string              m_tickerName;
    std::vector<std::string> m_date;
    std::vector<double>      m_closePrice;
    std::vector<double>      m_openPrice;
    std::vector<double>      m_lowPrice;
    std::vector<double>      m_highPrice;
    std::vector<double>      m_volume;
    u_int8_t                 m_periodInYrs { 0 };
    eTimeFrame               m_timeFrame   { _1d };
public:
    StockQuote();
    ~StockQuote();

    bool IsValid() const;
    std::string GetTickerName() const;
    void CreateStockQuote(
        std::string tickerName,
        std::vector<std::string> date,
        std::vector<double> closePrice,
        std::vector<double> openPrice,
        std::vector<double> lowPrice,
        std::vector<double> highPrice,
        std::vector<double> volume);
    std::vector<double> GetClosePrice() const;
};
