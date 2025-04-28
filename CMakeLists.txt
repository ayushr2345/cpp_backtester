cmake_minimum_required(VERSION 3.22)
project(cpp_backtester)

set (CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
    main.cpp
    StockQuote.cpp
    QuoteGenerator.cpp
    Strategies/SMASupportStrategy.cpp
    Strategies/EMASupportStrategy.cpp
    Indicators/SimpleMovingAverage.cpp
    Indicators/ExponentialMovingAverage.cpp
    Trade/BuyAndHold.cpp
    Trade/IndicatorBasedTrade.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})