#include <iostream>
#include <memory>
#include "QuoteGenerator.h"

QuoteGenerator::QuoteGenerator(const std::string tickerName)
    : m_tickerName(tickerName)
{
}

QuoteGenerator::~QuoteGenerator()
{
    // Close the file if it's open
    CloseFile();
}
bool QuoteGenerator::OpenFile(const std::string& fileName)
{
    m_file.open(fileName, std::ios::in);
    if (!m_file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return false;
    }
    return true;
}

void QuoteGenerator::CloseFile()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

bool QuoteGenerator::ReadLine(std::string& line)
{
    if (std::getline(m_file, line))
    {
        return true;
    }
    return false;
}

bool QuoteGenerator::ReadToken(std::stringstream& line, std::string& token, char delimiter)
{
    if (std::getline(line, token, delimiter))
    {
        return true;
    }
    return false;
}

std::unique_ptr<StockQuote> QuoteGenerator::CreateStockQuote()
{
    if (!m_file.is_open())
    {
        std::cerr << "File is not open" << std::endl;
        return nullptr;
    }

    // Check if the file is empty
    if (m_file.peek() == std::ifstream::traits_type::eof())
    {
        std::cerr << "File is empty" << std::endl;
        return nullptr;
    }

    // Start reading the file
    std::string line;

    // Skip the first line (header)
    if (!ReadLine(line))
    {
        std::cerr << "Error reading header line" << std::endl;
        return nullptr;
    }

    // Create a new StockQuote object
    auto stockQuote = std::make_unique<StockQuote>();
    if (!stockQuote)
    {
        std::cerr << "Error creating StockQuote object" << std::endl;
        return nullptr;
    }

    // Data vectors to hold the stock data
    std::vector<std::string> dateVector;
    std::vector<double>      openPriceVector;
    std::vector<double>      lowPriceVector;
    std::vector<double>      highPriceVector;
    std::vector<double>      closePriceVector;
    std::vector<double>      volumeVector;


    // Read the rest of the file
    while (ReadLine(line))
    {
        if (line.empty())
        {
            std::cerr << "Empty line encountered" << std::endl;
            break;
        }
        std::cout << line << std::endl;
        std::stringstream ss(line);
        std::string date, openPrice, lowPrice, highPrice, closePrice, volume;
        ReadToken(ss, date, ',');
        ReadToken(ss, closePrice, ',');
        // ReadToken(ss, openPrice, ',');
        // ReadToken(ss, highPrice, ',');
        // ReadToken(ss, lowPrice, ',');
        // ReadToken(ss, volume, ',');

        // Store the data in the vectors
        dateVector.push_back(date);
        openPriceVector.push_back(openPrice.empty() ? 0.0f : std::stof(openPrice));
        lowPriceVector.push_back(lowPrice.empty() ? 0.0f : std::stof(lowPrice));
        highPriceVector.push_back(highPrice.empty() ? 0.0f : std::stof(highPrice));
        closePriceVector.push_back(closePrice.empty() ? 0.0f : std::stof(closePrice));
        volumeVector.push_back(volume.empty() ? 0.0f : std::stof(volume));
    }

    if (dateVector.empty() || openPriceVector.empty() || lowPriceVector.empty() ||
        highPriceVector.empty() || closePriceVector.empty() || volumeVector.empty())
    {
        std::cerr << "Error: One or more data vectors are empty" << std::endl;
        return nullptr;
    }

    // Create the stock quote
    stockQuote->CreateStockQuote(
        m_tickerName,
        dateVector,
        closePriceVector,
        openPriceVector,
        lowPriceVector,
        highPriceVector,
        volumeVector);
    if (stockQuote->IsValid() == false)
    {
        std::cerr << "Error: Stock quote is not valid" << std::endl;
        return nullptr;
    }
    return stockQuote;
}
