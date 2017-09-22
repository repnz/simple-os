#pragma once

namespace threading {
	class mutex {
	private:
		bool _isLocked;
		int _id;
	public:
		mutex(int id);
		void lock();
		void release();
	};
}
