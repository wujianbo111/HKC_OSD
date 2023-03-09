@echo off
call checkDataSize
if not exist .\_Binary md .\_Binary
..\BIN2HEX /Q /4 ..\r2\2DTo3D\aeon.bin .\_Binary\aeon.hex

HEX2BIN /Q /L524288 obj\TSUM.H00 obj\TSUM56.BIN
HEX2BIN /Q /O65536 /M obj\TSUM.H01 obj\TSUM56.BIN
HEX2BIN /Q /O131072 /M obj\TSUM.H02 obj\TSUM56.BIN
HEX2BIN /Q /O196608 /M obj\TSUM.H03 obj\TSUM56.BIN
HEX2BIN /Q /O262144 /M obj\TSUM.H04 obj\TSUM56.BIN
HEX2BIN /Q /O327680 /M .\_Binary\aeon.hex obj\TSUM56.BIN
HEX2BIN /Q /O393216 /M obj\TSUM.H06 obj\TSUM56.BIN
HEX2BIN /Q /O458752 /M obj\TSUM.H07 obj\TSUM56.BIN




IF NOT EXIST bin md bin
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
Pause
