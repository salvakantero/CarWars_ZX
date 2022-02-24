// Easy menu
// First shows PLAY/PASSWORD
// Let's you introduce password.
// Returns level number 0-n
// Passwords are fixed lenght

#define PASSWORD_LENGTH	6
#define MENU_Y 			10
#define MENU_X			11

unsigned char *clearout = "          ";
unsigned char *password = "****** ";


unsigned char pass_ok(unsigned char *passtyped)
{
	gpt = 1;
	for (gpit = 0; gpit < PASSWORD_LENGTH; gpit ++)
		if (password[gpit] != passtyped[gpit]) gpt = 0;
	return gpt;
}


unsigned char which_level (void) 
{
	print_str (MENU_X, MENU_Y, 2, " PASSWORD ");	
	print_str (MENU_X, MENU_Y + 2, 7, clearout);
	print_str (MENU_X, MENU_Y + 3, 7, clearout);
	
	for (gpit = 0; gpit < PASSWORD_LENGTH; gpit ++) password [gpit] = '.';
	password [PASSWORD_LENGTH] = ' ';
	gpit = 0;
	sp_WaitForNoKey ();
	
	while (1) 
	{
		password [gpit] = '*';
		print_str (16 - PASSWORD_LENGTH / 2, MENU_Y + 2, 7, password);
		sp_UpdateNow ();
		do 
		{
			gpjt = sp_GetKey ();
		} 
		while (!gpjt);
		
		if (gpjt == 12 && gpit > 0) 
		{
			password [gpit] = gpit == PASSWORD_LENGTH ? ' ' : '.';
			gpit --;
		}
		if (gpjt == 13) break;
		if (gpjt > 'Z') gpjt -= 32;
		if (gpjt >= '0' && gpjt <= 'Z' && gpit < PASSWORD_LENGTH) 
		{
			password [gpit] = gpjt;
			gpit ++;
		}
		_AY_PL_SND (3);
		sp_WaitForNoKey ();
	}

	sp_WaitForNoKey ();
	
	// Check passwords
	if (pass_ok("LOU011")) return 1; //etapa 2
	if (pass_ok("PAE235")) return 2; //etapa 3
	return 0; //etapa 1
} 


unsigned char simple_menu (void) 
{
	blackout_area ();
	print_str (MENU_X, MENU_Y, 2, "== MENU ==");
	print_str (MENU_X, MENU_Y + 2, 7, "1 PLAY");
	print_str (MENU_X, MENU_Y + 3, 7, "2 PASSWORD");
	sp_UpdateNow ();
	while (1) 
	{
		gpit = sp_GetKey ();
		if (gpit == '1')
		{
			return 0;
			break;
		}
		else if (gpit == '2') 
		{
			_AY_PL_SND (1);
			return which_level ();
			break;
		}
	}
}
