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
#include <iostream>
#include <cstdint>

#include "tortilla.h"

// User defined functions
void delay_us_dummy(std::uint32_t us)
{
	std::cout<<__func__<<"("<<us<<") invoked\n";
}

void delay_ms_dummy(std::uint32_t ms)
{
	std::cout<<__func__<<"("<<ms<<") invoked\n";
}

int main()
{
	tia::Delay delay{delay_ms_dummy, delay_us_dummy};

	// delay.ms(54);
	// delay.us(1);

	delay.ms_(54);
	delay.us_(1);

	return 0;
}
