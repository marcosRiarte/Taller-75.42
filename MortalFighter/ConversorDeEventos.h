#pragma once
class ConversorDeEventos
{
public:
	#define NULO 9999999 
	enum Acciones {UP, DOWN, RIGHT, LEFT, HOLD, LOW_PUNCH, HIGH_PUNCH, LOW_KICK, HIGH_KICK, WEAPON, QUIT, REBOOT};

	ConversorDeEventos();
	bool setAccion(Acciones unaAccion, std::string keyName);
	SDL_Keycode getKeyCodeDeLaAccion(Acciones unaAccion);
	SDL_Scancode getScanCodeDeLaAccion(Acciones unaAccion);
	int getJbotonDeLaAccion(Acciones unaAccion);
	int geNnumeroDeJoystickDeLaAccion(Acciones unaAccion);
	~ConversorDeEventos();

private:
	struct Accion{
		SDL_Keycode keyCodeDelEvento;
		SDL_Scancode scanCodeDelEvento;
		int	jBoton;
		int numeroDeJoystick;
		Acciones accion;
	};

	struct CodigosDeEvento{
		SDL_Keycode keyCode;
		SDL_Scancode scanCode;
		int joystick;
		int jBoton;
	};

	Accion acciones[13];

	CodigosDeEvento getCodigosDeEventoDeTecla(std::string tecla);

};

