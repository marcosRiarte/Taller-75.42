#include "stdafx.h"
#include "Mundo.h"
#include "Cuerpo.h"
#include "Parser.h"

Mundo::Mundo()
{

}

Mundo::Mundo(const vector2D& valorGravedad)
{
	gravedad = valorGravedad;
	Cuerpos = std::vector<Cuerpo*>();
}

void Mundo::agregarCuerpo(Cuerpo *unCuerpo)
{
	Cuerpos.push_back(unCuerpo);
}

void Mundo::Paso(float difTiempo, Controlador::MOV_TIPO movimiento)
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Resolver(difTiempo, Cuerpos.at(i), movimiento);
		Cuerpos.at(i)->notificarObservadores();
	}		
}

void Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo, Controlador::MOV_TIPO movimiento)
{
	//vector2D unaVelocidad = unCuerpo->getVelocidad();

	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad
	/*if (!unCuerpo->estaEnPiso())
		unCuerpo->sumarVelocidad(gravedad * difTiempo);*/
	
	//TODO: chequear bordes piso,etc
	if (Controlador::cambiar() == Controlador::DER)	{
		unCuerpo->moverDerecha();
	}
	/// integra posicion	
	//unCuerpo->sumarPosicion(unaVelocidad * difTiempo);
}

