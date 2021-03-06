// ----------------------------------------------------
// Timer.cpp
// Body for CPU Tick Timer class
// ----------------------------------------------------

#include "Timer.h"
#include "SDL\include\SDL.h"

// ---------------------------------------------
Timer::Timer() {
	//Start();
	running = false;
	started_at = 0;
	stopped_at = 0;
}

// ---------------------------------------------
void Timer::Start() {
	running = true;
	started_at = SDL_GetTicks();
}

// ---------------------------------------------
void Timer::Stop() {
	running = false;
	stopped_at = SDL_GetTicks();
}

// ---------------------------------------------
void Timer::Reset() {
	running = true;
	started_at = SDL_GetTicks();
	stopped_at = 0;
}

// ---------------------------------------------
Uint32 Timer::Read() {
	if(running == true) {
		return SDL_GetTicks() - started_at;
	} else {
		return stopped_at - started_at;
	}
}

// ---------------------------------------------
bool Timer::Compare(Uint32 x) {
	if ((running == true) && (SDL_GetTicks() - started_at > x)) {
		return true;
	}
	return false;
}

bool Timer::CompareMin(Uint32 x) {
	if ((running == true) && (SDL_GetTicks() - started_at < x)) {
		return true;
	}
	return false;
}

// ---------------------------------------------
bool Timer::isRunning() {
	return running;
}


