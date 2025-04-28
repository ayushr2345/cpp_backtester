#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include "StockQuote.h"

class QuoteGenerator
{
private:
    std::fstream m_file;
    std::string  m_tickerName;
public:
    QuoteGenerator(const std::string tickerName);
    ~QuoteGenerator();
    bool                        OpenFile(const std::string& fileName);
    void                        CloseFile();
    bool                        ReadLine(std::string& line);
    bool                        ReadToken(std::stringstream& line, std::string& token, char delimiter);
    std::unique_ptr<StockQuote> CreateStockQuote();
};
