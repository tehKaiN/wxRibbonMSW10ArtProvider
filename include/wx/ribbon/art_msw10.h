///////////////////////////////////////////////////////////////////////////////
// Name:        wx/ribbon/art.h
// Purpose:     Windows10 art provider for ribbon-bar-style interface
// Author:      Marcin Nowosad
// Modified by:
// Created:     2017-08-31
// Copyright:   (C) Marcin Nowosad
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#include <wx/ribbon/art.h>

class wxRibbonMSW10ArtProvider: public wxRibbonMSWArtProvider
{
public:

	virtual void DrawPageBackground(wxDC &dc, wxWindow *wnd, const wxRect &rect);

	virtual void DrawPanelBackground(wxDC &dc, wxRibbonPanel *wnd, const wxRect &rect);

	virtual wxColour GetColour(int id) const;

	virtual void DrawButtonBarBackground (wxDC &dc, wxWindow *wnd, const wxRect &rect);

	virtual void DrawButtonBarButton(
		wxDC &dc, wxWindow *wnd, const wxRect &rect,
		wxRibbonButtonKind kind, long state, const wxString &label,
		const wxBitmap &bitmap_large, const wxBitmap &bitmap_small
	);

	virtual void DrawTabCtrlBackground (wxDC &dc, wxWindow *wnd, const wxRect &rect);

	virtual void DrawTab(
		wxDC& dc, wxWindow* WXUNUSED(wnd),	const wxRibbonPageTabInfo& tab
	);

	virtual void DrawToggleButton(
		wxDC& dc, wxRibbonBar* wnd,	const wxRect& rect,	wxRibbonDisplayMode mode
	);

	virtual void DrawScrollButton(
		wxDC &dc,	wxWindow *WXUNUSED(wnd), const wxRect &rect_,	long style
	);

};
