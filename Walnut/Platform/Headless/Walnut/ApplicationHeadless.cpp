#include "ApplicationHeadless.h"

#include "Walnut/Core/Log.h"

#include <iostream>
#include <chrono>

extern bool g_ApplicationRunning;

static Walnut::Application* s_Instance = nullptr;

namespace Walnut {

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		s_Instance = this;

		Init();
	}

	Application::~Application()
	{
		Shutdown();

		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	void Application::Init()
	{
		// Intialize logging
		Log::Init();
	}

	void Application::Shutdown()
	{
		for (auto& layer : m_LayerStack)
			layer->OnDetach();

		m_LayerStack.clear();

		g_ApplicationRunning = false;

		Log::Shutdown();
	}

	void Application::Run()
	{
		m_Running = true;

		// Main loop
		while (m_Running)
		{
			for (auto& layer : m_LayerStack)
				layer->OnUpdate(m_TimeStep);

			if (m_Specification.SleepDuration > 0.0f)
				std::this_thread::sleep_for(std::chrono::milliseconds(m_Specification.SleepDuration));

			float time = GetTime();
			m_FrameTime = time - m_LastFrameTime;
			m_TimeStep = glm::min<float>(m_FrameTime, 0.0333f);
			m_LastFrameTime = time;
		}

	}

	void Application::Close()
	{
		m_Running = false;
	}

	float Application::GetTime()
	{
		return m_AppTimer.Elapsed();
	}

}
