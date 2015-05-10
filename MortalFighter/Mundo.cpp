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
	unCuerpo->SetSensorActivoStr(QUIETODER);
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

std::pair<int, int> getPosicionAbsSensor(float x, float y, Cuerpo* unCuerpo){
	std::pair<int, int> posicionOtroCuerpo;
	ManejadorULogicas manejadorUnidades;

	int posX = manejadorUnidades.darLongUnidades(x) + unCuerpo->getPosicion().x;
	int posY = manejadorUnidades.darLongUnidades(y) + unCuerpo->getPosicion().y;
	posicionOtroCuerpo.first = posX;
	posicionOtroCuerpo.second = posY;
	return posicionOtroCuerpo;
}

bool Mundo::hayInterseccion(std::pair<int, int> unaPosicion, int unAncho, int unAlto, std::pair<int, int> otraPos, int otroAncho, int otroAlto){
	if ((unaPosicion.first + unAncho < otraPos.first) || (unaPosicion.first > otroAncho + otraPos.first) || (unaPosicion.second + unAlto < otraPos.second) || (unaPosicion.second > otraPos.second + otroAlto)){
		return false;
	}
	return true;
}

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO nuevoEstado = QUIETODER;
	std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();

	ESTADO estadoAnterior = unCuerpo->getEstadoAnterior();

	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad
	if (!unCuerpo->estaEnPiso()){
		if ((unCuerpo->getVelocidad().x == 0)){
			nuevoEstado = estadoAnterior;
			if (estadoAnterior == ARRIBA_DER)
				nuevoEstado = ARRIBA_DER;
		}
		else if (unCuerpo->getVelocidad().x > 0)
			nuevoEstado = SALTODER_DER;
		else
			nuevoEstado = SALTOIZQ_DER;
		unCuerpo->sumarVelocidad(gravedad * difTiempo);
		if (unCuerpo->EstaFrenado()){
			unCuerpo->SetVelocidadX(0.0f);
		}
	} // Si está frenado el cuerpo no lo mueve
	else if (unCuerpo->EstaFrenado()){
		unCuerpo->SetVelocidadX(0.0f);
		if ((movimientos.at(0) == ARRIBA)){
			nuevoEstado = ARRIBA_DER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}
		if (movimientos.at(0) == ABAJO){
			nuevoEstado = ABAJO_DER;
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

		if ((movimientos.at(0) == DER) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = DER_DER;
			if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
				unCuerpo->mover(DISTANCIA);
			else
				unCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
		}


		if ((movimientos.at(0) == IZQ) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = IZQ_DER;
			if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
				unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
			else
				unCuerpo->mover(-DISTANCIA);
		}


		if ((movimientos.at(0) == ARRIBA) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = ARRIBA_DER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}

		if ((movimientos.at(0) == SALTODER) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = SALTODER_DER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}

		if ((movimientos.at(0) == SALTOIZQ) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = SALTOIZQ_DER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));
		}

		//xjose estoy mandando fruta, nuevo estado "abajo derecha" y abajo izq???

		if ((movimientos.at(0) == ABAJO) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = ABAJO_DER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}

		//---------------------------------
		//xjose
		//aca hay que aplicar una demora para que reproduzca un tiempo el sprite de patada.
		// ojo, tener en cuenta que la demora se tiene que interrumpir si me barren y quedo golpeado mientras tiraba la patada.

		if (movimientos.at(0) == P_ALTA && !(unCuerpo->getEstado() == P_ALTADER)){
			nuevoEstado = P_ALTADER;
			unCuerpo->setEstadoAnterior(nuevoEstado);
			unCuerpo->setDemora((elSprite->getConstantes("PatadaAlta"))*(elSprite->listaDeCuadros("PatadaAlta")->size()));
		}

		
		if ((unCuerpo->getEstado() == GOLPEADOIZQ) && (estadoAnterior != GOLPEADOIZQ)){
			unCuerpo->setDemora((elSprite->getConstantes("Golpeado"))*(elSprite->listaDeCuadros("Golpeado")->size()));
			nuevoEstado = GOLPEADOIZQ;
			unCuerpo->setEstadoAnterior(nuevoEstado);
		}
		
		std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
		std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

		std::pair<float, float> posAbsOtroCuerpo;
		std::pair<float, float> posAbsCuerpo;

		if ((movimientos.at(0) == P_ALTA) || (unCuerpo->getEstado() == P_ALTADER)){
			for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
				for (unsigned j = 0; j < sensoresCuerpo->size(); j++){
					if (elOtroCuerpo->getEstado() != GOLPEADOIZQ){
						ManejadorULogicas manejadorUnidades;
						posAbsOtroCuerpo = getPosicionAbsSensor(sensoresOtroCuerpo->at(j)->getPosicion().first, sensoresOtroCuerpo->at(j)->getPosicion().second, elOtroCuerpo);
						posAbsCuerpo = getPosicionAbsSensor(sensoresCuerpo->at(i)->getPosicion().first, sensoresCuerpo->at(i)->getPosicion().second, unCuerpo);
						if (hayInterseccion(posAbsCuerpo, manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAncho()), manejadorUnidades.darLongUnidades(sensoresCuerpo->at(i)->getAlto()), posAbsOtroCuerpo, manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAncho()), manejadorUnidades.darLongUnidades(sensoresOtroCuerpo->at(j)->getAlto())))
							elOtroCuerpo->notificarObservadores(GOLPEADOIZQ);
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
			nuevoEstado = QUIETODER;
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
