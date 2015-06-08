#include "stdafx.h"
#include "Sonidos.h"


Sonidos::Sonidos()
{   
	
}
void Sonidos::cargaSonidoScorpion()
{
	//Lanza
	this->sonidosScorpion.push_back( Mix_LoadWAV("./son/ScorpionComeHer.wav"));
	this->sonidosScorpion.push_back(Mix_LoadWAV("./son/ScoSpea2.wav"));//no lo reproduce
	

	//Golpes
	 //High punch
	//this->sonidosScorpion.push_back(Mix_LoadWAV("./son/LiuFire.wav"));
	//Light punch
	//this->sonidosScorpion.push_back(Mix_LoadWAV("./son/LiuFire.wav"));
	//Hig kick
	this->sonidosScorpion.push_back(Mix_LoadWAV("./son/hk-Scorpion.wav"));
	//Salto
	this->sonidosScorpion.push_back(Mix_LoadWAV("./son/Scorpion-GolpeAereo-SaltoVertical.wav"));
	//Daño
	//Golpeado por upercat = efecto toasty

	//Wins ScorpionWins
	this->sonidosScorpion.push_back(Mix_LoadWAV("./son/scorpionwins.wav"));
	
}

void Sonidos::cargaSonidoLiuKang()
{
	//Bola de fuego
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/Liuwada.wav"));
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/LiuFire.wav")); 
	//HighKick
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/LiuhuaHighKick.wav"));
	//light kick
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/LiuKang-LowKick.wav"));

	//hight punch
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/Liuwada.wav"));
	//light punch
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/Liuwada.wav"));
	//Uppercut
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/Liuwada.wav")); 
	//Golepado por upercut
	this->sonidosLiuKang.push_back(Mix_LoadWAV("./son/liuKangGolpeadoUpercut.wav"));
	//wins liukanWins
	this->sonidosFx.push_back(Mix_LoadWAV("./son/liuwins.wav"));
	
}

void Sonidos::cargaSonidoEfectos()
{	
	
	//Seleccion de personaje
	//AperturaMenu,Choose your destiny,Hahahaaa,excelent,SelccionModo
	this->sonidosFx.push_back(Mix_LoadWAV("./son/eerie2.wav"));               
	this->sonidosFx.push_back(Mix_LoadWAV("./son/CYD4.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/Hahahaaa.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/Excellent.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/modoJuego.mp3"));
	
	
	//Round ,one,two,three,fight,finish him,fatality,
	this->sonidosFx.push_back(Mix_LoadWAV("./son/Round.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/one.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/two.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/three.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/Fight2.wav"));
    this->sonidosFx.push_back(Mix_LoadWAV("./son/FinHim2.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/mk4fata.wav"));
	
	
	//Sonido de fondo
	this->sonidosFx.push_back(Mix_LoadWAV("./son/wind.wav"));

	

	//Sangre
	this->sonidosFx.push_back(Mix_LoadWAV("./son/Blood1.wav"));
	this->sonidosFx.push_back(Mix_LoadWAV("./son/Blood2.wav"));

	//Toasty
	this->sonidosFx.push_back(Mix_LoadWAV("./son/toasty.wav"));
	
	
}

Mix_Chunk* Sonidos::getSonidoEfectos(int posicion)
{
	return this->sonidosFx.at(posicion);
}

Mix_Chunk* Sonidos::getSonidoLiuKang(int posicion)
{
	return this->sonidosLiuKang.at(posicion);   
}

Mix_Chunk* Sonidos::getSonidoScorpion(int posicion)
{
	return this->sonidosScorpion.at(posicion);
}

Sonidos::~Sonidos()
{   //liberamos sonido lista de efectos
	for (int i = 0; i < this->sonidosFx.size(); i++)
	{
		Mix_FreeChunk(this->sonidosFx.at(i)); 
	}
	//liberamos sonidos de liuKang
	for (int i = 0; i < this->sonidosLiuKang.size(); i++)
	{
		Mix_FreeChunk(this->sonidosLiuKang.at(i));
	}

	//Liberamos sonidos de Scorpion
	for (int i = 0; i < this->sonidosScorpion.size(); i++)
	{
		Mix_FreeChunk(this->sonidosScorpion.at(i));
	}

}
