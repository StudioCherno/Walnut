project "Lunanic"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   PrecompiledHeaderInclude = "Common.h"
   PrecompiledHeaderSource = "src/Common.cpp"

   includedirs
   {
      "src",

      "../vendor/imgui",
      "../vendor/imgui/misc/cpp",
      "../vendor/glfw/include",
      "../vendor/HTTPRequest/include",
      "../vendor/json/single_include",
      "../vendor/spdlog/include",

      "../Walnut/src",

      "%{IncludeDir.VulkanSDK}",
      "%{IncludeDir.glm}",
   }

    links
    {
        "Walnut",
	"ImGui"
    }

   targetdir ("../bin/%{prj.name}")
   objdir ("../bin/obj/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }

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
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"