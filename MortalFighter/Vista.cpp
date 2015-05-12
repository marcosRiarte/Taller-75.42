#include "stdafx.h"
#include "Vista.h"
#include "Mundo.h"
#include "Log.h"
#include "ControlDeColor.h"


Vista::Vista(Mundo* unMundo, Sprite* unSprite, bool* error)
{	
	*error = false;
	//VIBRACION
	vibraciones = 0;
	vibracion = false;

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

		renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
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

		//Se cargan los sprites
		elSprite = unSprite;
		
		//Dirección de la imagen de Sprites
		dirImgPersonaje = Parser::getInstancia().getPersonajes().at(0)->getSprite();

		//Carga la imagen desde la ruta especificada
		SDL_Surface* SuperficieUno = cargarSuperficieOptimizada(dirImgPersonaje);
		SDL_Surface* SuperficieDos = cargarSuperficieOptimizada(dirImgPersonaje);

		//Seteo del color		
		std::string pelea = Parser::getInstancia().getPelea();
		int h_inicio = Parser::getInstancia().getColorAlternativo().at(0);
		int h_final = Parser::getInstancia().getColorAlternativo().at(1);;
		int deplazamiento = Parser::getInstancia().getColorAlternativo().at(2);

		int xPixelSuperficie = 0;
		int yPixelSuperficie = 0;
		//Si ambos personajes son iguales
		if ((pelea == "scorpion VS scorpion") || (pelea == "liuKang VS liuKang"))
		{
			ControlDeColor color = ControlDeColor(SuperficieDos);
			if (SDL_MUSTLOCK(SuperficieDos))
			{
				int bloqueoDeSuperficie = SDL_LockSurface(SuperficieDos);
				if (bloqueoDeSuperficie == 0)
				{
					std::cout << "superficie bloqueada con exito";
				}
			}

			//La variable xPixelSuperficie sera la coordenada x en el pixel e ira de 0 a 100
			//La variable yPixelSuperficie sera la coordenada y en el pixel e ira de 0 a 100

				for (int xPixelSuperficie = 0; xPixelSuperficie < 100; xPixelSuperficie++)
				  {
					for (int yPixelSuperficie = 0; yPixelSuperficie < 100; yPixelSuperficie++)
					{
						//Convertimos de RGB a HSV
						/*H*/		double hue = color.RGBtoHSV(h_inicio, h_final, deplazamiento, color.getSuperficie(), xPixelSuperficie, yPixelSuperficie);
						/*S*/		double saturation = color.obtenerSaturacion((int)*(color.getRojo()), (int)*(color.getVerde()), (int)*(color.getAzul()));
						/*V*/		double value = color.obtenerBrillo((int)*(color.getRojo()), (int)*(color.getVerde()), (int)*(color.getAzul()));
						
						//Si el hue esta en el rango a cambiar
	
						if (hue != -1)
						{
						//Convertimos los nuevos valores HSV a RGB(devuelve un vector con cada color)
						std::vector<int> nuevosRGB = color.HSVtoRGB(hue, xPixelSuperficie, yPixelSuperficie, saturation, value);
                        
						 //Construye el Uint 32 con el nuevo color r g b
						//PONER EL RGBa
						Uint32 nuevoMapaRGB = SDL_MapRGB(color.getSuperficie()->format, nuevosRGB.at(0), nuevosRGB.at(1), nuevosRGB.at(2));
							 
						//Coloca los nuevos valores RGB en el pixel

						color.PutPixel(color.getSuperficie(), xPixelSuperficie, yPixelSuperficie, nuevoMapaRGB);

						//SDL_SetColorKey(SuperficieDos, SDL_TRUE, SDL_MapRGB(SuperficieDos->format, nuevosRGB.at(0), nuevosRGB.at(1), nuevosRGB.at(2)));
						
						 // Actualizamos la pantalla parar mostrar el cambio
						//SDL_SetColorKey(color.getSuperficie(), SDL_TRUE, nuevoMapaRGB);
						//int flip = SDL_Flip(SuperficieDos);
						}


				}

			}
			
		// Uint8 RGB = SuperficieDos->format->BytesPerPixel; //da un Uint8

		//SDL_SetColorKey(Superficie, SDL_TRUE, SDL_MapRGB(Superficie->format, 0, 0xFF, 0xFF));

			// Uint8 RGB = SuperficieDos->format->BytesPerPixel; //da un Uint8
			//Uint32 sonic = SuperficieDos->format->format;

			// Una vez dibujado procedemos a desbloquear la superficie siempre y cuando hubiese sido bloqueada
			if (SDL_MUSTLOCK(SuperficieDos))
			{
				SDL_UnlockSurface(SuperficieDos);
			}
		}//Fin del if

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

		estadoAnteriorPj1.movimiento = PARADO;
		estadoAnteriorPj2.movimiento = PARADO;
		refMundo = unMundo;
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

	MOV_TIPO mov1 = refMundo->getCuerpo(0)->getControlador()->getMovimientos().at(0);
	MOV_TIPO mov2 = refMundo->getCuerpo(1)->getControlador()->getMovimientos().at(0);

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
		for (int i = 0; i < personajesVista.size(); i++){
			if ((personajesVista.at(i)->getEstado().accion == PATADA_ALTA)){
				golpeado = true;
				break;
			}
		}
		/*Este es el codigo que deberia ir en realidad pero todavia no hay gancho
		if (personajesVista.at(0)->getEstado() == GOLPEADODER){
			if (personajesVista.at(1)->getEstado() == GANCHO_IZQ){
				golpeado = true;
			}
		}
		else {
			if (personajesVista.at(0)->getEstado() == GOLPEADOIZQ){
				if (personajesVista.at(1)->getEstado() == GANCHO_DER){
					golpeado = true;
				}
			}
		}
		else{
			if (personajesVista.at(1)->getEstado() == GOLPEADODER){
				if (personajesVista.at(0)->getEstado() == GANCHO_IZQ){
				golpeado = true;
				}
			}
			else {
				if (personajesVista.at(1)->getEstado() == GOLPEADOIZQ){
					if (personajesVista.at(0)->getEstado() == GANCHO_DER){
						golpeado = true;
					}
				}
			}
		}
		*/

		if (golpeado) vibraciones++;
		else vibraciones = 0;

		if (vibraciones != 0){
			if (vibraciones % 2 == 0){
				camaraXLog = camaraXLog - 5;
			}
			else{
				camaraXLog = camaraXLog + 5;
			}
		}
	}
	

	if (!PjUnoEstaEnBorde && !PjDosEstaEnBorde)
		refMundo->LiberarCuerpos();
	
	// Dibuja las capas y el personaje
	Dibujar(personajesVista);


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
	SDL_Rect* cuadroBase = elSprite->listaDeCuadros(estadoAux)->at(0);
	float relacionAnchoUno = (float)anchoPjUnoPx / (float)cuadroBase->w;
	float relacionAltoUno = (float)altoPjUnoPx / (float)cuadroBase->h;
	

	// ancho y alto lo calcula cuadro a cuadro
	ESTADO estadoDelPersonajeUno = personajesVista[0]->getEstado();

	float relacionAnchoDos = (float)anchoPjDosPx / (float)cuadroBase->w;
	float relacionAltoDos = (float)altoPjDosPx / (float)cuadroBase->h;
	
	ESTADO estadoDelPersonajeDos = personajesVista[1]->getEstado();

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosUno = elSprite->listaDeCuadros(estadoDelPersonajeUno);
	tiempoSecuenciaSpritesUno = elSprite->getConstantes(estadoDelPersonajeUno);


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
	personajeUno.x = manejadorULog.darLongPixels(xLogPjUnoEnCamara);
	personajeUno.y = personajesVista[0]->getPosicionPx(manejadorULog.darLongUnidades(cuadroActualUno->h)).second;

	//Se carga la lista de cuadros que corresponde acorde al estado del personaje.
	listaDeCuadrosDos = elSprite->listaDeCuadros(estadoDelPersonajeDos);

	tiempoSecuenciaSpritesDos = elSprite->getConstantes(estadoDelPersonajeDos);

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
	personajeDos.x = manejadorULog.darLongPixels(xLogPjDosEnCamara);
	personajeDos.y = personajesVista[1]->getPosicionPx(manejadorULog.darLongUnidades(cuadroActualDos->h)).second;

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
	SDL_DestroyTexture(texturaSpriteUno);
	SDL_DestroyTexture(texturaSpriteDos);
	SDL_DestroyTexture(texturaVerde);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(ventana);
	delete elSprite;

	IMG_Quit();
	SDL_Quit();
}
