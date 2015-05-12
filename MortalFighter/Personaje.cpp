#include "stdafx.h"
#include "Personaje.h"
#include "Parser.h"
#include "ManejadorULogicas.h"
#include "Sprites.h"

Personaje::Personaje(float anchoPersonaje, float altoPersonaje, int zIndexPersonaje, std::string unaorientacion, std::string spritesPersonaje, std::string CaminarParaAdelante, std::string CaminarParaAtras, std::string QuietoPersonaje, std::string SaltoPersonaje, std::string SaltoDiagonalPersonaje, std::string CaidaPersonaje, std::string PatadaAltaPersonaje, std::string GolpeadoPersonaje, std::string AgachadoPersonaje, std::string nombrePersonaje)
{
	ancho = anchoPersonaje;
	alto = altoPersonaje;
	zIndex = zIndexPersonaje;
	orientacion = unaorientacion;
	energy = 100;
	sprites = spritesPersonaje;
	caminaradelante = CaminarParaAdelante;
	caminaratras = CaminarParaAtras;
	quieto = QuietoPersonaje;
	salto = SaltoPersonaje;
	saltodiagonal = SaltoDiagonalPersonaje;
	caida = CaidaPersonaje;	
	nombreP = nombrePersonaje;
	//xjose
	patadaalta = PatadaAltaPersonaje;
	agachado = AgachadoPersonaje;
	golpeado = GolpeadoPersonaje;
}

float Personaje::getAncho() const
{
	return ancho;
}

float Personaje::getAlto() const
{
	return alto;
}

int Personaje::getZIndex() 
{
	return zIndex;
}

std::string Personaje::getSprite() const
{
	return sprites;
}




std::string Personaje::getCaminarParaAdelante() const
{
	return caminaradelante;
}

std::string Personaje:: getCaminarParaAtras() const
{
	return caminaratras;
}

std::string Personaje::getQuieto() const
{
	return quieto;
}

std::string Personaje::getSalto() const
{
	return salto;
}

std::string Personaje::getSaltoDiagonal() const
{
	return saltodiagonal;
}

std::string Personaje::getCaida() const
{
	return caida;
}

//xjose
std::string Personaje::getPatadaAlta() const
{
	return patadaalta;
}
std::string Personaje::getGolpeado() const
{
	return golpeado;
}

std::string Personaje::getAgacharse() const
{
	return agachado;
}

int  Personaje::getEnergy() 
{
	return this->energy;
}

void Personaje::setEnergy(int nuevaEnergia)
{
	this->energy = nuevaEnergia;
}

std::string Personaje::getNombre() const
{
	return nombreP;
}


//***************************************
std::string Personaje::getOrientacion() const
{
	return orientacion;
}


std::pair<int, int> Personaje::getPosicionPx() const
{
	ManejadorULogicas manejador;	
	float yCorrido = Parser::getInstancia().getEscenario().getAlto() - alto;
	float yRel = yCorrido - posicionUn.second;

	int yRelPx = manejador.darLongPixels(yRel, Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xRelPx = manejador.darLongPixels(posicionUn.first);

	return std::make_pair(xRelPx, yRelPx);
}

std::pair<int, int> Personaje::getPosicionPx(int altoSprite) const
{
	ManejadorULogicas manejador;
	float yCorrido = Parser::getInstancia().getEscenario().getAlto() - altoSprite + alto/4 ;
	float yRel = yCorrido - posicionUn.second;

	int yRelPx = manejador.darLongPixels(yRel, Parser::getInstancia().getVentana().getAltoPx(), Parser::getInstancia().getEscenario().getAlto());
	int xRelPx = manejador.darLongPixels(posicionUn.first);

	return std::make_pair(xRelPx, yRelPx);
}

std::pair<float, float> Personaje::getPosicionUn()const
{
	return posicionUn;
}

void Personaje::setPosicionUn(float x, float y)
{
	posicionUn = std::make_pair(x, y);	
}

float Personaje::getDeltaX() const
{
	return deltaX;
}

ESTADO Personaje::getEstado() const
{
	return estadoActual;
}

void Personaje::setEstado(ESTADO nuevoEstado)
{
	estadoActual = nuevoEstado;
}

//SETTERS
void Personaje::setDeltaX(float unDeltaX){
	deltaX = unDeltaX;
}

void Personaje::setAncho(float unAncho){
	ancho = unAncho;
}

void Personaje::setAlto(float unAlto){
	alto = unAlto;
}

void Personaje::setZIndex(int unZindex){
	zIndex = unZindex;
}

void Personaje::setOrientacion(std::string unaOrientacion){
	orientacion = unaOrientacion;
}

void Personaje::setSprites(std::string unosSprites){
	sprites = unosSprites;
}

void Personaje::setCaminarParaAdelante(std::string unCaminarParaAdelante){
	caminaradelante = unCaminarParaAdelante;
}

void Personaje::setCaminarParaAtras(std::string unCaminarParaAtras){
	caminaratras = unCaminarParaAtras;
}

void Personaje::setQuieto(std::string unQuieto){
	quieto = unQuieto;
}

void Personaje::setSalto(std::string unSalto){
	salto = unSalto;
}

void Personaje::setSaltoDiagonal(std::string unSaltoDiagonal){
	saltodiagonal = unSaltoDiagonal;
}

void Personaje::setCaida(std::string UnaCaida){
	caida = UnaCaida;
}

void Personaje::setNombre(std::string unNombre){
	nombreP = unNombre;
}

void Personaje::setPatadaAlta(std::string unaPatadaAlta){
	patadaalta = unaPatadaAlta;
}

void Personaje::setAgacharse(std::string unAgacharse){
	agachado = unAgacharse;
}

void Personaje::setGolpeado(std::string unGolpeado){
	golpeado = unGolpeado;
}


void Personaje::actualizar(float xNuevo, float yNuevo, ESTADO nuevoEstado)
{
	deltaX = posicionUn.first - xNuevo;	
	setPosicionUn(xNuevo, yNuevo);	
	setEstado(nuevoEstado);
}

Personaje::~Personaje()
{

}