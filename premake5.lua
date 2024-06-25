-- premake5.lua
workspace "TheGreatWar"
   startproject "TheGreatWar"
   architecture "x64"
   configurations {
      "Debug", 
      "Release" 
   }

   filter { "platforms:Win64" }
      system "Windows"

include "TheGreatWar"
include "IsometricEngine"
