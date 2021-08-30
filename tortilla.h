/**
 * @file tortilla.h
 * @author HugoS
 * @brief  Tortilla wrapper
 * @version 0.1
 * @date 2021-04-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TORTILLA_H_
#define TORTILLA_H_

#include <array>
#include <cstddef>
#include <cstdint>

namespace tia // tia is a shortcut for tortilla
{

	//-------------------------------------------------------------------------
	// Delay Wrapper
	//-------------------------------------------------------------------------

	namespace Delay_
	{
		using DelayFunc = void (&)(std::uint32_t);
	}

	template <Delay_::DelayFunc Ms,
			  Delay_::DelayFunc Us>
	struct Delay
	{

		/**
		 * @brief Wait for given number of milliseconds
		 * 
		 * @param ms milliseconds to wait
		 */
		void ms(std::uint32_t ms) { Ms(ms); }

		/**
		 * @brief Wait for given number of microseconds
		 * 
		 * @param us microseconds to wait
		 */
		void us(std::uint32_t us) { Us(us); }
	};

	//-------------------------------------------------------------------------
	// SPI Wrapper
	//-------------------------------------------------------------------------

	namespace SPI_
	{
		using ChipSelectFunc = void (&)(bool);
		using TransferFunc = int (&)(const std::uint8_t *,
									 std::size_t,
									 std::uint8_t *,
									 std::size_t);
	}

	/**
	 * @brief 	Wrapper for SPI bus which enables Chip Select auto control
	 * 
	 * @tparam Xfer 	Your SPI transfer function. This function must perform reads/writes through t
	 *                  he SPI bus and might accept null pointers as data buffers and 0 sized 
	 *                  buffers (for transmit buffer and receive buffer as well).
	 * 
	 * @tparam Cs		Your Chip Select function. This function must write the Chip select line of the SPI slave.
	 */
	template <SPI_::TransferFunc Xfer,
			  SPI_::ChipSelectFunc Cs>
	struct SPI
	{
		/**
		 * @brief Construct a new SPI object
		 * 
		 * @param autoCs
		 */
		SPI(bool autoCs) : autoCs{autoCs}
		{
		}

		SPI() : SPI{false}
		{
		}

		/**
		 * @brief Transfer data through the SPI bus.
		 * 
		 * @tparam TxSize       Tx buffer size (might be null)
		 * @tparam RxSize       Rx buffer size (might be null)
		 * @param txBuf        Buffer containing data to transmit
		 * @param rxBuf        Buffer to hold received data
		 * @return int 
		 */
		template <std::size_t TxSize, std::size_t RxSize>
		int transfer(const std::array<std::uint8_t, TxSize> &txBuf, std::array<std::uint8_t, RxSize> &rxBuf)
		{
			if (int res = 0; autoCs == true)
			{
				writeCs(false);
				res = Xfer(txBuf.data(), txBuf.size(), rxBuf.data(), rxBuf.size());
				writeCs(true);
				return res;
			}
			else
				return Xfer(txBuf.data(), txBuf.size(), rxBuf.data(), rxBuf.size());
		}

		/**
		 * @brief Write through the SPI bus. Ignore received data.
		 * 
		 * @tparam TxSize       Tx buffer size (might be null)
		 * @param txBuf        Buffer containing data to transmit
		 * @return int 
		 */
		template <std::size_t TxSize>
		int transferTx(const std::array<std::uint8_t, TxSize> &txBuf)
		{
			std::array<std::uint8_t, 0> dummy;
			return transfer(txBuf, dummy);
		}

		/**
		 * @brief Write the chip select line
		 * 
		 * @param enable Write Cs low if false, write Cs highif true.
		 */

		void writeCs(bool enable) { Cs(enable); }

		/**
		 * @brief 
		 * 
		 * @param enable 
		 */
		void enableAutoCs(bool enable) { autoCs = enable; };

		bool autoCs; //< Control Chip Select during transferts

	}; // struct SPI

	//-------------------------------------------------------------------------
	// I2C Wrapper
	//-------------------------------------------------------------------------

	namespace I2C_
	{
		using TransferFunc = int (&)(std::uint16_t address,
									 const std::uint8_t *,
									 std::size_t,
									 std::uint8_t *,
									 std::size_t);
	}

	/**
	 * @brief 	Wrapper for I2C bus
	 * 
	 * @tparam Xfer 	Your I2C transfer function. This function must perform reads/writes through t
	 *                  he I2C bus and might accept null pointers as data buffers and 0 sized 
	 *                  buffers (for transmit buffer and receive buffer as well).
	 */
	template <I2C_::TransferFunc Xfer>
	struct I2C
	{
		/**
		 * @brief Transfer data through the I2C bus.
		 * 
		 * @tparam TxSize	Tx buffer size (might be null)
		 * @tparam RxSize	Rx buffer size (might be null)
		 * @param address	8/10 bits slave address
		 * @param txBuf		Buffer containing data to transmit
		 * @param rxBuf		Buffer to hold received data
		 * @return int 
		 */
		template <std::size_t TxSize, std::size_t RxSize>
		int transfer(std::uint16_t address,
					 const std::array<std::uint8_t, TxSize> &txBuf,
					 std::array<std::uint8_t, RxSize> &rxBuf)
		{
			return Xfer(address, txBuf.data(), txBuf.size(), rxBuf.data(), rxBuf.size());
		}

		/**
		 * @brief Write data
		 * 
		 * @tparam TxSize	Tx buffer size (might be null)
		 * @param address	8/10 bits slave address
		 * @param txBuf		Buffer containing data to transmit
		 * @return int 
		 */
		template <std::size_t TxSize>
		int transferTx(std::uint16_t address, const std::array<std::uint8_t, TxSize> &txBuf)
		{
			std::array<std::uint8_t, 0> dummy;
			return transfer(address, txBuf, dummy);
		}

		/**
		 * @brief Write a byte
		 * 
		 * @param address 	8/10 bits slave address
		 * @param byte 		Byte to transmit
		 * @return int 
		 */
		int transferTx(std::uint16_t address, std::uint8_t byte)
		{
			return Xfer(address, nullptr, 0, &byte, 1);
		}

		/**
		 * @brief Receive data
		 * 
		 * @tparam RxSize	Rx buffer size (might be null)
		 * @param address	8/10 bits slave address
		 * @param rxBuf		Buffer in which to store received data
		 * @return int 
		 */
		template <std::size_t RxSize>
		int transferRx(std::uint16_t address, std::array<std::uint8_t, RxSize> &rxBuf)
		{
			std::array<std::uint8_t, 0> dummy;
			return transfer(address, dummy, rxBuf);
		}

		/**
		 * @brief Receive a byte
		 * 
		 * @param address	8/10 bits slave address
		 * @return std::uint8_t The received byte
		 */
		std::uint8_t transferRx(std::uint16_t address)
		{
			std::uint8_t data = 0x00;
			Xfer(address, &data, 1, nullptr, 0);
			return data;
		}

	}; // struct I2C

} // namespace tia

#endif // TORTILLA_H_
