project "Walnut-Headless"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files
   {
       "Source/**.h",
       "Source/**.cpp",

       "Platform/Headless/**.h",
       "Platform/Headless/**.cpp",
   }

   includedirs
   {
      "Source",
      "Platform/Headless",

      "%{IncludeDir.glm}",
      "%{IncludeDir.spdlog}",
   }

   links
   {
   }

   defines { "WL_HEADLESS" }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

   filter "system:linux"
      systemversion "latest"
      defines { "WL_PLATFORM_LINUX" }

      filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"