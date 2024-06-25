xcopy /y "libs\SFML\lib\PDB" "TheGreatWar\bin\Debug\*"
xcopy /y "libs\SFML\dll\Debug" "TheGreatWar\bin\Debug\*"
xcopy /y "libs\SFML\dll\openal32.dll" "TheGreatWar\bin\Debug\*"
xcopy /y "libs\SFML\dll\Release" "TheGreatWar\bin\Release\*"
xcopy /y "libs\SFML\dll\openal32.dll" "TheGreatWar\bin\Release\*"

start vendor\premake5.exe vs2022