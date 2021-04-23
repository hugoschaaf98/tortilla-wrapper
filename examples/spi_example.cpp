/**
 * @file spi_example.cpp
 * @author your name (you@domain.com)
 * @brief  Example using tortilla SPI class
 * 		   compile with <g++ -Wall -Wextra -std=c++11 -I../ -o spi_example spi_example.cpp>
 * @version 0.1
 * @date 2021-04-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <cstdint>
#include <array>

#include "tortilla.h"

// User defined functions
void spi_cs_dummy(bool enable)
{
	(void)enable;
	std::cout<<__func__<<"() invoked\n";
}

int spi_transfert_dummy(const std::uint8_t *tx_buf, size_t tx_size, std::uint8_t *rx_buf, size_t rx_size)
{
	(void)tx_buf; (void)tx_size; (void)rx_buf; (void)rx_size;
	std::cout<<__func__<<"() invoked\n";
	return 0;
}


int main()
{
	std::array<std::uint8_t, 10> tx_buf0, rx_buf0;
	std::array<std::uint8_t, 15> tx_buf1, rx_buf1;

	tia::SPI my_spi{spi_transfert_dummy, spi_cs_dummy};
	my_spi.writeCs(false);
	my_spi.transfert(tx_buf0, rx_buf0);
	my_spi.transfert(tx_buf1, rx_buf1);
	my_spi.writeCs(1);

	return 0;
}