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
#ifndef TORTILLA_H
#define TORTILLA_H

#include <cstdint>
#include <cstddef>
#include <array>

namespace tia // tia is a shortcut for tortilla
{

/**
 * @brief Delay Wrapper
 * 
 */
struct Delay
{
	using DelayFunc = void(&)(std::uint32_t);

	Delay(DelayFunc delay_ms, DelayFunc delay_us): ms_{delay_ms}, us_{delay_us}
	{}

	/**
	 * @brief Wait for given number of milliseconds
	 * 
	 * @param ms milliseconds to wait
	 */
	// void ms(std::uint32_t ms) { ms_(ms); }

	/**
	 * @brief Wait for given number of microseconds
	 * 
	 * @param us microseconds to wait
	 */
	// void us(std::uint32_t us) { us_(us); }

	DelayFunc ms_;
	DelayFunc us_;
};

/**
 * @brief SPI Wrapper
 * 
 */
struct SPI
{
	using ChipSelectFunc = void(&)(bool);
	using TransferFunc = int(&)(const std::uint8_t*, std::size_t, std::uint8_t*, std::size_t);

	/**
	 * @brief Construct a new SPI object
	 * 
	 * @param xfer 	Your SPI transfer function. This function must perform reads/writes through t
	 * 				he SPI bus and might accept null pointers as data buffers and 0 sized 
	 * 				buffers (for transmit buffer and receive buffer as well).
	 * @param cs 	Your Chip Select function. This function must write the Chip select line of the SPI slave.
	 * @param auto_cs
	 */
	SPI(TransferFunc xfer, ChipSelectFunc cs, bool auto_cs): cs_f{cs}, xfer_f{xfer}, automatic_cs{auto_cs}
	{}
	SPI(TransferFunc xfer, ChipSelectFunc cs): SPI{xfer, cs, false}
	{}

	/**
	 * @brief Transfer data through the SPI bus.
	 * 
	 * @tparam TxSize	Tx buffer size (might be null)
	 * @tparam RxSize 	Rx buffer size (might be null)
	 * @param tx_buf 	Buffer containing data to transmit
	 * @param rx_buf 	Buffer to hold received data
	 * @return int 
	 */
	template<std::size_t TxSize, std::size_t RxSize>
	int transfer(const std::array<std::uint8_t, TxSize>& tx_buf, std::array<std::uint8_t, RxSize>& rx_buf)
	{
		if(int res = 0; automatic_cs == true)
		{
			writeCs(false);
			res = xfer_f(tx_buf.data(), tx_buf.size(), rx_buf.data(), rx_buf.size());
			writeCs(true);
			return res;
		}
		else return xfer_f(tx_buf.data(), tx_buf.size(), rx_buf.data(), rx_buf.size());
	}

	/**
	 * @brief Write through the SPI bus. Ignore received data.
	 * 
	 * @tparam TxSize 	Tx buffer size (might be null)
	 * @param tx_buf 	Buffer containing data to transmit
	 * @return int 
	 */
	template<std::size_t TxSize>
	int transferTx(const std::array<std::uint8_t, TxSize>& tx_buf)
	{
		std::array<std::uint8_t,0> dummy;
		return transfer(tx_buf, dummy);
	}

	/**
	 * @brief Write the chip select line
	 * 
	 * @param enable Write Cs low if false, write Cs highif true.
	 */
	void writeCs(bool enable) { cs_f(enable); }

	/**
	 * @brief 
	 * 
	 * @param enable 
	 */
	void enableAutoCs(bool enable) { automatic_cs = enable; };

	ChipSelectFunc cs_f; 	/// Write the CS line
	TransferFunc xfer_f; 	/// Transmit/Receive data through the spi bus
	bool automatic_cs;		/// Control Chip Select during transferts
};

} // namespace tia

#endif // TORTILLA_H
