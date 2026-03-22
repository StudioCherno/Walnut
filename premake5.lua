-- premake5.lua
workspace "WalnutApp"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "WalnutApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "WalnutExternal.lua"
include "WalnutApp"

filter "system:windows"
    systemversion "latest"
    defines { "WL_PLATFORM_WINDOWS" }
    links { "%{Library.Vulkan}" }

filter "system:linux"
    links { "vulkan" }
