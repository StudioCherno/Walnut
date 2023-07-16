#include "UI.h"

namespace Walnut::UI {

	void ShiftCursorX(float distance)
	{
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + distance);
	}

	void ShiftCursorY(float distance)
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + distance);
	}

	void ShiftCursor(float x, float y)
	{
		const ImVec2 cursor = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(cursor.x + x, cursor.y + y));
	}

	ImRect GetItemRect()
	{
		return ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
	}

	ImRect RectExpanded(const ImRect& rect, float x, float y)
	{
		ImRect result = rect;
		result.Min.x -= x;
		result.Min.y -= y;
		result.Max.x += x;
		result.Max.y += y;
		return result;
	}

	ImRect RectOffset(const ImRect& rect, float x, float y)
	{
		ImRect result = rect;
		result.Min.x += x;
		result.Min.y += y;
		result.Max.x += x;
		result.Max.y += y;
		return result;
	}

	ImRect RectOffset(const ImRect& rect, ImVec2 xy)
	{
		return RectOffset(rect, xy.x, xy.y);
	}

	void DrawButtonImage(const std::shared_ptr<Walnut::Image>& imageNormal, const std::shared_ptr<Walnut::Image>& imageHovered, const std::shared_ptr<Walnut::Image>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImVec2 rectMin, ImVec2 rectMax)
	{
		auto* drawList = ImGui::GetForegroundDrawList();
		if (ImGui::IsItemActive())
			drawList->AddImage(imagePressed->GetDescriptorSet(), rectMin, rectMax, ImVec2(0, 0), ImVec2(1, 1), tintPressed);
		else if (ImGui::IsItemHovered())
			drawList->AddImage(imagePressed->GetDescriptorSet(), rectMin, rectMax, ImVec2(0, 0), ImVec2(1, 1), tintHovered);
		else
			drawList->AddImage(imagePressed->GetDescriptorSet(), rectMin, rectMax, ImVec2(0, 0), ImVec2(1, 1), tintNormal);
	};

	void DrawButtonImage(const std::shared_ptr<Walnut::Image>& imageNormal, const std::shared_ptr<Walnut::Image>& imageHovered, const std::shared_ptr<Walnut::Image>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImRect rectangle)
	{
		DrawButtonImage(imageNormal, imageHovered, imagePressed, tintNormal, tintHovered, tintPressed, rectangle.Min, rectangle.Max);
	};

	void DrawButtonImage(const std::shared_ptr<Walnut::Image>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImVec2 rectMin, ImVec2 rectMax)
	{
		DrawButtonImage(image, image, image, tintNormal, tintHovered, tintPressed, rectMin, rectMax);
	};

	void DrawButtonImage(const std::shared_ptr<Walnut::Image>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImRect rectangle)
	{
		DrawButtonImage(image, image, image, tintNormal, tintHovered, tintPressed, rectangle.Min, rectangle.Max);
	};


	void DrawButtonImage(const std::shared_ptr<Walnut::Image>& imageNormal, const std::shared_ptr<Walnut::Image>& imageHovered, const std::shared_ptr<Walnut::Image>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed)
	{
		DrawButtonImage(imageNormal, imageHovered, imagePressed, tintNormal, tintHovered, tintPressed, ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
	};

	void DrawButtonImage(const std::shared_ptr<Walnut::Image>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed)
	{
		DrawButtonImage(image, image, image, tintNormal, tintHovered, tintPressed, ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
	};

	// Exposed to be used for window with disabled decorations
// This border is going to be drawn even if window border size is set to 0.0f
	void RenderWindowOuterBorders(ImGuiWindow* window)
	{
		struct ImGuiResizeBorderDef
		{
			ImVec2 InnerDir;
			ImVec2 SegmentN1, SegmentN2;
			float  OuterAngle;
		};

		static const ImGuiResizeBorderDef resize_border_def[4] =
		{
			{ ImVec2(+1, 0), ImVec2(0, 1), ImVec2(0, 0), IM_PI * 1.00f }, // Left
			{ ImVec2(-1, 0), ImVec2(1, 0), ImVec2(1, 1), IM_PI * 0.00f }, // Right
			{ ImVec2(0, +1), ImVec2(0, 0), ImVec2(1, 0), IM_PI * 1.50f }, // Up
			{ ImVec2(0, -1), ImVec2(1, 1), ImVec2(0, 1), IM_PI * 0.50f }  // Down
		};

		auto GetResizeBorderRect = [](ImGuiWindow* window, int border_n, float perp_padding, float thickness)
		{
			ImRect rect = window->Rect();
			if (thickness == 0.0f)
			{
				rect.Max.x -= 1;
				rect.Max.y -= 1;
			}
			if (border_n == ImGuiDir_Left) { return ImRect(rect.Min.x - thickness, rect.Min.y + perp_padding, rect.Min.x + thickness, rect.Max.y - perp_padding); }
			if (border_n == ImGuiDir_Right) { return ImRect(rect.Max.x - thickness, rect.Min.y + perp_padding, rect.Max.x + thickness, rect.Max.y - perp_padding); }
			if (border_n == ImGuiDir_Up) { return ImRect(rect.Min.x + perp_padding, rect.Min.y - thickness, rect.Max.x - perp_padding, rect.Min.y + thickness); }
			if (border_n == ImGuiDir_Down) { return ImRect(rect.Min.x + perp_padding, rect.Max.y - thickness, rect.Max.x - perp_padding, rect.Max.y + thickness); }
			IM_ASSERT(0);
			return ImRect();
		};


		ImGuiContext& g = *GImGui;
		float rounding = window->WindowRounding;
		float border_size = 1.0f; // window->WindowBorderSize;
		if (border_size > 0.0f && !(window->Flags & ImGuiWindowFlags_NoBackground))
			window->DrawList->AddRect(window->Pos, { window->Pos.x + window->Size.x,  window->Pos.y + window->Size.y }, ImGui::GetColorU32(ImGuiCol_Border), rounding, 0, border_size);

		int border_held = window->ResizeBorderHeld;
		if (border_held != -1)
		{
			const ImGuiResizeBorderDef& def = resize_border_def[border_held];
			ImRect border_r = GetResizeBorderRect(window, border_held, rounding, 0.0f);
			ImVec2 p1 = ImLerp(border_r.Min, border_r.Max, def.SegmentN1);
			const float offsetX = def.InnerDir.x * rounding;
			const float offsetY = def.InnerDir.y * rounding;
			p1.x += 0.5f + offsetX;
			p1.y += 0.5f + offsetY;

			ImVec2 p2 = ImLerp(border_r.Min, border_r.Max, def.SegmentN2);
			p2.x += 0.5f + offsetX;
			p2.y += 0.5f + offsetY;

			window->DrawList->PathArcTo(p1, rounding, def.OuterAngle - IM_PI * 0.25f, def.OuterAngle);
			window->DrawList->PathArcTo(p2, rounding, def.OuterAngle, def.OuterAngle + IM_PI * 0.25f);
			window->DrawList->PathStroke(ImGui::GetColorU32(ImGuiCol_SeparatorActive), 0, ImMax(2.0f, border_size)); // Thicker than usual
		}
		if (g.Style.FrameBorderSize > 0 && !(window->Flags & ImGuiWindowFlags_NoTitleBar) && !window->DockIsActive)
		{
			float y = window->Pos.y + window->TitleBarHeight() - 1;
			window->DrawList->AddLine(ImVec2(window->Pos.x + border_size, y), ImVec2(window->Pos.x + window->Size.x - border_size, y), ImGui::GetColorU32(ImGuiCol_Border), g.Style.FrameBorderSize);
		}
	}

	// Exposed resize behavior for native OS windows
	bool UpdateWindowManualResize(ImGuiWindow* window, ImVec2& newSize, ImVec2& newPosition)
	{

		auto CalcWindowSizeAfterConstraint = [](ImGuiWindow* window, const ImVec2& size_desired)
		{
			ImGuiContext& g = *GImGui;
			ImVec2 new_size = size_desired;
			if (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint)
			{
				// Using -1,-1 on either X/Y axis to preserve the current size.
				ImRect cr = g.NextWindowData.SizeConstraintRect;
				new_size.x = (cr.Min.x >= 0 && cr.Max.x >= 0) ? ImClamp(new_size.x, cr.Min.x, cr.Max.x) : window->SizeFull.x;
				new_size.y = (cr.Min.y >= 0 && cr.Max.y >= 0) ? ImClamp(new_size.y, cr.Min.y, cr.Max.y) : window->SizeFull.y;
				if (g.NextWindowData.SizeCallback)
				{
					ImGuiSizeCallbackData data;
					data.UserData = g.NextWindowData.SizeCallbackUserData;
					data.Pos = window->Pos;
					data.CurrentSize = window->SizeFull;
					data.DesiredSize = new_size;
					g.NextWindowData.SizeCallback(&data);
					new_size = data.DesiredSize;
				}
				new_size.x = IM_FLOOR(new_size.x);
				new_size.y = IM_FLOOR(new_size.y);
			}

			// Minimum size
			if (!(window->Flags & (ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_AlwaysAutoResize)))
			{
				ImGuiWindow* window_for_height = (window->DockNodeAsHost && window->DockNodeAsHost->VisibleWindow) ? window->DockNodeAsHost->VisibleWindow : window;
				const float decoration_up_height = window_for_height->TitleBarHeight() + window_for_height->MenuBarHeight();
				new_size = ImMax(new_size, g.Style.WindowMinSize);
				new_size.y = ImMax(new_size.y, decoration_up_height + ImMax(0.0f, g.Style.WindowRounding - 1.0f)); // Reduce artifacts with very small windows
			}
			return new_size;
		};

		auto CalcWindowAutoFitSize = [CalcWindowSizeAfterConstraint](ImGuiWindow* window, const ImVec2& size_contents)
		{
			ImGuiContext& g = *GImGui;
			ImGuiStyle& style = g.Style;
			const float decoration_up_height = window->TitleBarHeight() + window->MenuBarHeight();
			ImVec2 size_pad{ window->WindowPadding.x * 2.0f, window->WindowPadding.y * 2.0f };
			ImVec2 size_desired = { size_contents.x + size_pad.x + 0.0f, size_contents.y + size_pad.y + decoration_up_height };
			if (window->Flags & ImGuiWindowFlags_Tooltip)
			{
				// Tooltip always resize
				return size_desired;
			}
			else
			{
				// Maximum window size is determined by the viewport size or monitor size
				const bool is_popup = (window->Flags & ImGuiWindowFlags_Popup) != 0;
				const bool is_menu = (window->Flags & ImGuiWindowFlags_ChildMenu) != 0;
				ImVec2 size_min = style.WindowMinSize;
				if (is_popup || is_menu) // Popups and menus bypass style.WindowMinSize by default, but we give then a non-zero minimum size to facilitate understanding problematic cases (e.g. empty popups)
					size_min = ImMin(size_min, ImVec2(4.0f, 4.0f));

				// FIXME-VIEWPORT-WORKAREA: May want to use GetWorkSize() instead of Size depending on the type of windows?
				ImVec2 avail_size = window->Viewport->Size;
				if (window->ViewportOwned)
					avail_size = ImVec2(FLT_MAX, FLT_MAX);
				const int monitor_idx = window->ViewportAllowPlatformMonitorExtend;
				if (monitor_idx >= 0 && monitor_idx < g.PlatformIO.Monitors.Size)
					avail_size = g.PlatformIO.Monitors[monitor_idx].WorkSize;
				ImVec2 size_auto_fit = ImClamp(size_desired, size_min, ImMax(size_min, { avail_size.x - style.DisplaySafeAreaPadding.x * 2.0f,
																						avail_size.y - style.DisplaySafeAreaPadding.y * 2.0f }));

				// When the window cannot fit all contents (either because of constraints, either because screen is too small),
				// we are growing the size on the other axis to compensate for expected scrollbar. FIXME: Might turn bigger than ViewportSize-WindowPadding.
				ImVec2 size_auto_fit_after_constraint = CalcWindowSizeAfterConstraint(window, size_auto_fit);
				bool will_have_scrollbar_x = (size_auto_fit_after_constraint.x - size_pad.x - 0.0f < size_contents.x && !(window->Flags & ImGuiWindowFlags_NoScrollbar) && (window->Flags & ImGuiWindowFlags_HorizontalScrollbar)) || (window->Flags & ImGuiWindowFlags_AlwaysHorizontalScrollbar);
				bool will_have_scrollbar_y = (size_auto_fit_after_constraint.y - size_pad.y - decoration_up_height < size_contents.y && !(window->Flags & ImGuiWindowFlags_NoScrollbar)) || (window->Flags & ImGuiWindowFlags_AlwaysVerticalScrollbar);
				if (will_have_scrollbar_x)
					size_auto_fit.y += style.ScrollbarSize;
				if (will_have_scrollbar_y)
					size_auto_fit.x += style.ScrollbarSize;
				return size_auto_fit;
			}
		};

		ImGuiContext& g = *GImGui;

		// Decide if we are going to handle borders and resize grips
		const bool handle_borders_and_resize_grips = (window->DockNodeAsHost || !window->DockIsActive);

		if (!handle_borders_and_resize_grips || window->Collapsed)
			return false;

		const ImVec2 size_auto_fit = CalcWindowAutoFitSize(window, window->ContentSizeIdeal);

		// Handle manual resize: Resize Grips, Borders, Gamepad
		int border_held = -1;
		ImU32 resize_grip_col[4] = {};
		const int resize_grip_count = g.IO.ConfigWindowsResizeFromEdges ? 2 : 1; // Allow resize from lower-left if we have the mouse cursor feedback for it.
		const float resize_grip_draw_size = IM_FLOOR(ImMax(g.FontSize * 1.10f, window->WindowRounding + 1.0f + g.FontSize * 0.2f));
		window->ResizeBorderHeld = (signed char)border_held;

		//const ImRect& visibility_rect;

		struct ImGuiResizeBorderDef
		{
			ImVec2 InnerDir;
			ImVec2 SegmentN1, SegmentN2;
			float  OuterAngle;
		};
		static const ImGuiResizeBorderDef resize_border_def[4] =
		{
			{ ImVec2(+1, 0), ImVec2(0, 1), ImVec2(0, 0), IM_PI * 1.00f }, // Left
			{ ImVec2(-1, 0), ImVec2(1, 0), ImVec2(1, 1), IM_PI * 0.00f }, // Right
			{ ImVec2(0, +1), ImVec2(0, 0), ImVec2(1, 0), IM_PI * 1.50f }, // Up
			{ ImVec2(0, -1), ImVec2(1, 1), ImVec2(0, 1), IM_PI * 0.50f }  // Down
		};

		// Data for resizing from corner
		struct ImGuiResizeGripDef
		{
			ImVec2  CornerPosN;
			ImVec2  InnerDir;
			int     AngleMin12, AngleMax12;
		};
		static const ImGuiResizeGripDef resize_grip_def[4] =
		{
			{ ImVec2(1, 1), ImVec2(-1, -1), 0, 3 },  // Lower-right
			{ ImVec2(0, 1), ImVec2(+1, -1), 3, 6 },  // Lower-left
			{ ImVec2(0, 0), ImVec2(+1, +1), 6, 9 },  // Upper-left (Unused)
			{ ImVec2(1, 0), ImVec2(-1, +1), 9, 12 }  // Upper-right (Unused)
		};

		auto CalcResizePosSizeFromAnyCorner = [CalcWindowSizeAfterConstraint](ImGuiWindow* window, const ImVec2& corner_target, const ImVec2& corner_norm, ImVec2* out_pos, ImVec2* out_size)
		{
			ImVec2 pos_min = ImLerp(corner_target, window->Pos, corner_norm);                // Expected window upper-left
			ImVec2 pos_max = ImLerp({ window->Pos.x + window->Size.x, window->Pos.y + window->Size.y }, corner_target, corner_norm); // Expected window lower-right
			ImVec2 size_expected = { pos_max.x - pos_min.x,  pos_max.y - pos_min.y };
			ImVec2 size_constrained = CalcWindowSizeAfterConstraint(window, size_expected);
			*out_pos = pos_min;
			if (corner_norm.x == 0.0f)
				out_pos->x -= (size_constrained.x - size_expected.x);
			if (corner_norm.y == 0.0f)
				out_pos->y -= (size_constrained.y - size_expected.y);
			*out_size = size_constrained;
		};

		auto GetResizeBorderRect = [](ImGuiWindow* window, int border_n, float perp_padding, float thickness)
		{
			ImRect rect = window->Rect();
			if (thickness == 0.0f)
			{
				rect.Max.x -= 1;
				rect.Max.y -= 1;
			}
			if (border_n == ImGuiDir_Left) { return ImRect(rect.Min.x - thickness, rect.Min.y + perp_padding, rect.Min.x + thickness, rect.Max.y - perp_padding); }
			if (border_n == ImGuiDir_Right) { return ImRect(rect.Max.x - thickness, rect.Min.y + perp_padding, rect.Max.x + thickness, rect.Max.y - perp_padding); }
			if (border_n == ImGuiDir_Up) { return ImRect(rect.Min.x + perp_padding, rect.Min.y - thickness, rect.Max.x - perp_padding, rect.Min.y + thickness); }
			if (border_n == ImGuiDir_Down) { return ImRect(rect.Min.x + perp_padding, rect.Max.y - thickness, rect.Max.x - perp_padding, rect.Max.y + thickness); }
			IM_ASSERT(0);
			return ImRect();
		};

		static const float WINDOWS_HOVER_PADDING = 4.0f;                        // Extend outside window for hovering/resizing (maxxed with TouchPadding) and inside windows for borders. Affect FindHoveredWindow().
		static const float WINDOWS_RESIZE_FROM_EDGES_FEEDBACK_TIMER = 0.04f;    // Reduce visual noise by only highlighting the border after a certain time.

		auto& style = g.Style;
		ImGuiWindowFlags flags = window->Flags;

		if (/*(flags & ImGuiWindowFlags_NoResize) || */(flags & ImGuiWindowFlags_AlwaysAutoResize) || window->AutoFitFramesX > 0 || window->AutoFitFramesY > 0)
			return false;
		if (window->WasActive == false) // Early out to avoid running this code for e.g. an hidden implicit/fallback Debug window.
			return false;

		bool ret_auto_fit = false;
		const int resize_border_count = g.IO.ConfigWindowsResizeFromEdges ? 4 : 0;
		const float grip_draw_size = IM_FLOOR(ImMax(g.FontSize * 1.35f, window->WindowRounding + 1.0f + g.FontSize * 0.2f));
		const float grip_hover_inner_size = IM_FLOOR(grip_draw_size * 0.75f);
		const float grip_hover_outer_size = g.IO.ConfigWindowsResizeFromEdges ? WINDOWS_HOVER_PADDING : 0.0f;

		ImVec2 pos_target(FLT_MAX, FLT_MAX);
		ImVec2 size_target(FLT_MAX, FLT_MAX);

		// Calculate the range of allowed position for that window (to be movable and visible past safe area padding)
		// When clamping to stay visible, we will enforce that window->Pos stays inside of visibility_rect.
		ImRect viewport_rect(window->Viewport->GetMainRect());
		ImRect viewport_work_rect(window->Viewport->GetWorkRect());
		ImVec2 visibility_padding = ImMax(style.DisplayWindowPadding, style.DisplaySafeAreaPadding);
		ImRect visibility_rect({ viewport_work_rect.Min.x + visibility_padding.x, viewport_work_rect.Min.y + visibility_padding.y },
			{ viewport_work_rect.Max.x - visibility_padding.x, viewport_work_rect.Max.y - visibility_padding.y });

		// Clip mouse interaction rectangles within the viewport rectangle (in practice the narrowing is going to happen most of the time).
		// - Not narrowing would mostly benefit the situation where OS windows _without_ decoration have a threshold for hovering when outside their limits.
		//   This is however not the case with current backends under Win32, but a custom borderless window implementation would benefit from it.
		// - When decoration are enabled we typically benefit from that distance, but then our resize elements would be conflicting with OS resize elements, so we also narrow.
		// - Note that we are unable to tell if the platform setup allows hovering with a distance threshold (on Win32, decorated window have such threshold).
		// We only clip interaction so we overwrite window->ClipRect, cannot call PushClipRect() yet as DrawList is not yet setup.
		const bool clip_with_viewport_rect = !(g.IO.BackendFlags & ImGuiBackendFlags_HasMouseHoveredViewport) || (g.IO.MouseHoveredViewport != window->ViewportId) || !(window->Viewport->Flags & ImGuiViewportFlags_NoDecoration);
		if (clip_with_viewport_rect)
			window->ClipRect = window->Viewport->GetMainRect();

		// Resize grips and borders are on layer 1
		window->DC.NavLayerCurrent = ImGuiNavLayer_Menu;

		// Manual resize grips
		ImGui::PushID("#RESIZE");
		for (int resize_grip_n = 0; resize_grip_n < resize_grip_count; resize_grip_n++)
		{
			const ImGuiResizeGripDef& def = resize_grip_def[resize_grip_n];

			const ImVec2 corner = ImLerp(window->Pos, { window->Pos.x + window->Size.x, window->Pos.y + window->Size.y }, def.CornerPosN);

			// Using the FlattenChilds button flag we make the resize button accessible even if we are hovering over a child window
			bool hovered, held;
			const ImVec2 min = { corner.x - def.InnerDir.x * grip_hover_outer_size, corner.y - def.InnerDir.y * grip_hover_outer_size };
			const ImVec2 max = { corner.x + def.InnerDir.x * grip_hover_outer_size, corner.y + def.InnerDir.y * grip_hover_outer_size };
			ImRect resize_rect(min, max);

			if (resize_rect.Min.x > resize_rect.Max.x) ImSwap(resize_rect.Min.x, resize_rect.Max.x);
			if (resize_rect.Min.y > resize_rect.Max.y) ImSwap(resize_rect.Min.y, resize_rect.Max.y);
			ImGuiID resize_grip_id = window->GetID(resize_grip_n); // == GetWindowResizeCornerID()
			ImGui::ButtonBehavior(resize_rect, resize_grip_id, &hovered, &held, ImGuiButtonFlags_FlattenChildren | ImGuiButtonFlags_NoNavFocus);
			//GetForegroundDrawList(window)->AddRect(resize_rect.Min, resize_rect.Max, IM_COL32(255, 255, 0, 255));
			if (hovered || held)
				g.MouseCursor = (resize_grip_n & 1) ? ImGuiMouseCursor_ResizeNESW : ImGuiMouseCursor_ResizeNWSE;

			if (held && g.IO.MouseDoubleClicked[0] && resize_grip_n == 0)
			{
				// Manual auto-fit when double-clicking
				size_target = CalcWindowSizeAfterConstraint(window, size_auto_fit);
				ret_auto_fit = true;
				ImGui::ClearActiveID();
			}
			else if (held)
			{
				// Resize from any of the four corners
				// We don't use an incremental MouseDelta but rather compute an absolute target size based on mouse position
				ImVec2 clamp_min = ImVec2(def.CornerPosN.x == 1.0f ? visibility_rect.Min.x : -FLT_MAX, def.CornerPosN.y == 1.0f ? visibility_rect.Min.y : -FLT_MAX);
				ImVec2 clamp_max = ImVec2(def.CornerPosN.x == 0.0f ? visibility_rect.Max.x : +FLT_MAX, def.CornerPosN.y == 0.0f ? visibility_rect.Max.y : +FLT_MAX);

				const float x = g.IO.MousePos.x - g.ActiveIdClickOffset.x + ImLerp(def.InnerDir.x * grip_hover_outer_size, def.InnerDir.x * -grip_hover_inner_size, def.CornerPosN.x);
				const float y = g.IO.MousePos.y - g.ActiveIdClickOffset.y + ImLerp(def.InnerDir.y * grip_hover_outer_size, def.InnerDir.y * -grip_hover_inner_size, def.CornerPosN.y);

				ImVec2 corner_target(x, y); // Corner of the window corresponding to our corner grip
				corner_target = ImClamp(corner_target, clamp_min, clamp_max);
				CalcResizePosSizeFromAnyCorner(window, corner_target, def.CornerPosN, &pos_target, &size_target);
			}

			// Only lower-left grip is visible before hovering/activating
			if (resize_grip_n == 0 || held || hovered)
				resize_grip_col[resize_grip_n] = ImGui::GetColorU32(held ? ImGuiCol_ResizeGripActive : hovered ? ImGuiCol_ResizeGripHovered : ImGuiCol_ResizeGrip);
		}
		for (int border_n = 0; border_n < resize_border_count; border_n++)
		{
			const ImGuiResizeBorderDef& def = resize_border_def[border_n];
			const ImGuiAxis axis = (border_n == ImGuiDir_Left || border_n == ImGuiDir_Right) ? ImGuiAxis_X : ImGuiAxis_Y;

			bool hovered, held;
			ImRect border_rect = GetResizeBorderRect(window, border_n, grip_hover_inner_size, WINDOWS_HOVER_PADDING);
			ImGuiID border_id = window->GetID(border_n + 4); // == GetWindowResizeBorderID()
			ImGui::ButtonBehavior(border_rect, border_id, &hovered, &held, ImGuiButtonFlags_FlattenChildren);
			//GetForegroundDrawLists(window)->AddRect(border_rect.Min, border_rect.Max, IM_COL32(255, 255, 0, 255));
			if ((hovered && g.HoveredIdTimer > WINDOWS_RESIZE_FROM_EDGES_FEEDBACK_TIMER) || held)
			{
				g.MouseCursor = (axis == ImGuiAxis_X) ? ImGuiMouseCursor_ResizeEW : ImGuiMouseCursor_ResizeNS;
				if (held)
					border_held = border_n;
			}
			if (held)
			{
				ImVec2 clamp_min(border_n == ImGuiDir_Right ? visibility_rect.Min.x : -FLT_MAX, border_n == ImGuiDir_Down ? visibility_rect.Min.y : -FLT_MAX);
				ImVec2 clamp_max(border_n == ImGuiDir_Left ? visibility_rect.Max.x : +FLT_MAX, border_n == ImGuiDir_Up ? visibility_rect.Max.y : +FLT_MAX);
				ImVec2 border_target = window->Pos;
				border_target[axis] = g.IO.MousePos[axis] - g.ActiveIdClickOffset[axis] + WINDOWS_HOVER_PADDING;
				border_target = ImClamp(border_target, clamp_min, clamp_max);
				CalcResizePosSizeFromAnyCorner(window, border_target, ImMin(def.SegmentN1, def.SegmentN2), &pos_target, &size_target);
			}
		}
		ImGui::PopID();

		bool changed = false;
		newSize = window->Size;
		newPosition = window->Pos;

		// Apply back modified position/size to window
		if (size_target.x != FLT_MAX)
		{
			//window->SizeFull = size_target;
			//MarkIniSettingsDirty(window);
			newSize = size_target;
			changed = true;
		}
		if (pos_target.x != FLT_MAX)
		{
			//window->Pos = ImFloor(pos_target);
			//MarkIniSettingsDirty(window);
			newPosition = pos_target;
			changed = true;
		}

		//window->Size = window->SizeFull;
		return changed;
	}

	bool BeginMenubar(const ImRect& barRectangle)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;
		/*if (!(window->Flags & ImGuiWindowFlags_MenuBar))
			return false;*/

		IM_ASSERT(!window->DC.MenuBarAppending);
		ImGui::BeginGroup(); // Backup position on layer 0 // FIXME: Misleading to use a group for that backup/restore
		ImGui::PushID("##menubar");

		const ImVec2 padding = window->WindowPadding;

		// We don't clip with current window clipping rectangle as it is already set to the area below. However we clip with window full rect.
		// We remove 1 worth of rounding to Max.x to that text in long menus and small windows don't tend to display over the lower-right rounded area, which looks particularly glitchy.
		ImRect bar_rect = UI::RectOffset(barRectangle, 0.0f, padding.y);// window->MenuBarRect();
		ImRect clip_rect(IM_ROUND(ImMax(window->Pos.x, bar_rect.Min.x + window->WindowBorderSize + window->Pos.x - 10.0f)), IM_ROUND(bar_rect.Min.y + window->WindowBorderSize + window->Pos.y),
			IM_ROUND(ImMax(bar_rect.Min.x + window->Pos.x, bar_rect.Max.x - ImMax(window->WindowRounding, window->WindowBorderSize))), IM_ROUND(bar_rect.Max.y + window->Pos.y));

		clip_rect.ClipWith(window->OuterRectClipped);
		ImGui::PushClipRect(clip_rect.Min, clip_rect.Max, false);

		// We overwrite CursorMaxPos because BeginGroup sets it to CursorPos (essentially the .EmitItem hack in EndMenuBar() would need something analogous here, maybe a BeginGroupEx() with flags).
		window->DC.CursorPos = window->DC.CursorMaxPos = ImVec2(bar_rect.Min.x + window->Pos.x, bar_rect.Min.y + window->Pos.y);
		window->DC.LayoutType = ImGuiLayoutType_Horizontal;
		window->DC.NavLayerCurrent = ImGuiNavLayer_Menu;
		window->DC.MenuBarAppending = true;
		ImGui::AlignTextToFramePadding();
		return true;
	}

	void EndMenubar()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;
		ImGuiContext& g = *GImGui;

		// Nav: When a move request within one of our child menu failed, capture the request to navigate among our siblings.
		if (ImGui::NavMoveRequestButNoResultYet() && (g.NavMoveDir == ImGuiDir_Left || g.NavMoveDir == ImGuiDir_Right) && (g.NavWindow->Flags & ImGuiWindowFlags_ChildMenu))
		{
			// Try to find out if the request is for one of our child menu
			ImGuiWindow* nav_earliest_child = g.NavWindow;
			while (nav_earliest_child->ParentWindow && (nav_earliest_child->ParentWindow->Flags & ImGuiWindowFlags_ChildMenu))
				nav_earliest_child = nav_earliest_child->ParentWindow;
			if (nav_earliest_child->ParentWindow == window && nav_earliest_child->DC.ParentLayoutType == ImGuiLayoutType_Horizontal && (g.NavMoveFlags & ImGuiNavMoveFlags_Forwarded) == 0)
			{
				// To do so we claim focus back, restore NavId and then process the movement request for yet another frame.
				// This involve a one-frame delay which isn't very problematic in this situation. We could remove it by scoring in advance for multiple window (probably not worth bothering)
				const ImGuiNavLayer layer = ImGuiNavLayer_Menu;
				IM_ASSERT(window->DC.NavLayersActiveMaskNext & (1 << layer)); // Sanity check
				ImGui::FocusWindow(window);
				ImGui::SetNavID(window->NavLastIds[layer], layer, 0, window->NavRectRel[layer]);
				g.NavDisableHighlight = true; // Hide highlight for the current frame so we don't see the intermediary selection.
				g.NavDisableMouseHover = g.NavMousePosDirty = true;
				ImGui::NavMoveRequestForward(g.NavMoveDir, g.NavMoveClipDir, g.NavMoveFlags, g.NavMoveScrollFlags); // Repeat
			}
		}

		IM_MSVC_WARNING_SUPPRESS(6011); // Static Analysis false positive "warning C6011: Dereferencing NULL pointer 'window'"
		// IM_ASSERT(window->Flags & ImGuiWindowFlags_MenuBar); // NOTE(Yan): Needs to be commented out because Jay
		IM_ASSERT(window->DC.MenuBarAppending);
		ImGui::PopClipRect();
		ImGui::PopID();
		window->DC.MenuBarOffset.x = window->DC.CursorPos.x - window->Pos.x; // Save horizontal position so next append can reuse it. This is kinda equivalent to a per-layer CursorPos.
		g.GroupStack.back().EmitItem = false;
		ImGui::EndGroup(); // Restore position on layer 0
		window->DC.LayoutType = ImGuiLayoutType_Vertical;
		window->DC.NavLayerCurrent = ImGuiNavLayer_Main;
		window->DC.MenuBarAppending = false;
	}

	bool ButtonCentered(const char* label, const ImVec2& size)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		float actualSize = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
		float avail = ImGui::GetContentRegionAvail().x;

		float off = (avail - actualSize) * 0.5f;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

		return ImGui::Button(label);
	}

	void DrawBorder(ImRect rect, float thickness, float rounding, float offsetX, float offsetY)
	{
		auto min = rect.Min;
		min.x -= thickness;
		min.y -= thickness;
		min.x += offsetX;
		min.y += offsetY;
		auto max = rect.Max;
		max.x += thickness;
		max.y += thickness;
		max.x += offsetX;
		max.y += offsetY;

		auto* drawList = ImGui::GetWindowDrawList();
		drawList->AddRect(min, max, ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiCol_Border)), rounding, 0, thickness);
	};

}