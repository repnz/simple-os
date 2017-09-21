#pragma once

namespace devices {
	namespace keyboard {
		typedef void(*handler)(byte scan_code, bool released);

		void initialize(handler e);
		void initialize();
	}
}
