#include "stdafx.h"
#include "ConversorDeEventos.h"


ConversorDeEventos::CodigosDeEvento ConversorDeEventos::getCodigosDeEventoDeTecla(std::string tecla){
	CodigosDeEvento keyAndScanCode;
	keyAndScanCode.jBoton = NULO;
	keyAndScanCode.joystick = NULO;
	keyAndScanCode.keyCode = NULL;
	keyAndScanCode.scanCode = SDL_SCANCODE_INTERNATIONAL9;

	//TECLADO
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
	if (tecla == "o" || tecla == "O"){
		keyAndScanCode.keyCode = SDLK_o;
		keyAndScanCode.scanCode = SDL_SCANCODE_O;
		return keyAndScanCode;
	}
	if (tecla == "p" || tecla == "P"){
		keyAndScanCode.keyCode = SDLK_p;
		keyAndScanCode.scanCode = SDL_SCANCODE_P;
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

	//JOYSTICK 1
	if (tecla == "j1_0" || tecla == "J1_0" || tecla == "j1_Button_0" || tecla == "J1_Button_0" || tecla == "j1_button_0" || tecla == "J1_button_0" || tecla == "J1_BUTTON_0" || tecla == "j1_Boton_0" || tecla == "J1_Boton_0" || tecla == "j1_boton_0" || tecla == "J1_boton_0" || tecla == "J1_BOTON_0"){
		keyAndScanCode.jBoton = 0;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_1" || tecla == "J1_1" || tecla == "j1_Button_1" || tecla == "J1_Button_1" || tecla == "j1_button_1" || tecla == "J1_button_1" || tecla == "J1_BUTTON_1" || tecla == "j1_Boton_1" || tecla == "J1_Boton_1" || tecla == "j1_boton_1" || tecla == "J1_boton_1" || tecla == "J1_BOTON_1"){
		keyAndScanCode.jBoton = 1;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_2" || tecla == "J1_2" || tecla == "j1_Button_2" || tecla == "J1_Button_2" || tecla == "j1_button_2" || tecla == "J1_button_2" || tecla == "J1_BUTTON_2" || tecla == "j1_Boton_2" || tecla == "J1_Boton_2" || tecla == "j1_boton_2" || tecla == "J1_boton_2" || tecla == "J1_BOTON_2"){
		keyAndScanCode.jBoton = 2;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_3" || tecla == "J1_3" || tecla == "j1_Button_3" || tecla == "J1_Button_3" || tecla == "j1_button_3" || tecla == "J1_button_3" || tecla == "J1_BUTTON_3" || tecla == "j1_Boton_3" || tecla == "J1_Boton_3" || tecla == "j1_boton_3" || tecla == "J1_boton_3" || tecla == "J1_BOTON_3"){
		keyAndScanCode.jBoton = 3;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_4" || tecla == "J1_4" || tecla == "j1_Button_4" || tecla == "J1_Button_4" || tecla == "j1_button_4" || tecla == "J1_button_4" || tecla == "J1_BUTTON_4" || tecla == "j1_Boton_4" || tecla == "J1_Boton_4" || tecla == "j1_boton_4" || tecla == "J1_boton_4" || tecla == "J1_BOTON_4"){
		keyAndScanCode.jBoton = 4;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_5" || tecla == "J1_5" || tecla == "j1_Button_5" || tecla == "J1_Button_5" || tecla == "j1_button_5" || tecla == "J1_button_5" || tecla == "J1_BUTTON_5" || tecla == "j1_Boton_5" || tecla == "J1_Boton_5" || tecla == "j1_boton_5" || tecla == "J1_boton_5" || tecla == "J1_BOTON_5"){
		keyAndScanCode.jBoton = 5;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_6" || tecla == "J1_6" || tecla == "j1_Button_6" || tecla == "J1_Button_6" || tecla == "j1_button_6" || tecla == "J1_button_6" || tecla == "J1_BUTTON_6" || tecla == "j1_Boton_6" || tecla == "J1_Boton_6" || tecla == "j1_boton_6" || tecla == "J1_boton_6" || tecla == "J1_BOTON_6"){
		keyAndScanCode.jBoton = 6;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_7" || tecla == "J1_7" || tecla == "j1_Button_7" || tecla == "J1_Button_7" || tecla == "j1_button_7" || tecla == "J1_button_7" || tecla == "J1_BUTTON_7" || tecla == "j1_Boton_7" || tecla == "J1_Boton_7" || tecla == "j1_boton_7" || tecla == "J1_boton_7" || tecla == "J1_BOTON_7"){
		keyAndScanCode.jBoton = 7;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_8" || tecla == "J1_8" || tecla == "j1_Button_8" || tecla == "J1_Button_8" || tecla == "j1_button_8" || tecla == "J1_button_8" || tecla == "J1_BUTTON_8" || tecla == "j1_Boton_8" || tecla == "J1_Boton_8" || tecla == "j1_boton_8" || tecla == "J1_boton_8" || tecla == "J1_BOTON_8"){
		keyAndScanCode.jBoton = 8;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}
	if (tecla == "j1_9" || tecla == "J1_9" || tecla == "j1_Button_9" || tecla == "J1_Button_9" || tecla == "j1_button_9" || tecla == "J1_button_9" || tecla == "J1_BUTTON_9" || tecla == "j1_Boton_9" || tecla == "J1_Boton_9" || tecla == "j1_boton_9" || tecla == "J1_boton_9" || tecla == "J1_BOTON_9"){
		keyAndScanCode.jBoton = 9;
		keyAndScanCode.joystick = 0;
		return keyAndScanCode;
	}

	//JOYSTICK 2
	if (tecla == "j2_0" || tecla == "J2_0" || tecla == "j2_Button_0" || tecla == "J2_Button_0" || tecla == "j2_button_0" || tecla == "J2_button_0" || tecla == "J2_BUTTON_0" || tecla == "j2_Boton_0" || tecla == "J2_Boton_0" || tecla == "j2_boton_0" || tecla == "J2_boton_0" || tecla == "J2_BOTON_0"){
		keyAndScanCode.jBoton = 0;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_1" || tecla == "J2_1" || tecla == "j2_Button_1" || tecla == "J2_Button_1" || tecla == "j2_button_1" || tecla == "J2_button_1" || tecla == "J2_BUTTON_1" || tecla == "j2_Boton_1" || tecla == "J2_Boton_1" || tecla == "j2_boton_1" || tecla == "J2_boton_1" || tecla == "J2_BOTON_1"){
		keyAndScanCode.jBoton = 1;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_2" || tecla == "J2_2" || tecla == "j2_Button_2" || tecla == "J2_Button_2" || tecla == "j2_button_2" || tecla == "J2_button_2" || tecla == "J2_BUTTON_2" || tecla == "j2_Boton_2" || tecla == "J2_Boton_2" || tecla == "j2_boton_2" || tecla == "J2_boton_2" || tecla == "J2_BOTON_2"){
		keyAndScanCode.jBoton = 2;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_3" || tecla == "J2_3" || tecla == "j2_Button_3" || tecla == "J2_Button_3" || tecla == "j2_button_3" || tecla == "J2_button_3" || tecla == "J2_BUTTON_3" || tecla == "j2_Boton_3" || tecla == "J2_Boton_3" || tecla == "j2_boton_3" || tecla == "J2_boton_3" || tecla == "J2_BOTON_3"){
		keyAndScanCode.jBoton = 3;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_4" || tecla == "J2_4" || tecla == "j2_Button_4" || tecla == "J2_Button_4" || tecla == "j2_button_4" || tecla == "J2_button_4" || tecla == "J2_BUTTON_4" || tecla == "j2_Boton_4" || tecla == "J2_Boton_4" || tecla == "j2_boton_4" || tecla == "J2_boton_4" || tecla == "J2_BOTON_4"){
		keyAndScanCode.jBoton = 4;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_5" || tecla == "J2_5" || tecla == "j2_Button_5" || tecla == "J2_Button_5" || tecla == "j2_button_5" || tecla == "J2_button_5" || tecla == "J2_BUTTON_5" || tecla == "j2_Boton_5" || tecla == "J2_Boton_5" || tecla == "j2_boton_5" || tecla == "J2_boton_5" || tecla == "J2_BOTON_5"){
		keyAndScanCode.jBoton = 5;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_6" || tecla == "J2_6" || tecla == "j2_Button_6" || tecla == "J1_Button_6" || tecla == "j2_button_6" || tecla == "J2_button_6" || tecla == "J2_BUTTON_6" || tecla == "j2_Boton_6" || tecla == "J2_Boton_6" || tecla == "j2_boton_6" || tecla == "J2_boton_6" || tecla == "J2_BOTON_6"){
		keyAndScanCode.jBoton = 6;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_7" || tecla == "J2_7" || tecla == "j2_Button_7" || tecla == "J2_Button_7" || tecla == "j2_button_7" || tecla == "J2_button_7" || tecla == "J2_BUTTON_7" || tecla == "j2_Boton_7" || tecla == "J2_Boton_7" || tecla == "j2_boton_7" || tecla == "J2_boton_7" || tecla == "J2_BOTON_7"){
		keyAndScanCode.jBoton = 7;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_8" || tecla == "J2_8" || tecla == "j2_Button_8" || tecla == "J2_Button_8" || tecla == "j2_button_8" || tecla == "J2_button_8" || tecla == "J2_BUTTON_8" || tecla == "j2_Boton_8" || tecla == "J2_Boton_8" || tecla == "j2_boton_8" || tecla == "J2_boton_8" || tecla == "J2_BOTON_8"){
		keyAndScanCode.jBoton = 8;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}
	if (tecla == "j2_9" || tecla == "J2_9" || tecla == "j2_Button_9" || tecla == "J2_Button_9" || tecla == "j2_button_9" || tecla == "J2_button_9" || tecla == "J2_BUTTON_9" || tecla == "j2_Boton_9" || tecla == "J2_Boton_9" || tecla == "j2_boton_9" || tecla == "J2_boton_9" || tecla == "J2_BOTON_9"){
		keyAndScanCode.jBoton = 9;
		keyAndScanCode.joystick = 1;
		return keyAndScanCode;
	}

	return keyAndScanCode;
}



ConversorDeEventos::ConversorDeEventos()
{
}


bool ConversorDeEventos::setAccion(Acciones unaAccion, std::string keyName){
	Accion nuevaAccion;
	CodigosDeEvento codigosDeEvento;
	nuevaAccion.accion = unaAccion;
	codigosDeEvento = getCodigosDeEventoDeTecla(keyName);
	nuevaAccion.keyCodeDelEvento = codigosDeEvento.keyCode;
	nuevaAccion.scanCodeDelEvento = codigosDeEvento.scanCode;
	nuevaAccion.jBoton = codigosDeEvento.jBoton;
	nuevaAccion.numeroDeJoystick = codigosDeEvento.joystick;
	acciones[unaAccion] = nuevaAccion;
	if (!codigosDeEvento.keyCode && codigosDeEvento.joystick == NULO){
		return false;
	}
	return true;
}


SDL_Keycode ConversorDeEventos::getKeyCodeDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].keyCodeDelEvento);
}


SDL_Scancode ConversorDeEventos::getScanCodeDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].scanCodeDelEvento);
}


int ConversorDeEventos::getJbotonDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].jBoton);
}


int ConversorDeEventos::geNnumeroDeJoystickDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].numeroDeJoystick);
}


ConversorDeEventos::~ConversorDeEventos()
{
}