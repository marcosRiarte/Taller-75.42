// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
//#include <windows.h>
#include "MortalFigther.h"
#include "Timer.h"


//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
int _tmain(int argc, _TCHAR* argv[])
{	

	#ifdef DEBUGENVENTANA
			cout << "Esta activado el modo DEBUG EN VENTANA, se registra solo por consola" << "\n";
	#endif


	int accion = REINICIAR;
	while (accion == REINICIAR){
		std::string nombreArchivo(PRUEBA_JSON);
		bool ParseoExitoso= Parser::getInstancia().parsear(nombreArchivo);
		
		if (!ParseoExitoso) return EXIT_FAILURE; //si el json por defecto fallo, el programa termina

		vector2D vecGravedad(0.0f, GRAVEDAD_Y);

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
			Log::getInstancia().logearMensajeEnModo("No se puede inicializar SDL, se cierra el programa", Log::MODO_ERROR);
			return  EXIT_FAILURE;
		}

		/*********************************************************************/
		/*      Inicialización de vista y variables del juego               */
		/*********************************************************************/
		Controlador* controladorUno = Parser::getInstancia().getControlador1();
		Controlador* controladorDos = Parser::getInstancia().getControlador2();

		//Parte de creación inicial.		
		Mundo* unMundo = new Mundo(vecGravedad);
		Vista* unaVista = new Vista(unMundo);
		Cuerpo *unCuerpo = new Cuerpo(defCuerpo(), controladorUno, Parser::getInstancia().getEscenario().getAncho()/2.3);
		unCuerpo->recibeObservador(Parser::getInstancia().getPersonajes().at(0));
		unMundo->agregarCuerpo(unCuerpo);

		Cuerpo *otroCuerpo = new Cuerpo(defCuerpo(), controladorDos, Parser::getInstancia().getEscenario().getAncho()/1.8);
		otroCuerpo->recibeObservador(Parser::getInstancia().getPersonajes().at(1));
		unMundo->agregarCuerpo(otroCuerpo);
		

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
			unaVista->actualizar();
			unMundo->Paso(0.13f);


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

