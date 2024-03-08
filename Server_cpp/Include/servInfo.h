#pragma once

#include <cstdint>

/*
Namespace that holds server related constants.
*/
namespace servinfo {
	const std::uint8_t MAX_CLIENTS = 16;
	const std::uint8_t CHANNELS = 2;
	const std::uint16_t PORT = 9999;
	const std::uint32_t POLLINTERVAL = 100;
}