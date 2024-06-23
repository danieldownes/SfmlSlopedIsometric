xcopy /y "libs\SFML\lib\PDB" "IsometricEngine\bin\Debug\*"
xcopy /y "libs\SFML\dll\Debug" "IsometricEngine\bin\Debug\*"
xcopy /y "libs\SFML\dll\openal32.dll" "IsometricEngine\bin\Debug\*"
xcopy /y "libs\SFML\dll\Release" "IsometricEngine\bin\Release\*"
xcopy /y "libs\SFML\dll\openal32.dll" "IsometricEngine\bin\Release\*"

start vendor\premake5.exe vs2022