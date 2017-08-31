///////////////////////////////////////////////////////////////////////////////
// Name:        wx/ribbon/art.h
// Purpose:     Windows10 art provider for ribbon-bar-style interface
// Author:      Marcin Nowosad
// Modified by:
// Created:     2017-08-31
// Copyright:   (C) Marcin Nowosad
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include <wx/wx.h>
#include "art_msw10.h"

void wxRibbonMSW10ArtProvider::DrawPageBackground(wxDC &dc, wxWindow *wnd, const wxRect &rect)
{
	auto bg = wxBrush(wxColour(0xF5,0xF6,0xF7));
	auto outline = wxPen(wxColour(0xDA,0xDB,0xDC));
	dc.SetBrush(bg);
	dc.SetPen(outline);
	dc.DrawRectangle(rect);
}

void wxRibbonMSW10ArtProvider::DrawPanelBackground(wxDC &dc, wxRibbonPanel *wnd, const wxRect &rect)
{
	auto bg = wxBrush(wxColour(0xF5,0xF6,0xF7));
	auto outline = wxPen(wxColour(0xF5,0xF6,0xF7));
	dc.SetBrush(bg);
	dc.SetPen(outline);
	dc.DrawRectangle(rect);

	// Separator line
	auto separatorColor = wxPen(wxColour(0xE2,0xE3,0xE4));
	dc.SetPen(separatorColor);
	dc.DrawLine(
		rect.GetRight(), rect.GetTop()+2,
		rect.GetRight(), rect.GetBottom()
	);

	// Label
	dc.SetFont(m_panel_label_font);
	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(wxColour(0xF5,0xF6,0xF7)); // m_panel_hover_label_background_brush
	dc.SetTextForeground(wxColour(0x5A, 0x5A, 0x5A)); // m_panel_hover_label_colour

	wxRect label_rect(rect);
	wxString label = wnd->GetLabel();
	bool clip_label = false;
	wxSize label_size(dc.GetTextExtent(label));

	label_rect.SetY(rect.GetBottom() - label_size.GetHeight());
	label_rect.SetHeight(label_size.GetHeight());
	int label_height = label_rect.GetHeight();
	bool has_ext_button = wnd->HasExtButton();

	wxRect label_bg_rect = label_rect;

	if (has_ext_button)
		label_rect.SetWidth(label_rect.GetWidth() - 13);

	if (label_size.GetWidth() > label_rect.GetWidth())
	{
		// Test if there is enough length for 3 letters and ellipsis
		wxString new_label = label.Mid(0, 3) + wxT("...");
		label_size = dc.GetTextExtent(new_label);
		if (label_size.GetWidth() > label_rect.GetWidth())
		{
			// Not enough room for three characters and ellipsis
			// Display the entire label and just crop it
			clip_label = true;
		}
		else
		{
			// Display as many characters as possible and append ellipsis
			for (size_t len = label.Len() - 1; len >= 3; --len)
			{
				new_label = label.Mid(0, len) + wxT("...");
				label_size = dc.GetTextExtent(new_label);
				if (label_size.GetWidth() <= label_rect.GetWidth())
				{
					label = new_label;
					break;
				}
			}
		}
	}

	dc.DrawRectangle(label_bg_rect);
	if (clip_label)
	{
		wxDCClipper clip(dc, label_rect);
		dc.DrawText(
			label,
			label_rect.GetX(),
			label_rect.GetY() + (label_rect.GetHeight() - label_size.GetHeight()) / 2
		);
	}
	else
	{
		dc.DrawText(
			label,
			label_rect.GetX() + (label_rect.GetWidth() - label_size.GetWidth()) / 2,
			label_rect.GetY() +	(label_rect.GetHeight() - label_size.GetHeight()) / 2
		);
	}

	if (has_ext_button)
	{
		if (wnd->IsExtButtonHovered())
		{
			dc.SetPen(m_panel_hover_button_border_pen);
			dc.SetBrush(m_panel_hover_button_background_brush);
			dc.DrawRoundedRectangle(label_rect.GetRight(), label_rect.GetBottom() - 13, 13, 13, 1.0);
			dc.DrawBitmap(m_panel_extension_bitmap[1], label_rect.GetRight() + 3, label_rect.GetBottom() - 10, true);
		}
		else
			dc.DrawBitmap(m_panel_extension_bitmap[0], label_rect.GetRight() + 3, label_rect.GetBottom() - 10, true);
	}
}

wxColour wxRibbonMSW10ArtProvider::GetColour(int id) const
{
	switch(id) {
		case wxRIBBON_ART_BUTTON_BAR_LABEL_COLOUR: return wxColour(0x3C,0x3C,0x3C);
		case wxRIBBON_ART_BUTTON_BAR_LABEL_DISABLED_COLOUR: return wxColour(0x8D, 0x8D, 0x8D);
		case wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_COLOUR: return wxColour(0xE8,0xEF,0xF7);
		case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_COLOUR: return wxColour(0xCF, 0xE6, 0xFE);
		case wxRIBBON_ART_BUTTON_BAR_ACTIVE_BORDER_COLOUR: return wxColour(0x65, 0xA6, 0xE7);
		case wxRIBBON_ART_BUTTON_BAR_HOVER_BORDER_COLOUR : return wxColour(0xAA, 0xD3, 0xFE);
	}
	return wxRibbonMSWArtProvider::GetColour(id);
}

void wxRibbonMSW10ArtProvider::DrawButtonBarBackground(wxDC &dc, wxWindow *wnd, const wxRect &rect)
{
	auto bg = wxBrush(wxColour(0xF5,0xF6,0xF7));
	auto outline = wxPen(wxColour(0xF5,0xF6,0xF7));
	dc.SetBrush(bg);
	dc.SetPen(outline);
	dc.DrawRectangle(rect);
}

void wxRibbonMSW10ArtProvider::DrawButtonBarButton (
	wxDC &dc, wxWindow *wnd, const wxRect &rect,
	wxRibbonButtonKind kind, long state, const wxString &label,
	const wxBitmap &bitmap_large, const wxBitmap &bitmap_small
)
{
	if(kind == wxRIBBON_BUTTON_TOGGLE)
	{
			kind = wxRIBBON_BUTTON_NORMAL;
			if(state & wxRIBBON_BUTTONBAR_BUTTON_TOGGLED)
					state ^= wxRIBBON_BUTTONBAR_BUTTON_ACTIVE_MASK;
	}
	if(state & (wxRIBBON_BUTTONBAR_BUTTON_HOVER_MASK |	wxRIBBON_BUTTONBAR_BUTTON_ACTIVE_MASK)) {
		// Highlight
		bool bIsHover = state & wxRIBBON_BUTTONBAR_BUTTON_HOVER_MASK;
		auto bg = wxBrush(bIsHover ? GetColor(wxRIBBON_ART_BUTTON_BAR_HOVER_BACKGROUND_COLOUR) : GetColor(wxRIBBON_ART_BUTTON_BAR_ACTIVE_BACKGROUND_COLOUR));
		auto outline = wxPen(bIsHover ? GetColor(wxRIBBON_ART_BUTTON_BAR_HOVER_BORDER_COLOUR) : GetColor(wxRIBBON_ART_BUTTON_BAR_ACTIVE_BORDER_COLOUR));
		dc.SetBrush(bg);
		dc.SetPen(outline);
		dc.DrawRectangle(rect);
	}

	// Text, icon & stuff
	dc.SetFont(GetFont(wxRIBBON_ART_BUTTON_BAR_LABEL_FONT));
	dc.SetTextForeground(state & wxRIBBON_BUTTONBAR_BUTTON_DISABLED
													? GetColor(wxRIBBON_ART_BUTTON_BAR_LABEL_DISABLED_COLOUR)
													: GetColor(wxRIBBON_ART_BUTTON_BAR_LABEL_COLOUR));
	DrawButtonBarButtonForeground(dc, rect, kind, state, label, bitmap_large, bitmap_small);
}

void wxRibbonMSW10ArtProvider::DrawButtonBarButton (
	wxDC &dc, wxWindow *wnd, const wxRect &rect,
	wxRibbonButtonKind kind, long state, const wxString &label,
	const wxBitmap &bitmap_large, const wxBitmap &bitmap_small
);

void wxRibbonMSW10ArtProvider::DrawTabCtrlBackground (wxDC &dc, wxWindow *wnd, const wxRect &rect)
{
	auto bg = wxBrush(wxColour(0xFF,0xFF,0xFF));
	auto outline = wxPen(wxColour(0xFF,0xFF,0xFF));
	dc.SetBrush(bg);
	dc.SetPen(outline);
	dc.DrawRectangle(rect);
}

void wxRibbonMSW10ArtProvider::DrawTab(
	wxDC& dc, wxWindow* WXUNUSED(wnd),	const wxRibbonPageTabInfo& tab
)
{
	if (tab.rect.height <= 2)
		return;

	if (tab.active || tab.hovered)
	{
		wxBrush bg;
		wxPen bgPen, tabBorderPen;
		if (tab.active)
		{
			bg = wxBrush(wxColour(0xF5,0xF6,0xF7));
			bgPen = wxPen(wxColour(0xF5,0xF6,0xF7));
			tabBorderPen = wxPen(wxColour(0xDA,0xDB,0xDC));
		}
		else if (tab.hovered)
		{
			bg = wxBrush(wxColour(0xFD, 0xFD, 0xFF));
			bgPen = wxPen(wxColour(0xFD, 0xFD, 0xFF));
			tabBorderPen = wxPen(wxColour(0xEB, 0xEC, 0xEC));
		}

		const wxRect &bgRect = tab.rect;
		dc.SetPen(tabBorderPen);
		dc.SetBrush(bg);
		dc.DrawRectangle(bgRect);

		dc.SetPen(bgPen);
		dc.DrawLine(
			bgRect.GetLeft()+1, bgRect.GetBottom(),
			bgRect.GetRight(), bgRect.GetBottom()
		);
	}

	if (m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
	{
		wxBitmap icon = tab.page->GetIcon();
		if (icon.IsOk())
		{
			int x = tab.rect.x + 4;
			if ((m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS) == 0)
				x = tab.rect.x + (tab.rect.width - icon.GetScaledWidth()) / 2;
			dc.DrawBitmap(icon, x, tab.rect.y + 1 + (tab.rect.height - 1 - icon.GetScaledHeight()) / 2, true);
		}
	}
	if (m_flags & wxRIBBON_BAR_SHOW_PAGE_LABELS)
	{
		wxString label = tab.page->GetLabel();
		if (!label.IsEmpty())
		{
			dc.SetFont(m_tab_label_font);
			dc.SetTextForeground(GetColor(wxRIBBON_ART_BUTTON_BAR_LABEL_COLOUR));
			dc.SetBackgroundMode(wxTRANSPARENT);

			int text_height;
			int text_width;
			dc.GetTextExtent(label, &text_width, &text_height);
			int width = tab.rect.width - 5;
			int x = tab.rect.x + 3;
			if (m_flags & wxRIBBON_BAR_SHOW_PAGE_ICONS)
			{
				x += 3 + tab.page->GetIcon().GetScaledWidth();
				width -= 3 + tab.page->GetIcon().GetScaledWidth();
			}
			int y = tab.rect.y + (tab.rect.height - text_height) / 2;

			if (width <= text_width)
			{
				dc.SetClippingRegion(x, tab.rect.y, width, tab.rect.height);
				dc.DrawText(label, x, y);
			}
			else
			{
				dc.DrawText(label, x + (width - text_width) / 2 + 1, y);
			}
		}
	}
}

void wxRibbonMSW10ArtProvider::DrawToggleButton(
	wxDC& dc, wxRibbonBar* wnd,	const wxRect& rect,	wxRibbonDisplayMode mode
)
{
	int bindex = 0;
	DrawPartialPageBackground(dc, wnd, rect, false);

	dc.DestroyClippingRegion();
	dc.SetClippingRegion(rect);

	if (wnd->IsToggleButtonHovered())
	{
		dc.SetPen(wxColour(0xAB, 0xD4, 0xFE));
		dc.SetBrush(wxColour(0xF1, 0xF7, 0xFE));
		dc.DrawRectangle(rect);
		bindex = 1;
	}
	switch (mode)
	{
	case wxRIBBON_BAR_PINNED:
		dc.DrawBitmap(m_ribbon_toggle_up_bitmap[bindex], rect.GetX() + 7, rect.GetY() + 6, true);
		break;
	case wxRIBBON_BAR_MINIMIZED:
		dc.DrawBitmap(m_ribbon_toggle_down_bitmap[bindex], rect.GetX() + 7, rect.GetY() + 6, true);
		break;
	case wxRIBBON_BAR_EXPANDED:
		dc.DrawBitmap(m_ribbon_toggle_pin_bitmap[bindex], rect.GetX() + 4, rect.GetY() + 5, true);
		break;
	}
}

void wxRibbonMSW10ArtProvider::DrawScrollButton(
	wxDC &dc,	wxWindow *WXUNUSED(wnd), const wxRect &rect_,	long style
)
{
	wxRect rect(rect_);

	if ((style & wxRIBBON_SCROLL_BTN_FOR_MASK) == wxRIBBON_SCROLL_BTN_FOR_PAGE)
	{
		// Page scroll buttons do not have the luxury of rendering on top of anything
		// else, and their size includes some padding, hence the background painting
		// and size adjustment.
		dc.SetPen(*wxTRANSPARENT_PEN);
		dc.SetBrush(m_tab_ctrl_background_brush);
		dc.DrawRectangle(rect);
		dc.SetClippingRegion(rect);
		switch (style & wxRIBBON_SCROLL_BTN_DIRECTION_MASK)
		{
		case wxRIBBON_SCROLL_BTN_UP:
			rect.x++;
			rect.y--;
			rect.width -= 2;
			rect.height++;
			break;
		case wxRIBBON_SCROLL_BTN_DOWN:
			rect.x++;
			rect.width -= 2;
			rect.height--;
			break;
		}
	}

	// Draw rectangle
	if(style & wxRIBBON_SCROLL_BTN_HOVERED) {
		dc.SetBrush(wxColour(0xE8, 0xEF, 0xF7));
		dc.SetPen(wxColour(0xA0, 0xCD, 0xF9));
	}
	else {
		dc.SetBrush(wxColour(0xF5, 0xF6, 0xF7));
		dc.SetPen(wxColour(0xDC, 0xDC, 0xDD));
	}
	dc.DrawRectangle(rect);

	// Draw arrows
	// NB: Code for handling hovered/active state is temporary
	wxPoint arrow_points[3];
	switch (style & wxRIBBON_SCROLL_BTN_DIRECTION_MASK)
	{
	case wxRIBBON_SCROLL_BTN_LEFT:
		arrow_points[0] = wxPoint(rect.width / 2 - 2, rect.height / 2);
		if (style & wxRIBBON_SCROLL_BTN_ACTIVE)
			arrow_points[0].y += 1;
		arrow_points[1] = arrow_points[0] + wxPoint(3, -3);
		arrow_points[2] = arrow_points[0] + wxPoint(3, 3);
		break;
	case wxRIBBON_SCROLL_BTN_RIGHT:
		arrow_points[0] = wxPoint(rect.width / 2 + 2, rect.height / 2);
		if (style & wxRIBBON_SCROLL_BTN_ACTIVE)
			arrow_points[0].y += 1;
		arrow_points[1] = arrow_points[0] - wxPoint(3, 3);
		arrow_points[2] = arrow_points[0] - wxPoint(3, -3);
		break;
	case wxRIBBON_SCROLL_BTN_UP:
		arrow_points[0] = wxPoint(rect.width / 2, rect.height / 2 - 2);
		if (style & wxRIBBON_SCROLL_BTN_ACTIVE)
			arrow_points[0].y += 1;
		arrow_points[1] = arrow_points[0] + wxPoint(3, 3);
		arrow_points[2] = arrow_points[0] + wxPoint(-3, 3);
		break;
	case wxRIBBON_SCROLL_BTN_DOWN:
		arrow_points[0] = wxPoint(rect.width / 2, rect.height / 2 + 2);
		if (style & wxRIBBON_SCROLL_BTN_ACTIVE)
			arrow_points[0].y += 1;
		arrow_points[1] = arrow_points[0] - wxPoint(3, 3);
		arrow_points[2] = arrow_points[0] - wxPoint(-3, 3);
		break;
	}

	dc.SetPen(*wxTRANSPARENT_PEN);
	wxBrush B(wxColour(0x4C, 0x60, 0x7A));
	dc.SetBrush(B);
	dc.DrawPolygon(
		sizeof(arrow_points) / sizeof(wxPoint),
		arrow_points, rect.x, rect.y
	);
}
