#include "stdafx.h"
#include "Mundo.h"
#include "Parser.h"

Mundo::Mundo()
{

}

Mundo::Mundo(const vector2D& valorGravedad, Sprite* unSprite)
{
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	gravedad = valorGravedad;
	Cuerpos = std::vector<Cuerpo*>();
	elSprite = unSprite;
}

void Mundo::agregarCuerpo(Cuerpo *unCuerpo)
{
	Cuerpos.push_back(unCuerpo);
	ESTADO parado;
	parado.movimiento = PARADO;
	unCuerpo->SetSensorActivoStr(parado);
}

Cuerpo* Mundo::getCuerpo(size_t pos)
{
	if (pos < Cuerpos.size())
		return Cuerpos.at(pos);

	return nullptr;
}

int Mundo::Paso(float difTiempo)
{
	int estadoJuego = CONTINUAR;
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		estadoJuego = Cuerpos.at(i)->notificarObservadores(Resolver(difTiempo, Cuerpos.at(i)));
		if (estadoJuego != CONTINUAR)
			break;
	}
	return estadoJuego;
}

void Mundo::FrenarCuerpos()
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Cuerpos.at(i)->Frenar();		
	}
}

void Mundo::LiberarCuerpos()
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Cuerpos.at(i)->Liberar();		
	}
}

std::pair<float, float> getPosicionAbsSensor(std::pair<float, float> posSensor, Cuerpo* unCuerpo, float anchoDelSensor, bool invertido){
	std::pair<float, float> posicionOtroCuerpo;
	float posX, posY, posFinPj;
	ManejadorULogicas manejadorUnidades;
	if (!(invertido)){
		posX = manejadorUnidades.darLongUnidades(posSensor.first) + unCuerpo->getPosicion().x;
	}
	else{
		posFinPj = unCuerpo->getPosicion().x + unCuerpo->getRefPersonaje()->getAncho();
		posX = posFinPj - manejadorUnidades.darLongUnidades(posSensor.first) - manejadorUnidades.darLongUnidades(anchoDelSensor);
	}

	posY = manejadorUnidades.darLongUnidades(posSensor.second) + unCuerpo->getPosicion().y;
	posicionOtroCuerpo.first = posX;
	posicionOtroCuerpo.second = posY;
	return posicionOtroCuerpo;
}

bool Mundo::hayInterseccion(std::pair<int, int> unaPosicion, int unAncho, int unAlto, std::pair<int, int> otraPos, int otroAncho, int otroAlto){
	if (!((unaPosicion.first >= 0 && unaPosicion.second >= 0) && (unAncho >= 0) && (unAlto >= 0) && (otraPos.first >= 0 && otraPos.second >= 0) && (otroAncho >= 0) && (otroAlto >= 0)))
		return false;
	if ((unaPosicion.first + unAncho < otraPos.first) || (unaPosicion.first > otroAncho + otraPos.first) || (unaPosicion.second + unAlto < otraPos.second) || (unaPosicion.second > otraPos.second + otroAlto)){
		return false;
	}
	return true;
}




// //esto deja personaje estadoactual.golpeado=golpeado si hubo colision  y le aplica demora o si no hubo no setea nada 
ESTADO Mundo::ResolverColisiones(float difTiempo, Cuerpo *unCuerpo, ESTADO nuevoEstado){
	//si llego aca es por que hay una colision.
	// 4 cconsideraciones, me golpearon??,  con que fue?, que estado tengo? por que en base a eso determino que golpeado soy
	// estoy en modo defensa???


	return nuevoEstado;

}

//logica de saltos
//el tipo en el aire -----> mantenerle el estado de salto, sacarle velocidad si se esta por chocar y la logica de bordes
//el tipo tocando piso recien -->chequear superposicion
ESTADO Mundo::ResolverSaltos(float difTiempo, Cuerpo *unCuerpo, ESTADO nuevoEstado){

	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();
	
	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad

	if (!unCuerpo->estaEnPiso()){
		//IMPLEMENTAR determinarsuperposicionenelaire osea si che chocan en el aire
		// si se estan por superponer setvelocidad.x=0
		
		
		//la velocidad puede ser 0 en 2 casos. si el tipo tiene un salto vertical o si estan por chocarse y se les anulo la velocidad en x
		if ((unCuerpo->getVelocidad().x == 0) & (nuevoEstado.movimiento==estadoAnterior.movimiento))
		
		{
			// si es salto, saltodiagizq, saltodiagder lo mantiene. si esta golpeado no importa por que va a ignorar el movimiento y tendra en cuenta el golpeado
			nuevoEstado.movimiento = estadoAnterior.movimiento;
						
		}

		else if (unCuerpo->getVelocidad().x > 0)
			nuevoEstado.movimiento = SALTODIAGDER;
		else
			nuevoEstado.movimiento = SALTODIAGIZQ;
		
		//Si estafrenado, osea si esta en un borde la velocidad en x deberia ser 0
		//igual a esto le falta vuelta de tuerca, al tipo sele debe impedir trasladarse hacia fuera de la ventana no hacia el medio
		unCuerpo->sumarVelocidad(gravedad * difTiempo);
		if (unCuerpo->EstaFrenado()){
			unCuerpo->SetVelocidadX(0.0f);
		}
	}
	else //aca evaluo el caso en el que el tipo acaba de llegar al piso
	{
		if (estadoAnterior.movimiento == SALTO || estadoAnterior.movimiento == SALTODIAGIZQ || estadoAnterior.movimiento == SALTODIAGDER)
		{
			//CHEQUEAR SUPERPOSICION
		//	unCuerpo->DeterminarSuperposicionDeCuerpos(otrcuerpo->posicion)
			
		   //SI HAY SUPERPOSICION // 
		//	unCuerpo->Superponer; //con esto en el proximo resolver lo manda a resolver la superposicion y los separa
		
		
		}
	//SI ESTA ACA Y NO ENTRO AL IF, EL NUEVO ESTADO ES QUIETO

	}
	
	return nuevoEstado;

}

//logica de acciones
//esta es la mas larga, pero es un case... quizas haya que modularizar con pequeños metodos... sino va a quedar un mundo
//RECORDA QUE ACA SOLO ENTRAS SI NO HAY DEMORA APLICADA, OSEA SI NO ESTAS HACIENDO ALGO VOS O SI NO ESTAS GOLPEADO
ESTADO Mundo::ResolverAcciones(float difTiempo, Cuerpo *unCuerpo, ESTADO nuevoEstado)
{
	/*
	IF CAMINAR , evaluar no irse de ventana y escenario. no podes invadir al personaje, si te chocas y no tiene defensa lo arrastras, si tiene defensa lo arrastras menos
	            , si estas en modo defensa no te podes mover.
	IF SALTAR , evaluar si estas frenado, osea en borde, tu velocidad en x tiene que ser 0

	IF GOLPES , evaluar que golpe es y en que lugar estas. quieto, agachado, salto vertical, saltodiagonal
	           //RECORDAR METER EL TEMBLEQUE DE CAMARA EN EL GANCHO


	IF DEFENSA, si no estas en piso no se puede aplicar, si estas en piso y no agachado es defensaquieto sino agachado defensa. evaluar contra estado anterior
	            y ordenes nuevas

	IF AGACHADO para agacharse tenes que estar en piso
	
	
	
	
	
	
	
	*/



	return nuevoEstado;
}

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO nuevoEstado;  //defino estado por defecto Si no es golpeado, si no vas a hacer nada y si no estas en el aire, devuelve esto
	nuevoEstado.movimiento = PARADO;
	nuevoEstado.accion = SIN_ACCION;
	nuevoEstado.golpeado = NOGOLPEADO;

	std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();
	bool invertido; // esto no se que es
	
	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();

	//la superposicion se da:
	// al final de un salto , al final de la caida de un golpe y la activa el metodo resolver saltos
	// o cuando estan los 2 en el aire saltando, en este caso deberia setearse velocidad.x ==0 para que no se toquen
	//
	if (unCuerpo->EstaSuperpuesto()) {
	    
		// resolver superposicion tiene una logica de separacion de personajes que despues detallo 
		//unCuerpo->ResolverSuperposicion();
		
	}
	else{ // NO HAY SUPERPOSICION, LO SIGUIENTE A RESOLVER ES LA COLISION
		
			/*
			if (hayInterseccion()) SEBA FIJATE SI PODES METER TODO LO DE INTERSECCION Y sensores EN UN METODO
			{
				// //esto deja personaje estadoactual.golpeado=golpeado si hubo colision  y le aplica demora o si no hubo no setea nada 
				 nuevoEstado= Mundo::ResolverColisiones(difTiempo, unCuerpo, nuevoEstado);

			}
			*/

			// PASO 3 RESOLVEMOS LA LOGICA DE SALTOS

			//ahora hay que resolver la logica de altura
			//el tipo puede estar saltando, pudo haber sido golpeado, pude estar superponiendose en el aire
			//tanto golpeado como golpeando no nos importa por que analizamos en principio la parte de .movimiento
			// al llegar al piso primero suspender accion de golpe por si esta con una patada boladora
			// y chequear superposicion
		nuevoEstado = Mundo::ResolverSaltos( difTiempo, unCuerpo, nuevoEstado);
		
			//AHORA HAY QUE ANALIZAR SI HAY DEMORA, LA DEMORA PUEDE SER POR UN UN ESTADO ANTERIOR O POR QUE SE APLICO EN EL ESTADO ACTUAL UN GOLPEADO
		    //casos:
		    //llevando a cabo una accion
		    // estoy golpeado
		    // me acaban de golpear
		
		
			//si hay demora
			if (unCuerpo->HayDemora())
			{
				//esta logica esta mal tiene que ser inversa pero no se me ocurre, por ahora dejarlo asi despues se pule
					
				if ((nuevoEstado.golpeado == GOLPEADO) & (estadoAnterior.golpeado != GOLPEADO)); // este caso es recien me golpearon en este if asi que no disminuyo demora

				else // aca entran todos los casos demorados que no sean recien golpeado
				{
				//	unCuerpo->DisminuirDemora();
				//	nuevoEstado = unCuerpo->getEstadoAnterior();
										
				}
				
			}
			
			else //no hay demora,// si llega aca, no esta golpeado y no esta haciendo nada (y voy a evaluar si ahora si va a hacer algo
			{
				nuevoEstado = Mundo::ResolverAcciones(difTiempo, unCuerpo, nuevoEstado);
				
			}// listo todo terminado


				//unCuerpo->setEstadoAnterior(nuevoEstado); //asigno estado actual como anterior para la proxima

			
		}// en esta parte finalizario el resolver

	
	

	/*
	
	 // Si está frenado el cuerpo no lo mueve
	  // CASO ESTA EN PISO y frenado
	// el caso frenado lo maneja la vista es cuando estan en borde... este frenado deberia ser imposibilitar el traslado en el eje x
	// ok esto hay que modularizar, la unica diferencia es que no tiene que tener impulso en el eje x por estar al borde la camara
	// no toccar por 
	else if (unCuerpo->EstaFrenado()){
		unCuerpo->SetVelocidadX(0.0f);
		if ((movimientos.at(0) == ARRIBA)){
			nuevoEstado.movimiento = SALTO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}
		if (movimientos.at(0) == ABAJO){
			if (unCuerpo->getEstado().accion == GUARDIA)
			nuevoEstado.movimiento = AGACHADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
		if ((movimientos.at(0) == SALTODER) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = SALTODIAGDER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}
		if ((movimientos.at(0) == SALTOIZQ) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = SALTODIAGIZQ;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));
		}
		if ((movimientos.at(0) == DER) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = CAMINARDER;
		}
		if ((movimientos.at(0) == IZQ) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = CAMINARIZQ;
		}
		if ((movimientos.at(0) == ABAJO) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = AGACHADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
	}

	*/
	
	//caso en piso no frenado
	
	//esto hace que no pueda saltar en el aire
	if (estadoAnterior.movimiento == SALTO || estadoAnterior.movimiento == SALTODIAGDER || estadoAnterior.movimiento == SALTODIAGIZQ)
	{
		unCuerpo->setEstadoAnterior(nuevoEstado);
		//aca frutie dividiendo por 20 por que necesitaba una demora chiquitita
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()) / 15);
	}

		

		//Se setea de que cuerpo se esta tratando.
		Cuerpo* elOtroCuerpo;
		if (unCuerpo == Cuerpos.at(0)){
			elOtroCuerpo = Cuerpos.at(1);
		}
		else{
			elOtroCuerpo = Cuerpos.at(0);
		}

		if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
			invertido = false;
		else
			invertido = true;

		if ((movimientos.at(0) == DER) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = CAMINARDER;
			if (!(invertido))
				unCuerpo->mover(DISTANCIA);
			else
				unCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
		}


		if ((movimientos.at(0) == IZQ) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = CAMINARIZQ;
			if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
				unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
			else
				unCuerpo->mover(-DISTANCIA);
		}


		if ((movimientos.at(0) == ARRIBA) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = SALTO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}

		if ((movimientos.at(0) == SALTODER) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = SALTODIAGDER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}

		if ((movimientos.at(0) == SALTOIZQ) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = SALTODIAGIZQ;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));
		}

		//xjose estoy mandando fruta, nuevo estado "abajo derecha" y abajo izq???

		if ((movimientos.at(0) == ABAJO) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = AGACHADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}

		//---------------------------------
		//xjose
		//aca hay que aplicar una demora para que reproduzca un tiempo el sprite de patada.
		// ojo, tener en cuenta que la demora se tiene que interrumpir si me barren y quedo golpeado mientras tiraba la patada.

		if ((movimientos.at(0) == G_BAJO) && !(unCuerpo->getEstado().accion == GOLPE_BAJO)){
			nuevoEstado.accion = GOLPE_BAJO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}
		if ((movimientos.at(0) == P_ALTA) && !(unCuerpo->getEstado().accion == PATADA_ALTA)){
			nuevoEstado.accion = PATADA_ALTA;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}

		if ((movimientos.at(0) == P_BAJA) && !(unCuerpo->getEstado().accion == PATADA_BAJA)){
			nuevoEstado.accion = PATADA_BAJA;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}
		if ((movimientos.at(0) == G_ALTO) && !(unCuerpo->getEstado().accion == GOLPE_ALTO)){
			nuevoEstado.accion = GOLPE_ALTO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}
		if ((movimientos.at(0) == ARMA) && !(unCuerpo->getEstado().accion == ARMA_ARROJABLE)){
			nuevoEstado.accion = ARMA_ARROJABLE;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}

		if ((movimientos.at(0) == DEFENSA) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = PARADO;
			nuevoEstado.accion = GUARDIA;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}

		if ((movimientos.at(0) == DEFENSA_AGACHADO) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado.movimiento = AGACHADO;
			nuevoEstado.accion = GUARDIA;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}
		
		if ((unCuerpo->getEstado().golpeado == GOLPEADO) && (estadoAnterior.golpeado != GOLPEADO)){
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
			nuevoEstado.golpeado = GOLPEADO;
			if ((unCuerpo->getRefPersonaje()->descontarVida(unCuerpo->getEstado(), elOtroCuerpo->getEstado())) == REINICIAR)
					nuevoEstado.golpeado = FALLECIDO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			}
				
		std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
		std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

		std::pair<float, float> posAbsSensoresOtroCuerpo;
		std::pair<float, float> posAbsSensoresCuerpo;

		if (!(unCuerpo->getEstado().accion == SIN_ACCION)){
			for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
				for (unsigned j = 0; j < sensoresOtroCuerpo->size(); j++){
						ManejadorULogicas manejadorUnidades;
						posAbsSensoresOtroCuerpo = getPosicionAbsSensor(sensoresOtroCuerpo->at(j)->getPosicion(), elOtroCuerpo, sensoresOtroCuerpo->at(j)->getAncho(), !invertido);
						posAbsSensoresCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(i)->getPosicion(), unCuerpo, sensoresCuerpo->at(i)->getAncho(), invertido);
						if (!(sensoresCuerpo->at(i)->getHitbox()) && (sensoresOtroCuerpo->at(j)->getHitbox()) && hayInterseccion(posAbsSensoresCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAlto()), posAbsSensoresOtroCuerpo, manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAlto()))){
							ESTADO unEstado = elOtroCuerpo->getEstado();
							unEstado.golpeado = GOLPEADO;
							elOtroCuerpo->notificarObservadores(unEstado);
						}
				}
				}
		}

		if (unCuerpo->GetDemora() > 0) {
			unCuerpo->DisminuirDemora();
			nuevoEstado = unCuerpo->getEstadoAnterior();
		}

		if ((movimientos.at(0) == QUIETO) && (unCuerpo->GetDemora() <= 0)){
			nuevoEstado.movimiento = PARADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}

		


	
		unCuerpo->SetSensorActivoStr(nuevoEstado);

		vector2D unaVelocidad = unCuerpo->getVelocidad();

		/// integra posicion	
		unCuerpo->sumarPosicion(unaVelocidad * difTiempo);
		return nuevoEstado;
}


float Mundo::getYPiso() const
{
	return yPiso;
}
