#pragma once

extern Walnut::Application* Walnut::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace Walnut {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Walnut::Application* app = Walnut::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#if defined(WL_DIST) && defined(WL_PLATFORM_WINDOWS)

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Walnut::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Walnut::Main(argc, argv);
}

#endif // WL_DIST && WL_PLATFORM_WINDOWS
