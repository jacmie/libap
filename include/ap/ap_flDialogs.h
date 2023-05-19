#ifndef AP_DIALOGS_H
#define AP_DIALOGS_H

// Implementation of fl_message, fl_ask, fl_choice, fl_input etc.

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>

namespace ap {

//! Customizable FLTK common dialogs 
/*!
 * Default FLTK dialog windows doesn't always match the created gui style.\n
 * ap::DIALOGS class provides methods to format style of the dilog windows and few additional features.
 */
class DIALOGS
{
	struct DIALOG_WIN : public Fl_Window {
		int *win_close;

		DIALOG_WIN(int W, int H, const char *l=0);
  		void hide();
	};

	class DIALOG_FORM {
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

	DIALOGS() = default;

	//! Messages from the dialog window is also passed to the std::clog and printed
	/** By default logs are on. */
	void logs_on();

	//! Messages from the dialog window are not passed to the std::clog
	/** By default logs are on. */
	void logs_off();


	//! Sets dialog buttons option as resizable when the dialog window is resized
	/** By default buttons have fixed size. */
	void resizebuttons_on();
	
	//! Sets dialog buttons option as fixed size when the dialog window is resized
	/** By default buttons have fixed size. */
	void resizebuttons_off();
	
	//! Sets the main button as hotspot for the mouse pointer when the dialog appears
	/** By default hotspot option is on. */
	void hotspot_on();
	
	//! Sets off hotspot for the mouse pointer
	/** By default hotspot option is on. */
	void hotspot_off();


	//! Sets dialog form title
	/** \param formtitle - title that will be displayed on the label */
	void form_label(std::string formtitle);

	//! Sets dialog form color
	/** \param formcolor - index in which color the form will be painted, see Fl_Color */
	void form_color(Fl_Color formcolor);

	//! Sets dialog form box type
	/** \param formboxtype - form box type, see Fl_Boxtype */
	void form_box(Fl_Boxtype formboxtype);
	

	//! Makes icon label visible
	/** By default icon label option is on. */
	void iconlabel_on();
	
	//! Makes icon label invisible
	/** By default icon label option is on. */
	void iconlabel_off();

	//! Makes icon image visible
	/** By default icon image option is off, but setting new log turns it on. */
	void iconimage_on();
	
	//! Makes icon image invisible
	/** By default icon image option is off, but setting new log turns it on. */
	void iconimage_off();

	//! Sets label in the icon field
	/** 
	 * \param icolabel - label in the icon field 
	 * \note It can be typical label, or single char with large font size.
	 */
	void icon_label(std::string icolabel);
	
	//! Sets icon from file
	/** 
	 * \param icofile - path to the icon file 
	 * \param textflag - should icon label text overlay over the icon image (image as background) 
	 * \note The image is not compiled into the program. Typically it means the icon image has to be distributed with the program.
	 * \sa icon_image(), where image is taken from Fl_Pixmap, which can be embedded in the code. Fl_Pixmap can be casted from other Fl_Image types. 
	 */
	void icon_file(std::string icofile, bool textflag=0);
	
	//! Sets icon from Fl_Pixmap
	/** 
	 * \param pixmap - path to the icon file 
	 * \param textflag - should icon label text overlay over the icon image (image as background) 
	 * \note Depending on the implementation the pixmap image can be compiled into the program. It means the icon image doesn't have to be distributed with the program.
	 * \sa icon_file() 
	 */
	void icon_image(Fl_Pixmap *pixmap, bool textflag=0);
	
	//! Sets icon label font and it's size
	/** 
	 * \param font - icon label font, see Fl_Font  
	 * \param size - icon label font size 
	 */
	void icon_font(Fl_Font font, Fl_Fontsize size=12);
	
	//! Sets icon font and backgound color
	/** 
	 * \param font_color - icon font color, see Fl_Color  
	 * \param bg_color - icon background color, see Fl_Color
	 */
	void icon_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR);
	
	//! Sets icon box type
	/** \param type - icon box type, see Fl_Boxtype */
	void icon_box(Fl_Boxtype type);

	
	//! Sets input field text font and it's size
	/** 
	 * \param font - input field text font, see Fl_Font  
	 * \param size - input field text font size 
	 */
	void input_font(Fl_Font font, Fl_Fontsize size=12);
	
	//! Sets input field text font color and backgound color
	/** 
	 * \param font_color - input field text font color, see Fl_Color  
	 * \param bg_color - input field background color, see Fl_Color
	 */
	void input_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR);
	
	//! Sets input field box type
	/** \param type - input field box type, see Fl_Boxtype */
	void input_box(Fl_Boxtype type);
	
	
	//! Sets message font and it's size
	/** 
	 * \param font - message font, see Fl_Font  
	 * \param size - message font size 
	 */
	void message_font(Fl_Font font, Fl_Fontsize size=12);
	
	//! Sets message font color and backgound color
	/** 
	 * \param font_color - message font color, see Fl_Color  
	 * \param bg_color - message background color, see Fl_Color
	 */
	void message_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR);
	
	//! Sets message box type
	/** \param type - message box type, see Fl_Boxtype */
	void message_box(Fl_Boxtype type);
	
	
	//! Sets buttons font and it's size
	/** 
	 * \param font - buttons font, see Fl_Font  
	 * \param size - buttons font size 
	 */
	void buttons_font(Fl_Font font, Fl_Fontsize size=12);
	
	//! Sets buttons font color, backgound color and pressed position color
	/** 
	 * \param font_color - buttons font color, see Fl_Color  
	 * \param bg_color - buttons background color, see Fl_Color
	 * \param down_color - buttons pressed position color, see Fl_Color
	 */
	void buttons_color(Fl_Color font_color, Fl_Color bg_color=FL_BACKGROUND_COLOR, Fl_Color down_color=FL_BACKGROUND_COLOR);
	
	//! Sets buttons box type
	/** \param type - buttons box type, see Fl_Boxtype */
	void buttons_box(Fl_Boxtype type);
	
	//! Alert dialog
	/** Message in sprintf-like format with alert icon. 
	 * \sa fl_alert() */
	void alert(const char *, ...);
	
	//! Message dialog
	/** Message in sprintf-like format.
	 * \sa fl_message() */
	void message(const char *, ...);
	
	//! Choice dialog 
	/** 
	 * Message with buttons as choice options.
	 * \param q - can be used as an sprintf-like format and variables for the message text
	 * \param b0 - text label of button 0
	 * \param b1 - text label of button 1 (can be 0)
	 * \param b2 - text label of button 2 (can be 0)
	 * \return Result:
	 * - 0 - if the first button with b0 text is pushed or another dialog box is still open
	 * - 1 - if the second button with b1 text is pushed
	 * - 2 - if the third button with b2 text is pushed 
	 * \sa fl_choice(), choice_s(), choice_n() 
	 */
	int  choice(const char *q, const char *b0, const char *b1, const char *b2, ...);
    
	//! Simple choice dialog 
	/** 
	 * Message with default Yes an No buttons.
	 * \param q - can be used as an sprintf-like format and variables for the message text
	 * \return Result:
	 * - 1 - if the Yes button is pushed
	 * - 0 - if the No button is pushed
	 * \sa choice(), choice_n() 
	 */
	int  choice_s(const char *q, ...); // simple
	
	//! Choice dialog with extended return values 
	/** 
	 * Message with buttons as choice options. Extended return values.
	 * \param q - can be used as an sprintf-like format and variables for the message text
	 * \param b0 - text label of button 0
	 * \param b1 - text label of button 1 (can be 0)
	 * \param b2 - text label of button 2 (can be 0)
	 * \return Result:
	 * - -3 - if another dialog box is still open (the dialog was blocked)
	 * - -2 - if the dialog window was closed by clicking the close button
	 * - -1 - if the dialog was closed by hitting Escape
	 * - 0 - if the first button with b0 text is pushed
	 * - 1 - if the second button with b1 text is pushed
	 * - 2 - if the third button with b2 text is pushed 
	 * \sa fl_choice_n(), choice_s(), choice() 
	 */
    int  choice_n(const char *q, const char *b0, const char *b1, const char *b2, ...);
	
	//! Input dialog 
	/** 
	 * Message with input field.
	 * \param label - message text
	 * \param deflt - input field text
	 * \return Text from the input field.
	 * \sa fl_input()
	 */
	const char *input(const char *label, const char *deflt = 0, ...);
	
	//! Password dialog 
	/** 
	 * Message with input field with hidden characters.
	 * \param label - message text
	 * \param deflt - input field text
	 * \return Text from the input field.
	 * \sa fl_password()
	 */
	const char *password(const char *label, const char *deflt = 0, ...);
	
	private:

	int innards(const char* fmt, const char *b0, const char *b1, const char *b2);
	const char* input_innards(const char* fmt, const char* defstr, uchar type);
};

} // namespace ap

#endif //AP_DIALOGS_H
