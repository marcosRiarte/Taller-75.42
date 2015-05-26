// Salida del gameloop
#define CONTINUAR	0
#define REINICIAR	1
#define FIN   		2

#define MODO_DEBUG_SDL true
#define MODO_COLOR true

//JSON
#define PRUEBA_JSON "prueba.json"
#define PRUEBA_JSON_DEFECTO "pruebaDefecto.json"

#define VIBRACIONES 3

//Constantes para la vista
//VENTANA
#define ANCHO_MIN 50
#define ALTO_MIN 50
#define ANCHO_PX_VENTANA 800
#define ALTO_PX_VENTANA 600
#define ANCHO_VENTANA 200.0f
#define TITULO_VENTANA "Bickbox"
#define ICONO "ima/Bbx_icono.png"

//FISICA
//
#define FPS 60.0f
const float MSxCUADRO = 1000.0f / FPS;
#define tiempoCaminarParaAdelante 1000.0f
#define tiempoCaminarParaAtras 1000.0f
#define tiempoQuieto 1700.0f
#define tiempoSalto 500.0f
#define tiempoSaltoDiagonal 500.0f
#define tiempoSaltoDiagonalIzq 500.0f
#define tiempoAgacharse 200.0f
#define tiempoAgachadoDefensa 500.0f
#define tiempoPatadaAlta 500.0f
#define tiempoPatadaBaja 500.0f
#define tiempoGolpeado 600.0f
#define tiempoDefensa 500.0f
#define tiempoGolpeAlto 400.0f
#define tiempoGolpeBajo 500.0f
#define tiempoArmaArrojable 700.0f
#define tiempoSaltoGolpeado 1400.0f
#define tiempoGancho 500.0f
#define tiempoAgachadoPatadaBaja 500.0f
#define tiempoSaltoPatada 500.0f
#define tiempoSaltoDiagonalPatada 500.0f
#define tiempoSaltoGolpe 500.0f
#define tiempoAgachadoGolpeBajo 500.0f
#define tiempoAgachadoPatadaAlta 500.0f
#define tiempoAgachadoGolpeado 500.0f


//ESCENARIO
#define ANCHO_ESCENARIO 1000.5f
#define MAX_ANCHO_ESCENARIO 4000.0f
#define ALTO_ESCENARIO 150.0f
#define MAX_ALTO_ESCENARIO 2000.0f
#define Y_PISO_ESCENARIO 15.0f

//CAPA
#define ANCHO_CAPA 500.0f
#define ZINDEX_CAPA 0

//PERSONAJE
#define ANCHO_PERSONAJE 80.0f
#define MAX_ANCHO_PERSONAJE 1000.0f
#define ALTO_PERSONAJE 90.0f
#define MAX_ALTO_PERSONAJE 1000.0f

#define ZINDEX 1
#define ORIENTACION_PERSONAJE "DER"
#define SPRITE_DEFAULT "ima/sprites/player_default.png"
#define FONDO_DEFAULT "ima/bkg/default_capa.png" // al ser varias capas la idea esa usar esta por que va a permitir que se vean el resto de las que si estan
#define CAMINARPARAADELANTE_DEFAULT "CaminarParaAdelante"
#define CAMINARPARAATRAS_DEFAULT "CaminarParaAtras"
#define QUIETO_DEFAULT "Quieto"
#define SALTO_DEFAULT "Salto"
#define SALTODIAGONAL_DEFAULT "SaltoDiagonal"
#define CAIDA_DEFAULT "Caida"

#define PELEA_INICIAL "scorpion VS scorpion"

#define H_INICIAL 40.0f
#define H_FINAL 70.0f
#define DESPLAZAMIENTO 162.0f

#define GOLPEADO_DEFAULT "Golpeado"
#define AGACHARSE_DEFAULT "Agacharse"
#define PATADAALTA_DEFAULT "PatadaAlta"
#define DISPARO_DEFAULT "Disparo"

#define LIU_KANG "LiuKang"

//CONTROLADOR
#define MOSTRAR_MOVIMIENTOS false
#define CANTIDAD_MAXIMA_EVENTOS 30
#define ARRIBA_DEFAULT_1 "up"
#define ABAJO_DEFAULT_1 "down"
#define IZQUIERDA_DEFAULT_1 "left"
#define DERECHA_DEFAULT_1 "right"
#define DEFENSA_DEFAULT_1 "z"
#define ARMA_DEFAULT_1 "x"
#define G_BAJO_DEFAULT_1 "c"
#define G_ALTO_DEFAULT_1 "v"
#define P_BAJA_DEFAULT_1 "b"
#define P_ALTA_DEFAULT_1 "n"
#define ARRIBA_DEFAULT_2 "w"
#define ABAJO_DEFAULT_2 "s"
#define IZQUIERDA_DEFAULT_2 "a"
#define DERECHA_DEFAULT_2 "d"
#define DEFENSA_DEFAULT_2 "j"
#define ARMA_DEFAULT_2 "u"
#define G_BAJO_DEFAULT_2 "k"
#define G_ALTO_DEFAULT_2 "l"
#define P_BAJA_DEFAULT_2 "i"
#define P_ALTA_DEFAULT_2 "o"
#define REINICIAR_DEFAULT "r"
#define SALIR_DEFAULT "esc"
