#include "stdafx.h"
#include "Mundo.h"
#include "Parser.h"

Mundo::Mundo()
{

}

Mundo::Mundo(const vector2D& valorGravedad)
{
	yPiso = Parser::getInstancia().getEscenario().getYPiso();
	gravedad = valorGravedad;
	Cuerpos = std::vector<Cuerpo*>();	
}

void Mundo::agregarCuerpo(Cuerpo *unCuerpo)
{
	if (unCuerpo->getNombre() == "proyectil")
		Proyectiles.push_back(unCuerpo);
	else
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

Cuerpo* Mundo::getProyectil(size_t pos)
{
	if (pos < Proyectiles.size())
		return Proyectiles.at(pos);

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

std::pair<float, float> getPosicionAbsSensor(std::pair<float, float> posSensor, Cuerpo* unCuerpo, float anchoDelSensor, float altoDelSensor, bool invertido){
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

	posY = unCuerpo->getPosicion().y + unCuerpo->getRefPersonaje()->getAlto() - manejadorUnidades.darLongUnidades(posSensor.second) - manejadorUnidades.darLongUnidades(altoDelSensor);
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
void Mundo::moverCuerpos(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido){
	if (invertido){
		if (unCuerpo->getEstado().movimiento != CAMINARIZQ)
		unCuerpo->mover(DISTANCIA);
		elOtroCuerpo->mover(-DISTANCIA);
	}
	if (unCuerpo->getEstado().movimiento != CAMINARDER)
	unCuerpo->mover(-DISTANCIA);
	elOtroCuerpo->mover(DISTANCIA);
}

//logica de saltos
//el tipo en el aire -----> mantenerle el estado de salto, sacarle velocidad si se esta por chocar y la logica de bordes
//el tipo tocando piso recien -->chequear superposicion
ESTADO Mundo::ResolverSaltos(float difTiempo, Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos){

	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();

	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad

		if (!elOtroCuerpo->estaEnPiso()){
			if (haySuperposicion(unCuerpo, elOtroCuerpo, invertido)){
				if ((unCuerpo->getEstado().accion == SIN_ACCION) && (elOtroCuerpo->getEstado().accion != SIN_ACCION) && (elOtroCuerpo->getEstado().accion != GUARDIA))
					ResolverGolpiza(elOtroCuerpo, unCuerpo, invertido);
			}
		}

		if ((unCuerpo->getVelocidad().x == 0)){
			nuevoEstado = estadoAnterior;
		}
		else if (unCuerpo->getVelocidad().x > 0)
			nuevoEstado.movimiento = SALTODIAGDER;
		else
			nuevoEstado.movimiento = SALTODIAGIZQ;

		if (unCuerpo->EstaFrenado()){
			unCuerpo->SetVelocidadX(0.0f);
		}

		if (unCuerpo->EstaFrenado()){
		unCuerpo->SetVelocidadX(0.0f);
		
		if ((movimientos->back() == SALTODER)){
			nuevoEstado.movimiento = SALTODIAGDER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
		if ((movimientos->back() == SALTOIZQ)){
			nuevoEstado.movimiento = SALTODIAGIZQ;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
	}
	return nuevoEstado;
}

ESTADO Mundo::ResolverAcciones(float difTiempo, Cuerpo *unCuerpo, Cuerpo* otroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos)
{
	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();
	Sprite* elSprite = unCuerpo->getSprite();

	if (unCuerpo->EstaFrenado()){
		if ((movimientos->back() == ARRIBA)){
			nuevoEstado.movimiento = SALTO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}
		if (movimientos->back() == ABAJO){
			if (unCuerpo->getEstado().accion == GUARDIA)
				nuevoEstado.movimiento = AGACHADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
		if ((movimientos->at(0) == SALTODER)){
			nuevoEstado.movimiento = SALTODIAGDER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0, SALTO_Y));
		}
		if ((movimientos->at(0) == SALTOIZQ)){
			nuevoEstado.movimiento = SALTODIAGIZQ;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0, SALTO_Y));
		}
		if ((movimientos->at(0) == DER)){
			nuevoEstado.movimiento = CAMINARDER;
		}
		if ((movimientos->at(0) == IZQ)){
			nuevoEstado.movimiento = CAMINARIZQ;
		}
		if (movimientos->at(0) == ABAJO){
			nuevoEstado.movimiento = AGACHADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
	}
	else{
		//esto hace que no pueda saltar en el aire
		if (estadoAnterior.movimiento == SALTO || estadoAnterior.movimiento == SALTODIAGDER || estadoAnterior.movimiento == SALTODIAGIZQ)
		{
			unCuerpo->setEstadoAnterior(nuevoEstado);
			//aca frutie dividiendo por 20 por que necesitaba una demora chiquitita
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()) / 10);
		}

		if ((movimientos->back() == DER)){
			nuevoEstado.movimiento = CAMINARDER;
			if (!(invertido)){
				if (!(unCuerpo->EstaSuperpuesto()))
					unCuerpo->mover(DISTANCIA);
			}
			else
				unCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
		}

		if ((movimientos->back() == IZQ)){
			nuevoEstado.movimiento = CAMINARIZQ;
			if (otroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
				unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
			else
				unCuerpo->mover(-DISTANCIA);
		}
		if ((movimientos->back() == ARRIBA)){
			nuevoEstado.movimiento = SALTO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}

		if ((movimientos->back() == SALTODER)){
			nuevoEstado.movimiento = SALTODIAGDER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
				unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}

		if ((movimientos->back() == SALTOIZQ)){
			nuevoEstado.movimiento = SALTODIAGIZQ;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));
		}

	if ((movimientos->back() == ABAJO)){
		nuevoEstado.movimiento = AGACHADO;
		unCuerpo->setEstadoAnterior(nuevoEstado);
	}
	
	if ((movimientos->back() == G_BAJO) && !(unCuerpo->getEstado().accion == GOLPE_BAJO)){
		nuevoEstado.accion = GOLPE_BAJO;
		unCuerpo->setEstadoAnterior(nuevoEstado);
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
	}
	if ((movimientos->back() == P_ALTA) && !(unCuerpo->getEstado().accion == PATADA_ALTA)){
		nuevoEstado.accion = PATADA_ALTA;
		unCuerpo->setEstadoAnterior(nuevoEstado);
		unCuerpo->setDemora(35);
		//unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
	}

	if ((movimientos->back() == P_BAJA) && !(unCuerpo->getEstado().accion == PATADA_BAJA)){
		nuevoEstado.accion = PATADA_BAJA;
		unCuerpo->setEstadoAnterior(nuevoEstado);
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
	}
	if ((movimientos->back() == G_ALTO) && !(unCuerpo->getEstado().accion == GOLPE_ALTO)){
		nuevoEstado.accion = GOLPE_ALTO;
		unCuerpo->setEstadoAnterior(nuevoEstado);
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
	}
	if ((movimientos->back() == ARMA) && !(unCuerpo->getEstado().accion == ARMA_ARROJABLE)){
		nuevoEstado.accion = ARMA_ARROJABLE;
		unCuerpo->setEstadoAnterior(nuevoEstado);
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
	}

	if ((movimientos->back() == DEFENSA)){
		nuevoEstado.movimiento = PARADO;
		nuevoEstado.accion = GUARDIA;
		unCuerpo->setEstadoAnterior(nuevoEstado);
	}

	if ((movimientos->back() == DEFENSA_AGACHADO)){
		nuevoEstado.movimiento = AGACHADO;
		nuevoEstado.accion = GUARDIA;
		unCuerpo->setEstadoAnterior(nuevoEstado);
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
	}

	if ((unCuerpo->getEstado().golpeado == GOLPEADO) && (estadoAnterior.golpeado != GOLPEADO)){
		unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		nuevoEstado.golpeado = GOLPEADO;
		if ((unCuerpo->getRefPersonaje()->descontarVida(unCuerpo->getEstado(), otroCuerpo->getEstado())) == REINICIAR){
			nuevoEstado.golpeado = FALLECIDO;
			std::string mensaje = "Gano personaje " + otroCuerpo->getRefPersonaje()->getNombre();
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_DEBUG);
		}
	}

	if ((movimientos->back() == QUIETO)){
		nuevoEstado.movimiento = PARADO;
		unCuerpo->setEstadoAnterior(nuevoEstado);
	}
	}

	return nuevoEstado;
}

bool Mundo::haySuperposicion(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido)
{
	std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
	std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

	std::pair<float, float> posAbsSensoresOtroCuerpo;
	std::pair<float, float> posAbsSensoresCuerpo;
	for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
		for (unsigned j = 0; j < sensoresOtroCuerpo->size(); j++){
			ManejadorULogicas manejadorUnidades;
			posAbsSensoresOtroCuerpo = getPosicionAbsSensor(sensoresOtroCuerpo->at(j)->getPosicion(), elOtroCuerpo, sensoresOtroCuerpo->at(j)->getAncho(), sensoresOtroCuerpo->at(j)->getAlto(), !invertido);
			posAbsSensoresCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(i)->getPosicion(), unCuerpo, sensoresCuerpo->at(i)->getAncho(), sensoresCuerpo->at(i)->getAlto(), invertido);
			if (hayInterseccion(posAbsSensoresCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAlto()), posAbsSensoresOtroCuerpo, manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAlto()))){
				return true;
			}
		}
	}
	return false;
}

void Mundo::ResolverGolpiza(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido){
	std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
	std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

	std::pair<float, float> posAbsSensoresOtroCuerpo;
	std::pair<float, float> posAbsSensoresCuerpo;

	if (!(unCuerpo->getEstado().accion == SIN_ACCION)){
		for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
			for (unsigned j = 0; j < sensoresOtroCuerpo->size(); j++){
				ManejadorULogicas manejadorUnidades;
				posAbsSensoresOtroCuerpo = getPosicionAbsSensor(sensoresOtroCuerpo->at(j)->getPosicion(), elOtroCuerpo, sensoresOtroCuerpo->at(j)->getAncho(), sensoresOtroCuerpo->at(j)->getAlto(), !invertido);
				posAbsSensoresCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(i)->getPosicion(), unCuerpo, sensoresCuerpo->at(i)->getAncho(), sensoresCuerpo->at(i)->getAlto(), invertido);
				if (!(sensoresCuerpo->at(i)->getHitbox()) && (sensoresOtroCuerpo->at(j)->getHitbox()) && hayInterseccion(posAbsSensoresCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAlto()), posAbsSensoresOtroCuerpo, manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAlto()))){
					ESTADO unEstado = elOtroCuerpo->getEstado();
					unEstado.golpeado = GOLPEADO;
					elOtroCuerpo->notificarObservadores(unEstado);
				}
			}
		}
	}

}

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO nuevoEstado;  //defino estado por defecto Si no es golpeado, si no vas a hacer nada y si no estas en el aire, devuelve esto
	nuevoEstado.movimiento = PARADO;
	nuevoEstado.accion = SIN_ACCION;
	nuevoEstado.golpeado = NOGOLPEADO;
	//Se setea de que cuerpo se esta tratando.
	Cuerpo* elOtroCuerpo;
	if (unCuerpo == Cuerpos.at(0)){
		elOtroCuerpo = Cuerpos.at(1);
	}
	else{
		elOtroCuerpo = Cuerpos.at(0);
	}

	bool invertido;

	if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
		invertido = false;
	else
		invertido = true;

	std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();

	if (unCuerpo->EstaSuperpuesto()){
		moverCuerpos(unCuerpo, elOtroCuerpo, invertido);
	}
	else{
		if (unCuerpo->HayDemora())
		{
			unCuerpo->DisminuirDemora();
			nuevoEstado = unCuerpo->getEstadoAnterior();
		}
		else
		{
			if(unCuerpo->estaEnPiso())
			nuevoEstado = Mundo::ResolverAcciones(difTiempo, unCuerpo, elOtroCuerpo, nuevoEstado, invertido, &movimientos);
			else
			nuevoEstado = Mundo::ResolverSaltos(difTiempo, unCuerpo, elOtroCuerpo, nuevoEstado, invertido, &movimientos);
		}
	}

	ResolverGolpiza(unCuerpo, elOtroCuerpo, invertido);

	if (haySuperposicion(unCuerpo, elOtroCuerpo, invertido) && (unCuerpo->getEstado().accion == SIN_ACCION) && (elOtroCuerpo->getEstado().accion == SIN_ACCION)){
		unCuerpo->Superponer();
	}
	else{
		unCuerpo->Separados();
	}
	unCuerpo->SetSensorActivoStr(nuevoEstado);
	unCuerpo->setEstadoAnterior(nuevoEstado);
	vector2D unaVelocidad = unCuerpo->getVelocidad();
	unCuerpo->sumarPosicion(unaVelocidad * difTiempo);
	unCuerpo->sumarVelocidad(gravedad * difTiempo);
	return nuevoEstado;
}


float Mundo::getYPiso() const
{
	return yPiso;
}
