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

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO nuevoEstado = QUIETODER;
	std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();

	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad
	if (!unCuerpo->estaEnPiso()){
		if ((unCuerpo->getVelocidad().x == 0)){
			nuevoEstado = estadoAnteriorPj1;
			if (estadoAnteriorPj1 == ARRIBA_DER)
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
			estadoAnteriorPj1 = nuevoEstado;
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}
		if (movimientos.at(0) == ABAJO){
			nuevoEstado = ABAJO_DER;
			estadoAnteriorPj1 = nuevoEstado;
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

		if (movimientos.at(0) == DER){
			nuevoEstado = DER_DER;
			if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
				unCuerpo->mover(DISTANCIA);
			else
				unCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
		}


		if (movimientos.at(0) == IZQ){
			nuevoEstado = IZQ_DER;
			if (elOtroCuerpo->getPosicion().x > unCuerpo->getPosicion().x)
				unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
			else
				unCuerpo->mover(-DISTANCIA);
		}


		if ((movimientos.at(0) == ARRIBA)){
			nuevoEstado = ARRIBA_DER;
			estadoAnteriorPj1 = nuevoEstado;
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}

		if ((movimientos.at(0) == SALTODER)){
			nuevoEstado = SALTODER_DER;
			estadoAnteriorPj1 = nuevoEstado;
			unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}

		if ((movimientos.at(0) == SALTOIZQ)){
			nuevoEstado = SALTOIZQ_DER;
			estadoAnteriorPj1 = nuevoEstado;
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));
		}

		//xjose estoy mandando fruta, nuevo estado "abajo derecha" y abajo izq???

		if (movimientos.at(0) == ABAJO){
			nuevoEstado = ABAJO_DER;
			estadoAnteriorPj1 = nuevoEstado;
		}

		//---------------------------------
		//xjose
		//aca hay que aplicar una demora para que reproduzca un tiempo el sprite de patada.
		// ojo, tener en cuenta que la demora se tiene que interrumpir si me barren y quedo golpeado mientras tiraba la patada.

		if (movimientos.at(0) == P_ALTA && !(unCuerpo->getEstado() == P_ALTADER)){
			nuevoEstado = P_ALTADER;
			estadoAnteriorPj1 = nuevoEstado;
			unCuerpo->setDemora((elSprite->getConstantes("PatadaAlta"))*(elSprite->listaDeCuadros("PatadaAlta")->size()));
		}

		
		if ((unCuerpo->getEstado() == GOLPEADOIZQ) && (estadoAnteriorPj1 != GOLPEADOIZQ)){
			unCuerpo->setDemora((elSprite->getConstantes("Golpeado"))*(elSprite->listaDeCuadros("Golpeado")->size()));
			nuevoEstado = GOLPEADOIZQ;
		}
		



		std::vector<Sensor*>* sensoresCuerpo = unCuerpo->getSensores();
		std::vector<Sensor*>* sensoresOtroCuerpo = elOtroCuerpo->getSensores();

		if ((movimientos.at(0) == P_ALTA) || (unCuerpo->getEstado() == P_ALTADER)){
			for (unsigned i = 0; i < sensoresCuerpo->size(); i++){
				if ((sensoresOtroCuerpo->at(i)->getHitbox()) && (sensoresCuerpo->at(0)->hayInterseccion(sensoresOtroCuerpo->at(i)->getPosicion(), sensoresOtroCuerpo->at(0)->getAncho(), sensoresOtroCuerpo->at(0)->getAlto())))
					elOtroCuerpo->notificarObservadores(GOLPEADOIZQ);
				estadoAnteriorPj2 = GOLPEADOIZQ;
			}
		}
		//aca deberia tener en cuenta ademas si no estoy en estado golpeado, por que si me pegaron se tiene que interrumpir
		if (unCuerpo->GetDemora() > 0) {
			unCuerpo->DisminuirDemora();
			if (nuevoEstado != GOLPEADOIZQ)
				nuevoEstado = estadoAnteriorPj1;
			else
				nuevoEstado = estadoAnteriorPj2;
		}

		if ((movimientos.at(0) == QUIETO) && (unCuerpo->GetDemora() == 0)){
			nuevoEstado = QUIETODER;
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
