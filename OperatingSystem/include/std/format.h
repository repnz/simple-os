#pragma once

namespace std {
	namespace format {
		int num_to_string(char* buffer, dword number, byte base = 10);
		int num_to_string_reverse(char* buffer, dword number, byte base = 10);

	}
}
