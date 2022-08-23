-- WalnutExternal.lua

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["glm"] = "../vendor/glm"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"


function linux_dpkg_check_if_package_is_installed(package)
   if os.isfile("/usr/bin/dpkg-query") then -- It's Debian or a derivative of it:
      local result, errorCode = os.outputof("/usr/bin/dpkg-query -Wf'${Status}' " .. package)
      if errorCode ~= 0 or result ~= "install ok installed" then
         premake.error("Install " .. package .. " using: sudo apt-get install " .. package)
      end
      premake.info(package .. " is installed")
   else -- Not a Debian-based Linux distro, for now just give a hint:
      premake.warn("Info: Please be sure that a package like " .. package .. " is installed")
    end
end


group "Dependencies"
   include "vendor/imgui"
   -- When build host and build target are Linux, see if we can check for needed libs:
   if os.ishost("linux") and os.istarget("linux") then
      linux_dpkg_check_if_package_is_installed("libglfw3-dev")
      linux_dpkg_check_if_package_is_installed("libvulkan-dev")
      linux_dpkg_check_if_package_is_installed("mesa-vulkan-drivers")
      linux_dpkg_check_if_package_is_installed("vulkan-tools")
      vulkaninfo_dir = os.pathsearch("vulkaninfo", os.getenv("PATH"))
      if not vulkaninfo_dir then
         premake.warn("vulkaninfo not found. Be sure that Vulkan works.")
      else
         vulkaninfo = vulkaninfo_dir .. "/vulkaninfo"
         local result, errorCode = os.outputof(vulkaninfo)
         if errorCode ~= 0 or string.find(result, "ERROR") then
               premake.error(vulkaninfo .. " reported an ERROR, please check")
         end
         premake.info(vulkaninfo .. " did not show an error, good.")
      end
   else
      -- For other operating systems, build GLFW in the cloned git submodule:
      include "vendor/GLFW"
   end
group ""

group "Core"
include "Walnut"
group ""
