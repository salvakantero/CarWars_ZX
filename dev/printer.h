// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// printer.h
// Printing functions

#define MESSAGE_COLOUR 7 //56 //79
unsigned char *spacer = "!!!!!!!!!!!!!!!";

unsigned char attr (char x, char y) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	if (x < 0 || y < 0 || x > 14 || y > 9) return 0;
	return map_attr [x + (y << 4) - y];
}

unsigned char qtile (unsigned char x, unsigned char y) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	return map_buff [x + (y << 4) - y];
}

#ifdef UNPACKED_MAP
// Funci�n que pinta un tile para mapas unpacked

void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t) {
	t = 64 + (t << 2);
	gen_pt = tileset + 2048 + t;
	sp_PrintAtInv (y, x, *gen_pt ++, t ++);
	sp_PrintAtInv (y, x + 1, *gen_pt ++, t ++);
	sp_PrintAtInv (y + 1, x, *gen_pt ++, t ++);
	sp_PrintAtInv (y + 1, x + 1, *gen_pt, t);
}

#else
// Funci�n que pinta un tile para mapas packed

void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t) {
	unsigned char xx, yy;
#ifdef USE_AUTO_TILE_SHADOWS
	unsigned char *gen_pt_alt;
	unsigned char t_alt;
#endif

#ifdef USE_AUTO_SHADOWS
	xx = (x - VIEWPORT_X) >> 1;
	yy = (y - VIEWPORT_Y) >> 1;
	if (!(attr (xx, yy) & 8) && (t < 16 || t == 19)) {
		t = 64 + (t << 2);
		gen_pt = tileset + 2048 + t;
		sp_PrintAtInv (y, x, attr (xx - 1, yy - 1) & 8 ? (gen_pt[0] & 7)-1 : gen_pt [0], t);
		sp_PrintAtInv (y, x + 1, attr (xx, yy - 1) & 8 ? (gen_pt[1] & 7)-1 : gen_pt [1], t + 1);
		sp_PrintAtInv (y + 1, x, attr (xx - 1, yy) & 8 ? (gen_pt[2] & 7)-1 : gen_pt [2], t + 2);
		sp_PrintAtInv (y + 1, x + 1, gen_pt [3], t + 3);
	} else {
#endif

#ifdef USE_AUTO_TILE_SHADOWS
	xx = (x - VIEWPORT_X) >> 1;
	yy = (y - VIEWPORT_Y) >> 1;
	if (!(attr (xx, yy) & 8) && (t < 16 || t == 19)) {
		t = 64 + (t << 2);
		if (t == 140) {
			gen_pt = (unsigned char *) &tileset [2188];
			t_alt = 192;
			gen_pt_alt = (unsigned char *) &tileset [2048 + 192];
		} else {
			gen_pt = (unsigned char *) &tileset [2048 + t];
			t_alt = 128 + t;
			gen_pt_alt = (unsigned char *) &tileset [2048 + t + 128];
		}

		if (attr (xx - 1, yy - 1) & 8) {
			sp_PrintAtInv (y, x, gen_pt_alt [0], t_alt);
		} else {
			sp_PrintAtInv (y, x, gen_pt [0], t);
		}
		if (attr (xx, yy - 1) & 8) {
			sp_PrintAtInv (y, x + 1, gen_pt_alt [1], t_alt + 1);
		} else {
			sp_PrintAtInv (y, x + 1, gen_pt [1], t + 1);
		}
		if (attr (xx - 1, yy) & 8) {
			sp_PrintAtInv (y + 1, x, gen_pt_alt [2], t_alt + 2);
		} else {
			sp_PrintAtInv (y + 1, x, gen_pt [2], t + 2);
		}
		sp_PrintAtInv (y + 1, x + 1, gen_pt [3], t + 3);
	} else {
#endif
		t = 64 + (t << 2);
		gen_pt = tileset + 2048 + t;
		sp_PrintAtInv (y, x, *gen_pt ++, t ++);
		sp_PrintAtInv (y, x + 1, *gen_pt ++, t ++);
		sp_PrintAtInv (y + 1, x, *gen_pt ++, t ++);
		sp_PrintAtInv (y + 1, x + 1, *gen_pt, t);
#ifdef USE_AUTO_SHADOWS
	}
#endif

#ifdef USE_AUTO_TILE_SHADOWS
	}
#endif
}
#endif

void draw_coloured_tile_gamearea (unsigned char x, unsigned char y, unsigned char tn) {
	draw_coloured_tile (VIEWPORT_X + (x << 1), VIEWPORT_Y + (y << 1), tn);
}

void print_number2 (unsigned char x, unsigned char y, unsigned char number) {
	sp_PrintAtInv (y, x, 7, 16 + (number / 10));
	sp_PrintAtInv (y, x + 1, 7, 16 + (number % 10));
}

#ifndef DEACTIVATE_OBJECTS
void draw_objs () {
#if defined(ONLY_ONE_OBJECT) && defined(ACTIVATE_SCRIPTING)
	if (p_objs) {
		sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X, 135, 132);
		sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X + 1, 135, 133);
		sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X, 135, 134);
		sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X + 1, 135, 135);
	} else {
		draw_coloured_tile (OBJECTS_ICON_X, OBJECTS_ICON_Y, 17);
	}
	print_number2 (OBJECTS_X, OBJECTS_Y, flags [OBJECT_COUNT]);
#else
	print_number2 (OBJECTS_X, OBJECTS_Y, p_objs);
#endif
}
#endif

void print_str (unsigned char x, unsigned char y, unsigned char c, unsigned char *s) {
	while (*s) sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
}

#if defined (COMPRESSED_LEVELS) || defined (SHOW_LEVEL_ON_SCREEN)
void blackout_area (void) {
	// blackens gameplay area for LEVEL XX display
	asm_int [0] = 22528 + 32 * VIEWPORT_Y + VIEWPORT_X;
	#asm
		ld	hl, _asm_int
		ld	a, (hl)
		ld	e, a
		inc	hl
		ld	a, (hl)
		ld	d, a

		ld b, 20
	.bal1
		push bc
		push de
		pop hl
		ld	(hl), 0
		inc de
		ld bc, 29
		ldir
		inc de
		inc de
		pop bc
		djnz bal1
	#endasm
}
#endif

unsigned char utaux = 0;
void update_tile (unsigned char x, unsigned char y, unsigned char b, unsigned char t) {
	utaux = (y << 4) - y + x;
	map_attr [utaux] = b;
	map_buff [utaux] = t;
	draw_coloured_tile_gamearea (x, y, t);
}

void print_message (unsigned char *s) {
	print_str (9,  9, MESSAGE_COLOUR, spacer);
	print_str (9, 10, MESSAGE_COLOUR, "!             !");
	print_str (9, 11, MESSAGE_COLOUR, "!             !");
	print_str (10, 11, 66, s);
	print_str (9, 12, MESSAGE_COLOUR, "!             !");
	print_str (9, 13, MESSAGE_COLOUR, spacer);
	sp_UpdateNow ();
	sp_WaitForNoKey ();
}

unsigned char button_pressed (void) {
	return (sp_GetKey () || ((((joyfunc) (&keys)) & sp_FIRE) == 0));
}
