-- WalnutExternal-Headless.lua

IncludeDir = {}
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["spdlog"] = "../vendor/spdlog/include"

group "Dependencies"
   include "vendor/yaml-cpp"
group ""

group "Core"
include "Walnut/Build-Walnut-Headless.lua"
group ""