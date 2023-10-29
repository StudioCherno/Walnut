-- premake5.lua
workspace "Lunanic"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Lunanic"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "WalnutExternal.lua"
include "Lunanic"