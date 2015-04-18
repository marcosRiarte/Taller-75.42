#pragma once

class Timer
{
public:
	//Inicializa las variables
	Timer();

	//Las diferentes acciones del reloj
	void start();
	void stop();
	void pause();
	void unpause();

	//Da el tiempo del Timer
	Uint32 getTicks();

	//Chequea el status del Timer
	bool isStarted();
	bool isPaused();

private:
	//El tiempo del reloj cuando comenzó el Timer
	Uint32 mStartTicks;

	//Los ticks guardados cuando el Timer fue pausado
	Uint32 mPausedTicks;

	//El estado del Timer
	bool mPaused;
	bool mStarted;
};
