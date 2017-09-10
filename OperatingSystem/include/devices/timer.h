#pragma once

namespace timer {
	typedef void(*on_tick)();

	void initialize(on_tick f);
}