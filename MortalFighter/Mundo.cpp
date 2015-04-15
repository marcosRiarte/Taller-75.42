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
	unCuerpo->recibeObservador(&Parser::getInstancia().getPersonaje());
}

void Mundo::Paso(float difTiempo, MOV_TIPO movimiento)
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Cuerpos.at(i)->notificarObservadores(Resolver(difTiempo, Cuerpos.at(i), movimiento));
	}
}

ESTADO Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo, MOV_TIPO movimiento)
{
	ESTADO nuevoEstado = QUIETODER;
	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad

	if (!unCuerpo->estaEnPiso()){
		unCuerpo->sumarVelocidad(gravedad * difTiempo);
		nuevoEstado = ABAJO_DER;
	}
	else{

		if (movimiento == DER) {
			nuevoEstado = DER_DER;
			unCuerpo->mover(DISTANCIA);
		}
		if (movimiento == IZQ){
			nuevoEstado = IZQ_DER;
			unCuerpo->mover(-DISTANCIA*FACTOR_DIST_REVERSA);
		}

		if (movimiento == ARRIBA){
			nuevoEstado = ARRIBA_DER;
			unCuerpo->aplicarImpulso(vector2D(0.0f, SALTO_Y));
		}

		if (movimiento == SALTODER){
			nuevoEstado = SALTODER_DER;
			unCuerpo->aplicarImpulso(vector2D(SALTO_X, SALTO_Y));
		}

		if (movimiento == SALTOIZQ){
			nuevoEstado = SALTOIZQ_DER;
			unCuerpo->aplicarImpulso(vector2D(-SALTO_X, SALTO_Y));

		}
	}
	//TODO: falta esta parte...
	// si el oponente está a izq voltear estados, abusando del enum
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
