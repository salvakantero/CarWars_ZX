// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// Tileset.h
// Fixed tileset for 48K mono-level games / placeholder
// Just loads up ts.bin as generated by ts2bin.exe

extern unsigned char tileset [0];
#asm
	._tileset
		BINARY "ts.bin"
#endasm