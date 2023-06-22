#include "Console.h"

#include "Walnut/ApplicationGUI.h"

#include "misc/cpp/imgui_stdlib.h"

namespace Walnut::UI {

	Console::Console(std::string_view title)
		: m_Title(title)
	{
	}

	void Console::ClearLog()
	{
		m_MessageHistory.clear();
	}

	void Console::OnUIRender()
	{
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin(m_Title.c_str()))
		{
			ImGui::End();
			return;
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &m_AutoScroll);
			ImGui::EndPopup();
		}

		// Options, Filter
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");

		ImGui::SameLine();
		ImGui::Text("Search");
		ImGui::SameLine();
		m_Filter.Draw("##search", 180);
		ImGui::Separator();

		// Reserve enough left-over height for 1 separator + 1 input text
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Clear")) ClearLog();
			ImGui::EndPopup();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		const float TextPadding = 8.0f;

		ImGui::SetCursorPosY(TextPadding);
		for (int i = 0; i < m_MessageHistory.size(); i++)
		{
			if (!m_Filter.PassFilter(m_MessageHistory[i].Message.c_str()))
				continue;

			ImGui::SetCursorPosX(TextPadding);

			// Normally you would store more information in your item than just a string.
			// (e.g. make Items[] an array of structure, store color/type etc.)
			ImGui::PushStyleColor(ImGuiCol_Text, ImColor(m_MessageHistory[i].Color).Value);
			ImVec4 finalColor = ImColor(m_MessageHistory[i].Color).Value;
			if (!m_MessageHistory[i].Tag.empty())
			{
				ImGui::PushFont(Application::GetFont("Bold"));
				ImGui::TextUnformatted(m_MessageHistory[i].Tag.c_str());
				ImGui::PopFont();
				ImGui::SameLine(0.0f, TextPadding);
			}

			if (m_MessageHistory[i].Italic)
				ImGui::PushFont(Application::GetFont("Italic"));

			ImGui::TextUnformatted(m_MessageHistory[i].Message.c_str());

			if (m_MessageHistory[i].Italic)
				ImGui::PopFont();

			ImGui::PopStyleColor();
		}

		if (m_ScrollToBottom || (m_AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
			ImGui::SetScrollHereY(1.0f);

		m_ScrollToBottom = false;

		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::Separator();

		// Command-line
		static bool reclaim_focus = false;
		ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;

		const float sendButtonWidth = 100.0f;
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - sendButtonWidth - TextPadding);
		if (ImGui::InputText("##input", &m_MessageBuffer, input_text_flags))
		{
			if (m_MessageSendCallback)
				m_MessageSendCallback(m_MessageBuffer);

			// Clear InputText
			m_MessageBuffer = "";
			reclaim_focus = true;
		}

		// Auto-focus on window apparition
		ImGui::SetItemDefaultFocus();
		if (reclaim_focus)
		{
			ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
			reclaim_focus = false;
		}

		ImGui::SameLine();
		if (ImGui::Button("Send", ImVec2(sendButtonWidth, 0.0f)))
		{
			if (m_MessageSendCallback)
				m_MessageSendCallback(m_MessageBuffer);

			// Clear InputText
			m_MessageBuffer = "";
			reclaim_focus = true;
		}

		ImGui::End();
	}

	void Console::SetMessageSendCallback(const MessageSendCallback& callback)
	{
		m_MessageSendCallback = callback;
	}

}