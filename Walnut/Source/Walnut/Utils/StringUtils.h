#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace Walnut::Utils {

	std::vector<std::string> SplitString(const std::string_view string, const std::string_view& delimiters);
	std::vector<std::string> SplitString(const std::string_view string, const char delimiter);

}
