#pragma once
class ValidadorDePelea
{
private:
	std::string pelea;
public:
	ValidadorDePelea();
	void validarPeleaDesdeParaLosPeronajes(Json::Value unaPelea, std::vector<Personaje*>* personajes);
	std::string getPelea();
	~ValidadorDePelea();
};

