/**
 * @file spi_example.cpp
 * @author your name (you@domain.com)
 * @brief  Example using tortilla SPI class
 * 		   compile with <g++ -Wall -Wextra -pedantic -std=c++17 -I../ -o bin/spi_example spi_example.cpp>
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
	std::cout<<__func__<<"("<<enable<<") invoked\n";
}

int spi_transfert_dummy(const std::uint8_t *tx_buf, size_t tx_size, std::uint8_t *rx_buf, size_t rx_size)
{
	(void)tx_buf; (void)rx_buf;
	std::cout<<__func__<<"(...,"<<tx_size<<','<<"...,"<<rx_size<<") invoked\n";
	return 0;
}


int main()
{
	std::array<std::uint8_t, 10> tx_buf0, rx_buf0;
	std::array<std::uint8_t, 15> tx_buf1, rx_buf1;

	std::uint8_t dummy_register_address = 0x01; // Slave's register at address 0x01  

	// Create a SPI object
	tia::SPI my_spi {
					spi_transfert_dummy, 
					[](bool enable)	{
						std::cout<<__func__<<"("<<enable<<") invoked\n";
					},
					true }; // setp automatic CS control
	// tia::SPI my_spi{spi_transfert_dummy, spi_cs_dummy, false}; // manual cs control
	
	// Test tia::SPI::writeCs()
	std::cout<<"Test tia::SPI::writeCs()\n";
	my_spi.writeCs(false); // Select the slave

	// Setup tx buffer
	tx_buf0[0] = dummy_register_address;
	tx_buf0[1] = 54; // Dummy data to write to the register (for example, obviously in this example it's 100% fake)

	// Test tia::SPI::transfer() with different sized buffers
	std::cout<<"\nTest tia::SPI::transfer() with different sized buffers\n";
	my_spi.transfer(tx_buf0, rx_buf0);
	my_spi.transfer(tx_buf1, rx_buf0);

	// Test tia::SPI::transfer() with a reference rvalue as tx buffer
	std::cout<<"\nTest tia::SPI::transfer() with a reference rvalue as tx buffer\n";
	my_spi.transfer(std::array<std::uint8_t, 2> {0x04,5} , rx_buf1);

	// Test tia::SPI::transferTx()
	std::cout<<"\nTest tia::SPI::transferTx()\n";
	my_spi.transferTx(tx_buf1);

	// We can use boolean values too
	std::cout<<"\nTest tia::SPI::writeCs() with boolean equivalent values\n";
	my_spi.writeCs(1); // Deselect the slave

	return 0;
}
