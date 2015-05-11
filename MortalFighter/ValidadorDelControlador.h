#pragma once
class ValidadorDelControlador
{
private:
	Controlador* controlador1;
	Controlador* controlador2;

	std::vector<std::string>* ValidadorDelControlador::cargarConstantesParaElControlador(int numeroDeControlador);
	int ValidadorDelControlador::crearYobtenerNumeroDeControlador();

public:
	ValidadorDelControlador();
	void validarControladorDesde(Json::Value unControlador);
	Controlador* getControlador1();
	Controlador* getControlador2();
	~ValidadorDelControlador();
};

