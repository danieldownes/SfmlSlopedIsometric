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
      "src/**.cpp",
      "*.lua",
      "resource/resource.h",
      "resource/resource.rc",
      "extlibs/**.cpp",
      "extlibs/**.h"
   }

   includedirs {
      "../include",
   }

   defines { 
      "SFML_DYNAMIC" 
   }

   linkoptions { 
      "/ignore:4006" 
   }

   filter "files:extlibs/**.cpp"
      flags { "NoPCH" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      libdirs { 
         "../libs/SFML/lib/Debug",
         "../libs/SFML/extlibs",
      }

      links {
         "opengl32.lib",
         "openal32.lib",
         "freetype.lib",
         "winmm.lib",
         "gdi32.lib",
         "flac.lib",
         "vorbisenc.lib",
         "vorbisfile.lib",
         "vorbis.lib",
         "ogg.lib",
         "ws2_32.lib",
         "legacy_stdio_definitions.lib",
         "sfml-graphics-d.lib",
         "sfml-window-d.lib",
         "sfml-system-d.lib",
         "sfml-audio-d.lib",
         "sfml-network-d.lib"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      libdirs { 
         "../libs/SFML/lib/Release",
         "../libs/SFML/extlibs"
      }

      links {
         "opengl32.lib",
         "openal32.lib",
         "freetype.lib",
         "winmm.lib",
         "gdi32.lib",
         "flac.lib",
         "vorbisenc.lib",
         "vorbisfile.lib",
         "vorbis.lib",
         "ogg.lib",
         "ws2_32.lib",
         "legacy_stdio_definitions.lib",
         "sfml-graphics.lib",
         "sfml-window.lib",
         "sfml-system.lib",
         "sfml-audio.lib",
         "sfml-network.lib"
      }
