#pragma once
class ConversorAString
{
public:
	ConversorAString();
	std::string getTeclaComoStringDelMovimientoParaElConversorDeEventos(MOV_TIPO unMovimiento, ConversorDeEventos* conversorDeEventos);
	~ConversorAString();
};

