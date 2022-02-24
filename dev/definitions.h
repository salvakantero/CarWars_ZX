// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// definitions.h
// Main definitions

struct sp_UDK keys;
void *joyfunc;				

unsigned char *gen_pt;
 
void *my_malloc(uint bytes) {
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;

// Gigaglobals

struct sp_SS *sp_player;
struct sp_SS *sp_moviles [3];
#ifdef PLAYER_CAN_FIRE
struct sp_SS *sp_bullets [MAX_BULLETS];
#endif
#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD) || defined(PLAYER_HAZ_WHIP) || defined (PLAYER_CAN_DRILL)
struct sp_SS *sp_hitter;
#endif
#ifdef ENABLE_SHOOTERS
struct sp_SS *sp_cocos [MAX_COCOS];
#endif
#ifdef ENABLE_FLOATING_OBJECTS
#ifdef ENABLE_FO_CARRIABLE_BOXES
struct sp_SS *sp_carriable;
#endif
#endif

struct sp_Rect spritesClipValues;
struct sp_Rect *spritesClip;

unsigned char enoffs;

// Aux

extern unsigned int asm_int [1];
extern unsigned int asm_int_2 [1];
unsigned char half_life = 0;

#asm
._asm_int
	defw 0
._asm_int_2
	defw 0
#endasm

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
#define sgni(n)			(n < 0 ? -1 : 1)
#define saturate(n)		(n < 0 ? 0 : n)
#define WTOP 1
#define WBOTTOM 2
#define WLEFT 3
#define WRIGHT 4

// Player
int p_x, p_y, p_cx;
#if defined(PHANTOMAS_ENGINE)
char p_vx, p_vy, ptgmx, ptgmy;
#elif defined (HANNA_ENGINE)
char p_v;
#else
int p_vx, p_vy, ptgmx, ptgmy;
#endif
char p_g, p_ax, p_rx;
unsigned char p_salto, p_cont_salto;
unsigned char *p_current_frame, *p_next_frame;
unsigned char p_saltando;
unsigned char p_frame, p_subframe, p_facing;
unsigned char p_estado;
unsigned char p_ct_estado;
unsigned char p_gotten;
unsigned char p_life, p_objs, p_keys;
#ifndef BODY_COUNT_ON
unsigned char p_killed;
#endif
unsigned char p_disparando;
#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP) || defined (PLAYER_CAN_DRILL)
unsigned char p_hitting;
#endif
#ifdef PLAYER_HAZ_SWORD
unsigned char p_up; 
#endif
#ifdef PLAYER_CAN_DRILL
unsigned char p_up, p_down, p_last_move;
#endif
unsigned char p_facing_v, p_facing_h;
#ifdef DIE_AND_RESPAWN
unsigned char p_killme, p_safe_pant, p_safe_x, p_safe_y;
#endif
#ifdef MAX_AMMO
unsigned char p_ammo;
#endif
#ifdef ENABLE_FO_CARRIABLE_BOXES
unsigned char p_hasbox;
#endif
#ifdef JETPAC_DEPLETES
unsigned char p_fuel;
#endif

// Make some player values variable. Preliminary, just the maximum jump speed...

#ifdef PLAYER_VARIABLE_JUMP
int player_max_vy_saltando;
#endif

#define FACING_RIGHT 0
#define FACING_LEFT 2
#define FACING_UP 4
#define FACING_DOWN 6

#define SENG_JUMP 0
#define SENG_SWIM 1
#define SENG_COPT 2
#define SENG_JETP 3
#define SENG_BOOT 4

// Enems on screen

unsigned char en_an_base_frame [3];
unsigned char en_an_frame [3];
unsigned char en_an_count [3];
unsigned char *en_an_current_frame [3], *en_an_next_frame [3];
unsigned char en_an_state [3];

#ifdef ENEMY_BACKUP
unsigned char enemy_backup [3 * MAP_W * MAP_H];
#endif

#ifdef PLAYER_CAN_FIRE
unsigned char en_an_morido [3];
#endif

#if defined (RANDOM_RESPAWN) || defined (ENABLE_CUSTOM_TYPE_6)
int en_an_x [3];
int en_an_y [3];
int en_an_vx [3];
int en_an_vy [3];
#ifdef RANDOM_RESPAWN
unsigned char en_an_fanty_activo [3];
#endif
#endif

#ifdef ENABLE_PURSUERS
unsigned char en_an_alive [3];
unsigned char en_an_dead_row [3];
unsigned char en_an_rawv [3];
#endif

#ifdef ENABLE_HANNA_MONSTERS_11
unsigned char en_an_dir [3];
#endif

#define TYPE_6_IDLE 		0
#define TYPE_6_PURSUING		1
#define TYPE_6_RETREATING	2
#define GENERAL_DYING		4

// Bullets

#ifdef PLAYER_CAN_FIRE
unsigned char bullets_x [MAX_BULLETS];
unsigned char bullets_y [MAX_BULLETS];
unsigned char bullets_mx [MAX_BULLETS];
unsigned char bullets_my [MAX_BULLETS];
unsigned char bullets_estado [MAX_BULLETS];
#ifdef LIMITED_BULLETS
unsigned char bullets_life [MAX_BULLETS];
#endif	
#endif

#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP) || defined (PLAYER_CAN_DRILL)
unsigned char hitter_on;
unsigned char hitter_type;
unsigned char hitter_frame;
unsigned char hitter_x, hitter_y;
unsigned char *hitter_current_frame, *hitter_next_frame;
unsigned char hitter_hit;
#endif

// Current screen buffers
unsigned char map_attr [150];
//unsigned char map_buff [150];
// There's XXX bytes free at FREEPOOL according to splib2's doc.
// (240 if in 128K mode, 512 - stack size (do not risk!) in 48K mode)
// Why not use them?
unsigned char *map_buff = FREEPOOL;
//

// Current screen hotspot
unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char orig_tile;
unsigned char do_respawn; 
unsigned char no_draw; 

// Flags para scripting
#if defined(ACTIVATE_SCRIPTING) || defined(TILE_GET) || defined(ENABLE_SIM)
#define MAX_FLAGS 10
unsigned char flags[MAX_FLAGS];
#endif

// Globalized
unsigned char n_pant, o_pant;
unsigned char level = 0;
unsigned char silent_level;

unsigned char maincounter;

// Breakable walls/etc
#ifdef BREAKABLE_WALLS
unsigned char brk_buff [150];
#ifdef BREAKABLE_ANIM
// Store this in the free memory pool (see ^)
unsigned char *breaking_x = FREEPOOL + 150;
unsigned char *breaking_y = FREEPOOL + 150 + MAX_BREAKABLE;
unsigned char *breaking_f = FREEPOOL + 150 + MAX_BREAKABLE + MAX_BREAKABLE;

unsigned char breaking_idx = 0;
unsigned char do_process_breakable = 0;
#endif
#endif

#ifdef BREAKABLE_WALLS_SIMPLE
#ifdef BREAKABLE_ANIM
unsigned char *breaking_x = FREEPOOL + 150;
unsigned char *breaking_y = FREEPOOL + 150 + MAX_BREAKABLE;
unsigned char *breaking_f = FREEPOOL + 150 + MAX_BREAKABLE + MAX_BREAKABLE;
//

unsigned char breaking_idx = 0;
unsigned char do_process_breakable = 0;
#endif
#endif

// Fire zone
#ifdef ENABLE_FIRE_ZONE
unsigned char fzx1, fzy1, fzx2, fzy2, f_zone_ac;
#endif

// Timer
#ifdef TIMER_ENABLE
typedef struct {
	unsigned char on;
	unsigned char t;
	unsigned char frames;
	unsigned char count;
	unsigned char zero;
} CTIMER;
CTIMER ctimer;
#endif

#if defined(ACTIVATE_SCRIPTING) && defined(ENABLE_PUSHED_SCRIPTING)
unsigned char just_pushed;
#endif

#ifdef ACTIVATE_SCRIPTING
void __FASTCALL__ draw_scr_background (void);
void __FASTCALL__ draw_scr (void);
#endif
void espera_activa (int espera);
void run_fire_script (void);

#ifdef USE_TWO_BUTTONS
int key_jump, key_fire;
#endif

#ifdef MODE_128K
void blackout_area (void);
void get_resource (unsigned char res, unsigned int dest);
#endif

#ifdef PLAYER_CHECK_MAP_BOUNDARIES
	unsigned char x_pant, y_pant;
#endif

unsigned char do_gravity = 1, p_engine;

//void cortina (void);
unsigned char rand (void);
void saca_a_todo_el_mundo_de_aqui (unsigned char which_ones);
void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t);

#ifdef ENABLE_FLOATING_OBJECTS
unsigned char FO_add (unsigned char x, unsigned char y, unsigned char t);
void FO_paint (unsigned char idx);
void FO_paint_all (void);
#endif

#define BUFFER_IDX(x,y) x+(y<<4)-y

#ifdef ENABLE_SIM
unsigned char items [SIM_DISPLAY_MAXITEMS];
void display_items (void);
#endif

unsigned char enoffsmasi;

#ifdef SCRIPTING_KEY_FIRE
unsigned char invalidate_fire = 0;
#endif

