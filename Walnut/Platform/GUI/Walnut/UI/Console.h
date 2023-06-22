#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <format>
#include <functional>

#include <imgui.h>

namespace Walnut::UI {

	class Console
	{
	public:
		using MessageSendCallback = std::function<void(std::string_view)>;
	public:
		Console(std::string_view title = "Walnut Console");
		~Console() = default;

		void ClearLog();

		template<typename... Args>
		void AddMessage(std::string_view fmt, Args&&... args)
		{
			std::string messageString = std::vformat(fmt, std::make_format_args(args...));
			m_MessageHistory.push_back(messageString);
		}

		template<typename... Args>
		void AddItalicMessage(std::string_view fmt, Args&&... args)
		{
			std::string messageString = std::vformat(fmt, std::make_format_args(args...));
			MessageInfo info = messageString;
			info.Italic = true;
			m_MessageHistory.push_back(info);
		}
		
		template<typename... Args>
		void AddTaggedMessage(std::string_view tag, std::string_view fmt, Args&&... args)
		{
			std::string messageString = std::vformat(fmt, std::make_format_args(args...));
			m_MessageHistory.push_back(MessageInfo(std::string(tag), messageString));
		}

		template<typename... Args>
		void AddMessageWithColor(uint32_t color, std::string_view fmt, Args&&... args)
		{
			std::string messageString = std::vformat(fmt, std::make_format_args(args...));
			m_MessageHistory.push_back(MessageInfo(messageString, color));
		}

		template<typename... Args>
		void AddItalicMessageWithColor(uint32_t color, std::string_view fmt, Args&&... args)
		{
			std::string messageString = std::vformat(fmt, std::make_format_args(args...));
			MessageInfo info(messageString, color);
			info.Italic = true;
			m_MessageHistory.push_back(info);
		}

		template<typename... Args>
		void AddTaggedMessageWithColor(uint32_t color, std::string_view tag, std::string_view fmt, Args&&... args)
		{
			std::string messageString = std::vformat(fmt, std::make_format_args(args...));
			m_MessageHistory.push_back(MessageInfo(std::string(tag), messageString, color));
		}

		void OnUIRender();

		void SetMessageSendCallback(const MessageSendCallback& callback);
	private:
		struct MessageInfo
		{
			std::string Tag;
			std::string Message;
			bool Italic = false;
			uint32_t Color = 0xffffffff;

			MessageInfo(const std::string& message, uint32_t color = 0xffffffff)
				: Message(message), Color(color) {}

			MessageInfo(const std::string& tag, const std::string& message, uint32_t color = 0xffffffff)
				: Tag(tag), Message(message), Color(color) {}
		};

		std::string m_Title;
		std::string m_MessageBuffer;
		std::vector<MessageInfo> m_MessageHistory;
		ImGuiTextFilter m_Filter;
		bool m_AutoScroll = true;
		bool m_ScrollToBottom = false;

		MessageSendCallback m_MessageSendCallback;

	};

}