-- premake5.lua
workspace "TheGreatWar"
   startproject "IsometricEngine"
   architecture "x64"
   configurations {
      "Debug", 
      "Release" 
   }

   filter { "platforms:Win64" }
      system "Windows"
      
include "IsometricEngine"