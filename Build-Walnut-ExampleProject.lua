-- premake5.lua
workspace "WalnutApp"
   configurations { "Debug", "Release", "Dist" }
   platforms { "x32", "x64" }
   startproject "WalnutApp"

   filter "platforms:x32"
      architecture "x32"
      defines { "ImTextureID=ImU64" }

   filter "platforms:x64"
      architecture "x64"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Build-Walnut-External.lua"
include "WalnutApp/Build-Walnut-App.lua"