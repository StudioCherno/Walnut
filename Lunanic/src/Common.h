#include <iostream>
#include <future>
#include <chrono>
#include <cstdio>
#include <string>
#include <filesystem>
#include <regex>
#include <map>
#include <fstream>
#include <thread>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <urlmon.h>
#pragma comment (lib, "urlmon.lib")

#include "spdlog/spdlog.h"
#include "spdlog/fmt/fmt.h"
#include "spdlog/fmt/ostr.h"
#include "nlohmann/json.hpp"

#include "imgui.h"
#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"