#pragma once

#include "KeyCodes.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <glm/glm.hpp>

namespace Walnut {

	class Input
	{
	public:
		static void InitKeysCallBack();

		static void SetKeyCallback(KeyCode keycode, std::function<void()> func);

		static bool IsKeyDown(KeyCode keycode);

		static bool IsMouseButtonDown(MouseButton button);

		static glm::vec2 GetMousePosition();

		static void SetCursorMode(CursorMode mode);

		static std::unordered_map<int, std::function<void()>> KEY_CALLBACK_MAP;
	};

}
