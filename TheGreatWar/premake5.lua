project "TheGreatWar"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "off"

   targetdir "bin/%{cfg.buildcfg}"
   objdir("bin/Obj/%{cfg.buildcfg}")

   files {
      "include/**.h", 
      "include/**.hpp",
      "src/**.h", 
      "src/**.hpp", 
      "src/**.cpp",
      "*.lua",
      "resource/resource.h",
      "resource/resource.rc"
   }

   includedirs {
      "../IsometricEngine/include",
      "../include",
   }

   links { 
      "IsometricEngine" 
   }
   
   defines { 
      "SFML_DYNAMIC" 
   }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
