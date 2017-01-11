#pragma once
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> TimePoint;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds Miliseconds;

class Timer
{
protected:
	TimePoint _start;

public:
	Timer()
	{
		_start = Clock::now();
	}

	inline void Restart()
	{
		_start = Clock::now();
	}

	inline int GetElapsedMS()
	{
		auto end = Clock::now();
		Miliseconds duration = std::chrono::duration_cast<Miliseconds>(end - _start);
		return duration.count();
	}
};

