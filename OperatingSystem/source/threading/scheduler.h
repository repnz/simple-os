#pragma once

typedef void(*thread_function)();

namespace threading 
{
	namespace scheduler 
	{
		void initialize();
		void create_thread(thread_function f);
		void thread_exit();
	}
}

