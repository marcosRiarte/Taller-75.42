
#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
	//Inicializa las variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void Timer::start()
{
	//Arranca el timer
	mStarted = true;

	//Saca de la pausa al timer
	mPaused = false;

	//Tomar el tiempo actual del timer
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//Detiene el Timer
	mStarted = false;

	//Resume su ejecución
	mPaused = false;

	//Limpia las variables del tictac
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	//Si el Timer esta corriendo y no fue pausado
	if (mStarted && !mPaused)
	{
		//Pausa al timer
		mPaused = true;

		//Calcular los ticks que pasaron desde que estuvo pausado
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//Si el Timer esta corriendo y fue pausado
	if (mStarted && mPaused)
	{
		//Quita la Pausa al timer
		mPaused = false;

		//Resetea los tics iniciales
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Resetea los tics pausados
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//El tiempo actual del timer
	Uint32 time = 0;

	//Si el timer esta corriendo
	if (mStarted)
	{
		//Si el timer esta pausado
		if (mPaused)
		{
			//Devuelve el número de tics cuando el timer fue pausado
			time = mPausedTicks;
		}
		else
		{
			//Devuelve el tiempo actual menos el tiempo inicial
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//el Timer esta corriendo y fue pausado o no
	return mStarted;
}

bool Timer::isPaused()
{
	//Timer esta corriendo y fue pausado
	return mPaused && mStarted;
}
