-- WalnutExternal.lua

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/include"
IncludeDir["glm"] = "../vendor/glm"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/lib"

Library = {}

if os.ishost("linux") and os.istarget("linux") then
   Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/libvulkan.so.1"
else
   Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
end 

function linux_check_if_package_is_installed(cmd, package)
   local result, errorCode = os.outputof(cmd .. " " .. package)
   if errorCode ~= 0 then
      premake.error("Install " .. package .. " using package manager")
   end
   premake.info(package .. " is installed")
end

group "Dependencies"
   include "vendor/imgui"
   if os.ishost("linux") and os.istarget("linux") then

      if os.isfile("/usr/bin/dpkg-query") then 
         local cmd = "/usr/bin/dpkg-query -Wf"
         linux_check_if_package_is_installed(cmd, "libglfw3-dev")
         linux_check_if_package_is_installed(cmd, "libvulkan-dev")
         linux_check_if_package_is_installed(cmd, "mesa-vulkan-drivers")
         linux_check_if_package_is_installed(cmd, "vulkan-tools")
      elseif os.isfile("/usr/bin/rpm") then 
         local cmd = "/usr/bin/rpm -qi"
         linux_check_if_package_is_installed(cmd, "glfw-devel")
      else
         premake.warn("Info: Please be sure that GLFW and Vulkan SDK are installed")
      end 

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
