#include "stdafx.h"
#include "SDL_ttf.h"
#include "Vista.h"
#include "Mundo.h"
#include "Log.h"
#include "ControlDeColor.h"
#include "Timer.h"


Vista::Vista(Mundo* unMundo, bool* error, bool habilitarAceleracionDeHardware)
{	
	*error = false;
	//VIBRACION
	vibraciones = 0;
	retraso = VIBRACIONES;
	vibracion = false;
	estaVibrando = false;

	//Se inicializa SDLttf
	//int TTF_Init(void);
	//this->fuente = TTF_OpenFont("ima/ttf/Vera.ttf",20);
	// Usa filtro anisotropico
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	// Se inicia SDL_image
	IMG_Init(IMG_INIT_PNG);
	ventana = SDL_CreateWindow(TITULO_VENTANA, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Parser::getInstancia().getVentana().getAnchoPx(), Parser::getInstancia().getVentana().getAltoPx(), SDL_WINDOW_SHOWN);
		if (ventana == nullptr){
			std::string mensaje = "SDL_CreateWindow Error: ";
			const char* elError = SDL_GetError();
			mensaje += elError;
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
			SDL_Quit();
			*error = true;
			return;
		}

		std::string icono(ICONO);
		SDL_Surface* iconoSurf = IMG_Load(icono.c_str());
		SDL_SetWindowIcon(ventana, iconoSurf);

		if (habilitarAceleracionDeHardware)
			renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
		else
			renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);

			if (renderer == nullptr){
				SDL_DestroyWindow(ventana);
				std::string mensaje = "SDL_CreateRenderer Error: ";
				const char* elError = SDL_GetError();
				mensaje += elError;
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
				SDL_Quit();
				*error = true;
				return;
			}			

		for (size_t i = 0; i < Parser::getInstancia().getCapas().size(); i++) 
		{
			std::string imgFondo(Parser::getInstancia().getCapas().at(i)->getImagenFondo());
			SDL_Surface* superficieCapa = cargarSuperficieOptimizada(imgFondo);
			SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, superficieCapa);
			// se queda con la textura libero la superficie
			SDL_FreeSurface(superficieCapa);

			if (tex == nullptr){				
				std::string mensaje = "SDL_CreateTextureFromSurface Error: ";
				const char* elError = SDL_GetError();
				mensaje += elError;
				Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_ERROR);
				*error = true;
				return;
			}

			Parser::getInstancia().getCapas().at(i)->setTexturaSDL(tex);			
		}

		// inicializo la camara en el centro del escenario
		camaraXLog = -Parser::getInstancia().getEscenario().getAncho()/2
			+ Parser::getInstancia().getVentana().getAncho()/2;

		//Creo el número de cuadros en 0,
		numeroDeCuadroUno = 0;
		//y la lista de cuadros puntero a null
		listaDeCuadrosUno = nullptr;

		//Creo el número de cuadros en 0,
		numeroDeCuadroDos = 0;
		//y la lista de cuadros puntero a null
		listaDeCuadrosDos = nullptr;

		//Se cargan los sprites:		
		
		//Dirección de la imagen de Sprites
		std::string dirImgPersonajeUno = Parser::getInstancia().getPersonajes().at(0)->getSpriteDir();
		std::string dirImgPersonajeDos = Parser::getInstancia().getPersonajes().at(1)->getSpriteDir();

		//Carga la imagen desde la ruta especificada
		SDL_Surface* SuperficieUno = cargarSuperficieOptimizada(dirImgPersonajeUno);
		SDL_Surface* SuperficieDos = cargarSuperficieOptimizada(dirImgPersonajeDos);

		//Seteo del color		
		std::string pelea = Parser::getInstancia().getPelea();
		int h_inicio = Parser::getInstancia().getColorAlternativo().at(0);
		int h_final = Parser::getInstancia().getColorAlternativo().at(1);;
		int deplazamiento = Parser::getInstancia().getColorAlternativo().at(2);

		//Tamaño de la imagen
		int ancho = ancho = SuperficieDos->w;
		int alto = ancho = SuperficieDos->h;
		AlfaVida = 200;

		if (!MODO_COLOR){
		//Si ambos personajes son iguales,modifico la superficie
		if ((pelea == "scorpion VS scorpion") || (pelea == "liuKang VS liuKang"))
		{
			ControlDeColor color = ControlDeColor(SuperficieDos);

			//Bloqueo superficie
			if (SDL_MUSTLOCK(SuperficieDos))
			{
				int bloqueoDeSuperficie = SDL_LockSurface(SuperficieDos);
				if (bloqueoDeSuperficie == 0)
				{
					std::cout << "superficie bloqueada con exito";
				}
			}

			//La variable xPixelSuperficie sera la coordenada x en el pixel
			//La variable yPixelSuperficie sera la coordenada y en el pixel 
			for (int xPixelSuperficie = 0; xPixelSuperficie < ancho; xPixelSuperficie++)
			{
				for (int yPixelSuperficie = 0; yPixelSuperficie < alto; yPixelSuperficie++)
				{
					//Convertimos de RGB a HSV
							double hue = color.RGBtoHSV(h_inicio, h_final, deplazamiento, color.getSuperficie(), xPixelSuperficie, yPixelSuperficie);
												
					//Si el hue esta en el rango a cambiar					
					if (hue != -1) 
					{
						double saturation = color.obtenerSaturacion((int)*(color.getRojo()), (int)*(color.getVerde()), (int)*(color.getAzul()));
						double value = color.obtenerBrillo((int)*(color.getRojo()), (int)*(color.getVerde()), (int)*(color.getAzul()));
						//Convertimos los nuevos valores HSV a RGB(devuelve un vector con cada color)
						std::vector<int> nuevosRGB = color.HSVtoRGB(hue,saturation, value);
						//Construye el Uint 32 con el nuevo color r g b
						Uint32 nuevoMapaRGB = SDL_MapRGBA(color.getSuperficie()->format, nuevosRGB.at(0), nuevosRGB.at(1), nuevosRGB.at(2), nuevosRGB.at(3));
						//Coloca los nuevos valores RGB en el pixel
						color.PutPixel(color.getSuperficie(), xPixelSuperficie, yPixelSuperficie, nuevoMapaRGB);                    
					}
				}

			}
			
			// Una vez dibujado procedemos a desbloquear la superficie siempre y cuando hubiese sido bloqueada
			if (SDL_MUSTLOCK(SuperficieDos))
			{
				SDL_UnlockSurface(SuperficieDos);
			}
		}//Fin del if
		}

		//Creación de la textura sobre la superficie
		texturaSpriteUno = SDL_CreateTextureFromSurface(renderer, SuperficieUno);
		texturaSpriteDos = SDL_CreateTextureFromSurface(renderer, SuperficieDos);
		SDL_FreeSurface(SuperficieUno);
		SDL_FreeSurface(SuperficieDos);

		capasVista = Parser::getInstancia().getCapas();
		//Ordeno las capas por su zindex para ser dibujadas
		OrdenarCapas();

		// Se crea textura para dibujar sensores
		SDL_Surface* sup = cargarSuperficieOptimizada("ima/bkg/texturaVerde.png");
		texturaVerde = SDL_CreateTextureFromSurface(renderer, sup);
		SDL_FreeSurface(sup);

		//Textura para la barra de vida
		superficieBarraDeVida = cargarSuperficieOptimizada("ima/bkg/barraDeVida.png");
		texturaBarraDeVida = SDL_CreateTextureFromSurface(renderer, superficieBarraDeVida);
		
		//Textura para la barra de vida roja
		superficieBarraDeVidaRoja = cargarSuperficieOptimizada("ima/bkg/barraDeVidaRoja.png");
		texturaBarraDeVidaRoja = SDL_CreateTextureFromSurface(renderer, superficieBarraDeVidaRoja);

		int anchoBarraDeVida = Parser::getInstancia().getVentana().getAnchoPx() / 2.2;
		int altoBarraDeVida = 12;

		int posXBarraDeVida1 = (Parser::getInstancia().getVentana().getAnchoPx() / 2) - anchoBarraDeVida - 10;
		int posXBarraDeVida2 = Parser::getInstancia().getVentana().getAnchoPx() / 2 + 10;
		
		int posYBarraDeVida = 10;
		int posYBarraDeVidaRoja = 40;

		barraDeVidaImagen1.x = 0;
		barraDeVidaImagen1.y = 0;
		barraDeVidaImagen1.w = superficieBarraDeVida->w;
		barraDeVidaImagen1.h = superficieBarraDeVida->h;
		
		barraRojaDeVidaImagen1.x = 0;
		barraRojaDeVidaImagen1.y = 0;
		barraRojaDeVidaImagen1.w = superficieBarraDeVidaRoja->w;
		barraRojaDeVidaImagen1.h = superficieBarraDeVidaRoja->h;

		SDL_FreeSurface(superficieBarraDeVida);
		SDL_FreeSurface(superficieBarraDeVidaRoja);

		barraDeVidaImagen2 = barraDeVidaImagen1;
		barraRojaDeVidaImagen2 = barraRojaDeVidaImagen1;

		anchoBarraDeVida1 = anchoBarraDeVida;
		anchoBarraDeVida2 = anchoBarraDeVida;

		anchoImagenBarraDeVida = barraDeVidaImagen1.w;

		anchoAnteriorBarra1 = anchoBarraDeVida;
		anchoAnteriorBarra2 = anchoBarraDeVida;

		anchoAnteriorBarraImagen1 = anchoImagenBarraDeVida;
		anchoAnteriorBarraImagen2 = anchoImagenBarraDeVida;

		posBarraDeVida1 = posXBarraDeVida1;
		//Carga de barras de vida
		barraDeVida1 = { posXBarraDeVida1, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };
		barraDeVida2 = { posXBarraDeVida2, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };

		barraRojaDeVida1 = { posXBarraDeVida1, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };
		barraRojaDeVida2 = { posXBarraDeVida2, posYBarraDeVida, anchoBarraDeVida, altoBarraDeVida };

		AlfaInicial = 200;
		AlfaAnterior = 1;
		estadoAnteriorPj1.movimiento = PARADO;
		estadoAnteriorPj2.movimiento = PARADO;
		refMundo = unMundo;

		//Carga efectos de fight (luego reloj)
		SDL_Surface* fight = cargarSuperficieOptimizada("ima/bkg/fight Hd.png");
		this->texturaFight = SDL_CreateTextureFromSurface(renderer, fight);
		SDL_FreeSurface(fight);

		//Carga  textura de round
		SDL_Surface* round = cargarSuperficieOptimizada("ima/bkg/round1.png");
		SDL_SetColorKey(round, SDL_TRUE, SDL_MapRGB(round->format, 255,255,255));
		this->texturaRound = SDL_CreateTextureFromSurface(renderer, round);
		SDL_FreeSurface(round);


		//Tiempo de permanecia en pantalla de efectos
		this->efectosTimer.start();

}


void Vista::actualizar(){

	// referencias más utilizadas al actualizar la vista
	std::vector<Personaje*> personajesVista = Parser::getInstancia().getPersonajes();
	Ventana ventanaVista = Parser::getInstancia().getVentana();

	//Parametros de la ventana

	float anchoVentana = ventanaVista.getAncho();
	int altoVentanaPx = ventanaVista.getAltoPx();

	Personaje* personajeUno = personajesVista[0];
	Personaje* personajeDos = personajesVista[1];

	//Parametros del personaje	
	xPjUno = personajeUno->getPosicionUn().first;
	float anchoPjUno = personajesVista[0]->getAncho();
	xPjDos = personajeDos->getPosicionUn().first;
	float anchoPjDos = personajesVista[1]->getAncho();

	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();

	// Correcion al desplazamiento del personaje que no sobrepase el
	// escenario con su ancho.
	xPjUno *= anchoEscenario / (anchoEscenario + anchoPjUno + 4);

	// Correcion al desplazamiento del personaje que no sobrepase el
	// escenario con su ancho.
	xPjDos *= anchoEscenario / (anchoEscenario + anchoPjDos + 4);

	//Se limpia la pantalla
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// condicion de borde Personaje Uno
	bool PjUnoEstaEnBordeIzq = false;
	bool PjUnoEstaEnBordeDer = false;
	if (xPjUno + anchoPjUno > anchoVentana - camaraXLog)
		PjUnoEstaEnBordeDer = true;
	if (xPjUno < -camaraXLog)
		PjUnoEstaEnBordeIzq = true;
	bool PjUnoEstaEnBorde = PjUnoEstaEnBordeIzq || PjUnoEstaEnBordeDer;

	// condicion de borde Personaje Dos
	bool PjDosEstaEnBordeIzq = false;
	bool PjDosEstaEnBordeDer = false;
	if (xPjDos + anchoPjDos > anchoVentana - camaraXLog)
		PjDosEstaEnBordeDer = true;
	if (xPjDos < -camaraXLog)
		PjDosEstaEnBordeIzq = true;
	bool PjDosEstaEnBorde = PjDosEstaEnBordeIzq || PjDosEstaEnBordeDer;

	MOV_TIPO mov1 = refMundo->getCuerpo(0)->getControlador()->getMovimientos().back();
	MOV_TIPO mov2 = refMundo->getCuerpo(1)->getControlador()->getMovimientos().back();

	if ((PjUnoEstaEnBordeIzq && PjDosEstaEnBordeDer) || (PjDosEstaEnBordeIzq && PjUnoEstaEnBordeDer)) {
		refMundo->FrenarCuerpos();

		if (PjUnoEstaEnBordeIzq && (mov1 == DER))
			refMundo->LiberarCuerpos();

		if (PjUnoEstaEnBordeDer && (mov1 == IZQ))
			refMundo->LiberarCuerpos();

		if (PjDosEstaEnBordeIzq && (mov2 == DER))
			refMundo->LiberarCuerpos();

		if (PjDosEstaEnBordeDer && (mov2 == IZQ))
			refMundo->LiberarCuerpos();
	}


	if (PjUnoEstaEnBorde && !PjDosEstaEnBorde) {
		camaraXLog += personajesVista[0]->getDeltaX();
	}
	if (!PjUnoEstaEnBorde && PjDosEstaEnBorde) {
		camaraXLog += personajesVista[1]->getDeltaX();
	}

	if (PjUnoEstaEnBordeIzq && PjDosEstaEnBordeIzq){
		if ((mov1 == IZQ) && (mov2 == IZQ))
			camaraXLog += personajesVista[0]->getDeltaX();
		else if (mov2 == IZQ)
			camaraXLog += personajesVista[1]->getDeltaX();
		else if (mov1 == IZQ)
			camaraXLog += personajesVista[0]->getDeltaX();
	}

	if (PjUnoEstaEnBordeDer && PjDosEstaEnBordeDer){
		if ((mov1 == DER) && (mov2 == DER))
			camaraXLog += personajesVista[0]->getDeltaX();
		else if (mov2 == DER)
			camaraXLog += personajesVista[1]->getDeltaX();
		else if (mov1 == DER)
			camaraXLog += personajesVista[0]->getDeltaX();
	}

	if (PjUnoEstaEnBordeDer && PjDosEstaEnBordeDer){
		if (mov1 == IZQ)
			camaraXLog += personajesVista[1]->getDeltaX();
	}

	//camaraXLog += personajesVista[0]->getDeltaX();

	//Vibracion de la camara
	if (vibracion){
		bool golpeado = false;
		/*for (int i = 0; i < personajesVista.size(); i++){
			if ((personajesVista.at(i)->getEstado().accion == PATADA_ALTA) && ){
				golpeado = true;
				break;
			}
		}*/
		//Este es el codigo que deberia ir en realidad pero todavia no hay gancho
		if (personajesVista.at(0)->getEstado().golpeado == GOLPEADO){
			if (personajesVista.at(1)->getEstado().accion == PATADA_ALTA){
				golpeado = true;
			}
		}
		else{
			if (personajesVista.at(1)->getEstado().golpeado == GOLPEADO){
				if (personajesVista.at(0)->getEstado().accion == PATADA_ALTA){
				golpeado = true;
				}
			}
		}
		
		if ((personajesVista.at(0)->getEstado().golpeado == GOLPEADO) || (personajesVista.at(1)->getEstado().golpeado == GOLPEADO)){
			AlfaInicial = AlfaInicial - AlfaAnterior;
			if (AlfaInicial < 128){
				AlfaInicial = 200;
			}
			alfa(AlfaInicial);
		}
		else
			alfa(128);
/*		if (golpeado) vibraciones++;
		else vibraciones = 0;*/

		if (golpeado){
			retraso--;
			if (retraso == 0){
				retraso = VIBRACIONES;
				if (!estaVibrando){
					camaraXLog = camaraXLog + 5;
					estaVibrando = true;
				}
				else{
					estaVibrando = false;
					camaraXLog = camaraXLog - 5;
				}
			}
		}
	}
	

	if (!PjUnoEstaEnBorde && !PjDosEstaEnBorde)
		refMundo->LiberarCuerpos();
	
	// Dibuja las capas y el personaje
	Dibujar(personajesVista);

	//Dibuja las barras de vida
	DibujarBarrasDeVida(personajesVista);

	//Se actualiza la pantalla
	SDL_RenderPresent(renderer);
}

SDL_Surface* Vista::cargarSuperficieOptimizada(std::string dirImagen)
{	
	SDL_Surface* superficieOptimizada = NULL;

	//cargo original
	SDL_Surface* superficieOriginal = IMG_Load(dirImagen.c_str());
	if (superficieOriginal == NULL)
		Log::getInstancia().logearMensajeEnModo("No se pudo cargar imagen" + dirImagen, Log::MODO_ERROR);	
	else 
	{	//Optimiza superfice a pantalla
		superficieOptimizada = SDL_ConvertSurface(superficieOriginal, superficieOriginal->format, NULL);
		if (superficieOptimizada == NULL)
			Log::getInstancia().logearMensajeEnModo("No se pudo optimizar imagen" + dirImagen + SDL_GetError(), Log::MODO_ERROR);

		//libero la original
		SDL_FreeSurface(superficieOriginal);
	}

	return superficieOptimizada;
}

void Vista::OrdenarCapas()
{	
	std::vector<Capa*> capasOrdenadas;
	int i = 0;
	while ( capasVista.size() > 0) {
		int minimo = 0;
		for (size_t j = 1; j < capasVista.size(); j++){
			if (capasVista[j]->getZIndex() < capasVista[minimo]->getZIndex()) {
				minimo = j;				
			}
		}		
		capasOrdenadas.push_back(capasVista[minimo]);
		capasVista.erase(capasVista.begin() + minimo);		
	}
	
	capasVista.clear();
	capasVista = capasOrdenadas;
}

void Vista::Dibujar(std::vector<Personaje*> personajesVista)
{
	Ventana ventanaVista = Parser::getInstancia().getVentana();

	float anchoVentana = ventanaVista.getAncho();
	int anchoVentanaPx = ventanaVista.getAnchoPx();
	int altoVentanaPx = ventanaVista.getAltoPx();
	float anchoEscenario = Parser::getInstancia().getEscenario().getAncho();

	DibujarCapasAnteriores(personajesVista, anchoVentana, anchoVentanaPx, altoVentanaPx, anchoEscenario);

	DibujarPersonajes(personajesVista);

	DibujarCapasPosteriores(personajesVista, anchoVentana, anchoVentanaPx, altoVentanaPx, anchoEscenario);
   
	DibujarEfectos(anchoVentana, anchoVentanaPx, altoVentanaPx,anchoEscenario); //Ver si esta en ellugar correcto
	
}

void Vista::alfa(Uint8 alfa){
	AlfaVida = alfa;
}

void Vista::DibujarBarrasDeVida(std::vector<Personaje*> personajesVista)
{
	SDL_SetRenderTarget(renderer, texturaBarraDeVida);
	SDL_SetRenderDrawColor(renderer, 225, 224, 227, AlfaVida);
	SDL_SetTextureAlphaMod(texturaBarraDeVida, AlfaVida);

	int vidaPj1 = personajesVista.at(0)->getVida();
	int vidaPj2 = personajesVista.at(1)->getVida();

	int nuevoAnchoBarraDeVida1 = (vidaPj1 * anchoBarraDeVida1) / 100;
	int nuevoAnchoBarraDeVida2 = (vidaPj2 * anchoBarraDeVida2) / 100;

	int nuevoanchoImagenBarraDeVida1 = (vidaPj1 *anchoImagenBarraDeVida) / 100;
	int nuevoanchoImagenBarraDeVida2 = (vidaPj2 *anchoImagenBarraDeVida) / 100;

	barraDeVida1.w = nuevoAnchoBarraDeVida1;
	barraDeVida2.w = nuevoAnchoBarraDeVida2;

	barraDeVidaImagen1.w = nuevoanchoImagenBarraDeVida1;
	barraDeVidaImagen2.w = nuevoanchoImagenBarraDeVida2;
	barraDeVida1.x = posBarraDeVida1 + anchoBarraDeVida1 - nuevoAnchoBarraDeVida1;

	SDL_RenderCopyEx(renderer, texturaBarraDeVida, &barraDeVidaImagen1, &barraDeVida1, 0, NULL, SDL_FLIP_HORIZONTAL);
	SDL_RenderCopy(renderer, texturaBarraDeVida, &barraDeVidaImagen2, &barraDeVida2);
	SDL_SetRenderTarget(renderer, NULL);

	//Parte barra roja
	SDL_SetRenderTarget(renderer, texturaBarraDeVidaRoja);
	SDL_SetRenderDrawColor(renderer, 215, 12, 25, AlfaVida);
	SDL_SetTextureAlphaMod(texturaBarraDeVidaRoja, AlfaVida);

	barraRojaDeVida2.x = barraDeVida2.x + barraDeVida2.w;
	barraRojaDeVida1.w = anchoAnteriorBarra1 - nuevoAnchoBarraDeVida1;
	barraRojaDeVida2.w = anchoAnteriorBarra2 - nuevoAnchoBarraDeVida2;
	barraRojaDeVida1.x = barraDeVida1.x - barraRojaDeVida1.w;

	barraRojaDeVidaImagen1.x = barraDeVidaImagen1.x + barraDeVidaImagen1.w;
	barraRojaDeVidaImagen2.x = barraDeVidaImagen2.x + barraDeVidaImagen2.w;
	barraRojaDeVidaImagen1.w = anchoAnteriorBarraImagen1 - nuevoanchoImagenBarraDeVida1;
	barraRojaDeVidaImagen2.w = anchoAnteriorBarraImagen2 - nuevoanchoImagenBarraDeVida2;

	//Se setean atributos anteriores para el próximo cuadro.
	if (!(personajesVista.at(0)->getEstado().golpeado == GOLPEADO) && !(personajesVista.at(1)->getEstado().golpeado == GOLPEADO)){
	anchoAnteriorBarra1 = nuevoAnchoBarraDeVida1;
	anchoAnteriorBarra2 = nuevoAnchoBarraDeVida2;

	anchoAnteriorBarraImagen1 = nuevoanchoImagenBarraDeVida1;
	anchoAnteriorBarraImagen2 = nuevoanchoImagenBarraDeVida2;
	}

	SDL_RenderCopyEx(renderer, texturaBarraDeVidaRoja, &barraRojaDeVidaImagen1, &barraRojaDeVida1, 0, NULL, SDL_FLIP_HORIZONTAL);
	SDL_RenderCopy(renderer, texturaBarraDeVidaRoja, &barraRojaDeVidaImagen2, &barraRojaDeVida2);

	SDL_SetRenderTarget(renderer, NULL);
}


void Vista::DibujarCapasAnteriores(std::vector<Personaje*> personajesVista, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };
	//Se cargan las capas anteriores al personaje
	for (size_t i = 0; i < capasVista.size(); i++)
	{
		if (capasVista.at(i)->getZIndex() <= personajesVista[0]->getZIndex()) {
			float anchoCapa = capasVista.at(i)->getAncho();
			camara.w = manejadorULog.darLongPixels(anchoCapa);
			// donde toma la camara a la capa parametrizado con el ancho del escenario	
			camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / (anchoEscenario - anchoVentana));

			SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
		}
	}
}
void Vista::DibujarEfectos(float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camaraFight;
	camaraFight = { (anchoVentanaPx / 3), (altoVentanaPx / 8), (anchoVentanaPx / 2), (altoVentanaPx) / 3 };

	camaraFight.w = manejadorULog.darLongPixels(100);

	// donde toma la camara a la capa parametrizado con el ancho del escenario
	camaraFight.x = manejadorULog.darLongPixels((camaraXLog)*(anchoVentana - 310) / (anchoEscenario - anchoVentana));

	//Si el cronometro de efectos es > 1 segundo y menor a 2 muestra Round.
	//Si es mayor a 2 segundos muestra fight
	//Si es mayor a 4 segundos detiene el cronometro y limpia pantalla
	if ((this->efectosTimer.getTicks() >= 1000) && (this->efectosTimer.getTicks() <= 2000))
	{
		SDL_RenderCopy(renderer, this->texturaRound, NULL, &camaraFight);
	}
	else
	{
		if ((this->efectosTimer.getTicks() > 2000) && (this->efectosTimer.getTicks() <= 4000))
		{
			SDL_DestroyTexture(this->texturaRound);
			SDL_RenderCopy(renderer, this->texturaFight, NULL, &camaraFight);

		}
		else
		{
			if (this->efectosTimer.getTicks() > 4000)
			{
				SDL_DestroyTexture(this->texturaFight);
				this->efectosTimer.stop();
			}
		}

	}
}

void Vista::DibujarCapasPosteriores(std::vector<Personaje*> personajesVista, float anchoVentana, int anchoVentanaPx, int altoVentanaPx, float anchoEscenario)
{
	SDL_Rect camara;
	camara = { 0, 0, anchoVentanaPx, altoVentanaPx };
	//Se cargan las capas posteriores al personaje
	for (size_t i = 0; i < capasVista.size(); i++)
	{
		if (capasVista.at(i)->getZIndex() > personajesVista[0]->getZIndex()) {
			float anchoCapa = capasVista.at(i)->getAncho();
			camara.w = manejadorULog.darLongPixels(anchoCapa);
			// donde toma la camara a la capa parametrizado con el ancho del escenario
			camara.x = manejadorULog.darLongPixels((camaraXLog)*(anchoCapa - anchoVentana) / (anchoEscenario - anchoVentana));
			SDL_RenderCopy(renderer, capasVista.at(i)->getTexturaSDL(), NULL, &camara);
		}
	}
}

void Vista::DibujarPersonajes(std::vector<Personaje*> personajesVista)
{
	//Parámetro para ver si el jugador esta a izquierda o derecha.
	bool invertido = (personajesVista.at(0)->getPosicionPx().first > personajesVista.at(1)->getPosicionPx().first);

	//Parametros del personaje 1
	int anchoPjUnoPx = manejadorULog.darLongPixels(personajesVista[0]->getAncho());
	int altoPjUnoPx = manejadorULog.darLongPixels(personajesVista[0]->getAlto(), Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xPjUnoPx = personajesVista[0]->getPosicionPx().first;
	int yPjUnoPx = personajesVista[0]->getPosicionPx().second;
	float anchoPjUno = personajesVista[0]->getAncho();

	//Parametros del personaje 2
	int anchoPjDosPx = manejadorULog.darLongPixels(personajesVista[1]->getAncho());
	int altoPjDosPx = manejadorULog.darLongPixels(personajesVista[1]->getAlto(), Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xPjDosPx = personajesVista[1]->getPosicionPx().first;
	int yPjDosPx = personajesVista[1]->getPosicionPx().second;
	float anchoPjDos = personajesVista[1]->getAncho();

	// Posicion x del personaje dentro de la camara
	float xLogPjUnoEnCamara = xPjUno + camaraXLog;
	SDL_Rect personajeUno;



	// Posicion x del personaje dentro de la camara
	float xLogPjDosEnCamara = xPjDos + camaraXLog;
	SDL_Rect personajeDos;

	ESTADO estadoAux;
	estadoAux.movimiento = PARADO;
	SDL_Rect* cuadroBase = personajesVista[0]->getSprite()->listaDeCuadros(estadoAux)->at(0);
	float relacionAnchoUno = (float)anchoPjUnoPx / (float)cuadroBase->w;
	float relacionAltoUno = (float)altoPjUnoPx / (float)cuadroBase->h;
	personajeUno.x = manejadorULog.darLongPixels(xLogPjUnoEnCamara);
	personajeUno.y = yPjUnoPx;




	// ancho y alto lo calcula cuadro a cuadro
	ESTADO estadoDelPersonajeUno = personajesVista[0]->getEstado();

	
	float relacionAnchoDos = (float)anchoPjDosPx / (float)cuadroBase->w;
	float relacionAltoDos = (float)altoPjDosPx / (float)cuadroBase->h;
	personajeDos.x = manejadorULog.darLongPixels(xLogPjDosEnCamara);
	personajeDos.y = yPjDosPx;

	ESTADO estadoDelPersonajeDos = personajesVista[1]->getEstado();

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosUno = personajesVista[0]->getSprite()->listaDeCuadros(estadoDelPersonajeUno);
	tiempoSecuenciaSpritesUno = personajesVista[0]->getSprite()->getConstantes(estadoDelPersonajeUno);


	if ((estadoAnteriorPj1.movimiento != estadoDelPersonajeUno.movimiento) || (estadoAnteriorPj1.accion != estadoDelPersonajeUno.accion) || (estadoAnteriorPj1.golpeado != estadoDelPersonajeUno.golpeado)){
		numeroDeCuadroUno = 0;
		estadoAnteriorPj1 = estadoDelPersonajeUno;
	}

	if ((estadoAnteriorPj2.movimiento != estadoDelPersonajeDos.movimiento) || (estadoAnteriorPj2.accion != estadoDelPersonajeDos.accion) || (estadoAnteriorPj2.golpeado != estadoDelPersonajeDos.golpeado)){
		numeroDeCuadroDos = 0;
		estadoAnteriorPj2 = estadoDelPersonajeDos;
	}
	
	if ((numeroDeCuadroUno) > (tiempoSecuenciaSpritesUno*listaDeCuadrosUno->size()))
		numeroDeCuadroUno = 0;

	if (0 >= ((listaDeCuadrosUno->size() - 1) - (numeroDeCuadroUno / tiempoSecuenciaSpritesUno)))
		numeroDeCuadroUno = 0;

	//Renderizar el sprite
	SDL_Rect* cuadroActualUno;
	if (invertido){
		cuadroActualUno = listaDeCuadrosUno->at((listaDeCuadrosUno->size() - 1) - (numeroDeCuadroUno / tiempoSecuenciaSpritesUno));
	}
	else{
		cuadroActualUno = listaDeCuadrosUno->at(numeroDeCuadroUno / (tiempoSecuenciaSpritesUno));
	}

	numeroDeCuadroUno++;

	personajeUno.w = (int)round(relacionAnchoUno*cuadroActualUno->w);
	personajeUno.h = (int)round(relacionAltoUno*cuadroActualUno->h);

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosDos = personajesVista[1]->getSprite()->listaDeCuadros(estadoDelPersonajeDos);
	tiempoSecuenciaSpritesDos = personajesVista[1]->getSprite()->getConstantes(estadoDelPersonajeDos);

	if ((numeroDeCuadroDos) > (tiempoSecuenciaSpritesDos*listaDeCuadrosDos->size()))
		numeroDeCuadroDos = 0;
	
	if (0 >= ((listaDeCuadrosDos->size() - 1) - (numeroDeCuadroDos / tiempoSecuenciaSpritesDos)))
		numeroDeCuadroDos = 0;

	//Renderizar el sprite
	SDL_Rect* cuadroActualDos;
	if (!invertido){
		cuadroActualDos = listaDeCuadrosDos->at((listaDeCuadrosDos->size()-1) - (numeroDeCuadroDos / tiempoSecuenciaSpritesDos));
	}
	else{
		cuadroActualDos = listaDeCuadrosDos->at(numeroDeCuadroDos / (tiempoSecuenciaSpritesDos));
	}
	numeroDeCuadroDos++; 
	
	personajeDos.w = (int)round(relacionAnchoDos*cuadroActualDos->w);
	personajeDos.h = (int)round(relacionAltoDos*cuadroActualDos->h);

	SDL_Rect proyectilUno;
	SDL_Rect proyectilDos;

	//Se cargan posiciones de los proyectiles
	if (!(invertido))
		proyectilUno.x = personajeUno.x + refMundo->getProyectil(1)->getPosicion().first;
	else
		proyectilUno.x = personajeUno.x + manejadorULog.darLongPixels(personajesVista.at(0)->getAncho()) - refMundo->getProyectil(1)->getPosicion().first - refMundo->getProyectil(1)->getAncho();
	proyectilUno.y = personajeUno.y + refMundo->getProyectil(1)->getPosicion().second;
	proyectilUno.w = (int)refMundo->getProyectil(1)->getAncho();
	proyectilUno.h = (int)refMundo->getProyectil(1)->getAlto();

	if (!(invertido))
		proyectilDos.x = personajeDos.x + manejadorULog.darLongPixels(personajesVista.at(1)->getAncho()) - refMundo->getProyectil(2)->getPosicion().first - refMundo->getProyectil(2)->getAncho();
	else
		proyectilDos.x = personajeDos.x + refMundo->getProyectil(2)->getPosicion().first;
	proyectilDos.y = personajeDos.y + refMundo->getProyectil(2)->getPosicion().second;
	proyectilDos.w = (int)refMundo->getProyectil(2)->getAncho();
	proyectilDos.h = (int)refMundo->getProyectil(2)->getAlto();
	
	float auxPj1 = (int)round(((relacionAnchoUno*cuadroActualUno->w) - manejadorULog.darLongPixels(personajesVista.at(0)->getAncho())));
	float auxPj2 = (int)round(((relacionAnchoDos*cuadroActualDos->w) - manejadorULog.darLongPixels(personajesVista.at(1)->getAncho())));

	SDL_Rect PersonajeUnoMovimiento = personajeUno;
	SDL_Rect PersonajeDosMovimiento = personajeDos;
	PersonajeUnoMovimiento.x = personajeUno.x - auxPj1;
	PersonajeDosMovimiento.x = personajeDos.x - auxPj2;

	//Se cargan ambos acorde a su posición relativa
	if (invertido){
		SDL_RenderCopyEx(renderer, texturaSpriteUno, cuadroActualUno, &personajeUno, 0, NULL, SDL_FLIP_HORIZONTAL);
		SDL_RenderCopy(renderer, texturaSpriteDos, cuadroActualDos, &PersonajeDosMovimiento);
	}
	else{
		SDL_RenderCopy(renderer, texturaSpriteUno, cuadroActualUno, &PersonajeUnoMovimiento);
		SDL_RenderCopyEx(renderer, texturaSpriteDos, cuadroActualDos, &personajeDos, 0, NULL, SDL_FLIP_HORIZONTAL);
	}

	if (MODO_DEBUG_SDL){
		SDL_Rect r;
		SDL_Rect r2;
		std::vector<Sensor*>* sensoresCuerpo1 = refMundo->getCuerpo(0)->getSensores();
		std::vector<Sensor*>* sensoresCuerpo2 = refMundo->getCuerpo(1)->getSensores();

		Uint8 Alfa = 128;
		SDL_SetRenderTarget(renderer, texturaVerde);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, Alfa);
		SDL_SetTextureAlphaMod(texturaVerde, Alfa);

		for (unsigned i = 0; i<sensoresCuerpo1->size(); i++){
			if (!(invertido)){
				r.x = sensoresCuerpo1->at(i)->getPosicion().first + personajeUno.x;
			}
			else{
				r.x = personajeUno.x + manejadorULog.darLongPixels(personajesVista.at(0)->getAncho()) - sensoresCuerpo1->at(i)->getPosicion().first - sensoresCuerpo1->at(i)->getAncho();
			}
			r.y = sensoresCuerpo1->at(i)->getPosicion().second + personajeUno.y;
			r.w = sensoresCuerpo1->at(i)->getAncho();
			r.h = sensoresCuerpo1->at(i)->getAlto();
			SDL_RenderCopy(renderer, texturaVerde, NULL, &r);
		}
		for (unsigned i = 0; i < sensoresCuerpo2->size(); i++){
			if (!(invertido)){
				r2.x = personajeDos.x + manejadorULog.darLongPixels(personajesVista.at(1)->getAncho()) - sensoresCuerpo2->at(i)->getPosicion().first - sensoresCuerpo2->at(i)->getAncho();
			}
			else{
				r2.x = sensoresCuerpo2->at(i)->getPosicion().first + personajeDos.x;
			}
			r2.y = sensoresCuerpo2->at(i)->getPosicion().second + personajeDos.y;
			r2.w = sensoresCuerpo2->at(i)->getAncho();
			r2.h = sensoresCuerpo2->at(i)->getAlto();
			SDL_RenderCopy(renderer, texturaVerde, NULL, &r2);
		}
		SDL_RenderCopy(renderer, texturaVerde, NULL, &proyectilUno);
		SDL_RenderCopy(renderer, texturaVerde, NULL, &proyectilDos);

		SDL_SetRenderTarget(renderer, NULL);
	}

}


void Vista::habilitarVibracion(){
	vibracion = true;
}


void Vista::deshabilitarVibracion(){
	vibracion = false;
}


Vista::~Vista()
{
	//TTF_CloseFont(this->fuente);
	SDL_DestroyTexture(texturaSpriteUno);
	SDL_DestroyTexture(texturaSpriteDos);
	SDL_DestroyTexture(texturaVerde);
	SDL_DestroyTexture(texturaBarraDeVida);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);	
    
	//TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
