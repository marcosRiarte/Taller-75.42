#pragma once
class Controlador
{
public:
	Controlador();
	enum MOV_TIPO { DER,IZQ,ARRIBA,ABAJO,SALTOIZQ,SALTODER,QUIETO};
	~Controlador();
	static MOV_TIPO cambiar();
};

