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
#include <array>
#include <cstdint>
#include <iostream>

#include "tortilla.h"

// User defined functions
void spiCsDummy(bool enable)
{
    std::cout << __func__ << "(" << enable << ") invoked\n";
}

int spiTransfertDummy([[maybe_unused]] const std::uint8_t *tx_buf,
                      [[maybe_unused]] size_t              tx_size,
                      [[maybe_unused]] std::uint8_t *      rx_buf,
                      [[maybe_unused]] size_t              rx_size)
{
    std::cout << __func__ << "(...," << tx_size << ',' << "...," << rx_size << ") invoked\n";
    return 0;
}

int main()
{
    constexpr std::uint8_t dummyRegisterAddress = 0x01; // Slave's register at address 0x01

    std::array<std::uint8_t, 10> txBuf0, rxBuf0;
    std::array<std::uint8_t, 15> txBuf1, rxBuf1;

    // Create a SPI object
    tia::SPI<spiTransfertDummy, spiCsDummy> mySpi{true}; // setp automatic CS control
    // tia::SPI<spiTransfertDummy, spiCsDummy> mySpi{false}; // manual cs control

    // Test tia::SPI::writeCs()
    std::cout << "Test tia::SPI::writeCs()\n";
    mySpi.writeCs(false); // Select the slave

    // Setup tx buffer
    txBuf0[0] = dummyRegisterAddress;
    txBuf0[1] = 54; // Dummy data to write to the register (for example, obviously in this example it's 100% fake)

    // Test tia::SPI::transfer() with different sized buffers
    std::cout << "\nTest tia::SPI::transfer() with different sized buffers\n";
    mySpi.transfer(txBuf0, rxBuf0);
    mySpi.transfer(txBuf1, rxBuf0);

    // Test tia::SPI::transfer() with a reference rvalue as tx buffer
    std::cout << "\nTest tia::SPI::transfer() with a reference rvalue as tx buffer\n";
    mySpi.transfer(std::array<std::uint8_t, 2>{0x04, 5}, rxBuf1);

    // Test tia::SPI::transferTx()
    std::cout << "\nTest tia::SPI::transferTx()\n";
    mySpi.write(txBuf1);

    // We can use boolean values too
    std::cout << "\nTest tia::SPI::writeCs() with boolean equivalent values\n";
    mySpi.writeCs(1); // Deselect the slave

    return 0;
}
