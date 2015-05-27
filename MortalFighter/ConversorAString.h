#pragma once
class ConversorAString
{
public:
	ConversorAString();
	std::string getTeclaComoStringDelMovimientoParaElConversorDeEventos(MOV_TIPO unMovimiento, ConversorDeEventos* conversorDeEventos);
	MOV_TIPO getMovimientoParaElString(std::string unMovimiento);
	~ConversorAString();
};

