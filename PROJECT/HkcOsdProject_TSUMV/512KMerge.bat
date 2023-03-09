
@echo off
call checkDataSize

echo "============================================"
echo "##========================================##"
echo "##========================================##"
echo "##===========   Day Day Up   =============##"
echo "##========================================##"
echo "##=========== 技术支持：L ================##"
echo "============================================"

FOR %%X IN (00 01 02 03 04 05 06 07 ) DO .\hex2bin32 -l 0x10000 -e X%%X ".\Obj\TSUM.H%%X"  > NULL

COPY "..\TSUM\TSUM.X05" ".\Obj\TSUM.X05"

COPY/B ".\Obj\TSUM.X*" ".\Obj\TSUM56.BIN"

IF NOT EXIST bin md bin
cd bin
if exist *.bin del *.bin
cd..
copy Checksum.exe bin\Checksum.exe
cd obj
COPY "TSUM56.BIN" %1.bin
DEL "TSUM56.*"
copy %1.bin ..\bin
del %1.bin
cd..
cd bin
if exist %1-*.bin del %1-*.bin
Checksum %1.bin /b
del Checksum.exe

set yyyymmdd_hhmmss=%date:~0,4%%date:~5,2%%date:~8,2%_%time:~0,2%%time:~3,2%%time:~6,2%

echo %yyyymmdd_hhmmss%




Pause
 
