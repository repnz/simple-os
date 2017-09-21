#pragma once

namespace devices {

	namespace timer {
		typedef void(*on_tick)();

		void initialize(on_tick f);

		void initialize();
	}
}
