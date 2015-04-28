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
	Cuerpos.push_back(unCuerpo);	
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
		Cuerpos.at(i)->notificarObservadores(QUIETODER);
	}
}

void Mundo::LiberarCuerpos()
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Cuerpos.at(i)->Liberar();
		Cuerpos.at(i)->notificarObservadores(QUIETODER);
	}
}

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo)
{
	ESTADO nuevoEstado = QUIETODER;

	/// integra velocidad, para salto, 
	// si no est� en el piso siente la gravedad
	if (!unCuerpo->estaEnPiso()){
		if (unCuerpo->getVelocidad().x == 0)
			nuevoEstado = ARRIBA_DER;
		else if (unCuerpo->getVelocidad().x > 0)
			nuevoEstado = SALTODER_DER;
		else
			nuevoEstado = SALTOIZQ_DER;
		unCuerpo->sumarVelocidad(gravedad * difTiempo);
	} // Si est� frenado el cuerpo no lo mueve
	else if (unCuerpo->EstaFrenado())
		nuevoEstado = QUIETODER;
	else {	

		std::vector<MOV_TIPO> movimientos = unCuerpo->getControlador()->getMovimientos();

		if (movimientos.at(0) == DER) {
			nuevoEstado = DER_DER;
			if (Parser::getInstancia().getPersonajes().at(0)->getOrientacion() == "DER")
				unCuerpo->mover(DISTANCIA);
			else
				unCuerpo->mover(DISTANCIA*FACTOR_DIST_REVERSA);
		}
		

		if (movimientos.at(0) == IZQ){
			nuevoEstado = IZQ_DER;
					if (Parser::getInstancia().getPersonajes().at(0)->getOrientacion() == "DER")
				unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
			else
				unCuerpo->mover(-DISTANCIA);
		}
		

		if (movimientos.at(0) == ARRIBA){
			nuevoEstado = ARRIBA_DER;
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}

		if (movimientos.at(0) == SALTODER){
			nuevoEstado = SALTODER_DER;
			unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}

		if (movimientos.at(0) == SALTOIZQ){
			nuevoEstado = SALTOIZQ_DER;
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));

		}
	}
	//TODO: falta esta parte...
	// si el oponente est� a izq voltear estados, abusando del enum
	//if (oponenteAIzq())
	//	nuevoEstado += 1;

	vector2D unaVelocidad = unCuerpo->getVelocidad();

	/// integra posicion	
	unCuerpo->sumarPosicion(unaVelocidad * difTiempo);

	return nuevoEstado;
}

float Mundo::getYPiso() const
{
	return yPiso;
}
