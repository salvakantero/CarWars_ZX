@echo off

rem set here the game name (used in filenames)
SET game=carwars

cls
echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

rem but for 48K/single level games... 
rem echo ### MAKING MAPS ###
rem the "Force" parameter is to force 16 tiles maps even if the actual map data
rem has more tan 16 tiles. Extra tiles are written to extra.spt. Me have to move
rem that file to the script folder.
rem ..\utils\map2bin.exe ..\map\mapa.map 2 2 99 map.bin bolts.bin force
rem move map.bin.spt ..\script

rem echo ### MAKING ENEMS ###
rem ..\utils\ene2bin.exe 2 2 3 ..\enems\enems.ene enems.bin hotspots.bin

rem echo ### MAKING TILESET ###
rem ..\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work.png ts.bin

rem echo ### MAKING SPRITESET ###
rem ..\utils\sprcnv.exe ..\gfx\sprites.png sprites.h

rem If you use arrows and/or drops this will make the sprites binary:
rem ..\utils\spg2bin.exe ..\gfx\drop.png spdrop.bin
..\utils\spg2bin.exe ..\gfx\arrow.png sparrow.bin

rem ###########################################################################
rem ## GAME TEXT
rem ###########################################################################

rem Each line in text.txt contains a text string for the game.
rem textstuffer.exe will compress and pack all text strings in
rem a binary file called texts.bin. The parameter "24" define how
rem many chars per line. Word wrapping is automatic.

echo ### MAKING TEXTS ###
cd ..\texts
..\utils\textstuffer.exe texts.txt texts.bin 22
copy texts.bin ..\bin\texts.bin
rem copy texts.bin ..\bin\preload7.bin
rem copy texts.bin ..\dev\

rem ###########################################################################
rem ## GAME SCRIPT
rem ###########################################################################
rem The game script is compiled by msc3.exe. For 128K games use "rampage" at
rem the end so the script compiler generates code to stuff everything in
rem extra pages; the second parameter is the # of screens in your game.
rem i.e. "msc3.exe ninjajar.spt 21 rampage

echo ### MAKING SCRIPT ###
cd ..\script
..\utils\msc3.exe %game%.spt 28 rampage
rem If scripts and texts are going to share the same RAM page, use this line
rem (for 128K games)
rem This calculates an offset for the scripts binary automaticly.
rem ..\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h
echo #define SCRIPT_INIT 49152 >> msc-config.h
copy msc.h ..\dev
copy msc-config.h ..\dev
copy scripts.bin ..\bin\preload7.bin
cd ..\dev

rem For 128K games with text + script sharing the same page, use this to
rem bundle both binaries...
rem echo ### BUNDLING TEXT + SCRIPT ###
rem copy /b ..\texts\texts.bin + ..\script\scripts.bin ..\bin\preload3.bin

rem ###########################################################################
rem ## FIXED SCREENS
rem ###########################################################################
echo ### MAKING FIXED ###
..\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr
..\utils\apack.exe ..\gfx\title.scr ..\bin\title.bin
..\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr
..\utils\apack.exe ..\gfx\ending.scr ..\bin\ending.bin
del ..\gfx\*.scr

rem echo ### MAKING LOADING ###
..\utils\png2scr.exe ..\gfx\loading.png loading.bin

rem ###########################################################################
rem ## LEVELS
rem ###########################################################################

rem we will delegate on makelevels.bat - if your game supports several levels,etc
echo ### BUILDING LEVELS
cd ..\levels
call buildlevels.bat
cd ..\dev

rem ###########################################################################
rem ## LIBRARIAN
rem ###########################################################################

echo ### BUILDING REUBICA ###
..\utils\pasmo reubica.asm reubica.bin

echo ### BUILDING RAMS ###
cd ..\bin
..\utils\librarian.exe
copy RAM3.bin ..\dev\ram3.bin
copy RAM4.bin ..\dev\ram4.bin
copy RAM6.bin ..\dev\ram6.bin
copy RAM7.bin ..\dev\ram7.bin
copy librarian.h ..\dev
cd ..\dev

rem ###########################################################################
rem ## MUSIC
rem ###########################################################################
echo ### COMPILANDO WYZ PLAYER ###
cd ..\mus
..\utils\pasmo WYZproPlay47aZXc.ASM RAM1.bin
copy RAM1.bin ..\dev
cd ..\dev

rem echo ### BUILDING ARKOS ###
rem cd ..\mus
rem if [%1]==[nomus] goto :nomus
rem ..\utils\build_mus_bin.exe ram1.bin
rem :nomus
rem copy ram1.bin ..\dev
rem copy arkos-addresses.h ..\dev\sound
rem cd ..\dev

rem ###########################################################################
rem ## COMPILATION AND TAPE BUILDING
rem ###########################################################################

echo ### COMPILING ###
zcc +zx -vn %game%.c -o %game%.bin -lsplib2 -zorg=24200

echo ### MAKING TAPS ###
..\utils\bas2tap -a10 -sCARWARS loader.bas loader.tap
..\utils\bin2tap -o reubica.tap -a 25000 reubica.bin
..\utils\bin2tap -o ram1.tap -a 32768 ram1.bin
..\utils\bin2tap -o ram3.tap -a 32768 ram3.bin
..\utils\bin2tap -o ram4.tap -a 32768 ram4.bin
..\utils\bin2tap -o ram6.tap -a 32768 ram6.bin
..\utils\bin2tap -o ram7.tap -a 32768 ram7.bin
..\utils\bin2tap -o screen.tap -a 16384 loading.bin
..\utils\bin2tap -o main.tap -a 24200 %game%.bin
copy /b loader.tap + screen.tap + reubica.tap + ram1.tap + ram3.tap + ram4.tap + ram6.tap + ram7.tap + main.tap %game%.tap

echo ### CLEANING ###
del loader.tap
del screen.tap
del main.tap
del reubica.tap
del ram1.bin
del ram3.bin
del ram4.bin
del ram6.bin
del ram7.bin
del ram1.tap
del ram3.tap
del ram4.tap
del ram6.tap
del ram7.tap
del %game%.bin
del zcc_opt.def

dir *.tap

echo ### DONE ###