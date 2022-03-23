#include "JMdialogs.h"

using namespace std;

DIALOG_WIN::DIALOG_WIN(int W, int H, const char *l) : Fl_Window(W, H, l) 
{
}

void DIALOG_WIN::hide() 
{
	if ((Fl::event() == FL_KEYBOARD || Fl::event() == FL_SHORTCUT) && (Fl::event_key() == FL_Escape))	*win_close = -1;
  	else																								*win_close = -2;

	Fl_Window::hide();
}

void DIALOG_FORM::button_cb_i(Fl_Button*, void *v) 
{
  	ret_val	= *(int*)v;
  	message_form->hide();
}

void DIALOG_FORM::button_cb(Fl_Button *o, void *v)
{
  	((DIALOG_FORM*)(o->parent()->user_data()))->button_cb_i(o,v);
}

DIALOG_FORM::DIALOG_FORM() 
{
 	// make sure that the dialog does not become the child of some
 	// current group
 	Fl_Group *previously_current_group = Fl_Group::current();
 	Fl_Group::current(0);
 
 	message_form = new DIALOG_WIN(410, 103);
 	message_form->user_data((void*)(this));
	message_form->win_close = &win_close;
 	
	icon = new Fl_Box(10, 10, 50, 50);
	icon->align(FL_ALIGN_IMAGE_BACKDROP);

	input = new Fl_Input(65, 37, 335, 23);
	input->hide();
 	
	message = new Fl_Box(65, 25, 335, 20);
	message->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
 	
 	message_form->end(); // don't add the buttons automatically
 
	// create the buttons (right to left)
   	for (int b=0, x=310; b<3; b++, x-=100) 
	{
    	//if (b==1)	button[b] = new Fl_Return_Button(x, 70, 80, 20);
    	/*else*/	button[b] = new Fl_Button(x, 70, 80, 20);
    	
		button[b]->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
    	button[b]->callback((Fl_Callback*)button_cb, &button_val[b]);
   	}

 	// add the buttons (left to right)
 	{
   		for (int b=2; b>=0; b--)
     		message_form->add(button[b]);
 	}

 	message_form->begin();
 	message_form->resizable(new Fl_Box(65, 10, 110-65, 27));
	message_form->end();

 	message_form->set_modal();

	Fl_Group::current(previously_current_group);
}

void DIALOG_FORM::set_form(bool hotspot_flag, std::string form_label, Fl_Color bgcolor, Fl_Boxtype boxtype) 
{
  	if (hotspot_flag) message_form->hotspot(button[0]);

   	message_form->label(form_label.c_str());
  	message_form->color(bgcolor);
  	message_form->box(boxtype);
}

void DIALOG_FORM::set_icon(Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color bgcolor, Fl_Boxtype boxtype, bool textflag, const char *text, bool logoflag, Fl_Pixmap *logo) 
{
  	icon->labelfont(font);
  	icon->labelsize(size);
  	icon->labelcolor(textcolor);
  	icon->color(bgcolor);
  	icon->box(boxtype);

	if(textflag) icon->label(text);
	else		 icon->label(0);

	if(logoflag) icon->image(logo);
}

void DIALOG_FORM::set_input(bool flag, const char *defstr, uchar type, Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color bgcolor, Fl_Boxtype boxtype)
{
	input->type(type);
  	input->value(defstr);
  	input->take_focus();
  	
	input->labelfont(font);
  	input->labelsize(size);
  	input->labelcolor(textcolor);
  	input->color(bgcolor);
  	input->box(boxtype);
	
	if(flag)
	{
  		message->position(65, 10); // move
  		input->show();
	}
}

void DIALOG_FORM::set_message(const char* fmt, va_list ap, Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color bgcolor, Fl_Boxtype boxtype) 
{
	if (!strcmp(fmt,"%s")) 
	{
    	message->label( va_arg(ap, const char*) );
  	} 

	else 
	{
    	::vsnprintf(buffer, 1024, fmt, ap);
    	message->label(buffer);
  	}

  	message->labelfont(font);
  	message->labelsize(size);
  	message->labelcolor(textcolor);
  	message->color(bgcolor);
  	message->box(boxtype);
}

void DIALOG_FORM::set_buttons(const char *b0, const char *b1, const char *b2, Fl_Font font, Fl_Fontsize size, Fl_Color textcolor, Fl_Color upcolor, Fl_Color downcolor, Fl_Boxtype boxtype) 
{
	if(b0) 
	{
		button[0]->show(); 
		button[0]->label(b0); 
		button[1]->position(210, 70);
	}
  	else 
	{
		button[0]->hide(); 
		button[1]->position(310, 70);
	}
  
	if(b1) 
	{
		button[1]->show(); 
		button[1]->label(b1);
	}
  	else
	{
		button[1]->hide();
	}

	if(b2) 
	{
		button[2]->show(); 
		button[2]->label(b2);
	}
  	else
	{
		button[2]->hide();
	}
  	
	if (button[1]->visible() && !input->visible())	button[1]->take_focus();
  	if (b0 && Fl_Widget::label_shortcut(b0))		button[0]->shortcut(0);

	for (int b=0; b<3; b++) 
	{

  		button[b]->labelfont(font);
  		button[b]->labelsize(size);
  		button[b]->labelcolor(textcolor);
  		button[b]->color(upcolor);
  		button[b]->down_color(downcolor);
		button[b]->box(boxtype);
   	}
}

void DIALOG_FORM::resizeform(bool adjust_size, bool resize_buttons) 
{
  	int	i;
  	int	message_w, message_h;
  	int	text_height;
  	int	button_w[3], button_h[3];
  	int	x, w, h, max_w, max_h=20;
	const int icon_size = 50;

  	message_w = message_h = 0;
  	if(adjust_size) fl_measure(message->label(), message_w, message_h);

  	message_w += 10;
  	message_h += 10;
  
	if (message_w < 340)	message_w = 340;
	if (message_h < 30)		message_h = 30;

  	memset(button_w, 0, sizeof(button_w));
  	memset(button_h, 0, sizeof(button_h));

  	for(max_h=25, i=0; i<3; i ++)
	{
    	if(button[i]->visible())
    	{
      		fl_measure(button[i]->label(), button_w[i], button_h[i]);
			
      		if (i == 1) button_w[1] += 20;

      		button_w[i] += 30;
      		button_h[i] += 10;

      		if (button_h[i] > max_h) max_h = button_h[i];
    	}
	}

  	if (input->visible()) 	text_height = message_h + 25;
  	else 					text_height = message_h;

  	max_w = message_w + 10 + icon_size;
  	w     = button_w[0] + button_w[1] + button_w[2] - 10;

  	if(w > max_w) max_w = w;

  	message_w = max_w - 10 - icon_size;

  	w = max_w + 20;
  	h = max_h + 30 + text_height;

  	message_form->size(w, h);
  	message_form->size_range(w, h, w, h);

  	message->resize(20 + icon_size, 10, message_w, message_h);
  	icon->resize(10, 10, icon_size, icon_size);
  	icon->labelsize(icon_size - 10);
  	input->resize(20 + icon_size, 10 + message_h, message_w, 25);

  	for (x=w, i=0; i<3; i++)
	{
    	if(button_w[i])
    	{
			if(resize_buttons) 	
			{
      			x -= button_w[i];
				button[i]->resize(x, h - 10 - max_h, button_w[i] - 10, 20/*max_h*/);
			}
			
			else
			{
	      		x -= 100;
				button[i]->resize(x, h - 10 - max_h, 80 /*button_w[i]-10*/, 20/*max_h*/);
			}
		}
    }
}

std::string DIALOG_FORM::get_userinput()
{
	return input->value();
}

DIALOGS::DIALOGS()
{
}

void DIALOGS::resizebuttons_on() 
{
	resize_buttons = 1;
}

void DIALOGS::resizebuttons_off() 
{
	resize_buttons = 0;
}

void DIALOGS::hotspot_on()
{
	hotspot_flag = 1;
}

void DIALOGS::hotspot_off()
{
	hotspot_flag = 0;
}

void DIALOGS::form_title(std::string formlabel)
{
	form_label = formlabel;
}

void DIALOGS::form_color(Fl_Color formcolor, Fl_Boxtype formboxtype)
{
	form_bgcolor = formcolor; 
	form_boxtype = formboxtype;
}

void DIALOGS::icon_text(std::string icotext)
{
	icon_textflag = 1;
	icon_newtext  = icotext;
}

void DIALOGS::icon_file(std::string icofile, bool textflag)
{
	icon_logoflag = 1;
	logo = new Fl_XPM_Image(icofile.c_str());
	
	icon_textflag = textflag;
}

void DIALOGS::icon_image(Fl_Pixmap *Pixmap, bool textflag)
{
	icon_logoflag = 1;
	logo = Pixmap;
	
	icon_textflag = textflag;
}

void DIALOGS::icon_text(Fl_Font font, Fl_Fontsize size)
{
	icon_font = font; 
	icon_size = size; 
}

void DIALOGS::icon_color(Fl_Color font_color, Fl_Color bg_color)
{
	icon_textcolor = font_color; 
	icon_bgcolor   = bg_color; 
}

void DIALOGS::icon_style(Fl_Boxtype type)
{
	icon_boxtype = type;
}
	
void DIALOGS::input_text(Fl_Font font, Fl_Fontsize size)
{
	input_font = font; 
	input_size = size; 
}

void DIALOGS::input_color(Fl_Color font_color, Fl_Color bg_color)
{
	input_textcolor	= font_color;
	input_bgcolor	= bg_color;
}

void DIALOGS::input_style(Fl_Boxtype type)
{
	input_boxtype = type;
}

void DIALOGS::message_text(Fl_Font font, Fl_Fontsize size)
{
	message_font = font; 
	message_size = size; 
}

void DIALOGS::message_color(Fl_Color font_color, Fl_Color bg_color)
{
	message_textcolor = font_color;
	message_bgcolor	  = bg_color;
}

void DIALOGS::message_style(Fl_Boxtype type)
{
	message_boxtype	= type;
}

void DIALOGS::buttons_text(Fl_Font font, Fl_Fontsize size)
{
	buttons_font = font; 
	buttons_size = size; 
}

void DIALOGS::buttons_color(Fl_Color font_color, Fl_Color bg_color, Fl_Color down_color)
{
	buttons_textcolor	= font_color; 
	buttons_upcolor		= bg_color; 
	buttons_downcolor	= down_color; 
}

void DIALOGS::buttons_style(Fl_Boxtype type)
{
	buttons_boxtype	= type;
}

int DIALOGS::innards(const char* fmt, va_list ap, const char *b0, const char *b1, const char *b2)
{
  	Fl::pushed(0); // stop dragging (STR #2159)

  	avoidRecursion = 1;
	
	DIALOG_FORM *message_win = new DIALOG_FORM();
  
	if(icon_textflag)
	{
		if(icon_newtext.length() == 0)
			icon_newtext = icon_deftext;
	}
	else icon_newtext = "";

	message_win -> set_form(hotspot_flag, form_label, form_bgcolor, form_boxtype);
	message_win -> set_icon(icon_font, icon_size, icon_textcolor, icon_bgcolor, icon_boxtype, icon_textflag, icon_newtext.c_str(), icon_logoflag, logo); 
	message_win -> set_message(fmt, ap, message_font, message_size, message_textcolor, message_bgcolor, message_boxtype);
	message_win -> set_input(input_flag, input_defstr.c_str(), input_type, input_font, input_size, input_textcolor, input_bgcolor, input_boxtype);
	message_win -> set_buttons(b0, b1, b2, buttons_font, buttons_size, buttons_textcolor, buttons_upcolor, buttons_downcolor, buttons_boxtype);
  	message_win -> resizeform(adjust_size, resize_buttons);
  	message_win -> message_form->redraw();

	// deactivate Fl::grab(), because it is incompatible with modal windows
  	Fl_Window* g = Fl::grab();
  	if(g) Fl::grab(0);
  	Fl_Group *current_group = Fl_Group::current(); // make sure the dialog does not interfere with any active group
  	message_win->message_form->show();
  	Fl_Group::current(current_group);
	while( message_win->message_form->shown() ) Fl::wait();
	if(input_flag) input_defstr = message_win->get_userinput();
	if(g) Fl::grab(g); // regrab the previous popup menu, if there was one

  	avoidRecursion = 0;

  	return message_win->ret_val;
}

const char* DIALOGS::input_innards(const char* fmt, va_list ap, const char* defstr, uchar type) 
{
	input_type		= type;
	input_defstr	= defstr;

  	int r = innards(fmt, ap, fl_cancel, fl_ok, 0);
  	
	return r ? input_defstr.c_str() : 0;
}

void DIALOGS::message(const char *fmt, ...) 
{
    if(avoidRecursion) return;

    va_list ap;
    va_start(ap, fmt);
    icon_deftext = "i";
    innards(fmt, ap, 0, fl_close, 0);
    va_end(ap);
    icon_deftext = "?";
}

void DIALOGS::alert(const char *fmt, ...) 
{
  	if(avoidRecursion) return;

  	va_list ap;
  	va_start(ap, fmt);
  	icon_deftext = "!";
  	innards(fmt, ap, 0, fl_close, 0);
  	va_end(ap);
  	icon_deftext = "?";
}

int DIALOGS::choice(const char *fmt, const char *b0, const char *b1, const char *b2, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;
  	va_start(ap, b2);
  	int r = innards(fmt, ap, b0, b1, b2);
  	va_end(ap);
  
	return r;
}

int DIALOGS::choice_n(const char *fmt, const char *b0, const char *b1, const char *b2, ...) 
{
  	if (avoidRecursion) return -3;

  	va_list ap;
  	va_start(ap, b2);
  	int r = innards(fmt, ap, b0, b1, b2);
  	va_end(ap);
/*
  	if (win_closed != 0 && r == 0) return win_closed;
*/
  	return r;
}

const char* DIALOGS::input(const char *fmt, const char *defstr, ...) 
{
	input_flag = 1;
  	
	if (avoidRecursion) return 0;

  	va_list ap;  
	va_start(ap, defstr);
  	const char* r = input_innards(fmt, ap, defstr, FL_NORMAL_INPUT);
  	va_end(ap);
	
	input_flag = 0;
  
	return r;
}

const char* DIALOGS::password(const char *fmt, const char *defstr, ...) 
{
	input_flag = 1;

  	if (avoidRecursion) return 0;

  	va_list ap;
  	va_start(ap, defstr);
  	const char* r = input_innards(fmt, ap, defstr, FL_SECRET_INPUT);
  	va_end(ap);
  
	input_flag = 0;
	
	return r;
}

