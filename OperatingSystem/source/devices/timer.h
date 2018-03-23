#pragma once

namespace devices 
{
	class timer_device
	{
	public:
		static void ignore();
		static void set_handler(void (*on_tick)());
	};
}
