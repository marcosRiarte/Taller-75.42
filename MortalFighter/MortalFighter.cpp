// MortalFighter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parser.h"
#include "Vista.h"
#include "Mundo.h"
//#include <windows.h>
#include "Controlador.h"
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
		
		if (!ParseoExitoso) return 1; //si el json por defecto fallo, el programa termina

		vector2D vecGravedad(0.0f, GRAVEDAD_Y);

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
			const char* msg = ((std::string)"Error iniciando SDL: ").append(SDL_GetError()).c_str();
			//WARNING WARNING WARNING!!! ACA NO VA UN RETURN 1 ???
		}

		/*********************************************************************/
		/*      Inicialización de vista y variables del juego               */
		/*********************************************************************/
		//Parte de creación inicial.
		Vista* unaVista = new Vista();
		Mundo* unMundo = new Mundo(vecGravedad);
		Cuerpo *unCuerpo = new Cuerpo(defCuerpo());
		unMundo->agregarCuerpo(unCuerpo);

		//Timer de cuadros por segundo
		Timer fpsTimer;
		//Timer del corte de cuadros por segundo
		Timer capTimer;

		//Contador de cuadros
		int conteoDeCuadros = 0;
		fpsTimer.start();

		std::vector<MOV_TIPO> movimientos = std::vector<MOV_TIPO>();



		/*********************************************************************/
		/*       Sonido - SDL_mixer                                          */
		/*********************************************************************/
		// Se inicializa la librería SDL_Mixer
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, \
			MIX_DEFAULT_CHANNELS, 4096) < 0) {
			cerr << "Error iniciando SDL_mixer: " << endl;
			exit(1);
		}

		// Se carga un sonido
		Mix_Chunk *sonido;

		sonido = Mix_LoadWAV("./son/the_who.wav");

		if (sonido == NULL) {

			cerr << "Falla al cargar el sonido" << endl;
			exit(1);

		}

		// volumen de reproducción
		int volumen = 100;

		Mix_VolumeChunk(sonido, volumen);

		// Se establece 2 canales
		Mix_AllocateChannels(2);

		// Se reproduce el sonido en el canal 1
		// 0 para reproducir una sola vez 
		// o -1 para reproducir loop infinito
		Mix_PlayChannel(1, sonido, 0);

		/**************************************************************************/
		/**************************************************************************/
		

		/***************************************************************************/
		/*     GAMELOOP															   */
		/***************************************************************************/
		while (true) {
			int estado = Controlador::cambiar(&movimientos);
			if (estado == REINICIAR){
				break;
			}
			else if (estado == FIN){
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
			unaVista->actualizar(Parser::getInstancia().getPersonaje().getEstado());
			unMundo->Paso(0.13f, &movimientos);


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
		Parser::FreeInstancia();
		
		// Eliminar el sonido y liberar memoria
		Mix_FreeChunk(sonido);

		// Cerrar SDL_mixer
		Mix_CloseAudio();

		SDL_Quit();
		
	}

	return 0;
}

