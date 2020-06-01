#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/ApplicationEvent.h"


namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleaseEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseSrcolledEvent(MouseScrolledEvent& e);
		
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	private:
		float m_Time = 0.0f;
	};
}