#pragma once
class ConversorDeEventos
{
public:
	enum Acciones {UP, DOWN, RIGHT, LEFT, HOLD, LOW_PUNCH, HIGH_PUNCH, LOW_KICK, HIGH_KICK, WEAPON, QUIT, REBOOT};

	ConversorDeEventos();
	void setAccion(Acciones unaAccion, std::string keyName);
	void setAccionesPorDefecto();
	SDL_Keycode getKeyCodeDeLaAccion(Acciones unaAccion);
	SDL_Scancode getScanCodeDeLaAccion(Acciones unaAccion);
	~ConversorDeEventos();

private:
	struct Accion{
		SDL_Keycode keyCodeDelEvento;
		SDL_Scancode scanCodeDelEvento;
		Acciones accion;
	};

	struct KeyAndScanCode{
		SDL_Keycode keyCode;
		SDL_Scancode scanCode;
	};

	Accion acciones[13];

	KeyAndScanCode getKeyYScanCodeDeTecla(std::string tecla);

};

