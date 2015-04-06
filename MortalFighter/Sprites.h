#pragma once
class Sprites
{
public:
	Sprites();
	Sprites(std::string);

	void determinarClips();
	int seleccionarClips(MOV_TIPO);//Devuelve el numero de clip segun las teclas pulsadas
	void dibujarClip();//Va a la vista
	std::string Sprites::getPath();
	void setPath(std::string nuevoPath);	
	~Sprites();

private:
	std::string path;
};

