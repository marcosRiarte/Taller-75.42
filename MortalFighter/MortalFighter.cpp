// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
//#include <windows.h>
#include "MortalFighter.h"
#include "Timer.h"
#include "Sprites.h"


//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int _tmain(int argc, _TCHAR* argv[])
{

#ifdef DEBUGENVENTANA
	cout << "Esta activado el modo DEBUG EN VENTANA, se registra solo por consola" << "\n";
#endif
	bool error;

	int accion = REINICIAR;
	while (accion == REINICIAR){

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
			Log::getInstancia().logearMensajeEnModo("No se puede inicializar SDL, se cierra el programa", Log::MODO_ERROR);
			return  EXIT_FAILURE;
		}

		std::string nombreArchivo(PRUEBA_JSON);
		bool ParseoExitoso = Parser::getInstancia().parsear(nombreArchivo);

		if (!ParseoExitoso) return EXIT_FAILURE; //si el json por defecto fallo, el programa termina

		vector2D vecGravedad(0.0f, GRAVEDAD_Y);	

		/*********************************************************************/
		/*      Inicialización de vista y variables del juego               */
		/*********************************************************************/
		Controlador* controladorUno = Parser::getInstancia().getControlador1();
		Controlador* controladorDos = Parser::getInstancia().getControlador2();

		//Parte de creación inicial.		
		Mundo* unMundo = new Mundo(vecGravedad);
		Vista* unaVista = new Vista(unMundo, &error, true);

		if (error){
			Log::getInstancia().logearMensajeEnModo("Error iniciando SDL con aceleracion de hardware, se iniciara en modo software...", Log::MODO_WARNING);
			delete unaVista;
			Vista* unaVista = new Vista(unMundo, &error, false);
		}
		if (error){
			std::string mensaje = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
			mensaje += ", se cierra el programa";
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
			delete unaVista;
			return  EXIT_FAILURE;
		}

		defCuerpo personaje1 = defCuerpo();
		personaje1.posicion = vector2D((Parser::getInstancia().getEscenario().getAncho() / 2.3), (Parser::getInstancia().getEscenario().getYPiso()));

		Cuerpo *unCuerpo = new Cuerpo(personaje1, controladorUno);
		unCuerpo->recibeObservador(Parser::getInstancia().getPersonajes().at(0));
		unCuerpo->setSensores(unCuerpo->getSprite()->getSensores());
		unCuerpo->setSensoresProyectil(unCuerpo->getSprite()->getSensoresDisparo());

		unMundo->agregarCuerpo(unCuerpo);

		defCuerpo personaje2 = defCuerpo();
		personaje2.posicion = vector2D((float)(Parser::getInstancia().getEscenario().getAncho() / 1.8), (Parser::getInstancia().getEscenario().getYPiso()));

		Cuerpo *otroCuerpo = new Cuerpo(personaje2, controladorDos);
		otroCuerpo->recibeObservador(Parser::getInstancia().getPersonajes().at(1));
		otroCuerpo->setSensores(otroCuerpo->getSprite()->getSensores());
		otroCuerpo->setSensoresProyectil(otroCuerpo->getSprite()->getSensoresDisparo());

		unMundo->agregarCuerpo(otroCuerpo);
					
		//HABILITAR VIBRACION
		unaVista->habilitarVibracion();
		//Timer de cuadros por segundo
		Timer fpsTimer;
		//Timer del corte de cuadros por segundo
		Timer capTimer;

		//Contador de cuadros
		int conteoDeCuadros = 0;
		fpsTimer.start();
		


		/***************************************************************************/
		/*     GAMELOOP															   */
		/***************************************************************************/
		while (true) {
			int estadoUno = controladorUno->cambiar();
			int estadoDos = controladorDos->cambiar();

			if (estadoUno == REINICIAR || estadoDos == REINICIAR){
				break;
			}
			else if (estadoUno == FIN || estadoDos == FIN){
				accion = FIN;
				break;
			};

			//Se inicializa el Timer de corte
			capTimer.start();

			//Calcula y corrije cuadros por segundo
			float avgFPS = conteoDeCuadros / (fpsTimer.getTicks() / 1000.f);
			if (avgFPS > 2000000)
			{
				avgFPS = 0;
			}

			//Se actualiza la pantalla
			int estadoVida = unMundo->Paso(0.13f);
			unaVista->actualizar();

			if (estadoVida == REINICIAR || estadoVida == REINICIAR){
				break;
			}
			else if (estadoVida == FIN || estadoVida == FIN){
				accion = FIN;
				break;
			};

			++conteoDeCuadros;
			
			//Si el cuadro finalizó antes
			int frameTicks = capTimer.getTicks();
			if (frameTicks < MSxCUADRO)
			{
				//Se espera el tiempo que queda
				SDL_Delay((Uint32)round(MSxCUADRO - frameTicks));
			}
		}

		// Se eliminan variables del juego y se libera la memoria
		delete unaVista;
		delete unMundo;
		delete unCuerpo;
		delete controladorUno;
		delete controladorDos;
		Parser::FreeInstancia();

		SDL_Quit();

	}

	return EXIT_SUCCESS;
}



