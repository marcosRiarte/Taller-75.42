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
	bool hayEjeParaLaAccion(Acciones unaAccion);
	Sint16 getValorDesdeDelEjeDeLaAccion(Acciones unaAccion);
	Sint16 getValorHastaDelEjeDeLaAccion(Acciones unaAccion);
	~ConversorDeEventos();

private:
	struct Accion{
		SDL_Keycode keyCodeDelEvento;
		SDL_Scancode scanCodeDelEvento;
		int	jBoton;
		bool eje;
		Sint16 ejeDesde;
		Sint16 ejeHasta;
		int numeroDeJoystick;
		Acciones accion;
	};

	struct CodigosDeEvento{
		SDL_Keycode keyCode;
		SDL_Scancode scanCode;
		bool eje;
		int joystick;
		int jBoton;
		Sint16 ejeDesde;
		Sint16 ejeHasta;
	};

	Accion acciones[13];

	CodigosDeEvento getCodigosDeEventoDeTecla(std::string tecla);

};

