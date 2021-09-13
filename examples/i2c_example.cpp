/**
 * @file 	i2c_example.cpp
 * @author 	your name (you@domain.com)
 * @brief  	Example using tortilla I2C class
 * 		   	compile with <g++ -Wall -Wextra -pedantic -std=c++17 -I../ -o bin/i2c_example i2c_example.cpp>
 * @version 0.1
 * @date 	2021-04-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <array>
#include <cstdint>
#include <iostream>

#include "tortilla.h"

int i2cTransfertDummy([[maybe_unused]] std::uint16_t       address,
                      [[maybe_unused]] const std::uint8_t *txBuf,
                      [[maybe_unused]] size_t              txSize,
                      [[maybe_unused]] std::uint8_t *      rxBuf,
                      [[maybe_unused]] size_t              rxSize,
                      [[maybe_unused]] bool                repeated = false)
{
    std::cout << __func__ << "(" << address << ",...," << txSize << ',' << "...," << rxSize << "," << repeated << ") invoked\n";
    return 0;
}

int main()
{
    constexpr std::uint8_t dummyPeripheralAddress = 0x51; // I2C slave's address

    std::array<std::uint8_t, 10> txBuf0, rxBuf0;
    std::array<std::uint8_t, 15> txBuf1, rxBuf1;

    // Create an I2C object
    tia::I2C<i2cTransfertDummy> myI2C{};

    // Setup tx buffer
    txBuf0[0] = 21;
    txBuf0[1] = 54; // Dummy data to write to the slave

    // Test tia::I2C::transfer() with different sized buffers
    std::cout << "\nTest tia::I2C::transfer() with different sized buffers\n";
    myI2C.transfer(dummyPeripheralAddress, txBuf0, rxBuf0);
    myI2C.transfer(dummyPeripheralAddress, txBuf1, rxBuf0, true); // with repeated transfer

    // Test tia::I2C::transfer() with a reference rvalue as tx buffer
    std::cout << "\nTest tia::I2C::transfer() with a reference rvalue as tx buffer\n";
    myI2C.transfer(dummyPeripheralAddress, std::array<std::uint8_t, 2>{0x04, 0x05}, rxBuf1);

    // Test tia::I2C::write()
    std::cout << "\nTest tia::I2C::write()\n";
    myI2C.write(dummyPeripheralAddress, txBuf1);

    // Test tia::I2C::read()
    std::cout << "\nTest tia::I2C::read()\n";
    myI2C.read(dummyPeripheralAddress, rxBuf0);

    // Test tia::I2C::read()
    std::cout << "\nTest tia::I2C::read()\n";
    [[maybe_unused]] auto dummyData = myI2C.read(dummyPeripheralAddress);

    return 0;
}