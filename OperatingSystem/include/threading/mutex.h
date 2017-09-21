#pragma once

namespace threading {
	class mutex {
	private:
		bool _isLocked;

	public:
		mutex() : _isLocked(false){}

		void acquire();
		void release();
	};
}