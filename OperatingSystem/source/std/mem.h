#pragma once

namespace std {

	namespace mem {
		template <typename T>
		T* copy(T* dest, const T* src, int length) 
		{
			for (int i = 0; i < length; ++i) 
			{
				dest[i] = src[i];
			}

			return dest;
		}

		template <typename T>
		T* reverse_copy(T* dest, const T* src, int length) 
		{
			for (int i = length - 1; i >= 0; --i) 
			{
				dest[i] = src[i];
			}

			return dest;
		}

		template <typename T>
		T* set(T* mem, const T& value, int length) 
		{
			while (length != 0) 
			{
				*mem = value;
				++mem;
				--length;
			}

			return mem;
		}

		template <typename T>
		int index_of(const T* mem, const T& value, int length) 
		{
			for (int i = 0; i<length; ++i) 
			{
				if (mem[i] == value) 
				{
					return i;
				}
			}

			return -1;
		}

		template <typename T>
		bool has_value(const T* mem, const T& value, int length) 
		{
			return index_of(mem, value, length) != -1;
		}

		template <typename T>
		void zero(T* mem, int length) 
		{
			byte* addr = (byte*)mem;

			for (int i = 0; i < length * sizeof(T); ++i)
			{
				addr[i] = 0;
			}
		}

		template <typename T>
		void zero(T* mem) 
		{
			zero<T>(mem, 1);
		}
	}


}
