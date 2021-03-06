// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// hitter_h
// Hitter (punch/sword/whip/drill) helper functions

#ifdef PLAYER_CAN_PUNCH
	//								H   H   H
	unsigned char hoffs_x [] = {12, 14, 16, 16, 12};
	#define HITTER_MAX_FRAME 5
#endif
#ifdef PLAYER_HAZ_SWORD
	//                                     H   H   H   H
	unsigned char hoffs_x [] = {8, 10, 12, 14, 15, 15, 14, 13, 10};
	unsigned char hoffs_y [] = {2,  2,  2, 3,  4,  4,  5,  6,  7};
	#define HITTER_MAX_FRAME 9
#endif
#ifdef PLAYER_HAZ_WHIP
	//                          H  H   H
	unsigned char hoffs_x [] = {8, 16, 16, 12, 8,  4, 0};
	unsigned char hoffs_y [] = {4, 4,  4,  6,  8, 10, 12};
	#define HITTER_MAX_FRAME 7
#endif
#ifdef PLAYER_CAN_DRILL
	//                                     H   H   H   H
	unsigned char hoffs_x [] = {8, 10, 12, 14, 16, 16, 14, 13, 10};
	#define HITTER_MAX_FRAME 9
#endif

void __FASTCALL__ render_hitter (void) {
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
	gpy = p_y;
	gpx = p_x;
#else
	gpy = (p_y >> 6);
	gpx = (p_x >> 6);
#endif

// Punching main code

#ifdef PLAYER_CAN_PUNCH
	hitter_y = gpy + 6;
	if (p_facing) {
		hitter_x = gpx + hoffs_x [hitter_frame];
		hitter_next_frame = sprite_20_a;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 7) >> 4; gpyy = (hitter_y + 3) >> 4;
#endif
	} else {
		hitter_x = gpx + 8 - hoffs_x [hitter_frame];
		hitter_next_frame = sprite_21_a;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x) >> 4; gpyy = (hitter_y + 3) >> 4;
#endif
	}
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
	if (hitter_frame >= 1 && hitter_frame <= 3)
		break_wall (gpxx, gpyy);
#endif		
#endif

// Sword main code

#ifdef PLAYER_HAZ_SWORD
	if (p_up) {
		hitter_x = gpx + hoffs_y [hitter_frame];
		hitter_y = gpy + 6 - hoffs_x [hitter_frame];
		hitter_next_frame = sprite_sword_u;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 4) >> 4; gpyy = (hitter_y) >> 4;
#endif		
	} else {
		hitter_y = gpy + hoffs_y [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpyy = (hitter_y + 4) >> 4;
#endif
		if (p_facing) {
			hitter_x = gpx + hoffs_x [hitter_frame];
			hitter_next_frame = sprite_sword_r;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			gpxx = (hitter_x + 7) >> 4; 
#endif
		} else {
			hitter_x = gpx + 8 - hoffs_x [hitter_frame];
			hitter_next_frame = sprite_sword_l;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			gpxx = (hitter_x) >> 4; 
#endif			
		}
	}
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
	if (hitter_frame > 2 && hitter_frame < 7)
		break_wall (gpxx, gpyy);
#endif
#endif

// Whippo main code

#ifdef PLAYER_HAZ_WHIP
	hitter_y = gpy + hoffs_y [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
	gpyy = (hitter_y + 3) >> 4;
#endif
	if (p_facing) {
		hitter_x = gpx + hoffs_x [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 15) >> 4; 
#endif
	} else {
		hitter_x = gpx - hoffs_x [hitter_frame];
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x) >> 4; 
#endif			
	}
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
if (hitter_frame < 3)
	break_wall (gpxx, gpyy);
#endif
#endif

// Drill main code
#ifdef PLAYER_CAN_DRILL
	if (p_last_move == 0) {
		hitter_x = gpx + 4;
		hitter_y = gpy + 6 - hoffs_x [hitter_frame];
		if (level == 0)
			hitter_next_frame = sprite_drill0_u;
		else if (level == 1)
			hitter_next_frame = sprite_drill1_u;
		else
			hitter_next_frame = sprite_drill2_u;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 4) >> 4; gpyy = (hitter_y) >> 4;
#endif		
	} else if (p_last_move == 1) {
		hitter_x = gpx + 4;
		hitter_y = gpy + 2 + hoffs_x [hitter_frame];
		if (level == 0)
			hitter_next_frame = sprite_drill0_d;
		else if (level == 1)
			hitter_next_frame = sprite_drill1_d;
		else
			hitter_next_frame = sprite_drill2_d;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpxx = (hitter_x + 4) >> 4; gpyy = (hitter_y) >> 4;
#endif		
	} else {
		hitter_y = gpy + 4;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
		gpyy = (hitter_y + 4) >> 4;
#endif
		if (p_last_move == 2) {
			hitter_x = gpx + 6 - hoffs_x [hitter_frame];
			if (level == 0)
				hitter_next_frame = sprite_drill0_l;
			else if (level == 1)
				hitter_next_frame = sprite_drill1_l;
			else
				hitter_next_frame = sprite_drill2_l;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			gpxx = (hitter_x) >> 4; 
#endif	
		} else {
			hitter_x = gpx + 2 + hoffs_x [hitter_frame];
			if (level == 0)
				hitter_next_frame = sprite_drill0_r;
			else if (level == 1)
				hitter_next_frame = sprite_drill1_r;
			else 
				hitter_next_frame = sprite_drill2_r;
#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			gpxx = (hitter_x + 7) >> 4; 
#endif		
		}
	}
#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
	if (hitter_frame > 2 && hitter_frame < 7)
		break_wall (gpxx, gpyy);
#endif
#endif


// End of main codes.

	sp_MoveSprAbs (sp_hitter, spritesClip,
		hitter_next_frame - hitter_current_frame,
		VIEWPORT_Y + (hitter_y >> 3), VIEWPORT_X + (hitter_x >> 3),
		hitter_x & 7, hitter_y & 7);
	hitter_current_frame = hitter_next_frame;

	hitter_frame ++;
	if (hitter_frame == HITTER_MAX_FRAME) {
		hitter_on = 0;
		sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
		p_hitting = 0;
	}
}
