#pragma once

namespace threading {
	class atomic_bool {
	private:
		dword _value;
	public:
		atomic_bool() :_value(false) {
		}

		bool test_and_set();
	};
}