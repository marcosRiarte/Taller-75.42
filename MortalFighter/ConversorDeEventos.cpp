#include "stdafx.h"
#include "ConversorDeEventos.h"


ConversorDeEventos::KeyAndScanCode ConversorDeEventos::getKeyYScanCodeDeTecla(std::string tecla){
	KeyAndScanCode keyAndScanCode;

	if (tecla == "0"){
		keyAndScanCode.keyCode = SDLK_0;
		keyAndScanCode.scanCode = SDL_SCANCODE_0;
		return keyAndScanCode;
	}
	if (tecla == "1"){
		keyAndScanCode.keyCode = SDLK_1;
		keyAndScanCode.scanCode = SDL_SCANCODE_1;
		return keyAndScanCode;
	}
	if (tecla == "2"){
		keyAndScanCode.keyCode = SDLK_2;
		keyAndScanCode.scanCode = SDL_SCANCODE_2;
		return keyAndScanCode;
	}
	if (tecla == "3"){
		keyAndScanCode.keyCode = SDLK_3;
		keyAndScanCode.scanCode = SDL_SCANCODE_3;
		return keyAndScanCode;
	}
	if (tecla == "4"){
		keyAndScanCode.keyCode = SDLK_4;
		keyAndScanCode.scanCode = SDL_SCANCODE_4;
		return keyAndScanCode;
	}
	if (tecla == "5"){
		keyAndScanCode.keyCode = SDLK_5;
		keyAndScanCode.scanCode = SDL_SCANCODE_5;
		return keyAndScanCode;
	}
	if (tecla == "6"){
		keyAndScanCode.keyCode = SDLK_6;
		keyAndScanCode.scanCode = SDL_SCANCODE_6;
		return keyAndScanCode;
	}
	if (tecla == "7"){
		keyAndScanCode.keyCode = SDLK_7;
		keyAndScanCode.scanCode = SDL_SCANCODE_7;
		return keyAndScanCode;
	}
	if (tecla == "8"){
		keyAndScanCode.keyCode = SDLK_8;
		keyAndScanCode.scanCode = SDL_SCANCODE_8;
		return keyAndScanCode;
	}
	if (tecla == "9"){
		keyAndScanCode.keyCode = SDLK_9;
		keyAndScanCode.scanCode = SDL_SCANCODE_9;
		return keyAndScanCode;
	}
	if (tecla == "q" || tecla == "Q"){
		keyAndScanCode.keyCode = SDLK_q;
		keyAndScanCode.scanCode = SDL_SCANCODE_Q;
		return keyAndScanCode;
	}
	if (tecla == "w" || tecla == "W"){
		keyAndScanCode.keyCode = SDLK_w;
		keyAndScanCode.scanCode = SDL_SCANCODE_W;
		return keyAndScanCode;
	}
	if (tecla == "e" || tecla == "E"){
		keyAndScanCode.keyCode = SDLK_e;
		keyAndScanCode.scanCode = SDL_SCANCODE_E;
		return keyAndScanCode;
	}
	if (tecla == "r" || tecla == "R"){
		keyAndScanCode.keyCode = SDLK_r;
		keyAndScanCode.scanCode = SDL_SCANCODE_R;
		return keyAndScanCode;
	}
	if (tecla == "t" || tecla == "T"){
		keyAndScanCode.keyCode = SDLK_t;
		keyAndScanCode.scanCode = SDL_SCANCODE_T;
		return keyAndScanCode;
	}
	if (tecla == "y" || tecla == "Y"){
		keyAndScanCode.keyCode = SDLK_y;
		keyAndScanCode.scanCode = SDL_SCANCODE_Y;
		return keyAndScanCode;
	}
	if (tecla == "u" || tecla == "U"){
		keyAndScanCode.keyCode = SDLK_u;
		keyAndScanCode.scanCode = SDL_SCANCODE_U;
		return keyAndScanCode;
	}
	if (tecla == "i" || tecla == "I"){
		keyAndScanCode.keyCode = SDLK_i;
		keyAndScanCode.scanCode = SDL_SCANCODE_I;
		return keyAndScanCode;
	}
	if (tecla == "p" || tecla == "O"){
		keyAndScanCode.keyCode = SDLK_p;
		keyAndScanCode.scanCode = SDL_SCANCODE_O;
		return keyAndScanCode;
	}
	if (tecla == "a" || tecla == "A"){
		keyAndScanCode.keyCode = SDLK_a;
		keyAndScanCode.scanCode = SDL_SCANCODE_A;
		return keyAndScanCode;
	}
	if (tecla == "s" || tecla == "S"){
		keyAndScanCode.keyCode = SDLK_s;
		keyAndScanCode.scanCode = SDL_SCANCODE_S;
		return keyAndScanCode;
	}
	if (tecla == "d" || tecla == "D"){
		keyAndScanCode.keyCode = SDLK_d;
		keyAndScanCode.scanCode = SDL_SCANCODE_D;
		return keyAndScanCode;
	}
	if (tecla == "f" || tecla == "F"){
		keyAndScanCode.keyCode = SDLK_f;
		keyAndScanCode.scanCode = SDL_SCANCODE_F;
		return keyAndScanCode;
	}
	if (tecla == "g" || tecla == "G"){
		keyAndScanCode.keyCode = SDLK_g;
		keyAndScanCode.scanCode = SDL_SCANCODE_G;
		return keyAndScanCode;
	}
	if (tecla == "h" || tecla == "H"){
		keyAndScanCode.keyCode = SDLK_h;
		keyAndScanCode.scanCode = SDL_SCANCODE_H;
		return keyAndScanCode;
	}
	if (tecla == "j" || tecla == "J"){
		keyAndScanCode.keyCode = SDLK_j;
		keyAndScanCode.scanCode = SDL_SCANCODE_J;
		return keyAndScanCode;
	}
	if (tecla == "k" || tecla == "K"){
		keyAndScanCode.keyCode = SDLK_k;
		keyAndScanCode.scanCode = SDL_SCANCODE_K;
		return keyAndScanCode;
	}
	if (tecla == "l" || tecla == "L"){
		keyAndScanCode.keyCode = SDLK_l;
		keyAndScanCode.scanCode = SDL_SCANCODE_L;
		return keyAndScanCode;
	}
	if (tecla == "z" || tecla == "Z"){
		keyAndScanCode.keyCode = SDLK_z;
		keyAndScanCode.scanCode = SDL_SCANCODE_Z;
		return keyAndScanCode;
	}
	if (tecla == "x" || tecla == "X"){
		keyAndScanCode.keyCode = SDLK_x;
		keyAndScanCode.scanCode = SDL_SCANCODE_X;
		return keyAndScanCode;
	}
	if (tecla == "c" || tecla == "C"){
		keyAndScanCode.keyCode = SDLK_c;
		keyAndScanCode.scanCode = SDL_SCANCODE_C;
		return keyAndScanCode;
	}
	if (tecla == "v" || tecla == "V"){
		keyAndScanCode.keyCode = SDLK_v;
		keyAndScanCode.scanCode = SDL_SCANCODE_V;
		return keyAndScanCode;
	}
	if (tecla == "b" || tecla == "B"){
		keyAndScanCode.keyCode = SDLK_b;
		keyAndScanCode.scanCode = SDL_SCANCODE_B;
		return keyAndScanCode;
	}
	if (tecla == "n" || tecla == "N"){
		keyAndScanCode.keyCode = SDLK_n;
		keyAndScanCode.scanCode = SDL_SCANCODE_N;
		return keyAndScanCode;
	}
	if (tecla == "m" || tecla == "M"){
		keyAndScanCode.keyCode = SDLK_m;
		keyAndScanCode.scanCode = SDL_SCANCODE_M;
		return keyAndScanCode;
	}
	if (tecla == "esc" || tecla == "Esc" || tecla == "ESC" || tecla == "ESCAPE" || tecla == "escape" || tecla == "Escape"){
		keyAndScanCode.keyCode = SDLK_ESCAPE;
		keyAndScanCode.scanCode = SDL_SCANCODE_ESCAPE;
		return keyAndScanCode;
	}
	if (tecla == "Space" || tecla == "space" || tecla == "SPACE"){
		keyAndScanCode.keyCode = SDLK_SPACE;
		keyAndScanCode.scanCode = SDL_SCANCODE_SPACE;
		return keyAndScanCode;
	}
	if (tecla == "Ctrl" || tecla == "ctrl" || tecla == "CTRL" || tecla == "Control" || tecla == "control" || tecla == "CONTROL"){
		keyAndScanCode.keyCode = SDLK_LCTRL;
		keyAndScanCode.scanCode = SDL_SCANCODE_LCTRL;
		return keyAndScanCode;
	}
	if (tecla == "Shift" || tecla == "shift" || tecla == "SHIFT"){
		keyAndScanCode.keyCode = SDLK_LSHIFT;
		keyAndScanCode.scanCode = SDL_SCANCODE_LSHIFT;
		return keyAndScanCode;
	}
	if (tecla == "Alt" || tecla == "alt" || tecla == "ALT"){
		keyAndScanCode.keyCode = SDLK_LALT;
		keyAndScanCode.scanCode = SDL_SCANCODE_LALT;
		return keyAndScanCode;
	}
	if (tecla == "Alt Gr" || tecla == "alt gr" || tecla == "ALT GR" || tecla == "Alt gr" || tecla == "AltGr" || tecla == "altgr" || tecla == "ALTGR" || tecla == "Altgr"){
		keyAndScanCode.keyCode = SDLK_RALT;
		keyAndScanCode.scanCode = SDL_SCANCODE_RALT;
		return keyAndScanCode;
	}
	if (tecla == "Bloq Mayus" || tecla == "bloq mayus" || tecla == "BLOQ MAYUS" || tecla == "Bloq mayus" || tecla == "BloqMayus" || tecla == "bloqmayus" || tecla == "BLOQMAYUS" || tecla == "Bloqmayus" || tecla == "Caps Lock" || tecla == "caps lock" || tecla == "Caps lock" || tecla == "CAPS LOCK" || tecla == "CapsLock" || tecla == "capslock" || tecla == "Capslock" || tecla == "CAPSLOCK"){
		keyAndScanCode.keyCode = SDLK_CAPSLOCK;
		keyAndScanCode.scanCode = SDL_SCANCODE_CAPSLOCK;
		return keyAndScanCode;
	}
	if (tecla == "Tab" || tecla == "tab" || tecla == "TAB"){
		keyAndScanCode.keyCode = SDLK_TAB;
		keyAndScanCode.scanCode = SDL_SCANCODE_TAB;
		return keyAndScanCode;
	}
	if (tecla == "f1" || tecla == "F1"){
		keyAndScanCode.keyCode = SDLK_F1;
		keyAndScanCode.scanCode = SDL_SCANCODE_F1;
		return keyAndScanCode;
	}
	if (tecla == "f2" || tecla == "F2"){
		keyAndScanCode.keyCode = SDLK_F2;
		keyAndScanCode.scanCode = SDL_SCANCODE_F2;
		return keyAndScanCode;
	}
	if (tecla == "f3" || tecla == "F3"){
		keyAndScanCode.keyCode = SDLK_F3;
		keyAndScanCode.scanCode = SDL_SCANCODE_F3;
		return keyAndScanCode;
	}
	if (tecla == "f4" || tecla == "F4"){
		keyAndScanCode.keyCode = SDLK_F4;
		keyAndScanCode.scanCode = SDL_SCANCODE_F4;
		return keyAndScanCode;
	}
	if (tecla == "f5" || tecla == "F5"){
		keyAndScanCode.keyCode = SDLK_F5;
		keyAndScanCode.scanCode = SDL_SCANCODE_F5;
		return keyAndScanCode;
	}
	if (tecla == "f6" || tecla == "F6"){
		keyAndScanCode.keyCode = SDLK_F6;
		keyAndScanCode.scanCode = SDL_SCANCODE_F6;
		return keyAndScanCode;
	}
	if (tecla == "f7" || tecla == "F7"){
		keyAndScanCode.keyCode = SDLK_F7;
		keyAndScanCode.scanCode = SDL_SCANCODE_F7;
		return keyAndScanCode;
	}
	if (tecla == "f8" || tecla == "F8"){
		keyAndScanCode.keyCode = SDLK_F8;
		keyAndScanCode.scanCode = SDL_SCANCODE_F8;
		return keyAndScanCode;
	}
	if (tecla == "f9" || tecla == "F9"){
		keyAndScanCode.keyCode = SDLK_F9;
		keyAndScanCode.scanCode = SDL_SCANCODE_F9;
		return keyAndScanCode;
	}
	if (tecla == "enter" || tecla == "Enter" || tecla == "ENTER" || tecla == "Return" || tecla == "return" || tecla == "RETURN"){
		keyAndScanCode.keyCode = SDLK_RETURN;
		keyAndScanCode.scanCode = SDL_SCANCODE_RETURN;
		return keyAndScanCode;
	}
	if (tecla == "back" || tecla == "Back" || tecla == "BACK" || tecla == "BACKSPACE" || tecla == "BackSpace" || tecla == "Backspace" || tecla == "backspace" || tecla == "Back Space" || tecla == "BACK SPACE" || tecla == "Back space" || tecla == "back space"){
		keyAndScanCode.keyCode = SDLK_BACKSPACE;
		keyAndScanCode.scanCode = SDL_SCANCODE_BACKSPACE;
		return keyAndScanCode;
	}
	if (tecla == "up" || tecla == "Up" || tecla == "UP" || tecla == "arriba" || tecla == "Arriba" || tecla == "ARRIBA"){
		keyAndScanCode.keyCode = SDLK_UP;
		keyAndScanCode.scanCode = SDL_SCANCODE_UP;
		return keyAndScanCode;
	}
	if (tecla == "down" || tecla == "Down" || tecla == "DOWN" || tecla == "abajo" || tecla == "Abajo" || tecla == "ABAJO"){
		keyAndScanCode.keyCode = SDLK_DOWN;
		keyAndScanCode.scanCode = SDL_SCANCODE_DOWN;
		return keyAndScanCode;
	}
	if (tecla == "izquierda" || tecla == "Izquierda" || tecla == "IZQUIERDA" || tecla == "left" || tecla == "Left" || tecla == "LEFT"){
		keyAndScanCode.keyCode = SDLK_LEFT;
		keyAndScanCode.scanCode = SDL_SCANCODE_LEFT;
		return keyAndScanCode;
	}
	if (tecla == "right" || tecla == "Right" || tecla == "RIGHT" || tecla == "derecha" || tecla == "Derecha" || tecla == "DERECHA"){
		keyAndScanCode.keyCode = SDLK_RIGHT;
		keyAndScanCode.scanCode = SDL_SCANCODE_RIGHT;
		return keyAndScanCode;
	}
	
}



ConversorDeEventos::ConversorDeEventos()
{
}


void ConversorDeEventos::setAccionesPorDefecto(){

}


void ConversorDeEventos::setAccion(Acciones unaAccion, std::string keyName){
	Accion nuevaAccion;
	KeyAndScanCode keyYScanCode;
	nuevaAccion.accion = unaAccion;
	keyYScanCode = getKeyYScanCodeDeTecla(keyName);
	nuevaAccion.keyCodeDelEvento = keyYScanCode.keyCode;
	nuevaAccion.scanCodeDelEvento = keyYScanCode.scanCode;
	acciones[unaAccion] = nuevaAccion;
}


SDL_Keycode ConversorDeEventos::getKeyCodeDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].keyCodeDelEvento);
}


SDL_Scancode ConversorDeEventos::getScanCodeDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].scanCodeDelEvento);
}


ConversorDeEventos::~ConversorDeEventos()
{
}
