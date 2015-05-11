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

void Mundo::Paso(float difTiempo)
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Cuerpos.at(i)->notificarObservadores(Resolver(difTiempo, Cuerpos.at(i)));
	}
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

std::pair<int, int> getPosicionAbsSensor(std::pair<float, float> posSensor, Cuerpo* unCuerpo, float anchoDelSensor, bool invertido){
	std::pair<int, int> posicionOtroCuerpo;
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

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO nuevoEstado; 
	nuevoEstado.movimiento = PARADO;
	std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();
	bool invertido;

	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();

	/// integra velocidad, para salto, 
	// si no est� en el piso siente la gravedad
	if (!unCuerpo->estaEnPiso()){
		if ((unCuerpo->getVelocidad().x == 0)){
			nuevoEstado = estadoAnterior;
			if (estadoAnterior.movimiento == SALTO)
				nuevoEstado.movimiento = SALTO;
		}
		else if (unCuerpo->getVelocidad().x > 0)
			nuevoEstado.movimiento = SALTODIAGDER;
		else
			nuevoEstado.movimiento = SALTODIAGIZQ;
		unCuerpo->sumarVelocidad(gravedad * difTiempo);
		if (unCuerpo->EstaFrenado()){
			unCuerpo->SetVelocidadX(0.0f);
		}
	} // Si est� frenado el cuerpo no lo mueve
	else if (unCuerpo->EstaFrenado()){
		unCuerpo->SetVelocidadX(0.0f);
		if ((movimientos.at(0) == ARRIBA)){
			nuevoEstado.movimiento = SALTO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}
		if (movimientos.at(0) == ABAJO){
			nuevoEstado.movimiento = AGACHADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
	}
	else {

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

		if (movimientos.at(0) == P_ALTA && !(unCuerpo->getEstado().accion == PATADA_ALTA)){
			nuevoEstado.accion = PATADA_ALTA;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
		}

		
		if ((unCuerpo->getEstado().golpeado == GOLPEADO) && (estadoAnterior.golpeado != GOLPEADO)){
			unCuerpo->setDemora((elSprite->getConstantes(unCuerpo->getEstado()))*(elSprite->listaDeCuadros(unCuerpo->getEstado())->size()));
			nuevoEstado.golpeado = GOLPEADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
		
		std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
		std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

		std::pair<float, float> posAbsSensoresOtroCuerpo;
		std::pair<float, float> posAbsSensoresCuerpo;

		if ((movimientos.at(0) == P_ALTA) || (unCuerpo->getEstado().accion == PATADA_ALTA)){
			for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
				for (unsigned j = 0; j < sensoresCuerpo->size(); j++){
					if (elOtroCuerpo->getEstado().movimiento != GOLPEADO){
						ManejadorULogicas manejadorUnidades;
						posAbsSensoresOtroCuerpo = getPosicionAbsSensor(sensoresOtroCuerpo->at(j)->getPosicion(), elOtroCuerpo, sensoresOtroCuerpo->at(j)->getAncho(), !invertido);
						posAbsSensoresCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(i)->getPosicion(), unCuerpo, sensoresCuerpo->at(i)->getAncho(), invertido);
						if (!(sensoresCuerpo->at(i)->getHitbox()) && (sensoresOtroCuerpo->at(j)->getHitbox()) && hayInterseccion(posAbsSensoresCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAlto()), posAbsSensoresOtroCuerpo, manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAlto()))){
							ESTADO unEstado;
							unEstado.golpeado = GOLPEADO;
							elOtroCuerpo->notificarObservadores(unEstado);
						}
					}
				}
				}
		}

		//aca deberia tener en cuenta ademas si no estoy en estado golpeado, por que si me pegaron se tiene que interrumpir
		if ( (unCuerpo->GetDemora() > 0)) {
			unCuerpo->DisminuirDemora();
			nuevoEstado = unCuerpo->getEstadoAnterior();
		}

		if ((movimientos.at(0) == QUIETO) && (unCuerpo->GetDemora() <= 0)){
			nuevoEstado.movimiento = PARADO;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}

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
