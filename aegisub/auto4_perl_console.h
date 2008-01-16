// Copyright (c) 2008, Simone Cociancich
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Aegisub Group nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// -----------------------------------------------------------------------------
//
// AEGISUB
//
// Website: http://aegisub.cellosoft.com
// Contact: mailto:jiifurusu@gmail.com
//


#pragma once
#ifndef _AUTO4_PERL_CONSOLE_H
#define _AUTO4_PERL_CONSOLE_H


#include "auto4_perl.h"
#include <wx/textctrl.h>


namespace Automation4 {

  class PerlConsole : public PerlFeatureMacro {
  private:
	static PerlConsole *registered;

	// Nested classes are messy, therefore we use them :)
	class Dialog : public wxDialog {
	private:
	  wxTextCtrl *txt_out, *txt_hist, *txt_in;
	  
	public:
	  Dialog();

	  bool Create(wxWindow* parent, wxWindowID id, const wxString& title,
				  const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
				  long style = wxDEFAULT_DIALOG_STYLE, const wxString& name = _T("console_dialog"));

	  void InputEnter(wxCommandEvent& evt);
	  void Echo(const wxString &str);
	};
	
	Dialog *dialog;
	wxWindow *parent_window;

	SV *cout;
	wxString evaluate(const wxString &str);

  public:
	PerlConsole(const wxString &name, const wxString &desc, PerlScript *script);
	virtual ~PerlConsole();

	static PerlConsole *GetConsole() { return registered; }

	virtual bool Validate(AssFile *subs, const std::vector<int> &selected, int active) { return true; }
	virtual void Process(AssFile *subs, std::vector<int> &selected, int active, wxWindow * const progress_parent);

	static wxString Evaluate(const wxString &str) { if(registered) return registered->evaluate(str); }
	static XS(register_console);
	static XS(echo);
  };

};


#endif
