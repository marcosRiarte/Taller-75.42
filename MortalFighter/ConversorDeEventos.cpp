#include "stdafx.h"
#include "ConversorDeEventos.h"


ConversorDeEventos::CodigosDeEvento ConversorDeEventos::getCodigosDeEventoDeTecla(std::string tecla){
	CodigosDeEvento codigosDeEvento;
	codigosDeEvento.jBoton = NULO;
	codigosDeEvento.joystick = NULO;
	codigosDeEvento.keyCode = NULL;
	codigosDeEvento.hat = (Uint8)NULO;
	codigosDeEvento.eje = false;
	codigosDeEvento.flechas = false;
	codigosDeEvento.ejeDesde = -10;
	codigosDeEvento.ejeHasta = -10;
	codigosDeEvento.scanCode = SDL_SCANCODE_INTERNATIONAL9;

	//TECLADO
	if (tecla == "0"){
		codigosDeEvento.keyCode = SDLK_0;
		codigosDeEvento.scanCode = SDL_SCANCODE_0;
		return codigosDeEvento;
	}
	if (tecla == "1"){
		codigosDeEvento.keyCode = SDLK_1;
		codigosDeEvento.scanCode = SDL_SCANCODE_1;
		return codigosDeEvento;
	}
	if (tecla == "2"){
		codigosDeEvento.keyCode = SDLK_2;
		codigosDeEvento.scanCode = SDL_SCANCODE_2;
		return codigosDeEvento;
	}
	if (tecla == "3"){
		codigosDeEvento.keyCode = SDLK_3;
		codigosDeEvento.scanCode = SDL_SCANCODE_3;
		return codigosDeEvento;
	}
	if (tecla == "4"){
		codigosDeEvento.keyCode = SDLK_4;
		codigosDeEvento.scanCode = SDL_SCANCODE_4;
		return codigosDeEvento;
	}
	if (tecla == "5"){
		codigosDeEvento.keyCode = SDLK_5;
		codigosDeEvento.scanCode = SDL_SCANCODE_5;
		return codigosDeEvento;
	}
	if (tecla == "6"){
		codigosDeEvento.keyCode = SDLK_6;
		codigosDeEvento.scanCode = SDL_SCANCODE_6;
		return codigosDeEvento;
	}
	if (tecla == "7"){
		codigosDeEvento.keyCode = SDLK_7;
		codigosDeEvento.scanCode = SDL_SCANCODE_7;
		return codigosDeEvento;
	}
	if (tecla == "8"){
		codigosDeEvento.keyCode = SDLK_8;
		codigosDeEvento.scanCode = SDL_SCANCODE_8;
		return codigosDeEvento;
	}
	if (tecla == "9"){
		codigosDeEvento.keyCode = SDLK_9;
		codigosDeEvento.scanCode = SDL_SCANCODE_9;
		return codigosDeEvento;
	}
	if (tecla == "q" || tecla == "Q"){
		codigosDeEvento.keyCode = SDLK_q;
		codigosDeEvento.scanCode = SDL_SCANCODE_Q;
		return codigosDeEvento;
	}
	if (tecla == "w" || tecla == "W"){
		codigosDeEvento.keyCode = SDLK_w;
		codigosDeEvento.scanCode = SDL_SCANCODE_W;
		return codigosDeEvento;
	}
	if (tecla == "e" || tecla == "E"){
		codigosDeEvento.keyCode = SDLK_e;
		codigosDeEvento.scanCode = SDL_SCANCODE_E;
		return codigosDeEvento;
	}
	if (tecla == "r" || tecla == "R"){
		codigosDeEvento.keyCode = SDLK_r;
		codigosDeEvento.scanCode = SDL_SCANCODE_R;
		return codigosDeEvento;
	}
	if (tecla == "t" || tecla == "T"){
		codigosDeEvento.keyCode = SDLK_t;
		codigosDeEvento.scanCode = SDL_SCANCODE_T;
		return codigosDeEvento;
	}
	if (tecla == "y" || tecla == "Y"){
		codigosDeEvento.keyCode = SDLK_y;
		codigosDeEvento.scanCode = SDL_SCANCODE_Y;
		return codigosDeEvento;
	}
	if (tecla == "u" || tecla == "U"){
		codigosDeEvento.keyCode = SDLK_u;
		codigosDeEvento.scanCode = SDL_SCANCODE_U;
		return codigosDeEvento;
	}
	if (tecla == "i" || tecla == "I"){
		codigosDeEvento.keyCode = SDLK_i;
		codigosDeEvento.scanCode = SDL_SCANCODE_I;
		return codigosDeEvento;
	}
	if (tecla == "o" || tecla == "O"){
		codigosDeEvento.keyCode = SDLK_o;
		codigosDeEvento.scanCode = SDL_SCANCODE_O;
		return codigosDeEvento;
	}
	if (tecla == "p" || tecla == "P"){
		codigosDeEvento.keyCode = SDLK_p;
		codigosDeEvento.scanCode = SDL_SCANCODE_P;
		return codigosDeEvento;
	}
	if (tecla == "a" || tecla == "A"){
		codigosDeEvento.keyCode = SDLK_a;
		codigosDeEvento.scanCode = SDL_SCANCODE_A;
		return codigosDeEvento;
	}
	if (tecla == "s" || tecla == "S"){
		codigosDeEvento.keyCode = SDLK_s;
		codigosDeEvento.scanCode = SDL_SCANCODE_S;
		return codigosDeEvento;
	}
	if (tecla == "d" || tecla == "D"){
		codigosDeEvento.keyCode = SDLK_d;
		codigosDeEvento.scanCode = SDL_SCANCODE_D;
		return codigosDeEvento;
	}
	if (tecla == "f" || tecla == "F"){
		codigosDeEvento.keyCode = SDLK_f;
		codigosDeEvento.scanCode = SDL_SCANCODE_F;
		return codigosDeEvento;
	}
	if (tecla == "g" || tecla == "G"){
		codigosDeEvento.keyCode = SDLK_g;
		codigosDeEvento.scanCode = SDL_SCANCODE_G;
		return codigosDeEvento;
	}
	if (tecla == "h" || tecla == "H"){
		codigosDeEvento.keyCode = SDLK_h;
		codigosDeEvento.scanCode = SDL_SCANCODE_H;
		return codigosDeEvento;
	}
	if (tecla == "j" || tecla == "J"){
		codigosDeEvento.keyCode = SDLK_j;
		codigosDeEvento.scanCode = SDL_SCANCODE_J;
		return codigosDeEvento;
	}
	if (tecla == "k" || tecla == "K"){
		codigosDeEvento.keyCode = SDLK_k;
		codigosDeEvento.scanCode = SDL_SCANCODE_K;
		return codigosDeEvento;
	}
	if (tecla == "l" || tecla == "L"){
		codigosDeEvento.keyCode = SDLK_l;
		codigosDeEvento.scanCode = SDL_SCANCODE_L;
		return codigosDeEvento;
	}
	if (tecla == "z" || tecla == "Z"){
		codigosDeEvento.keyCode = SDLK_z;
		codigosDeEvento.scanCode = SDL_SCANCODE_Z;
		return codigosDeEvento;
	}
	if (tecla == "x" || tecla == "X"){
		codigosDeEvento.keyCode = SDLK_x;
		codigosDeEvento.scanCode = SDL_SCANCODE_X;
		return codigosDeEvento;
	}
	if (tecla == "c" || tecla == "C"){
		codigosDeEvento.keyCode = SDLK_c;
		codigosDeEvento.scanCode = SDL_SCANCODE_C;
		return codigosDeEvento;
	}
	if (tecla == "v" || tecla == "V"){
		codigosDeEvento.keyCode = SDLK_v;
		codigosDeEvento.scanCode = SDL_SCANCODE_V;
		return codigosDeEvento;
	}
	if (tecla == "b" || tecla == "B"){
		codigosDeEvento.keyCode = SDLK_b;
		codigosDeEvento.scanCode = SDL_SCANCODE_B;
		return codigosDeEvento;
	}
	if (tecla == "n" || tecla == "N"){
		codigosDeEvento.keyCode = SDLK_n;
		codigosDeEvento.scanCode = SDL_SCANCODE_N;
		return codigosDeEvento;
	}
	if (tecla == "m" || tecla == "M"){
		codigosDeEvento.keyCode = SDLK_m;
		codigosDeEvento.scanCode = SDL_SCANCODE_M;
		return codigosDeEvento;
	}
	if (tecla == "esc" || tecla == "Esc" || tecla == "ESC" || tecla == "ESCAPE" || tecla == "escape" || tecla == "Escape"){
		codigosDeEvento.keyCode = SDLK_ESCAPE;
		codigosDeEvento.scanCode = SDL_SCANCODE_ESCAPE;
		return codigosDeEvento;
	}
	if (tecla == "Space" || tecla == "space" || tecla == "SPACE"){
		codigosDeEvento.keyCode = SDLK_SPACE;
		codigosDeEvento.scanCode = SDL_SCANCODE_SPACE;
		return codigosDeEvento;
	}
	if (tecla == "Ctrl" || tecla == "ctrl" || tecla == "CTRL" || tecla == "Control" || tecla == "control" || tecla == "CONTROL"){
		codigosDeEvento.keyCode = SDLK_LCTRL;
		codigosDeEvento.scanCode = SDL_SCANCODE_LCTRL;
		return codigosDeEvento;
	}
	if (tecla == "Shift" || tecla == "shift" || tecla == "SHIFT"){
		codigosDeEvento.keyCode = SDLK_LSHIFT;
		codigosDeEvento.scanCode = SDL_SCANCODE_LSHIFT;
		return codigosDeEvento;
	}
	if (tecla == "Alt" || tecla == "alt" || tecla == "ALT"){
		codigosDeEvento.keyCode = SDLK_LALT;
		codigosDeEvento.scanCode = SDL_SCANCODE_LALT;
		return codigosDeEvento;
	}
	if (tecla == "Alt Gr" || tecla == "alt gr" || tecla == "ALT GR" || tecla == "Alt gr" || tecla == "AltGr" || tecla == "altgr" || tecla == "ALTGR" || tecla == "Altgr"){
		codigosDeEvento.keyCode = SDLK_RALT;
		codigosDeEvento.scanCode = SDL_SCANCODE_RALT;
		return codigosDeEvento;
	}
	if (tecla == "Bloq Mayus" || tecla == "bloq mayus" || tecla == "BLOQ MAYUS" || tecla == "Bloq mayus" || tecla == "BloqMayus" || tecla == "bloqmayus" || tecla == "BLOQMAYUS" || tecla == "Bloqmayus" || tecla == "Caps Lock" || tecla == "caps lock" || tecla == "Caps lock" || tecla == "CAPS LOCK" || tecla == "CapsLock" || tecla == "capslock" || tecla == "Capslock" || tecla == "CAPSLOCK"){
		codigosDeEvento.keyCode = SDLK_CAPSLOCK;
		codigosDeEvento.scanCode = SDL_SCANCODE_CAPSLOCK;
		return codigosDeEvento;
	}
	if (tecla == "Tab" || tecla == "tab" || tecla == "TAB"){
		codigosDeEvento.keyCode = SDLK_TAB;
		codigosDeEvento.scanCode = SDL_SCANCODE_TAB;
		return codigosDeEvento;
	}
	if (tecla == "f1" || tecla == "F1"){
		codigosDeEvento.keyCode = SDLK_F1;
		codigosDeEvento.scanCode = SDL_SCANCODE_F1;
		return codigosDeEvento;
	}
	if (tecla == "f2" || tecla == "F2"){
		codigosDeEvento.keyCode = SDLK_F2;
		codigosDeEvento.scanCode = SDL_SCANCODE_F2;
		return codigosDeEvento;
	}
	if (tecla == "f3" || tecla == "F3"){
		codigosDeEvento.keyCode = SDLK_F3;
		codigosDeEvento.scanCode = SDL_SCANCODE_F3;
		return codigosDeEvento;
	}
	if (tecla == "f4" || tecla == "F4"){
		codigosDeEvento.keyCode = SDLK_F4;
		codigosDeEvento.scanCode = SDL_SCANCODE_F4;
		return codigosDeEvento;
	}
	if (tecla == "f5" || tecla == "F5"){
		codigosDeEvento.keyCode = SDLK_F5;
		codigosDeEvento.scanCode = SDL_SCANCODE_F5;
		return codigosDeEvento;
	}
	if (tecla == "f6" || tecla == "F6"){
		codigosDeEvento.keyCode = SDLK_F6;
		codigosDeEvento.scanCode = SDL_SCANCODE_F6;
		return codigosDeEvento;
	}
	if (tecla == "f7" || tecla == "F7"){
		codigosDeEvento.keyCode = SDLK_F7;
		codigosDeEvento.scanCode = SDL_SCANCODE_F7;
		return codigosDeEvento;
	}
	if (tecla == "f8" || tecla == "F8"){
		codigosDeEvento.keyCode = SDLK_F8;
		codigosDeEvento.scanCode = SDL_SCANCODE_F8;
		return codigosDeEvento;
	}
	if (tecla == "f9" || tecla == "F9"){
		codigosDeEvento.keyCode = SDLK_F9;
		codigosDeEvento.scanCode = SDL_SCANCODE_F9;
		return codigosDeEvento;
	}
	if (tecla == "enter" || tecla == "Enter" || tecla == "ENTER" || tecla == "Return" || tecla == "return" || tecla == "RETURN"){
		codigosDeEvento.keyCode = SDLK_RETURN;
		codigosDeEvento.scanCode = SDL_SCANCODE_RETURN;
		return codigosDeEvento;
	}
	if (tecla == "back" || tecla == "Back" || tecla == "BACK" || tecla == "BACKSPACE" || tecla == "BackSpace" || tecla == "Backspace" || tecla == "backspace" || tecla == "Back Space" || tecla == "BACK SPACE" || tecla == "Back space" || tecla == "back space"){
		codigosDeEvento.keyCode = SDLK_BACKSPACE;
		codigosDeEvento.scanCode = SDL_SCANCODE_BACKSPACE;
		return codigosDeEvento;
	}
	if (tecla == "up" || tecla == "Up" || tecla == "UP" || tecla == "arriba" || tecla == "Arriba" || tecla == "ARRIBA"){
		codigosDeEvento.keyCode = SDLK_UP;
		codigosDeEvento.scanCode = SDL_SCANCODE_UP;
		return codigosDeEvento;
	}
	if (tecla == "down" || tecla == "Down" || tecla == "DOWN" || tecla == "abajo" || tecla == "Abajo" || tecla == "ABAJO"){
		codigosDeEvento.keyCode = SDLK_DOWN;
		codigosDeEvento.scanCode = SDL_SCANCODE_DOWN;
		return codigosDeEvento;
	}
	if (tecla == "izquierda" || tecla == "Izquierda" || tecla == "IZQUIERDA" || tecla == "left" || tecla == "Left" || tecla == "LEFT"){
		codigosDeEvento.keyCode = SDLK_LEFT;
		codigosDeEvento.scanCode = SDL_SCANCODE_LEFT;
		return codigosDeEvento;
	}
	if (tecla == "right" || tecla == "Right" || tecla == "RIGHT" || tecla == "derecha" || tecla == "Derecha" || tecla == "DERECHA"){
		codigosDeEvento.keyCode = SDLK_RIGHT;
		codigosDeEvento.scanCode = SDL_SCANCODE_RIGHT;
		return codigosDeEvento;
	}

	//JOYSTICK 1
	if (tecla == "j1_0" || tecla == "J1_0" || tecla == "j1_Button_0" || tecla == "J1_Button_0" || tecla == "j1_button_0" || tecla == "J1_button_0" || tecla == "J1_BUTTON_0" || tecla == "j1_Boton_0" || tecla == "J1_Boton_0" || tecla == "j1_boton_0" || tecla == "J1_boton_0" || tecla == "J1_BOTON_0"){
		codigosDeEvento.jBoton = 0;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_1" || tecla == "J1_1" || tecla == "j1_Button_1" || tecla == "J1_Button_1" || tecla == "j1_button_1" || tecla == "J1_button_1" || tecla == "J1_BUTTON_1" || tecla == "j1_Boton_1" || tecla == "J1_Boton_1" || tecla == "j1_boton_1" || tecla == "J1_boton_1" || tecla == "J1_BOTON_1"){
		codigosDeEvento.jBoton = 1;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_2" || tecla == "J1_2" || tecla == "j1_Button_2" || tecla == "J1_Button_2" || tecla == "j1_button_2" || tecla == "J1_button_2" || tecla == "J1_BUTTON_2" || tecla == "j1_Boton_2" || tecla == "J1_Boton_2" || tecla == "j1_boton_2" || tecla == "J1_boton_2" || tecla == "J1_BOTON_2"){
		codigosDeEvento.jBoton = 2;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_3" || tecla == "J1_3" || tecla == "j1_Button_3" || tecla == "J1_Button_3" || tecla == "j1_button_3" || tecla == "J1_button_3" || tecla == "J1_BUTTON_3" || tecla == "j1_Boton_3" || tecla == "J1_Boton_3" || tecla == "j1_boton_3" || tecla == "J1_boton_3" || tecla == "J1_BOTON_3"){
		codigosDeEvento.jBoton = 3;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_4" || tecla == "J1_4" || tecla == "j1_Button_4" || tecla == "J1_Button_4" || tecla == "j1_button_4" || tecla == "J1_button_4" || tecla == "J1_BUTTON_4" || tecla == "j1_Boton_4" || tecla == "J1_Boton_4" || tecla == "j1_boton_4" || tecla == "J1_boton_4" || tecla == "J1_BOTON_4"){
		codigosDeEvento.jBoton = 4;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_5" || tecla == "J1_5" || tecla == "j1_Button_5" || tecla == "J1_Button_5" || tecla == "j1_button_5" || tecla == "J1_button_5" || tecla == "J1_BUTTON_5" || tecla == "j1_Boton_5" || tecla == "J1_Boton_5" || tecla == "j1_boton_5" || tecla == "J1_boton_5" || tecla == "J1_BOTON_5"){
		codigosDeEvento.jBoton = 5;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_6" || tecla == "J1_6" || tecla == "j1_Button_6" || tecla == "J1_Button_6" || tecla == "j1_button_6" || tecla == "J1_button_6" || tecla == "J1_BUTTON_6" || tecla == "j1_Boton_6" || tecla == "J1_Boton_6" || tecla == "j1_boton_6" || tecla == "J1_boton_6" || tecla == "J1_BOTON_6"){
		codigosDeEvento.jBoton = 6;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_7" || tecla == "J1_7" || tecla == "j1_Button_7" || tecla == "J1_Button_7" || tecla == "j1_button_7" || tecla == "J1_button_7" || tecla == "J1_BUTTON_7" || tecla == "j1_Boton_7" || tecla == "J1_Boton_7" || tecla == "j1_boton_7" || tecla == "J1_boton_7" || tecla == "J1_BOTON_7"){
		codigosDeEvento.jBoton = 7;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_8" || tecla == "J1_8" || tecla == "j1_Button_8" || tecla == "J1_Button_8" || tecla == "j1_button_8" || tecla == "J1_button_8" || tecla == "J1_BUTTON_8" || tecla == "j1_Boton_8" || tecla == "J1_Boton_8" || tecla == "j1_boton_8" || tecla == "J1_boton_8" || tecla == "J1_BOTON_8"){
		codigosDeEvento.jBoton = 8;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_9" || tecla == "J1_9" || tecla == "j1_Button_9" || tecla == "J1_Button_9" || tecla == "j1_button_9" || tecla == "J1_button_9" || tecla == "J1_BUTTON_9" || tecla == "j1_Boton_9" || tecla == "J1_Boton_9" || tecla == "j1_boton_9" || tecla == "J1_boton_9" || tecla == "J1_BOTON_9"){
		codigosDeEvento.jBoton = 9;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_10" || tecla == "J1_10" || tecla == "j1_Button_10" || tecla == "J1_Button_10" || tecla == "j1_button_10" || tecla == "J1_button_10" || tecla == "J1_BUTTON_10" || tecla == "j1_Boton_10" || tecla == "J1_Boton_10" || tecla == "j1_boton_10" || tecla == "J1_boton_10" || tecla == "J1_BOTON_10"){
		codigosDeEvento.jBoton = 10;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_11" || tecla == "J1_11" || tecla == "j1_Button_11" || tecla == "J1_Button_11" || tecla == "j1_button_11" || tecla == "J1_button_11" || tecla == "J1_BUTTON_11" || tecla == "j1_Boton_11" || tecla == "J1_Boton_11" || tecla == "j1_boton_11" || tecla == "J1_boton_11" || tecla == "J1_BOTON_11"){
		codigosDeEvento.jBoton = 11;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j1_analog_up" || tecla == "j1_Analog_Up" || tecla == "j1_ANALOG_UP" || tecla == "J1_analog_up" || tecla == "J1_Analog_Up" || tecla == "J1_ANALOG_UP" || tecla == "j1_analog_arriba" || tecla == "j1_Analog_Arriba" || tecla == "j1_ANALOG_ARRIBA" || tecla == "J1_analog_arriba" || tecla == "J1_Analog_Arriba" || tecla == "J1_ANALOG_ARRIBA" || tecla == "j1_analogic_up" || tecla == "j1_Analogic_Up" || tecla == "j1_ANALOGIC_UP" || tecla == "J1_analogic_up" || tecla == "J1_Analogic_Up" || tecla == "J1_ANALOG_UP" || tecla == "j1_analogic_arriba" || tecla == "j1_Analogic_Arriba" || tecla == "j1_ANALOGIC_ARRIBA" || tecla == "J1_analogic_arriba" || tecla == "J1_Analogic_Arriba" || tecla == "J1_ANALOGIC_ARRIBA" || tecla == "j1_analogico_up" || tecla == "j1_Analogico_Up" || tecla == "j1_ANALOGICO_UP" || tecla == "J1_analogico_up" || tecla == "J1_Analogico_Up" || tecla == "J1_ANALOGICO_UP" || tecla == "j1_analogico_arriba" || tecla == "j1_Analogico_Arriba" || tecla == "j1_ANALOGICO_ARRIBA" || tecla == "J1_analogico_arriba" || tecla == "J1_Analogico_Arriba" || tecla == "J1_ANALOGICO_ARRIBA"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 1;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.ejeDesde = -32768;
		codigosDeEvento.ejeHasta = -2000;
		return codigosDeEvento;
	}
	if (tecla == "j1_analog_down" || tecla == "j1_Analog_Down" || tecla == "j1_ANALOG_DOWN" || tecla == "J1_analog_down" || tecla == "J1_Analog_Down" || tecla == "J1_ANALOG_DOWN" || tecla == "j1_analog_abajo" || tecla == "j1_Analog_Abajo" || tecla == "j1_ANALOG_ABAJO" || tecla == "J1_analog_abajo" || tecla == "J1_Analog_Abajo" || tecla == "J1_ANALOG_ABAJO" || tecla == "j1_analogic_down" || tecla == "j1_Analogic_Down" || tecla == "j1_ANALOGIC_Down" || tecla == "J1_analogic_Down" || tecla == "J1_Analogic_Down" || tecla == "J1_ANALOG_DOWN" || tecla == "j1_analogic_down" || tecla == "j1_Analogic_Down" || tecla == "j1_ANALOGIC_DOWN" || tecla == "J1_analogic_down" || tecla == "J1_Analogic_Down" || tecla == "J1_ANALOGIC_DOWN" || tecla == "j1_analogico_down" || tecla == "j1_Analogico_Down" || tecla == "j1_ANALOGICO_DOWN" || tecla == "J1_analogico_up" || tecla == "J1_Analogico_Down" || tecla == "J1_ANALOGICO_DOWN" || tecla == "j1_analogico_abajo" || tecla == "j1_Analogico_Abajo" || tecla == "j1_ANALOGICO_ABAJO" || tecla == "J1_analogico_abajo" || tecla == "J1_Analogico_Abajo" || tecla == "J1_ANALOGICO_ABAJO"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 1;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.ejeDesde = 2000;
		codigosDeEvento.ejeHasta = 32767;
		return codigosDeEvento;
	}
	if (tecla == "j1_analog_right" || tecla == "j1_Analog_Right" || tecla == "j1_ANALOG_RIGHT" || tecla == "J1_analog_right" || tecla == "J1_Analog_Right" || tecla == "J1_ANALOG_RIGHT" || tecla == "j1_analog_derecha" || tecla == "j1_Analog_Derecha" || tecla == "j1_ANALOG_DERECHA" || tecla == "J1_analog_derecha" || tecla == "J1_Analog_Derecha" || tecla == "J1_ANALOG_DERECHA" || tecla == "j1_analogic_right" || tecla == "j1_Analogic_Right" || tecla == "j1_ANALOGIC_RIGHT" || tecla == "J1_analogic_right" || tecla == "J1_Analogic_Right" || tecla == "J1_ANALOG_RIGHT" || tecla == "j1_analogic_derecha" || tecla == "j1_Analogic_Derecha" || tecla == "j1_ANALOGIC_DERECHA" || tecla == "J1_analogic_derecha" || tecla == "J1_Analogic_Derecha" || tecla == "J1_ANALOGIC_DERECHA" || tecla == "j1_analogico_right" || tecla == "j1_Analogico_Right" || tecla == "j1_ANALOGICO_RIGHT" || tecla == "J1_analogico_right" || tecla == "J1_Analogico_Right" || tecla == "J1_ANALOGICO_RIGHT" || tecla == "j1_analogico_derecha" || tecla == "j1_Analogico_Derecha" || tecla == "j1_ANALOGICO_DERECHA" || tecla == "J1_analogico_derecha" || tecla == "J1_Analogico_Derecha" || tecla == "J1_ANALOGICO_DERECHA"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 0;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.ejeDesde = 2000;
		codigosDeEvento.ejeHasta = 32767;
		return codigosDeEvento;
	}
	if (tecla == "j1_analog_left" || tecla == "j1_Analog_Left" || tecla == "j1_ANALOG_LEFT" || tecla == "J1_analog_left" || tecla == "J1_Analog_Left" || tecla == "J1_ANALOG_LEFT" || tecla == "j1_analog_izquierda" || tecla == "j1_Analog_Izquierda" || tecla == "j1_ANALOG_IZQUIERDA" || tecla == "J1_analog_izquierda" || tecla == "J1_Analog_Izquierda" || tecla == "J1_ANALOG_IZQUIERDA" || tecla == "j1_analogic_left" || tecla == "j1_Analogic_Left" || tecla == "j1_ANALOGIC_LEFT" || tecla == "J1_analogic_left" || tecla == "J1_Analogic_Left" || tecla == "J1_ANALOG_LEFT" || tecla == "j1_analogic_izquierda" || tecla == "j1_Analogic_Izquierda" || tecla == "j1_ANALOGIC_IZQUIERDA" || tecla == "J1_analogic_izquierda" || tecla == "J1_Analogic_Izquierda" || tecla == "J1_ANALOGIC_IZQUIERDA" || tecla == "j1_analogico_left" || tecla == "j1_Analogico_Left" || tecla == "j1_ANALOGICO_LEFT" || tecla == "J1_analogico_left" || tecla == "J1_Analogico_Left" || tecla == "J1_ANALOGICO_LEFT" || tecla == "j1_analogico_izquierda" || tecla == "j1_Analogico_Izquierda" || tecla == "j1_ANALOGICO_IZQUIERDA" || tecla == "J1_analogico_izquierda" || tecla == "J1_Analogico_Izquierda" || tecla == "J1_ANALOGICO_IZQUIERDA"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 0;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.ejeDesde = -32768;
		codigosDeEvento.ejeHasta = -2000;
		return codigosDeEvento;
	}
	if (tecla == "j1_up" || tecla == "j1_Up" || tecla == "j1_UP" || tecla == "J1_up" || tecla == "J1_Up" || tecla == "J1_UP" || tecla == "j1_arriba" || tecla == "j1_Arriba" || tecla == "j1_ARRIBA" || tecla == "J1_arriba" || tecla == "J1_Arriba" || tecla == "J1_ARRIBA"){
		codigosDeEvento.hat = SDL_HAT_UP;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}
	if (tecla == "j1_down" || tecla == "j1_Down" || tecla == "j1_DOWN" || tecla == "J1_down" || tecla == "J1_Down" || tecla == "J1_DOWN" || tecla == "j1_abajo" || tecla == "j1_Abajo" || tecla == "j1_ABAJO" || tecla == "J1_abajo" || tecla == "J1_Abajo" || tecla == "J1_ABAJO"){
		codigosDeEvento.hat = SDL_HAT_DOWN;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}
	if (tecla == "j1_right" || tecla == "j1_Right" || tecla == "j1_RIGHT" || tecla == "J1_right" || tecla == "J1_Right" || tecla == "J1_RIGHT" || tecla == "j1_derecha" || tecla == "j1_Derecha" || tecla == "j1_DERECHA" || tecla == "J1_derecha" || tecla == "J1_Derecha" || tecla == "J1_DERECHA"){
		codigosDeEvento.hat = SDL_HAT_RIGHT;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}
	if (tecla == "j1_left" || tecla == "j1_Left" || tecla == "j1_LEFT" || tecla == "J1_left" || tecla == "J1_Left" || tecla == "J1_LEFT" || tecla == "j1_izquierda" || tecla == "j1_Izquierda" || tecla == "j1_IZQUIERDA" || tecla == "J1_izquierda" || tecla == "J1_Izquierda" || tecla == "J1_IZQUIERDA"){
		codigosDeEvento.hat = SDL_HAT_LEFT;
		codigosDeEvento.joystick = 0;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}

	//JOYSTICK 2
	if (tecla == "j2_0" || tecla == "J2_0" || tecla == "j2_Button_0" || tecla == "J2_Button_0" || tecla == "j2_button_0" || tecla == "J2_button_0" || tecla == "J2_BUTTON_0" || tecla == "j2_Boton_0" || tecla == "J2_Boton_0" || tecla == "j2_boton_0" || tecla == "J2_boton_0" || tecla == "J2_BOTON_0"){
		codigosDeEvento.jBoton = 0;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_1" || tecla == "J2_1" || tecla == "j2_Button_1" || tecla == "J2_Button_1" || tecla == "j2_button_1" || tecla == "J2_button_1" || tecla == "J2_BUTTON_1" || tecla == "j2_Boton_1" || tecla == "J2_Boton_1" || tecla == "j2_boton_1" || tecla == "J2_boton_1" || tecla == "J2_BOTON_1"){
		codigosDeEvento.jBoton = 1;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_2" || tecla == "J2_2" || tecla == "j2_Button_2" || tecla == "J2_Button_2" || tecla == "j2_button_2" || tecla == "J2_button_2" || tecla == "J2_BUTTON_2" || tecla == "j2_Boton_2" || tecla == "J2_Boton_2" || tecla == "j2_boton_2" || tecla == "J2_boton_2" || tecla == "J2_BOTON_2"){
		codigosDeEvento.jBoton = 2;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_3" || tecla == "J2_3" || tecla == "j2_Button_3" || tecla == "J2_Button_3" || tecla == "j2_button_3" || tecla == "J2_button_3" || tecla == "J2_BUTTON_3" || tecla == "j2_Boton_3" || tecla == "J2_Boton_3" || tecla == "j2_boton_3" || tecla == "J2_boton_3" || tecla == "J2_BOTON_3"){
		codigosDeEvento.jBoton = 3;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_4" || tecla == "J2_4" || tecla == "j2_Button_4" || tecla == "J2_Button_4" || tecla == "j2_button_4" || tecla == "J2_button_4" || tecla == "J2_BUTTON_4" || tecla == "j2_Boton_4" || tecla == "J2_Boton_4" || tecla == "j2_boton_4" || tecla == "J2_boton_4" || tecla == "J2_BOTON_4"){
		codigosDeEvento.jBoton = 4;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_5" || tecla == "J2_5" || tecla == "j2_Button_5" || tecla == "J2_Button_5" || tecla == "j2_button_5" || tecla == "J2_button_5" || tecla == "J2_BUTTON_5" || tecla == "j2_Boton_5" || tecla == "J2_Boton_5" || tecla == "j2_boton_5" || tecla == "J2_boton_5" || tecla == "J2_BOTON_5"){
		codigosDeEvento.jBoton = 5;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_6" || tecla == "J2_6" || tecla == "j2_Button_6" || tecla == "J1_Button_6" || tecla == "j2_button_6" || tecla == "J2_button_6" || tecla == "J2_BUTTON_6" || tecla == "j2_Boton_6" || tecla == "J2_Boton_6" || tecla == "j2_boton_6" || tecla == "J2_boton_6" || tecla == "J2_BOTON_6"){
		codigosDeEvento.jBoton = 6;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_7" || tecla == "J2_7" || tecla == "j2_Button_7" || tecla == "J2_Button_7" || tecla == "j2_button_7" || tecla == "J2_button_7" || tecla == "J2_BUTTON_7" || tecla == "j2_Boton_7" || tecla == "J2_Boton_7" || tecla == "j2_boton_7" || tecla == "J2_boton_7" || tecla == "J2_BOTON_7"){
		codigosDeEvento.jBoton = 7;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_8" || tecla == "J2_8" || tecla == "j2_Button_8" || tecla == "J2_Button_8" || tecla == "j2_button_8" || tecla == "J2_button_8" || tecla == "J2_BUTTON_8" || tecla == "j2_Boton_8" || tecla == "J2_Boton_8" || tecla == "j2_boton_8" || tecla == "J2_boton_8" || tecla == "J2_BOTON_8"){
		codigosDeEvento.jBoton = 8;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_10" || tecla == "J2_10" || tecla == "j2_Button_10" || tecla == "J2_Button_10" || tecla == "j2_button_10" || tecla == "J2_button_10" || tecla == "J2_BUTTON_10" || tecla == "j2_Boton_10" || tecla == "J2_Boton_10" || tecla == "j2_boton_10" || tecla == "J2_boton_10" || tecla == "J2_BOTON_10"){
		codigosDeEvento.jBoton = 10;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j2_11" || tecla == "J2_11" || tecla == "j2_Button_11" || tecla == "J2_Button_11" || tecla == "j2_button_11" || tecla == "J2_button_11" || tecla == "J2_BUTTON_11" || tecla == "j2_Boton_11" || tecla == "J2_Boton_11" || tecla == "j2_boton_11" || tecla == "J2_boton_11" || tecla == "J2_BOTON_11"){
		codigosDeEvento.jBoton = 11;
		codigosDeEvento.joystick = 0;
		return codigosDeEvento;
	}
	if (tecla == "j2_9" || tecla == "J2_9" || tecla == "j2_Button_9" || tecla == "J2_Button_9" || tecla == "j2_button_9" || tecla == "J2_button_9" || tecla == "J2_BUTTON_9" || tecla == "j2_Boton_9" || tecla == "J2_Boton_9" || tecla == "j2_boton_9" || tecla == "J2_boton_9" || tecla == "J2_BOTON_9"){
		codigosDeEvento.jBoton = 9;
		codigosDeEvento.joystick = 1;
		return codigosDeEvento;
	}
	if (tecla == "j2_analog_up" || tecla == "j2_Analog_Up" || tecla == "j2_ANALOG_UP" || tecla == "J2_analog_up" || tecla == "J2_Analog_Up" || tecla == "J2_ANALOG_UP" || tecla == "j2_analog_arriba" || tecla == "j2_Analog_Arriba" || tecla == "j2_ANALOG_ARRIBA" || tecla == "J2_analog_arriba" || tecla == "J2_Analog_Arriba" || tecla == "J2_ANALOG_ARRIBA" || tecla == "j2_analogic_up" || tecla == "j2_Analogic_Up" || tecla == "j2_ANALOGIC_UP" || tecla == "J2_analogic_up" || tecla == "J2_Analogic_Up" || tecla == "J2_ANALOG_UP" || tecla == "j2_analogic_arriba" || tecla == "j2_Analogic_Arriba" || tecla == "j2_ANALOGIC_ARRIBA" || tecla == "J2_analogic_arriba" || tecla == "J2_Analogic_Arriba" || tecla == "J2_ANALOGIC_ARRIBA" || tecla == "j2_analogico_up" || tecla == "j2_Analogico_Up" || tecla == "j2_ANALOGICO_UP" || tecla == "J2_analogico_up" || tecla == "J2_Analogico_Up" || tecla == "J2_ANALOGICO_UP" || tecla == "j2_analogico_arriba" || tecla == "j2_Analogico_Arriba" || tecla == "j2_ANALOGICO_ARRIBA" || tecla == "J2_analogico_arriba" || tecla == "J2_Analogico_Arriba" || tecla == "J2_ANALOGICO_ARRIBA"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 1;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.ejeDesde = -32768;
		codigosDeEvento.ejeHasta = -2000;
		return codigosDeEvento;
	}
	if (tecla == "j2_analog_down" || tecla == "j2_Analog_Down" || tecla == "j2_ANALOG_DOWN" || tecla == "J2_analog_down" || tecla == "J2_Analog_Down" || tecla == "J2_ANALOG_DOWN" || tecla == "j2_analog_abajo" || tecla == "j2_Analog_Abajo" || tecla == "j2_ANALOG_ABAJO" || tecla == "J2_analog_abajo" || tecla == "J2_Analog_Abajo" || tecla == "J2_ANALOG_ABAJO" || tecla == "j2_analogic_down" || tecla == "j2_Analogic_Down" || tecla == "j2_ANALOGIC_Down" || tecla == "J2_analogic_Down" || tecla == "J2_Analogic_Down" || tecla == "J2_ANALOG_DOWN" || tecla == "j2_analogic_down" || tecla == "j2_Analogic_Down" || tecla == "j2_ANALOGIC_DOWN" || tecla == "J2_analogic_down" || tecla == "J2_Analogic_Down" || tecla == "J2_ANALOGIC_DOWN" || tecla == "j2_analogico_down" || tecla == "j2_Analogico_Down" || tecla == "j2_ANALOGICO_DOWN" || tecla == "J2_analogico_up" || tecla == "J2_Analogico_Down" || tecla == "J2_ANALOGICO_DOWN" || tecla == "j2_analogico_abajo" || tecla == "j2_Analogico_Abajo" || tecla == "j2_ANALOGICO_ABAJO" || tecla == "J2_analogico_abajo" || tecla == "J2_Analogico_Abajo" || tecla == "J2_ANALOGICO_ABAJO"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 1;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.ejeDesde = 2000;
		codigosDeEvento.ejeHasta = 32767;
		return codigosDeEvento;
	}
	if (tecla == "j2_analog_right" || tecla == "j2_Analog_Right" || tecla == "j2_ANALOG_RIGHT" || tecla == "J2_analog_right" || tecla == "J2_Analog_Right" || tecla == "J2_ANALOG_RIGHT" || tecla == "j2_analog_derecha" || tecla == "j2_Analog_Derecha" || tecla == "j2_ANALOG_DERECHA" || tecla == "J2_analog_derecha" || tecla == "J2_Analog_Derecha" || tecla == "J2_ANALOG_DERECHA" || tecla == "j2_analogic_right" || tecla == "j2_Analogic_Right" || tecla == "j2_ANALOGIC_RIGHT" || tecla == "J2_analogic_right" || tecla == "J2_Analogic_Right" || tecla == "J2_ANALOG_RIGHT" || tecla == "j2_analogic_derecha" || tecla == "j2_Analogic_Derecha" || tecla == "j2_ANALOGIC_DERECHA" || tecla == "J2_analogic_derecha" || tecla == "J2_Analogic_Derecha" || tecla == "J2_ANALOGIC_DERECHA" || tecla == "j2_analogico_right" || tecla == "j2_Analogico_Right" || tecla == "j2_ANALOGICO_RIGHT" || tecla == "J2_analogico_right" || tecla == "J2_Analogico_Right" || tecla == "J2_ANALOGICO_RIGHT" || tecla == "j2_analogico_derecha" || tecla == "j2_Analogico_Derecha" || tecla == "j2_ANALOGICO_DERECHA" || tecla == "J2_analogico_derecha" || tecla == "J2_Analogico_Derecha" || tecla == "J2_ANALOGICO_DERECHA"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 0;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.ejeDesde = 2000;
		codigosDeEvento.ejeHasta = 32767;
		return codigosDeEvento;
	}
	if (tecla == "j2_analog_left" || tecla == "j2_Analog_Left" || tecla == "j2_ANALOG_LEFT" || tecla == "J2_analog_left" || tecla == "J2_Analog_Left" || tecla == "J2_ANALOG_LEFT" || tecla == "j2_analog_izquierda" || tecla == "j2_Analog_Izquierda" || tecla == "j2_ANALOG_IZQUIERDA" || tecla == "J2_analog_izquierda" || tecla == "J2_Analog_Izquierda" || tecla == "J2_ANALOG_IZQUIERDA" || tecla == "j2_analogic_left" || tecla == "j2_Analogic_Left" || tecla == "j2_ANALOGIC_LEFT" || tecla == "J2_analogic_left" || tecla == "J2_Analogic_Left" || tecla == "J2_ANALOG_LEFT" || tecla == "j2_analogic_izquierda" || tecla == "j2_Analogic_Izquierda" || tecla == "j2_ANALOGIC_IZQUIERDA" || tecla == "J2_analogic_izquierda" || tecla == "J2_Analogic_Izquierda" || tecla == "J2_ANALOGIC_IZQUIERDA" || tecla == "j2_analogico_left" || tecla == "j2_Analogico_Left" || tecla == "j2_ANALOGICO_LEFT" || tecla == "J2_analogico_left" || tecla == "J2_Analogico_Left" || tecla == "J2_ANALOGICO_LEFT" || tecla == "j2_analogico_izquierda" || tecla == "j2_Analogico_Izquierda" || tecla == "j2_ANALOGICO_IZQUIERDA" || tecla == "J2_analogico_izquierda" || tecla == "J2_Analogico_Izquierda" || tecla == "J2_ANALOGICO_IZQUIERDA"){
		codigosDeEvento.eje = true;
		codigosDeEvento.jBoton = 0;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.ejeDesde = -32768;
		codigosDeEvento.ejeHasta = -2000;
		return codigosDeEvento;
	}
	if (tecla == "j2_up" || tecla == "j2_Up" || tecla == "j2_UP" || tecla == "J2_up" || tecla == "J2_Up" || tecla == "J2_UP" || tecla == "j2_arriba" || tecla == "j2_Arriba" || tecla == "j2_ARRIBA" || tecla == "J2_arriba" || tecla == "J2_Arriba" || tecla == "J2_ARRIBA"){
		codigosDeEvento.hat = SDL_HAT_UP;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}
	if (tecla == "j2_down" || tecla == "j2_Down" || tecla == "j2_DOWN" || tecla == "J2_down" || tecla == "J2_Down" || tecla == "J2_DOWN" || tecla == "j2_abajo" || tecla == "j2_Abajo" || tecla == "j2_ABAJO" || tecla == "J2_abajo" || tecla == "J2_Abajo" || tecla == "J2_ABAJO"){
		codigosDeEvento.hat = SDL_HAT_DOWN;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}
	if (tecla == "j2_right" || tecla == "j2_Right" || tecla == "j2_RIGHT" || tecla == "J2_right" || tecla == "J2_Right" || tecla == "J2_RIGHT" || tecla == "j2_derecha" || tecla == "j2_Derecha" || tecla == "j2_DERECHA" || tecla == "J2_derecha" || tecla == "J2_Derecha" || tecla == "J2_DERECHA"){
		codigosDeEvento.hat = SDL_HAT_RIGHT;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}
	if (tecla == "j2_left" || tecla == "j2_Left" || tecla == "j2_LEFT" || tecla == "J2_left" || tecla == "J2_Left" || tecla == "J2_LEFT" || tecla == "j2_izquierda" || tecla == "j2_Izquierda" || tecla == "j2_IZQUIERDA" || tecla == "J2_izquierda" || tecla == "J2_Izquierda" || tecla == "J2_IZQUIERDA"){
		codigosDeEvento.hat = SDL_HAT_LEFT;
		codigosDeEvento.joystick = 1;
		codigosDeEvento.flechas = true;
		return codigosDeEvento;
	}

	return codigosDeEvento;
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
	nuevaAccion.eje = codigosDeEvento.eje;
	nuevaAccion.flechas = codigosDeEvento.flechas;
	nuevaAccion.ejeDesde = codigosDeEvento.ejeDesde;
	nuevaAccion.ejeHasta = codigosDeEvento.ejeHasta;
	nuevaAccion.hat = codigosDeEvento.hat;
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


bool ConversorDeEventos::hayEjeParaLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].eje);
}


bool ConversorDeEventos::hayFlechasParaLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].flechas);
}


Sint16 ConversorDeEventos::getValorDesdeDelEjeDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].ejeDesde);
}


Sint16 ConversorDeEventos::getValorHastaDelEjeDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].ejeHasta);
}


Uint8 ConversorDeEventos::getHatDeLaAccion(Acciones unaAccion){
	return (acciones[unaAccion].hat);
}


ConversorDeEventos::~ConversorDeEventos()
{
}
