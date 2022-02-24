// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// engine.h
// Well, self explanatory innit?

#ifndef PLAYER_MIN_KILLABLE
#define PLAYER_MIN_KILLABLE 0
#endif

// Animation frames
#include "engine/frames.h"

// Prepare level (compressed levels)
#if defined (SIMPLE_LEVEL_MANAGER)
#include "engine/clevels-s.h"
#elif defined (COMPRESSED_LEVELS)
#include "engine/clevels.h"
#endif

// Init player
#include "engine/initplayer.h"

// Collision
#include "engine/collision.h"

// Random
#include "engine/random.h"

// Messages
#include "engine/messages.h"

#ifdef PLAYER_STEP_SOUND
void step (void) {
	#asm
		ld a, 16
		out (254), a
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		xor 16
		out (254), a
	#endasm
}
#endif

/*
void cortina (void) {
	#asm
		ld b, 7
	.fade_out_extern
		push bc

		ld   e, 3               ; 3 tercios
		ld   hl, 22528          ; aqu� empiezan los atributos
	#endasm
#ifdef MODE_128K
	#asm
		halt                    ; esperamos retrazo.
	#endasm
#endif
	#asm
	.fade_out_bucle
		ld   a, (hl )           ; nos traemos el atributo actual

		ld   d, a               ; tomar atributo
		and  7                  ; aislar la tinta
		jr   z, ink_done        ; si vale 0, no se decrementa
		dec  a                  ; decrementamos tinta
	.ink_done
		ld   b, a               ; en b tenemos ahora la tinta ya procesada.

		ld   a, d               ; tomar atributo
		and  56                 ; aislar el papel, sin modificar su posición en el byte
		jr   z, paper_done      ; si vale 0, no se decrementa
		sub  8                  ; decrementamos papel restando 8
	.paper_done
		ld   c, a               ; en c tenemos ahora el papel ya procesado.
		ld   a, d
		and  192                ; nos quedamos con bits 6 y 7 (BRIGHT y FLASH)
		or   c                  ; a�adimos paper
		or   b                  ; e ink, con lo que recompuesto el atributo
		ld   (hl),a             ; lo escribimos,
		inc  l                  ; e incrementamos el puntero.
		jr   nz, fade_out_bucle ; continuamos hasta acabar el tercio (cuando L valga 0)
		inc  h                  ; siguiente tercio
		dec  e
		jr   nz, fade_out_bucle ; repetir las 3 veces
		pop bc
		djnz fade_out_extern
	#endasm
} */

/*
void cortina (void) {
	#asm
		;; Antes que nada vamos a limpiar el PAPER de toda la pantalla
		;; para que no queden artefactos feos
		
		ld	de, 22528			; Apuntamos con DE a la zona de atributos
		ld	b,	3				; Procesamos 3 tercios
	.clearb1
		push bc
		
		ld	b, 0				; Procesamos los 256 atributos de cada tercio
	.clearb2
	
		ld	a, (de)				; Nos traemos un atributo
		and	199					; Le hacemos la m�scara 11000111 y dejamos PAPER a 0
		ld	(de), a				; Y lo volvemos a poner
		
		inc de					; Siguiente atributo
	
		djnz clearb2
		
		pop bc
		djnz clearb1
		
		;; Y ahora el c�digo original que escrib� para UWOL:	
	
		ld	a,	8
	
	.repitatodo
		ld	c,	a			; Salvamos el contador de "repitatodo" en 'c'
	
		ld	hl, 16384
		ld	a,	12
	
	.bucle
		ld	b,	a			; Salvamos el contador de "bucle" en 'b'
		ld	a,	0
	
	.bucle1
		sla (hl)
		inc hl
		dec a
		jr	nz, bucle1
			
		ld	a,	0
	.bucle2
		srl (hl)
		inc hl
		dec a
		jr	nz, bucle2
			
		ld	a,	b			; Restituimos el contador de "bucle" a 'a'
		dec a
		jr	nz, bucle
	
		ld	a,	c			; Restituimos el contador de "repitatodo" a 'a'
		dec a
		jr	nz, repitatodo
	#endasm
} */

signed int addsign (signed int n, signed int value) {
	//if (n >= 0) return value; else return -value;
	return n == 0 ? 0 : n > 0 ? value : -value;
}

unsigned int abs (int n) {
	if (n < 0)
		return (unsigned int) (-n);
	else
		return (unsigned int) n;
}

// Engine globals (for speed) & size!
unsigned char gpx, gpy, gpd, gpc, gpt, gps;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpen_xx, gpen_yy, gpaux;
unsigned char tocado, active, killable, animate;
unsigned char gpit, gpjt;
unsigned char *map_pointer;

void kill_player (unsigned char sound) {
	p_life --;
#ifdef MODE_128K
	//_AY_ST_ALL ();
	_AY_PL_SND (sound);
#else
	peta_el_beeper (sound);
#endif
#ifdef DIE_AND_RESPAWN
	p_killme = 1;
	half_life = 0;
#endif
#ifdef PLAYER_FLICKERS
	p_estado = EST_PARP;
	p_ct_estado = 50;
#endif
#ifdef REENTER_ON_DEATH
	o_pant = 99;
	saca_a_todo_el_mundo_de_aqui (0);
#endif
}

// Floating objects
#if defined(ENABLE_FLOATING_OBJECTS) || defined (ENABLE_SIM)
#include "engine/floating.h"
#ifdef ENABLE_SIM
#include "engine/sim.h"
#endif
#endif

// Animated tiles
#ifdef ENABLE_TILANIMS
#include "tilanim.h"
#endif

// Breakable tiles helper functions
#ifdef BREAKABLE_WALLS
#include "engine/breakable.h"
#endif

#ifdef BREAKABLE_WALLS_SIMPLE
#include "engine/breakable-s.h"
#endif

// Initialization functions
#include "engine/inits.h"

// Hitter (punch/sword/drill) helper functions
#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD) || defined(PLAYER_HAZ_WHIP) || defined(PLAYER_CAN_DRILL)
#include "engine/hitter.h"
#endif

// Bullets helper functions
#ifdef PLAYER_CAN_FIRE
#include "engine/bullets.h"
#endif

// Simple bomb helper functions
#ifdef PLAYER_SIMPLE_BOMBS
#include "engine/bombs-s.h"
#endif

// Block processing
#include "engine/blocks.h"

// Main player movement
#if defined (PHANTOMAS_ENGINE)
#include "engine/phantomasmove.h"
#else
#include "engine/playermove.h"
#endif

#ifdef ACTIVATE_SCRIPTING
void run_entering_script (void) {
#ifdef EXTENDED_LEVELS
	if (level_data->activate_scripting) {
#endif
#ifdef LINE_OF_TEXT
		print_str (LINE_OF_TEXT_X, LINE_OF_TEXT, LINE_OF_TEXT_ATTR, "                              ");
#endif
		// Ejecutamos los scripts de entrar en pantalla:
		run_script (2 * MAP_W * MAP_H + 1);
		run_script (n_pant + n_pant);
#ifdef EXTENDED_LEVELS
	}
#endif
}
#endif

// Extra prints (screen drawing helpers)
#ifdef ENABLE_EXTRA_PRINTS
#include "engine/extraprints.h"
#endif

// Level names (screen drawing helpers)
#ifdef ENABLE_LEVEL_NAMES
#include "engine/levelnames.h"
#endif

// Screen drawing
#include "engine/drawscr.h"

// Enemies
#ifdef USE_OLD_ENEMS
#include "engine/oldenems.h"
#else
#include "engine/enems.h"
#endif

void espera_activa (int espera) {
	do {
#ifndef MODE_128K
		gpjt = 250; do { gpit = 1; } while (--gpjt);
#else
		#asm
			halt
		#endasm
#endif
#ifdef DIE_AND_RESPAWN
		if (p_killme == 0 && button_pressed ()) break;
#else
		if (button_pressed ()) break;
#endif
	} while (--espera);
	sp_Border (0);
}

#ifdef ACTIVATE_SCRIPTING
void run_fire_script (void) {
	run_script (2 * MAP_W * MAP_H + 2);
	run_script (n_pant + n_pant + 1);
	// I use this for debug when further developing the engine, it comes handy:
/*
	for (gpit = 0; gpit < 16; gpit ++) {
		sp_PrintAtInv (0, gpit + gpit, 71, 16 + flags [gpit]);
	}
*/
/*
	for (gpit = 0; gpit < 16; gpit ++) {
		//sp_PrintAtInv (23, gpit + gpit, 71, 16 + baddies [enoffs + gpit].t);
		print_number2(gpit+gpit,23,flags [gpit]);
	}
*/
}
#endif

/*
#ifndef PHANTOMAS_ENGINE
// UP DOWN LEFT RIGHT FIRE JUMP <- with fire/hitter/throwable
// UP DOWN LEFT RIGHT JUMP xxxx <- with just jump, so configure ahead:
unsigned int keyscancodes [] = {
//	0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,		// WSADMN
//#ifdef USE_TWO_BUTTONS
	//0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0x087f 		// QAOP(SPC)N	//Salva (13/12/15)
	0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f		// WSADMN
//#else
//	0x01fb, 0x01fd, 0x02df, 0x01df, 0x01fb, 0 			// QAOPQ-
//#endif
};
#endif

void select_joyfunc (void) {
#ifdef PHANTOMAS_ENGINE
	joyfunc = sp_JoyKeyboard;
	keys.up    = 0x01fb;	// Q
	keys.down  = 0x01fd;	// A
	keys.left  = 0x02df;	// O
	keys.right = 0x01df;	// P
	keys.fire  = 0x017f;	// SPACE
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
	while (0 == sp_GetKey ());
#else
#ifdef MODE_128K
#else
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
#endif
	while (1) {
		gpit = sp_GetKey ();
		if (gpit == '1' || gpit == '2') {
			joyfunc = sp_JoyKeyboard;
			gpjt = (gpit - '1') ? 6 : 0;
#ifdef USE_TWO_BUTTONS
			keys.up = keyscancodes [gpjt ++];
			keys.down = keyscancodes [gpjt ++];
			keys.left = keyscancodes [gpjt ++];
			keys.right = keyscancodes [gpjt ++];
			key_fire = keys.fire = keyscancodes [gpjt ++];
			key_jump = keyscancodes [gpjt];
#else
			keys.up = keyscancodes [gpjt ++];		// UP
			keys.down = keyscancodes [gpjt ++];		// DOWN
			keys.left = keyscancodes [gpjt ++];		// LEFT
			keys.right = keyscancodes [gpjt ++];	// RIGHT
			keys.fire = keyscancodes [gpjt ++];		// FIRE
			//key_jump = keyscancodes [gpjt];		// JUMP		//Salva (13/12/15)
#endif
			break;
		} else if (gpit == '3') {
			joyfunc = sp_JoyKempston;
			break;
		} else if (gpit == '4') {
			joyfunc = sp_JoySinclair1;
			break;
		}
	}
#ifdef MODE_128K
	_AY_PL_SND (0);
	sp_WaitForNoKey ();
#else
	#asm
		di
	#endasm
#endif
#endif
}

// Experimental
#ifdef ENABLE_LAVA
#include "engine\lava.h"
#endif

*/

#ifndef PHANTOMAS_ENGINE
// UP DOWN LEFT RIGHT FIRE JUMP <- with fire/hitter/throwable
// UP DOWN LEFT RIGHT JUMP xxxx <- with just jump, so configure ahead:
//unsigned int keyscancodes [] = {
//	0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,		// WSADMN
//#ifdef USE_TWO_BUTTONS
	//0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0x087f 		// QAOP(SPC)N	//Salva (13/12/15)
	//0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f		// WSADMN
//#else
//	0x01fb, 0x01fd, 0x02df, 0x01df, 0x01fb, 0 			// QAOPQ-
//#endif
//};
#endif

void select_joyfunc (void) {
#ifdef PHANTOMAS_ENGINE
	joyfunc = sp_JoyKeyboard;
	keys.up    = 0x01fb;	// Q
	keys.down  = 0x01fd;	// A
	keys.left  = 0x02df;	// O
	keys.right = 0x01df;	// P
	keys.fire  = 0x017f;	// SPACE
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
	while (0 == sp_GetKey ());
#else
#ifdef MODE_128K
#else
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
#endif
	while (1) {
		gpit = sp_GetKey ();
		
		if (gpit == '1' || gpit == '2') 
		{
			joyfunc = sp_JoyKeyboard;
			gpjt = (gpit - '1') ? 6 : 0;
			
			if (gpit == '1')
			{	
				//0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0x087f 		// QAOP(SPC)N
				keys.up = 0x01fb;
				keys.down = 0x01fd;
				keys.left = 0x02df;
				keys.right = 0x01df;
				keys.fire = 0x017f;
				break;
			}
			else
			{			
				//0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f		// WSADMN
				keys.up = 0x02fb;
				keys.down = 0x02fd;
				keys.left = 0x01fd;
				keys.right = 0x04fd;
				keys.fire = 0x087f;
				break;
			}
		} 
		else if (gpit == '3') 
		{
			joyfunc = sp_JoyKempston;
			break;
		} 
		else if (gpit == '4') 
		{
			joyfunc = sp_JoySinclair1;
			break;
		}
	}
#ifdef MODE_128K
	_AY_PL_SND (0);
	sp_WaitForNoKey ();
#else
	#asm
		di
	#endasm
#endif
#endif
}