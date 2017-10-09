#pragma once

namespace devices {
	namespace keyboard {
		typedef void(*handler)(byte scan_code, bool released);
		void initialize(handler e);
		void initialize();

		typedef byte led;

		namespace leds {
			const led scroll_lock = 0;
			const led number_lock = 1;
			const led caps_lock = 2;
		}

		typedef byte result_code;

		namespace results {
			const result_code resend = 0xFE;
			const result_code ack = 0xFA;
			const result_code echo = 0xEE;

		}

		result_code set_rate_and_delay();

		byte get_scan_code_set();

		result_code set_scan_code_set(byte set_id);

		result_code set_leds(byte leds_code);

		result_code echo();


	}
}
