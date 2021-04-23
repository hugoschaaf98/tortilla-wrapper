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
#include <array>

namespace tia // tia is a shortcut for tortilla
{

class SPI
{
public:

	using TransfertFptr = int(*)(const std::uint8_t *tx_buf, size_t tx_size, std::uint8_t *rx_buf, size_t rx_size);
	using ChipSelectFptr = void(*)(bool enable);

	SPI(const TransfertFptr xfer, const ChipSelectFptr cs): cs_f_{cs}, xfer_f_{xfer}
	{ }

	void writeCs(bool enable)
	{
		cs_f_(enable);
	}

	template<std::size_t TxSize, std::size_t RxSize>
	int transfert(std::array<std::uint8_t, TxSize> const &tx_buf, std::array<std::uint8_t, RxSize> &rx_buf)
	{
		return xfer_f_(tx_buf.data(), tx_buf.size(), rx_buf.data(), rx_buf.size());
	}

private :
	ChipSelectFptr cs_f_; 	/// Write the CS line
	TransfertFptr xfer_f_; 	/// Transmit/Receive data through the spi bus
};

} // namespace tia

#endif // TORTILLA_H