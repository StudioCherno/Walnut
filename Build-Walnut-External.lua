-- WalnutExternal.lua

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["spdlog"] = "../vendor/spdlog/include"

LibraryDir = {}
LibraryDir["VulkanSDK32"] = "%{VULKAN_SDK}/Lib32"
LibraryDir["VulkanSDK64"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan32"] = "%{LibraryDir.VulkanSDK32}/vulkan-1.lib"
Library["Vulkan64"] = "%{LibraryDir.VulkanSDK64}/vulkan-1.lib"

group "Dependencies"
   include "vendor/imgui"
   include "vendor/glfw"
   include "vendor/yaml-cpp"
group ""

group "Core"
    include "Walnut/Build-Walnut.lua"

    -- Optional modules
    if os.isfile("Walnut-Modules/Walnut-Networking/Build-Walnut-Networking.lua") then
        include "Walnut-Modules/Walnut-Networking/Build-Walnut-Networking.lua"
    end
group ""