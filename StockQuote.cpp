#include "StockQuote.h"

StockQuote::StockQuote():
    m_isValid     (false),
    m_tickerName  (""),
    m_date        (),
    m_closePrice  (),
    m_openPrice   (),
    m_lowPrice    (),
    m_highPrice   (),
    m_volume      (),
    m_periodInYrs (0),
    m_timeFrame   (_1d)
{
}

StockQuote::~StockQuote()
{
    // Destructor
    // Free any dynamically allocated memory if needed
    // No dynamic memory allocation in this class, so nothing
}

bool StockQuote::IsValid() const
{
    return m_isValid;
}

std::string StockQuote::GetTickerName() const
{
    return m_isValid ? m_tickerName : "";
}

void StockQuote::CreateStockQuote(
    std::string tickerName,
    std::vector<std::string> date,
    std::vector<double> closePrice,
    std::vector<double> openPrice,
    std::vector<double> lowPrice,
    std::vector<double> highPrice,
    std::vector<double> volume)
{
    this->m_tickerName = tickerName;
    this->m_date = date;
    this->m_closePrice = closePrice;
    this->m_openPrice = openPrice;
    this->m_lowPrice = lowPrice;
    this->m_highPrice = highPrice;
    this->m_volume = volume;
    this->m_isValid = true;
}

std::vector<double> StockQuote::GetClosePrice() const
{
    return m_closePrice;
}
