#pragma once
class Controlador
{
public:
	Controlador();
	enum MOV_TIPO { QUIETO, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER, CERRAR };
	~Controlador();
	static MOV_TIPO cambiar();
};

