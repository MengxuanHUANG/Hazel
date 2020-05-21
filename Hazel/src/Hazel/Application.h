#pragma once

#include "Core.h"

#include "Hazel/Layer.h"
#include "Hazel/LayerStack.h"
#include "Event/Event.h"
#include "Hazel/Event/ApplicationEvent.h"

#include "Window.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	Application* CreateApplication();
}
