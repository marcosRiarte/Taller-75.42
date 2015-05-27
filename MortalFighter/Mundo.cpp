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
	cambioGolpeAlto = false;
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

Sensor* Mundo::getProyectil(size_t pos)
{
	if (pos == 1)
		return Cuerpos.at(0)->getSensoresProyectil().at(0);
	if (pos == 2)
		return Cuerpos.at(1)->getSensoresProyectil().at(0);
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
	Sprite* elSprite = unCuerpo->getSprite();

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

bool Mundo::hayInterseccion(std::pair<float, float> unaPosicion, float unAncho, float unAlto, std::pair<float, float> otraPos, float otroAncho, float otroAlto){
	if ((unaPosicion.first + unAncho < otraPos.first) || (unaPosicion.first > otroAncho + otraPos.first) || (unaPosicion.second + unAlto < otraPos.second) || (unaPosicion.second > otraPos.second + otroAlto)){
		return false;
	}
	return true;
}




ESTADO Mundo::ResolverColisiones(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido, ESTADO nuevoEstado){
	//si llego aca es por que hay una colision.

	ESTADO estadoanterior = unCuerpo->getEstadoAnterior();

	std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
	std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

	std::pair<float, float> posAbsSensoresOtroCuerpo;
	std::pair<float, float> posAbsSensoresCuerpo;

	//si otrocuerpo esta haciendo algo y yo no estoy golpeado, evaluo
	if ((elOtroCuerpo->getEstado().accion != SIN_ACCION) && estadoanterior.golpeado == NOGOLPEADO){
		for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
			for (unsigned j = 0; j < sensoresOtroCuerpo->size(); j++){
				ManejadorULogicas manejadorUnidades;
				posAbsSensoresOtroCuerpo = getPosicionAbsSensor(sensoresOtroCuerpo->at(j)->getPosicion(), elOtroCuerpo, sensoresOtroCuerpo->at(j)->getAncho(), sensoresOtroCuerpo->at(j)->getAlto(), !invertido);
				posAbsSensoresCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(i)->getPosicion(), unCuerpo, sensoresCuerpo->at(i)->getAncho(), sensoresCuerpo->at(i)->getAlto(), invertido);


				if ((sensoresCuerpo->at(i)->getHitbox()) && !(sensoresOtroCuerpo->at(j)->getHitbox()) && hayInterseccion(posAbsSensoresCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAlto()), posAbsSensoresOtroCuerpo, manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAlto()))){
					//ERROR ESTAS ENTRANDO MILES DE VECES

					if (nuevoEstado.golpeado == NOGOLPEADO){
						nuevoEstado = ResolverGolpes(unCuerpo, elOtroCuerpo, invertido, nuevoEstado);
						break;
					}
					//unCuerpo->notificarObservadores(nuevoEstado);
				}
			}
		}
	}

	return nuevoEstado;
}


//determina si mi personaje es golpeado o no
// ya hubo colision, en caso de ser golpeado tambien calculo la vitalidad
// 4 cconsideraciones,   con que me golpearon?, que estado tengo? por que en base a eso determino que golpeado soy
// estoy en modo defensa???
ESTADO Mundo::ResolverGolpes(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, bool invertido, ESTADO nuevoEstado){

	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();
	ESTADO estadoEnemigo = elOtroCuerpo->getEstado();
	Sprite* elSprite = unCuerpo->getSprite();


	if (!unCuerpo->estaEnPiso()){ //si esta en el aire no tiene defensa,
		nuevoEstado.golpeado = GOLPEADO;

		if (estadoEnemigo.accion == GANCHO || (estadoEnemigo.accion == PATADA_ALTA && !(elOtroCuerpo->estaEnPiso()))){

			//aca hay que aplicar un impulso

				unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));

		}
		else if (estadoEnemigo.accion != GUARDIA){ // aca como no lo arroja el impulso tiene que ser un toque


				unCuerpo->aplicarImpulso(vector2D(-SALTO_X / 10, SALTO_Y / 10));
		}

	}
	else{ // esta en piso o agachado
		nuevoEstado.golpeado = GOLPEADO;
		if (estadoAnterior.movimiento == AGACHADO){ //no estoy teniendo en cuenta si son golpes fuertes o ganchos......

			if (estadoAnterior.accion == GUARDIA){ //poca demora, poco desplazamiento
				nuevoEstado.accion = GUARDIA;
				if (!(invertido))
				unCuerpo->aplicarImpulso(vector2D(-SALTO_X, 0));
				else
				unCuerpo->aplicarImpulso(vector2D(SALTO_X, 0));
				//unCuerpo->setDemora(200);
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros(nuevoEstado)->size()));
			}
			else{
				if (!(invertido))
				unCuerpo->aplicarImpulso(vector2D(-SALTO_X, 0));
				else
					unCuerpo->aplicarImpulso(vector2D(SALTO_X, 0));
				//unCuerpo->setDemora(300);
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros(nuevoEstado)->size()));

			}
			nuevoEstado.movimiento = AGACHADO;
		}

		else // caso el tipo en el piso
		{

			nuevoEstado.golpeado = GOLPEADO;

			if (estadoAnterior.accion == GUARDIA){ //poca demora, poco desplazamiento
				nuevoEstado.accion = GUARDIA;
				if (!(invertido))
				unCuerpo->aplicarImpulso(vector2D(-SALTO_X, 0));
				else
				unCuerpo->aplicarImpulso(vector2D(SALTO_X, 0));
				//unCuerpo->setDemora(10);
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros(nuevoEstado)->size()));
			}
			else{// no esta en guardia analizar golpes
				
				if (estadoEnemigo.accion == GANCHO || (estadoEnemigo.accion == PATADA_ALTA && (!(elOtroCuerpo->estaEnPiso())))){

					//aca hay que aplicar un impulso
						if (!(invertido))
							unCuerpo->aplicarImpulso(vector2D((0.5)*-SALTO_X, (0.5)*SALTO_Y));
						else
							unCuerpo->aplicarImpulso(vector2D((0.5)*SALTO_X, (0.5)*SALTO_Y));

				}
				else if (estadoEnemigo.accion != GUARDIA){ // aca como no lo arroja el impulso tiene que ser un toque

						unCuerpo->aplicarImpulso(vector2D(10, 10));

				}

			}

		}




	}

	/* logica anterior
	if ((unCuerpo->getEstado().golpeado == GOLPEADO) && (estadoAnterior.golpeado != GOLPEADO)){
	nuevoEstado.golpeado = GOLPEADO;
	unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros(nuevoEstado)->size()));
	if ((unCuerpo->getRefPersonaje()->descontarVida(unCuerpo->getEstado(), otroCuerpo->getEstado())) == REINICIAR){
	nuevoEstado.golpeado = FALLECIDO;
	std::string mensaje = "Gano personaje " + otroCuerpo->getRefPersonaje()->getNombre();
	Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_DEBUG);
	}
	}

	*/

	return nuevoEstado;
}

ESTADO Mundo::moverCuerpos(Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, bool invertido, std::vector<MOV_TIPO>* movimientos, ESTADO nuevoEstado) {


	if (invertido){
		if (unCuerpo->getEstado().movimiento != CAMINARIZQ){
			nuevoEstado.movimiento = CAMINARDER;

			if ((movimientos->back() == DEFENSA) || (movimientos->back() == DEFENSA_AGACHADO)){
				if (!(unCuerpo->EstaFrenado()))
					unCuerpo->mover(-0.1f);
				if (!(elOtroCuerpo->EstaFrenado()))
					elOtroCuerpo->mover(0.1f);
			}

			else{
				if (!(unCuerpo->EstaFrenado()))
					unCuerpo->mover(DISTANCIA);
				if (!(elOtroCuerpo->EstaFrenado()))
					elOtroCuerpo->mover(-DISTANCIA);
			}
		}
	}
	else{
		if (unCuerpo->getEstado().movimiento != CAMINARDER){
			nuevoEstado.movimiento = CAMINARIZQ;

			if ((movimientos->back() == DEFENSA) || (movimientos->back() == DEFENSA_AGACHADO)){
				if (!(unCuerpo->EstaFrenado()))
					unCuerpo->mover(0.1f);
				if (!(elOtroCuerpo->EstaFrenado()))
					elOtroCuerpo->mover(-0.1f);
			}
			else{
				if (!(unCuerpo->EstaFrenado()))
					unCuerpo->mover(-DISTANCIA);
				if (!(elOtroCuerpo->EstaFrenado()))
					elOtroCuerpo->mover(DISTANCIA);
			}

		}
	}


	return nuevoEstado;
}



//logica de saltos
//el tipo en el aire -----> mantenerle el estado de salto, sacarle velocidad si se esta por chocar y la logica de bordes
//el tipo tocando piso recien -->chequear superposicion
ESTADO Mundo::ResolverSaltos(float difTiempo, Cuerpo *unCuerpo, Cuerpo *elOtroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos){

	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();


	// si no esta en piso, mantenele el movimiento anterior
	if (!unCuerpo->estaEnPiso()){
		nuevoEstado.movimiento = estadoAnterior.movimiento;  //si el flaco metio una accion en el aire, esta tiene una demora mas chica aplicada que es la que lo mantiene
		//si fue golpeado en el aire antes deberia mantenerlo una demora y si fue recien nose....

	}

	// si el flaco acaba de llegar al piso y estaba haciendo algo en el aire pero no esta golpeado entonces suspendele la accion cuando llega al piso (evito patada voladora en piso)
	if (unCuerpo->estaEnPiso() && (estadoAnterior.movimiento == SALTO || estadoAnterior.movimiento == SALTODIAGDER || estadoAnterior.movimiento == SALTODIAGIZQ)){

		if ((estadoAnterior.accion != SIN_ACCION) && nuevoEstado.golpeado == NOGOLPEADO){
			unCuerpo->setDemora(0);
		}

	}

	return nuevoEstado;
}




ESTADO Mundo::ResolverAcciones(float difTiempo, Cuerpo *unCuerpo, Cuerpo* otroCuerpo, ESTADO nuevoEstado, bool invertido, std::vector<MOV_TIPO>* movimientos)
{
	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();
	Sprite* elSprite = unCuerpo->getSprite();



	//
	//*************************************************************************************************//
	//                                EL EL AIRE SOLO SE PUEDEN REALIZAR 4 GOLPES
	//
	// SEBA, EVALUA QUE SPRITE APLICAR dependiendo de si estado.movimiento es (SALTO) o  (SALTODIAGDER SALTODIAGIZQ)
	//************************************************************************************************//
	if (!unCuerpo->estaEnPiso())
	{


		if (movimientos->back() == G_BAJO){
			nuevoEstado.accion = GOLPE_BAJO;
			unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));

		}
		if (movimientos->back() == P_ALTA) {
			nuevoEstado.accion = PATADA_ALTA;
			unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
		}

		if (movimientos->back() == P_BAJA) {
			nuevoEstado.accion = PATADA_BAJA;
			unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
		}

		if (movimientos->back() == G_ALTO){
			nuevoEstado.accion = GOLPE_ALTO1;
			unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
		}


	}





	//*************************************************************************************************//
	//                               ESTA EN EL PISO, EVALUO AGACHADO Y PARADO
	//
	//************************************************************************************************//
	else{

		//*************************************************************************************************//
		//                            CASO TIPO AGACHADO
		//
		//************************************************************************************************//
		if (estadoAnterior.movimiento == AGACHADO)
		{

			if (movimientos->back() == ABAJO) {
				nuevoEstado.movimiento = AGACHADO;
			}

			if (movimientos->back() == DEFENSA_AGACHADO){
				nuevoEstado.movimiento = AGACHADO;
				nuevoEstado.accion = GUARDIA;
				//unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
			}

			//*************************************************************************************************//
			//                                GOLPES AGACHADO
			//************************************************************************************************//

			if (movimientos->back() == G_ABAJO){

				if (estadoAnterior.accion != GOLPE_BAJO){
					nuevoEstado.movimiento = AGACHADO;
					nuevoEstado.accion = GOLPE_BAJO;
					unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
				}
			}
			if (movimientos->back() == P_ALTA_ABAJO) {

				if (estadoAnterior.accion != PATADA_ALTA){

					nuevoEstado.movimiento = AGACHADO;
					nuevoEstado.accion = PATADA_ALTA;
					unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
				}
			}

			if (movimientos->back() == P_BAJA_ABAJO) {

				if (estadoAnterior.accion != PATADA_BAJA){
					nuevoEstado.movimiento = AGACHADO;
					nuevoEstado.accion = PATADA_BAJA;
					unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
				}
			}

			if (movimientos->back() == G_GANCHO){

				if (estadoAnterior.accion != GANCHO){
					nuevoEstado.movimiento = AGACHADO;
					nuevoEstado.accion = GANCHO;
					unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
				}
			}






		}

		//*************************************************************************************************//
		//                            CASO TIPO PARADO
		//
		//************************************************************************************************//
		else
		{
				//DESPLAZAMIENTOS

				if ((movimientos->back() == DER)){
					nuevoEstado.movimiento = CAMINARDER;

					if (!(invertido)){
						if (!unCuerpo->EstaSuperpuesto()){
							if (!(unCuerpo->EstaFrenado()))
								unCuerpo->mover(DISTANCIA);
						}
						else{//esta superpueso
							if (!otroCuerpo->estaEnBorde()){
								if (!otroCuerpo->getEstado().accion == GUARDIA){
									if (!(unCuerpo->EstaFrenado()))
										unCuerpo->mover(DISTANCIA);
									if (!(otroCuerpo->EstaFrenado()))
										otroCuerpo->mover(DISTANCIA);
								}
								else{
									if (!(unCuerpo->EstaFrenado()))
										unCuerpo->mover(DISTANCIA / 10);
									if (!(otroCuerpo->EstaFrenado()))
										otroCuerpo->mover(DISTANCIA / 10);
								}
							}

						}
					}//no esta invertido
					else
						if (!(unCuerpo->EstaFrenado()))
							unCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
				}


				if ((movimientos->back() == IZQ)){
					nuevoEstado.movimiento = CAMINARIZQ;
					if (!invertido){
						if (!unCuerpo->EstaSuperpuesto()){
							if (!(unCuerpo->EstaFrenado()))
								unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
						}
						else{
							if (!otroCuerpo->estaEnBorde()){
								if (!otroCuerpo->getEstado().accion == GUARDIA){
									if (!(unCuerpo->EstaFrenado()))
										unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
									if (!(otroCuerpo->EstaFrenado()))
										otroCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
								}
								else{
									if (!(unCuerpo->EstaFrenado()))
										unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA / 10);
									if (!(otroCuerpo->EstaFrenado()))
										otroCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA / 10);

								}
							}
							else{
								if (!(unCuerpo->EstaFrenado()))
									unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
							}
						}
					}// el tipo no esta adelante mio
					else{
						if (!unCuerpo->EstaSuperpuesto()){
							if (!(unCuerpo->EstaFrenado()))
								unCuerpo->mover(-DISTANCIA);
						}
						else{

							if (!otroCuerpo->estaEnBorde()){
								if (!otroCuerpo->getEstado().accion == GUARDIA){
									if (!(unCuerpo->EstaFrenado()))
										unCuerpo->mover(-DISTANCIA);
									if (!(otroCuerpo->EstaFrenado()))
										otroCuerpo->mover(-DISTANCIA);
								}
								else{
									if (!(unCuerpo->EstaFrenado()))
										unCuerpo->mover(-DISTANCIA / 10);
									if (!(otroCuerpo->EstaFrenado()))
										otroCuerpo->mover(-DISTANCIA / 10);

								}
							}
							else{
								if (!otroCuerpo->estaEnBorde() && (!(unCuerpo->EstaFrenado()))) unCuerpo->mover(DISTANCIA);
							}
						}//cierra else

					}
				}
			


			//SALTOS

			if (movimientos->back() == ARRIBA) {
				nuevoEstado.movimiento = SALTO;
				unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
			}


			if (movimientos->back() == SALTODER){
				nuevoEstado.movimiento = SALTODIAGDER;
				unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
			}

			if (movimientos->back() == SALTOIZQ){
				nuevoEstado.movimiento = SALTODIAGIZQ;
				unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));
			}

			//AGACHARSE

			if (movimientos->back() == ABAJO){
				nuevoEstado.movimiento = AGACHADO;
			}

			if (movimientos->back() == DEFENSA_AGACHADO) { //ESTO ESTA ASI A PROPOSITO. en el mk si esta bloqueado y se agacha, tarda en bloquearse agachado
				nuevoEstado.movimiento = AGACHADO;
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
			}

			// GOLPES


			// aca no deberia ir (! arma arrojable) por que deberia tener una demora que le impide entrar a este resolver
			// pero como no sabemos que demora va a tener el arma por que le van a aumentar la velocidad.... dejemos la redundancia por las dudas


			if ((movimientos->back() == ARMA) && !(unCuerpo->getEstado().accion == ARMA_ARROJABLE)){
				nuevoEstado.accion = ARMA_ARROJABLE;
				unCuerpo->getSensoresProyectil().at(0)->activarSensor();
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
			}

			if (movimientos->back() == DEFENSA) {
				nuevoEstado.accion = GUARDIA;
			}


			if (movimientos->back() == G_BAJO){
				nuevoEstado.accion = GOLPE_BAJO;
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
			}
			if (movimientos->back() == P_ALTA) {
				nuevoEstado.accion = PATADA_ALTA;
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
			}

			if (movimientos->back() == P_BAJA) {
				nuevoEstado.accion = PATADA_BAJA;
				unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
			}
			if (movimientos->back() == G_ALTO) {

				if (cambioGolpeAlto){

					nuevoEstado.accion = GOLPE_ALTO1;
					cambioGolpeAlto = false;
					unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
				}
				else{
					nuevoEstado.accion = GOLPE_ALTO2;
					cambioGolpeAlto = true;
					unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros((nuevoEstado))->size()));
				}

			}



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


ESTADO Mundo::ResolverArma(Cuerpo* elOtroCuerpo, Cuerpo* unCuerpo, Sensor* proyectil, bool invertido, ESTADO nuevoEstado){

	ManejadorULogicas manejadorUnidades;

	std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
	std::pair<float, float> posAbsSensorProyectil;
	std::pair<float, float> posAbsSensoresCuerpo;

	std::pair<float, float> posProyectilEngloba;

	posProyectilEngloba.first = elOtroCuerpo->getXProyectilAnterior();
	posProyectilEngloba.second = manejadorUnidades.darLongPixels(elOtroCuerpo->getPosicion().y + (3 / 4)*elOtroCuerpo->getRefPersonaje()->getAlto());

	float anchoEngloba = proyectil->getPosicion().first - elOtroCuerpo->getXProyectilAnterior() + proyectil->getAncho();

	posAbsSensorProyectil = getPosicionAbsSensor(posProyectilEngloba, elOtroCuerpo, anchoEngloba, proyectil->getAlto(), !invertido);

	for (unsigned j = 0; j < sensoresCuerpo->size(); j++){
		posAbsSensoresCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(j)->getPosicion(), unCuerpo, sensoresCuerpo->at(j)->getAncho(), sensoresCuerpo->at(j)->getAlto(), invertido);
		if (hayInterseccion(posAbsSensorProyectil, manejadorUnidades.darLongUnidades(anchoEngloba), manejadorUnidades.darLongUnidades(proyectil->getAlto()), posAbsSensoresCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(j)->getAlto()))){
			nuevoEstado.golpeado = GOLPEADO;
			proyectil->desactivarSensor();
			break;
		}
	}
	return nuevoEstado;
}

//Solución del choque entre proyectiles.
void Mundo::resolverChoque(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, Sensor* proyectilUno, Sensor* proyectilDos, bool invertido){

	ManejadorULogicas manejadorUnidades;

	std::pair<float, float> posAbsSensorProyectil1;
	std::pair<float, float> posAbsSensorProyectil2;

	std::pair<float, float> posProyectilEngloba1;
	std::pair<float, float> posProyectilEngloba2;

	posProyectilEngloba1.first = unCuerpo->getXProyectilAnterior();
	posProyectilEngloba1.second = proyectilUno->getPosicion().second;

	posProyectilEngloba2.first = elOtroCuerpo->getXProyectilAnterior();
	posProyectilEngloba2.second = proyectilDos->getPosicion().second;

	float anchoEngloba1 = proyectilUno->getPosicion().first - unCuerpo->getXProyectilAnterior() + proyectilUno->getAncho();
	float anchoEngloba2 = proyectilDos->getPosicion().first - elOtroCuerpo->getXProyectilAnterior() + proyectilDos->getAncho();

	posAbsSensorProyectil1 = getPosicionAbsSensor(posProyectilEngloba1, unCuerpo, anchoEngloba1, proyectilUno->getAlto(), invertido);
	posAbsSensorProyectil2 = getPosicionAbsSensor(posProyectilEngloba2, elOtroCuerpo, anchoEngloba2, proyectilDos->getAlto(), !invertido);

	if (hayInterseccion(posAbsSensorProyectil1, manejadorUnidades.darLongUnidades(anchoEngloba1), manejadorUnidades.darLongUnidades(proyectilUno->getAlto()), posAbsSensorProyectil2, manejadorUnidades.darLongUnidades(anchoEngloba2), manejadorUnidades.darLongUnidades(proyectilDos->getAlto()))){
		unCuerpo->getSensoresProyectil().at(0)->desactivarSensor();
		elOtroCuerpo->getSensoresProyectil().at(0)->desactivarSensor();
	}
}


//resuelve todo
//para entrar aca ninguno de los 2 puede estar golpeado y al menos uno tiene que estar hacieno algo
ESTADO Mundo::ResolverAtaques(Cuerpo* unCuerpo, Cuerpo* elOtroCuerpo, ESTADO nuevoEstado, Sensor* proyectilUno, Sensor* proyectilDos, bool invertido){

	//**********************************************************
	// resuelve proyeciles

	if ((proyectilUno->estaActivo()) && (proyectilDos->estaActivo())){
		resolverChoque(unCuerpo, elOtroCuerpo, proyectilUno, proyectilDos, invertido);
	}
	else {
		
		if (proyectilDos->estaActivo()){
			nuevoEstado = ResolverArma(elOtroCuerpo, unCuerpo, proyectilDos, invertido, nuevoEstado);
		}
	}

	//********************************
	//resuelve golpes
	nuevoEstado = Mundo::ResolverColisiones(unCuerpo, elOtroCuerpo, invertido, nuevoEstado);

	return nuevoEstado;
}


ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO estadoanterior = unCuerpo->getEstadoAnterior();
	ESTADO nuevoEstado;  //defino estado por defecto Si no es golpeado, si no vas a hacer nada y si no estas en el aire, devuelve esto
	nuevoEstado.movimiento = PARADO;
	nuevoEstado.accion = SIN_ACCION;
	nuevoEstado.golpeado = NOGOLPEADO;

	Sprite* elSprite = unCuerpo->getSprite();

	//Se setea de que cuerpo se esta tratando.
	Cuerpo* elOtroCuerpo;

	if (unCuerpo == Cuerpos.at(0)){
		elOtroCuerpo = Cuerpos.at(1);
	}
	else{
		elOtroCuerpo = Cuerpos.at(0);
	}


	Sensor* proyectilUno = unCuerpo->getSensoresProyectil().at(0);
	Sensor* proyectilDos = elOtroCuerpo->getSensoresProyectil().at(0);


	/////////////////////////////////////////////////////////////////////////////
	bool invertido;

	float posMedia1 = unCuerpo->getPosicion().x + unCuerpo->getRefPersonaje()->getAncho() / 2;
	float posMedia2 = elOtroCuerpo->getPosicion().x + elOtroCuerpo->getRefPersonaje()->getAncho() / 2;

	if (posMedia2 > posMedia1)
		invertido = false;
	else
		invertido = true;
	//////////////////////////////////////////////////////////////////////////////

	std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();
	std::vector<MOV_TIPO> movimientosOtro = elOtroCuerpo->getControlador()->getMovimientos();


	//la superposicion se da:
	// al final de un salto , al final de la caida de un golpe y la activa el metodo resolver saltos
	// o cuando estan los 2 en el aire saltando, en este caso deberia setearse velocidad.x ==0 para que no se toquen
	//
	if (unCuerpo->EstaSuperpuesto() && !(unCuerpo->estaEnPiso() && elOtroCuerpo->estaEnPiso())){

		nuevoEstado = Mundo::moverCuerpos(unCuerpo, elOtroCuerpo, invertido, &movimientosOtro, nuevoEstado);

		//mejorar esto
		if (invertido){
			if (unCuerpo->getEstado().movimiento != CAMINARIZQ){
				nuevoEstado = unCuerpo->getEstadoAnterior();

			}
			//nuevoEstado.movimiento = CAMINARIZQ;

		}
		else{
			if (unCuerpo->getEstado().movimiento != CAMINARDER){
				nuevoEstado = unCuerpo->getEstadoAnterior();
			}

			//nuevoEstado.movimiento = CAMINARDER;
		}

	}
	else{
		// NO HAY SUPERPOSICION, LO SIGUIENTE A RESOLVER ES LA COLISION

		//si el tipo ya esta golpeado o el otro no vuelvo a evaluar
		// ademas, alguno tiene que estar haciendo algo.. habria que desconsiderar las guardias......
		// es sucio pero es una optimizacion, sino aca va a entrar siempre para el otro cuerpo no golpeado
		if (estadoanterior.golpeado != GOLPEADO && elOtroCuerpo->getEstado().golpeado != GOLPEADO && ((unCuerpo->getEstado().accion != SIN_ACCION) || (elOtroCuerpo->getEstado().accion != SIN_ACCION))){


			nuevoEstado = Mundo::ResolverAtaques(unCuerpo, elOtroCuerpo, nuevoEstado, proyectilUno, proyectilDos, invertido);

		}

		//esto deja personaje estadoactual.golpeado=golpeado si hubo colision  y le aplica demora o si no hubo no setea nada

		// PASO 3 RESOLVEMOS LA LOGICA DE SALTOS

		//ahora hay que resolver la logica de altura
		//el tipo puede estar saltando, pudo haber sido golpeado, pude estar superponiendose en el aire
		//tanto golpeado como golpeando no nos importa por que analizamos en principio la parte de .movimiento
		// al llegar al piso primero suspender accion de golpe por si esta con una patada boladora
		// y chequear superposicion

		nuevoEstado = Mundo::ResolverSaltos(difTiempo, unCuerpo, elOtroCuerpo, nuevoEstado, invertido, &movimientos);


		//AHORA HAY QUE ANALIZAR SI HAY DEMORA, LA DEMORA PUEDE SER POR UN UN ESTADO ANTERIOR O POR QUE SE APLICO EN EL ESTADO ACTUAL UN GOLPEADO
		//casos:
		//llevando a cabo una accion
		// estoy golpeado
		// me acaban de golpear

		//si hay demora
		if (unCuerpo->HayDemora())
		{


			if ((!(nuevoEstado.golpeado == GOLPEADO && unCuerpo->getEstadoAnterior().golpeado == NOGOLPEADO)) && nuevoEstado.golpeado != FALLECIDO){
				unCuerpo->DisminuirDemora();
				nuevoEstado = unCuerpo->getEstadoAnterior();
			} //en el caso de que se cumpla, el tipo sale de aca con el estado actual que es golpeado!
			//si estadoactual=golpeado y estado anterior no lo es no disminuir

		}



		else
		{//no hay demora,// si llega aca, no esta golpeado y no esta haciendo nada (y voy a evaluar si ahora si va a hacer algo (puede estar en el aire o en piso)

			nuevoEstado = Mundo::ResolverAcciones(difTiempo, unCuerpo, elOtroCuerpo, nuevoEstado, invertido, &movimientos);


		}


	} //cierra el else

	//Si estan superpuestos y los 2 sin ninguna accion, salvo guardia y caminando
	if (haySuperposicion(unCuerpo, elOtroCuerpo, invertido) && (unCuerpo->getEstado().accion == SIN_ACCION || unCuerpo->getEstado().accion == GUARDIA || unCuerpo->getEstado().movimiento == CAMINARDER || unCuerpo->getEstado().movimiento == CAMINARIZQ) && (elOtroCuerpo->getEstado().accion == SIN_ACCION || elOtroCuerpo->getEstado().accion == GUARDIA || elOtroCuerpo->getEstado().movimiento == CAMINARIZQ || elOtroCuerpo->getEstado().movimiento == CAMINARDER)){
		unCuerpo->Superponer();
	}
	else{
		unCuerpo->Separados();
	}


	if (!(nuevoEstado.accion == ARMA_ARROJABLE)){
		unCuerpo->getSensoresProyectil().at(0)->resetearPosicionInicial();
		unCuerpo->getSensoresProyectil().at(0)->desactivarSensor();
	}

	//TODO aca tiene que ser estado anterior********
	if ((nuevoEstado.accion == ARMA_ARROJABLE) && (unCuerpo->getSensoresProyectil().at(0)->estaActivo())){
		unCuerpo->setposProyectilAnterior(unCuerpo->getSensoresProyectil().at(0)->getPosicion().first);
		unCuerpo->getSensoresProyectil().at(0)->moverProyectil(VELOCIDADPROYECTIL);
	}





	//****************************************************************
	// Se evalua vitalidad y demora de golpeado
	//************************************************************************
	//xerror hay que arreglar esto por que se cambio la logica.
	// aca uncuerpo es el golpeado entonces se le tiene que descontar a uncuerpo
	if ((nuevoEstado.golpeado == GOLPEADO) && (estadoanterior.golpeado != GOLPEADO)){
		unCuerpo->setDemora((elSprite->getConstantes(nuevoEstado))*(elSprite->listaDeCuadros(nuevoEstado)->size()));
		if ((unCuerpo->getRefPersonaje()->descontarVida(unCuerpo->getEstado(), elOtroCuerpo->getEstado())) == REINICIAR){
			nuevoEstado.golpeado = FALLECIDO;
			std::string mensaje = "Gano personaje " + elOtroCuerpo->getRefPersonaje()->getNombre();
			Log::getInstancia().logearMensajeEnModo(mensaje, Log::MODO_DEBUG);
		}
	}

	if (unCuerpo->EstaFrenado()){
		unCuerpo->SetVelocidadX(0.0f);
	}

	unCuerpo->SetSensorActivoStr(nuevoEstado);
	unCuerpo->setEstadoAnterior(nuevoEstado);

	// velocidades
	vector2D unaVelocidad = unCuerpo->getVelocidad();  //obtengo la velocidad actual
	unCuerpo->sumarPosicion(unaVelocidad * difTiempo); //cambio la posicion
	unCuerpo->sumarVelocidad(gravedad * difTiempo); // aplico gravedad

	return nuevoEstado;
}


float Mundo::getYPiso() const
{
	return yPiso;
}
