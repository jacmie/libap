#ifndef DIALOGS_H
#define DIALOGS_H

// Implementation of fl_message, fl_ask, fl_choice, fl_input etc.

#ifdef _WIN32
	#include <windows.h>
#else
	#include <cstdarg>
#endif

#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>

#include <FL/fl_ask.H>
#include <FL/Fl_XPM_Image.H>

class DIALOG_WIN : public Fl_Window 
{
	public:
 
	int *win_close;

	DIALOG_WIN(int W, int H, const char *l=0);
  	void hide();
};

class DIALOG_FORM
{
	int  button_val[3] = {0, 1, 2};
	
	Fl_Box 		*icon;
	Fl_Input 	*input;
	Fl_Box 		*message;
	Fl_Button 	*button[3];

	public:
	
	DIALOG_WIN 	*message_form;
	int ret_val   = 0;  // button return value: 0 -> Canel, 1, 2
	int win_close = 0;	// -1 -> Escape, -2 -> X close button, -3 -> blocked by another dialog window

	DIALOG_FORM();

	void set_form(bool hotspot_flag, std::string form_label, Fl_Color bgcolor, Fl_Boxtype boxtype); 
	void set_icon(Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color bgcolor, Fl_Boxtype boxtype, bool textflag, const char *text, bool logoflag, Fl_Pixmap *logo);
	void set_input(bool	flag, const char *defstr, uchar type, Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color bgcolor, Fl_Boxtype boxtype);
	void set_message(const char* fmt, Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color bgcolor, Fl_Boxtype boxtype);
	void set_buttons(const char *b0, const char *b1, const char *b2, Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color color, Fl_Color downcolor, Fl_Boxtype boxtype);
	void resizeform(bool resize_buttons);
	std::string get_userinput();

	private:
	
	inline void button_cb_i(Fl_Button*, void*);
	static void button_cb(Fl_Button*, void*);
};

class DIALOGS
{
   	char buffer[1024];

	char avoidRecursion = 0;

    bool        print_logs          = 1;

	// --- Form ---
    
	bool		resize_buttons		= 0;
	bool		hotspot_flag 		= 1;

	std::string	form_title			= "";
	Fl_Color 	form_bgcolor		= FL_BACKGROUND_COLOR; 
	Fl_Boxtype 	form_boxtype		= FL_FLAT_BOX;
	
	// --- Icon ---

	bool		icon_logoflag		= 0;
	bool		icon_textflag		= 1;
	std::string	icon_deftext		= "?";
	std::string icon_newtext		= "";
	Fl_Pixmap 	*logo;
	
	Fl_Font 	icon_font_style		= FL_TIMES_BOLD; 
	Fl_Fontsize icon_size			= 34; 
	Fl_Color 	icon_textcolor		= FL_DARK_BLUE; 
	Fl_Color 	icon_bgcolor		= FL_WHITE; 
	Fl_Boxtype 	icon_boxtype		= FL_THIN_UP_BOX;
	
	// --- Input ---

	bool		input_flag			= 0;
	uchar  		input_type			= FL_SECRET_INPUT;
	std::string input_defstr		= "";
	
	Fl_Font 	input_font_style	= FL_HELVETICA; 
	Fl_Fontsize input_size			= 12; 
	Fl_Color 	input_textcolor		= FL_BLACK;
	Fl_Color 	input_bgcolor		= FL_WHITE;
	Fl_Boxtype 	input_boxtype		= FL_THIN_DOWN_BOX;

	// --- Message ---
	
	Fl_Font 	message_font_style	= FL_HELVETICA; 
	Fl_Fontsize message_size		= 12; 
	Fl_Color 	message_textcolor	= FL_BLACK;
	Fl_Color 	message_bgcolor		= FL_BACKGROUND_COLOR;
	Fl_Boxtype 	message_boxtype		= FL_FLAT_BOX;
	
	// --- Buttons ---
	
	// pointers you can use to change FLTK to a foreign language:
	/*const char* fl_no;
	const char* fl_yes;
	const char* fl_ok;
	const char* fl_cancel;
	const char* fl_close;*/
	
	Fl_Font 	buttons_font_style	= FL_HELVETICA; 
	Fl_Fontsize buttons_size		= 12; 
	Fl_Color 	buttons_textcolor	= FL_BLACK; 
	Fl_Color 	buttons_upcolor		= FL_BACKGROUND_COLOR; 
	Fl_Color 	buttons_downcolor	= FL_BACKGROUND_COLOR; 
	Fl_Boxtype 	buttons_boxtype		= FL_GLEAM_THIN_UP_BOX;
	
	public:

	DIALOGS();

	void logs_on();
	void logs_off();

	void resizebuttons_on();
	void resizebuttons_off();
	void hotspot_on();
	void hotspot_off();

	void form_label(std::string formtitle);
	void form_color(Fl_Color formcolor);
	void form_box(Fl_Boxtype formboxtype);
	
	void icon_label(std::string icolabel);
	void icon_file(std::string icofile, bool textflag=0);
	void icon_image(Fl_Pixmap *pixmap, bool textflag=0);
	void icon_font(Fl_Font font, Fl_Fontsize size=12);
	void icon_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR);
	void icon_box(Fl_Boxtype type);

	void input_font(Fl_Font font, Fl_Fontsize size=12);
	void input_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR);
	void input_box(Fl_Boxtype type);
	
	void message_font(Fl_Font font, Fl_Fontsize size=12);
	void message_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR);
	void message_box(Fl_Boxtype type);
	
	void buttons_font(Fl_Font font, Fl_Fontsize size=12);
	void buttons_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR, Fl_Color down_color=FL_BACKGROUND_COLOR);
	void buttons_box(Fl_Boxtype type);
	
	void alert(const char *, ...);
	void message(const char *, ...);
	int  choice(const char *q, const char *b0, const char *b1, const char *b2, ...);
    int  choice_s(const char *q, ...); // simple
    int  choice_n(const char *q, const char *b0, const char *b1, const char *b2, ...);
	const char *input(const char *label, const char *deflt = 0, ...);
	const char *password(const char *label, const char *deflt = 0, ...);
	
	private:

	int innards(const char* fmt, const char *b0, const char *b1, const char *b2);
	const char* input_innards(const char* fmt, const char* defstr, uchar type);
};

#endif
