/**
 * @file delay_example.cpp
 * @author your name (you@domain.com)
 * @brief  Example using tortilla Delay class
 * 		   compile with <g++ -Wall -Wextra -pedantic -std=c++17 -I../ -o bin/delay_example delay_example.cpp>
 * @version 0.1
 * @date 2021-04-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <cstdint>
#include <iostream>

#include "tortilla.h"

// User defined functions
void delayUsDummy([[maybe_unused]] std::uint32_t us)
{
    std::cout << __func__ << "(" << us << ") invoked\n";
}

void delayMsDummy([[maybe_unused]] std::uint32_t ms)
{
    std::cout << __func__ << "(" << ms << ") invoked\n";
}

int main()
{
    tia::Delay<delayMsDummy, delayUsDummy> myDelay{};

    myDelay.ms(54);
    myDelay.us(1);

    return 0;
}
