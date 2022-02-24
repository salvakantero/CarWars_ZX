			// Collide with bullets
				for (gpjt = 0; gpjt < MAX_BULLETS; gpjt ++) 
				{
					if (bullets_estado [gpjt] == 1) 
					{
						if (collide_pixel (bullets_x [gpjt] + 3, bullets_y [gpjt] + 3, gpen_cx, gpen_cy)) 
						{
							bullets_estado [gpjt] = 0;						
							enemy_kill (PLAYER_BULLETS_STRENGTH);
							continue;
						}
					}
				}
