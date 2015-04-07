#pragma once
enum MOV_TIPO { QUIETO, DER, IZQ, ARRIBA, ABAJO, SALTOIZQ, SALTODER, CERRAR, RECARGAR };

class Controlador
{
public:
	Controlador();
	
	~Controlador();
	static MOV_TIPO cambiar();
};

