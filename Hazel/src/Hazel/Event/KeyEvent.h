#pragma once

#include "Event.h"

namespace Hazel {
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeycode() const { return m_Keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode)
			:m_Keycode(keycode) {}
		int m_Keycode;
	};

	class HAZEL_API KeyPressed : public KeyEvent
	{
	public:
		KeyPressed(int keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Keycode << ", " << m_RepeatCount;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleased : public KeyEvent
	{
		KeyReleased(int keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
