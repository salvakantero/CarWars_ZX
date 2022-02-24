@echo off
echo BUILDING LEVELS!
echo ================

echo LEVEL 1
..\utils\buildlevel.exe ..\map\map1.map 4 7 99 ..\gfx\font.png ..\gfx\work1.png ..\gfx\sprites1.png ..\enems\enems1.ene 0 3 1 99 1 behs1.txt level1.bin decorations1.spt
..\utils\apack.exe level1.bin ..\bin\level1c.bin
move decorations1.spt ..\script

echo LEVEL 2
..\utils\buildlevel.exe ..\map\map2.map 4 7 99 ..\gfx\font.png ..\gfx\work2.png ..\gfx\sprites2.png ..\enems\enems2.ene 0 3 1 99 1 behs2.txt level2.bin decorations2.spt
..\utils\apack.exe level2.bin ..\bin\level2c.bin
move decorations2.spt ..\script

echo LEVEL 3
..\utils\buildlevel.exe ..\map\map3.map 4 7 99 ..\gfx\font.png ..\gfx\work3.png ..\gfx\sprites3.png ..\enems\enems3.ene 0 3 1 99 1 behs3.txt level3.bin decorations3.spt
..\utils\apack.exe level3.bin ..\bin\level3c.bin
move decorations3.spt ..\script

echo DONE!
