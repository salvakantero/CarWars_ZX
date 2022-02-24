
			en_an_count [gpit] ++;
			
			if (gpt != 2) 
			{
				if (en_an_count [gpit] == 4) 
				{
					en_an_count [gpit] = 0;
					en_an_frame [gpit] = !en_an_frame [gpit];
					en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + en_an_frame [gpit]];
				}
			} 
			else 
			{
				en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + (en_an_vx [gpit] > 0)];
			}
