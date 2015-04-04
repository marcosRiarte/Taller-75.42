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
	unCuerpo->recibeObservador(&Parser::getInstancia().getPersonaje());
}

void Mundo::Paso(float difTiempo, MOV_TIPO movimiento)
{
	for (unsigned int i = 0; i < Cuerpos.size(); i++)
	{
		Cuerpos.at(i)->notificarObservadores();
		Resolver(difTiempo, Cuerpos.at(i), movimiento);		
	}		
}

void Mundo::Resolver(float difTiempo, Cuerpo *unCuerpo, MOV_TIPO movimiento)
{
	/// integra velocidad, para salto, 
	// si no está en el piso siente la gravedad
	if (!unCuerpo->estaEnPiso())
		unCuerpo->sumarVelocidad(gravedad * difTiempo);

	if (movimiento == IZQ)
		unCuerpo->moverIzquierda();
	
	//TODO: chequear bordes piso,etc
	if (movimiento == DER)
		unCuerpo->moverDerecha();	
	
	if (movimiento == ARRIBA && unCuerpo->estaEnPiso())
		unCuerpo->aplicarImpulso(vector2D(0.0f, 400.0f));

	vector2D unaVelocidad = unCuerpo->getVelocidad();

	/// integra posicion	
	unCuerpo->sumarPosicion(unaVelocidad * difTiempo);
}

