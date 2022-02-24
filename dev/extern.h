// MT Engine MK2
// Copyleft 2014 the Mojon Twins

// extern.h
// External custom code to be run from a script

// =======[CUSTOM MODIFICATION]=======
unsigned char *textbuff = 23458;
unsigned char *extaddress;
unsigned char exti, extx, exty, stepbystep, keyp;
extern unsigned char textos_load [0];


void do_extern_action (unsigned char n) 
{
	if (n < 250) 
	{	
		// Show text n
		stepbystep = 1;
		
		asm_int [0] = (n - 1) << 1;
		#asm
			; First we get where to look for the packed string
		
			ld a, (_asm_int)
			ld e, a
			ld a, (_asm_int + 1)
			ld d, a
			
			ld hl, _textos_load
			add hl, de
			ld c, (hl)
			inc hl
			ld b, (hl)
			push bc
			pop de
			ld hl, _textos_load
			add hl, de
			
			ld de, 23458
	
			; 5-bit scaped depacker by na_th_an
			; Contains code by Antonio Villena
			
			ld a, $80
	
		.fbsd_mainb
	        call fbsd_unpackc
	        ld c, a
	        ld a, b
	        and a
	        jr z, fbsd_fin
	        call fbsd_stor
	        ld a, c
	        jr fbsd_mainb	
	
		.fbsd_stor
	        cp 31
	        jr z, fbsd_escaped
	        add a, 64
	        jr fbsd_stor2
		.fbsd_escaped
	        ld a, c
	        call fbsd_unpackc
	        ld c, a
	        ld a, b
	        add a, 32
		.fbsd_stor2
	        ld (de), a
	        inc de
	        ret
	
		.fbsd_unpackc
	        ld      b, 0x08
		.fbsd_bucle
	        call    fbsd_getbit
	        rl      b
	        jr      nc, fbsd_bucle
	        ret
	
		.fbsd_getbit
	        add     a, a
	        ret     nz
	        ld      a, (hl)
	        inc     hl
	        rla
	        ret        
	        
		.fbsd_fin
			ld (de), a	
			;
			;		
			
		#endasm	
		
		// Show
		exti = textbuff [0] - 64;
			
		// Draw empty frame
		extx = 3 + exti + exti;
		exti = !((VIEWPORT_Y + (p_y >> 9)) < extx);	
		saca_a_todo_el_mundo_de_aqui (exti);
		print_str (3, 3, 7, "!!!!!!!!!!!!!!!!!!!!!!!!!!");
		for (exty = 4; exty < extx - 2; exty ++) print_str (3, exty, 7, "!                        !");
		print_str (3, extx - 2, 7, "!!!!!!!!!!!!!!!!!!!!!!!!!!");
			
		exty = 5;
		
		// Draw text
		extx = 5; 
		extaddress = textbuff + 1;
		keyp = 1;
		while (exti = *extaddress ++) 
		{
			if (exti == '%') 
			{
				extx = 5; exty += 1;
			} 
			else 
			{
				sp_PrintAtInv (exty, extx, 70, exti - 32);
				extx ++;
			}
			if (stepbystep) 
			{
				#asm
				halt
				#endasm
				if (exti != 32) _AY_PL_SND (2);
				#asm
				halt
				#endasm
				sp_UpdateNow ();
			}
			
			if (button_pressed ()) 
			{
				if (keyp == 0) 
				{
					stepbystep = 0;
				} 
			} 
			else 
			{
				keyp = 0;
			}
		}
		sp_UpdateNow ();
		sp_WaitForNoKey ();
		while (button_pressed ());
		espera_activa (5000);
	} 
}

#asm
	._textos_load
		BINARY "..\bin\texts.bin"
#endasm
