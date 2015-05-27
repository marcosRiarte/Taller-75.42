#pragma once
class Toma
{
public:
	Toma();
	void setNombre(std::string unNombre);
	void setMovimiento(MOV_TIPO unMovimiento);
	void setError(int unError);
	void setTiempo(int unTiempo);
	int getTiempo();
	std::string getNombre();
	int getError();
	std::vector<MOV_TIPO>* getMovimientos();
	~Toma();
	
private:
	std::string nombre;
	std::vector<MOV_TIPO> movimientos;
	int error;
	int tiempo;
};

