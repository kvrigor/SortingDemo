/*
 * utils.h
 *
 *  Created on: Apr 15, 2017
 *      Author: paul.rigor
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <windows.h>
#include <ctime>
#include <sstream>
#include <random>
// Returns the amount of milliseconds elapsed since the UNIX epoch.
// Source copied from http://stackoverflow.com/a/1861337/6592879
typedef long long int64; typedef unsigned long long uint64;
uint64 GetTimeMs64()
{
	/* Windows */
	FILETIME ft;
	LARGE_INTEGER li;

	/* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
	 * to a LARGE_INTEGER structure. */
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;

	uint64 ret = li.QuadPart;
	ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
	ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */
	return ret;
}

//Class encapsulating the measurement of elapsed time.
class SimpleTimer
{
	private:
		double _PCFreq_us;
		__int64 _startTicks;
		__int64 _accumulatedTicks;
		bool _timerStarted;
		__int64 GetCounter()
		{
			LARGE_INTEGER counter;
			QueryPerformanceCounter(&counter);
			return counter.QuadPart;
		}

	public:
		SimpleTimer(bool startTimer = false)
		{
			_accumulatedTicks = 0;
			startTimer ? Start() : Reset();
		}
		void Start()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			_PCFreq_us = double(freq.QuadPart)/1000000.0;
			_startTicks = GetCounter();
			_timerStarted = true;
		}
		void Reset()
		{
			_startTicks = 0;
			_timerStarted = false;
			_accumulatedTicks = 0;
		}
		void Pause()
		{
			if (_timerStarted)
			{
				_accumulatedTicks += (GetCounter() - _startTicks);
				_timerStarted = false;
			}
		}
		void Restart()
		{
			Reset();
			Start();
		}
		bool IsRunning() { return _timerStarted; }
		double Elapsed_us()
		{
			if (_timerStarted)
				return (_accumulatedTicks + (GetCounter() - _startTicks)) / _PCFreq_us;
			else
				return _accumulatedTicks / _PCFreq_us;
		}
		std::string Elapsed_us_str()
		{
			std::stringstream elapsedTime;
			elapsedTime<<Elapsed_us();
			return (elapsedTime.str() + " us");
		}
};

class RandomNumGen
{
	private:
		std::mt19937 mersenne_rng;

	public:
		RandomNumGen()
		{
			mersenne_rng.seed(GetTimeMs64());
		}

		int Next(int min, int max)
		{
			std::uniform_int_distribution<int> dist(min, max);
			return dist(mersenne_rng);
		}

};


// Source copied from: http://www.cplusplus.com/articles/4z18T05o/#Windows
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

void SetConsoleBufferHeight(int height)
{
	COORD coord;
	coord.X = 80;
	coord.Y = height;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(Handle, coord);
}

bool IsKeyDown(int vKey)
{
	return (GetAsyncKeyState(vKey) & 0x8000);
}

uint64 GetRandomNumber(uint64 seedValue = GetTimeMs64())
{
	return seedValue+rand();
}

uint64 GetRandomNumber(uint64 maxValue, uint64 seedValue = GetTimeMs64())
{
	return seedValue+rand() % (maxValue + 1);
}

#endif /* UTILS_H_ */
