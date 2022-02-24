			if (hitter_on && killable && hitter_hit == 0) {
#if defined (PLAYER_CAN_PUNCH)
				if (hitter_frame <= 3) {
					if (collide_pixel (hitter_x + (p_facing ? 6 : 1), hitter_y + 3, gpen_cx, gpen_cy)) {
#elif defined (PLAYER_HAZ_SWORD)
				if (hitter_frame > 2 && hitter_frame < 7) {
					if ((p_up == 0 && collide_pixel (hitter_x + (p_facing ? 6 : 1), hitter_y + 3, gpen_cx, gpen_cy)) ||
						(p_up && collide_pixel (hitter_x + 4, hitter_y, gpen_cx, gpen_cy))
					) {
#elif defined (PLAYER_CAN_DRILL)
				if (hitter_frame > 2 && hitter_frame < 7 && 
				    baddies [enoffsmasi].t != 16 && 
					baddies [enoffsmasi].t != 12 &&
					baddies [enoffsmasi].t != 8) { // (CARWARS) voladores no mueren
					if ((p_up == 0 && collide_pixel (hitter_x + (p_facing ? 6 : 1), hitter_y + 3, gpen_cx, gpen_cy)) ||
						(p_up && collide_pixel (hitter_x + 4, hitter_y, gpen_cx, gpen_cy))
					) {
#elif defined (PLAYER_HAZ_WHIP)
				if (hitter_frame < 5) {
					if (collide_pixel (hitter_x + (p_facing ? 14 : 1), hitter_y + 3, gpen_cx, gpen_cy)) {
#endif
						hitter_hit = 1;
#ifdef MODE_128K
						_AY_PL_SND (7);
#else
						peta_el_beeper (1);
#endif
						enemy_kill (PLAYER_HITTER_STRENGTH);
						continue;
					}
				}
			}
