#ifndef DIALOGS_H
#define DIALOGS_H

// Implementation of fl_message, fl_ask, fl_choice, fl_input etc.

#include <stdarg.h>
#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>

#include <FL/fl_ask.H>

class DIALOG_WIN : public Fl_Window 
{
	public:
 
	int *win_close;

	DIALOG_WIN(int W, int H, const char *l=0);
  	void hide();
};

class DIALOG_FORM
{
	public:

	DIALOG_WIN 	*message_form;
	Fl_Box 		*message;
	Fl_Box 		*icon;
	Fl_Button 	*button[3];
	Fl_Input 	*input;

	int button_val[3] = {0, 1, 2};
	int ret_val   = 0;  // button return value: 0 -> Canel, 1, 2
	int win_close = 0;	// -1 -> Escape, -2 -> X close button, -3 -> blocked by another dialog window

	public:

	DIALOG_FORM();

	void set_message(const char* fmt, va_list ap, Fl_Font font, Fl_Fontsize size, Fl_Color color);
	void set_buttons(const char *b0, const char *b1, const char *b2, Fl_Font font, Fl_Fontsize size, Fl_Color color, Fl_Boxtype boxtype);
	
	void resizeform();

	private:
	
	inline void button_cb_i(Fl_Button*, void*);
	static void button_cb(Fl_Button*, void*);
};

class DIALOGS
{
	public:

	const char *iconlabel = "?";
	const char *message_title_default;
	int enableHotspot = 1;

	char avoidRecursion = 0;

	//DIALOG_FORM *message_win;

	// --- Form ---

	bool		resize_flag		= 0;
	Fl_Color 	form_color		= FL_BACKGROUND_COLOR; 
	Fl_Boxtype 	form_boxtype	= FL_FLAT_BOX;
	
	void resize(bool resize_flag);
	void form(Fl_Color form_color, Fl_Boxtype form_boxtype);
	
	// --- Message ---
	
	Fl_Font 	message_font 		= FL_HELVETICA; 
	Fl_Fontsize message_size		= 12; 
	Fl_Color 	message_textcolor	= FL_BLACK;
	Fl_Color 	message_bgcolor		= FL_BACKGROUND_COLOR;
	Fl_Boxtype 	message_boxtype		= FL_FLAT_BOX;
	
	void message_text(Fl_Font font, Fl_Fontsize size);
	void message_color(Fl_Color font_color, Fl_Color bg_color);
	void message_style(Fl_Boxtype type);
	
	// --- Buttons ---
	
	// pointers you can use to change FLTK to a foreign language:
	/*const char* fl_no;
	const char* fl_yes;
	const char* fl_ok;
	const char* fl_cancel;
	const char* fl_close;*/
	
	Fl_Font 	buttons_font 		= FL_HELVETICA; 
	Fl_Fontsize buttons_size		= 12; 
	Fl_Color 	buttons_textcolor	= FL_BLACK; 
	Fl_Color 	buttons_bgcolor		= FL_BACKGROUND_COLOR; 
	Fl_Boxtype 	buttons_boxtype		= FL_GLEAM_THIN_UP_BOX;
	
	void buttons_text(Fl_Font font, Fl_Fontsize size);
	void buttons_color(Fl_Color font_color, Fl_Color bg_color);
	void buttons_style(Fl_Boxtype type);
	
	// --- Icon ---
	
	Fl_Font 	icon_font 		= FL_HELVETICA; 
	Fl_Fontsize icon_size		= 12; 
	Fl_Color 	icon_textcolor	= FL_BLACK; 
	Fl_Color 	icon_bgcolor		= FL_BACKGROUND_COLOR; 
	Fl_Boxtype 	icon_boxtype		= FL_GLEAM_THIN_UP_BOX;
	
	//icon(xpm);
	//icon_text();
	//icon_bg();

	void JM_alert(const char *, ...);// __fl_attr((__format__ (__printf__, 1, 2)));
	void JM_message(const char *, ...);// __fl_attr((__format__ (__printf__, 1, 2)));
	int JM_choice(const char *q,const char *b0,const char *b1,const char *b2, ...);// __fl_attr((__format__ (__printf__, 1, 5)));
	const char *JM_input(const char *label, const char *deflt = 0, ...);// __fl_attr((__format__ (__printf__, 1, 3)));
	const char *JM_password(const char *label, const char *deflt = 0, ...);// __fl_attr((__format__ (__printf__, 1, 3)));
	int JM_choice_n(const char *q,const char *b0,const char *b1,const char *b2, ...);// __fl_attr((__format__ (__printf__, 1, 5)));
	
	private:
	
	Fl_Font fl_message_font_;
	Fl_Fontsize fl_message_size_;
	inline void fl_message_font(Fl_Font f, Fl_Fontsize s) {fl_message_font_ = f; fl_message_size_ = s;}
	
	int innards(const char* fmt, va_list ap, const char *b0, const char *b1, const char *b2);
	const char* input_innards(const char* fmt, va_list ap, const char* defstr, uchar type);
};

#endif
