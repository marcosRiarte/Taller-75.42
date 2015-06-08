#pragma once
class Sonidos
{
public:
	Sonidos();
	~Sonidos();
	void cargaSonidoScorpion();
	void cargaSonidoLiuKang();
	void cargaSonidoEfectos();
	Mix_Chunk* getSonidoEfectos(int posicion);
	Mix_Chunk* getSonidoLiuKang(int posicion);
	Mix_Chunk* getSonidoScorpion(int posicion);

	private:
	std::vector<Mix_Chunk*> sonidosFx;
	std::vector<Mix_Chunk*> sonidosLiuKang;
	std::vector<Mix_Chunk*> sonidosScorpion;

};

