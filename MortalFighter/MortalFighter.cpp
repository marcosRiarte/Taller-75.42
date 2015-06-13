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
		// nacho: constantes truchas (-90) para que no se explote cuando les pones ancho 80 a los dos personajes
		personaje1.posicion = vector2D((-90 + Parser::getInstancia().getEscenario().getAncho() / 2), (Parser::getInstancia().getEscenario().getYPiso()));
		personaje1.nombre = Parser::getInstancia().getPelea()->getPersonaje1()->getNombre();

		Cuerpo *unCuerpo = new Cuerpo(personaje1, controladorUno);
		unCuerpo->recibeObservador(Parser::getInstancia().getPelea()->getPersonaje1());
		unCuerpo->setSensores(unCuerpo->getSprite()->getSensores());
		unCuerpo->setSensoresProyectil(unCuerpo->getSprite()->getSensoresDisparo());

		unMundo->agregarCuerpo(unCuerpo);

		defCuerpo personaje2 = defCuerpo();
		// nacho: constantes truchas (10) para que no se explote cuando les pones ancho 80 a los dos personajes
		personaje2.posicion = vector2D((float)(10 + Parser::getInstancia().getEscenario().getAncho() / 2), (Parser::getInstancia().getEscenario().getYPiso()));
		personaje2.nombre = Parser::getInstancia().getPelea()->getPersonaje2()->getNombre();

		Cuerpo *otroCuerpo = new Cuerpo(personaje2, controladorDos);
		Personaje* unPersonaje = Parser::getInstancia().getPelea()->getPersonaje2();
		otroCuerpo->recibeObservador(Parser::getInstancia().getPelea()->getPersonaje2());
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
		/*********************************************************************/
		/*       Sonido - SDL_mixer                                          */
		/*********************************************************************/
		// Se inicializa la librería SDL_Mixer
		// iniciamos el audio a la frecuencia 22hz, 16 bits, 2 canales y un buffer de 4096 
		//(segun el sonido poner mas o menos cantidad de buffer)
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, \
			MIX_DEFAULT_CHANNELS, 4096) < 0) {
			cerr << "Error iniciando SDL_mixer: " << endl;
			exit(1);
		}
		//Se cargan musicas de fondo.
		Mix_Music *musicaCombate = Mix_LoadMUS("./son/mortal64.mid");
		/*Mix_Music *musicaMenu = Mix_LoadMUS("./son/musicaMenu.wma");
		if ((musicaCombate == NULL) || (musicaMenu == NULL))
		{
		cerr << "Falla al cargar la musica de fondo" << endl;
		   exit(1);
		}*/
		//void Mix_RewindMusic();
		int volumenMusica = 80;
		
		Mix_VolumeMusic(volumenMusica);
		//Mix_PlayMusic(musicaCombate,0);//loops  0 normal  -1 infinito
		//Mix_PlayMusic(musicaMenu, 0);
		// volumen de reproducción
		int volumenSonido = 100;
		Sonidos voces = Sonidos();
		voces.cargaSonidoEfectos();
		voces.cargaSonidoLiuKang();
		voces.cargaSonidoScorpion();
		Mix_PlayChannel(1, voces.getSonidoEfectos(0), 0);
		Mix_PlayChannel(2, voces.getSonidoEfectos(1), 0);
		Mix_Chunk *chunk = Mix_LoadWAV("./son/musicaMenu.wav");
		
		// Se establece 3 canales, 0 musica,1 sonido,2 efecto arma o poder,3 efectos de intro,4 daño
		Mix_AllocateChannels(5);
		// Mix_PlayChannelTimed(1, chunk,0,15000);//8000
		//int Mix_FadeInMusciPos(Mix_Music *music, int loops, int ms, double position);
		// Se reproduce el sonido en el canal 1		// 0 para reproducir una sola vez 
		// o -1 para reproducir loop infinito
		Mix_PlayChannel(0,chunk, 0);
		
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
		// Eliminar el sonido y liberar memoria
		//paramos la musica de fondo
		Mix_HaltMusic(); 
		//liberamos la musica
		//Mix_FreeMusic(musicaMenu); 
		Mix_FreeMusic(musicaCombate);
		// Cerrar SDL_mixer
		Mix_CloseAudio();
		SDL_Quit();

	}

	return EXIT_SUCCESS;
}



