// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// mapa.h
// Fixed map for 48K mono-level games / placeholder
// Loads "map.bin" and "bolts.bin" as generated by map2bin.exe

extern unsigned char map [0];

#asm
	._map
		BINARY "map.bin"
#endasm

#ifndef COMPRESSED_LEVELS
typedef struct {
    unsigned char np, x, y, st;
} BOLTS;
#endif

#ifndef DEACTIVATE_KEYS
#define MAX_bolts 32
extern BOLTS bolts [0];
#asm
	._bolts
		BINARY "bolts.bin"
#endasm
#else
#define MAX_bolts 0
#endif

#ifdef ENABLE_CUSTOM_CONNECTIONS
typedef struct {
	unsigned char left, right, up, down;
} CUSTOM_CONNECTION;

CUSTOM_CONNECTION custom_connections [MAP_W * MAP_H];
#endif
