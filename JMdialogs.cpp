#include "JMdialogs.h"

#include <stdarg.h>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>

static Fl_Window *message_form;
static Fl_Box *message;
static Fl_Box *icon;
static Fl_Button *button[3];
static Fl_Input *input;
static int ret_val;     // button return value: 0, 1, 2
static int win_closed;  // window close flag (-1 = Escape, -2 = close button)
static const char *iconlabel = "?";
static const char *message_title_default;
//Fl_Font fl_message_font_ = FL_HELVETICA;
//Fl_Fontsize fl_message_size_ = -1;
static int enableHotspot = 1;

static char avoidRecursion = 0;

// Sets the global return value 'ret_val' according to the button
// that was pushed (0, 1, 2), sets the 'win_closed' flag = 0
// and hides the window.

static void button_cb(Fl_Widget *, long val) 
{
  	ret_val = (int)val;
  	win_closed = 0;
  	message_form->hide();
}

// Sets the global return value 'ret_val' = 0 (no button pushed) and
// sets the 'win_closed' flag to -1 for Escape or -2 else (Close Button)
// and hides the window.

static void window_cb(Fl_Widget *, long val) 
{
  	ret_val = 0;
  	
	if ((Fl::event() == FL_KEYBOARD || Fl::event() == FL_SHORTCUT) && (Fl::event_key() == FL_Escape))	win_closed = -1;
  	else																								win_closed = -2;
	
	message_form->hide();
}

static Fl_Window *makeform() 
{
 	if (message_form) return message_form;

 	// make sure that the dialog does not become the child of some
 	// current group
 	Fl_Group *previously_current_group = Fl_Group::current();
 	Fl_Group::current(0);
 
	// create a new top level window
 	Fl_Window *w = message_form = new Fl_Window(410, 103);
 	//message_form->box(FL_THIN_UP_BOX);
	message_form->callback(window_cb);
 	
	message = new Fl_Box(65, 25, 335, 20);
	message->box(FL_THIN_UP_BOX);
	message->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
 	
	input = new Fl_Input(65, 37, 335, 23);
	input->box(FL_THIN_DOWN_BOX);
	input->textsize(fl_message_size_);
	input->hide();
 	
	{
		Fl_Box* o = icon = new Fl_Box(10, 10, 50, 50);
  		o->box(FL_THIN_UP_BOX);
  		o->labelfont(FL_TIMES_BOLD);
  		o->labelsize(34);
  		o->color(FL_WHITE);
  		o->labelcolor(FL_BLUE);
 	}

 	w->end(); // don't add the buttons automatically
 
	// create the buttons (right to left)
 	{
   		for (int b=0, x=310; b<3; b++, x-=100) 
		{
     		//if (b==1)	button[b] = new Fl_Return_Button(x, 70, 80, 20);
     		/*else*/	button[b] = new Fl_Button(x, 70, 80, 20);
     		
			button[b]->box(FL_GLEAM_THIN_UP_BOX);
			button[b]->labelsize(fl_message_size_);
			button[b]->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
     		button[b]->callback(button_cb, b);
   		}
 	}

 	// add the buttons (left to right)
 	{
   		for (int b=2; b>=0; b--)
     		w->add(button[b]);
 	}

 	w->begin();
 	w->resizable(new Fl_Box(70, 10, 110-70, 27));
 	w->end();
 	w->set_modal();

	Fl_Group::current(previously_current_group);
 
	return w;
}

static void resizeform() 
{
  	int	i;
  	int	message_w, message_h;
  	int	text_height;
  	int	button_w[3], button_h[3];
  	int	x, w, h, max_w, max_h=20;
	const int icon_size = 50;

  	message_form->size(410, 103);

  	fl_font(message->labelfont(), message->labelsize());
  	message_w = message_h = 0;
  	fl_measure(message->label(), message_w, message_h);

  	message_w += 10;
  	message_h += 10;
  
	if (message_w < 340)	message_w = 340;
	if (message_h < 30)		message_h = 30;

  	fl_font(button[0]->labelfont(), button[0]->labelsize());

  	memset(button_w, 0, sizeof(button_w));
  	memset(button_h, 0, sizeof(button_h));

  	for(max_h=25, i=0; i<3; i ++)
	{
    	if(button[i]->visible())
    	{
      		fl_measure(button[i]->label(), button_w[i], button_h[i]);
			/*
      		if (i == 1) button_w[1] += 20;

      		button_w[i] += 30;
      		button_h[i] += 10;

      		if (button_h[i] > max_h) max_h = button_h[i];*/
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
      		x -= 100;//button_w[i];
      		//button[i]->resize(x, h - 10 - max_h, button_w[i] - 10, max_h);
      		button[i]->resize(x, h - 10 - max_h, 80 /*button_w[i]-10*/, 20/*max_h*/);

			//printf("button %d (%s) is %dx%d+%d,%d\n", i, button[i]->label(),
			//button[i]->w(), button[i]->h(),
			//button[i]->x(), button[i]->y());
		}
    }
}

static int innards(const char* fmt, va_list ap, const char *b0, const char *b1, const char *b2)
{
  	Fl::pushed(0); // stop dragging (STR #2159)

  	avoidRecursion = 1;

  	makeform();
  	message_form->size(410, 103);

  	char buffer[1024];
  
	if (!strcmp(fmt,"%s")) 
	{
    	message->label(va_arg(ap, const char*));
  	} 
	else 
	{
    	::vsnprintf(buffer, 1024, fmt, ap);
    	message->label(buffer);
  	}

  	message->labelfont(fl_message_font_);
  
	if (fl_message_size_ == -1) message->labelsize(FL_NORMAL_SIZE);
  	else						message->labelsize(fl_message_size_);
  
	if (b0) {button[0]->show(); button[0]->label(b0); button[1]->position(210, 70);}
  	else {button[0]->hide(); button[1]->position(310, 70);}
  
	if (b1) {button[1]->show(); button[1]->label(b1);}
  	else button[1]->hide();
  
	if (b2) {button[2]->show(); button[2]->label(b2);}
  	else button[2]->hide();
  
	const char* prev_icon_label = icon->label();
  	
	if (!prev_icon_label) icon->label(iconlabel);

  	resizeform();

  	if (button[1]->visible() && !input->visible())	button[1]->take_focus();
  	if (enableHotspot)								message_form->hotspot(button[0]);
  	if (b0 && Fl_Widget::label_shortcut(b0))		button[0]->shortcut(0);

  	// set default window title, if defined and a specific title is not set
  	if (!message_form->label() && message_title_default)
    	message_form->label(message_title_default);

  	// deactivate Fl::grab(), because it is incompatible with modal windows
  	Fl_Window* g = Fl::grab();
  	if (g) Fl::grab(0);
  	Fl_Group *current_group = Fl_Group::current(); // make sure the dialog does not interfere with any active group
  	message_form->show();
  	Fl_Group::current(current_group);
  	while (message_form->shown()) Fl::wait();
  	if (g) Fl::grab(g); // regrab the previous popup menu, if there was one
  	icon->label(prev_icon_label);
  	message_form->label(0); // reset window title

  	avoidRecursion = 0;
  	return ret_val;
}

static const char* input_innards(const char* fmt, va_list ap, const char* defstr, uchar type) 
{
  	makeform();
  	message_form->size(410, 103);
  	message->position(65, 10);
  	input->type(type);
  	input->show();
  	input->value(defstr);
  	input->take_focus();

  	int r = innards(fmt, ap, fl_cancel, fl_ok, 0);
  	input->hide();
  	message->position(65,25);
  	return r ? input->value() : 0;
}

void JM_message(const char *fmt, ...) 
{
    if(avoidRecursion) return;

    va_list ap;
    va_start(ap, fmt);
    iconlabel = "i";
    innards(fmt, ap, 0, fl_close, 0);
    va_end(ap);
    iconlabel = "?";
}

void JM_alert(const char *fmt, ...) 
{
  	if(avoidRecursion) return;

  	va_list ap;
  	va_start(ap, fmt);
  	iconlabel = "!";
  	innards(fmt, ap, 0, fl_close, 0);
  	va_end(ap);
  	iconlabel = "?";
}

int JM_choice(const char *fmt, const char *b0, const char *b1, const char *b2, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;
  	va_start(ap, b2);
  	int r = innards(fmt, ap, b0, b1, b2);
  	va_end(ap);
  
	return r;
}

int JM_choice_n(const char *fmt, const char *b0, const char *b1, const char *b2, ...) 
{
  	if (avoidRecursion) return -3;

  	va_list ap;
  	va_start(ap, b2);
  	int r = innards(fmt, ap, b0, b1, b2);
  	va_end(ap);

  	if (win_closed != 0 && r == 0) return win_closed;

  	return r;
}

const char* JM_input(const char *fmt, const char *defstr, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;  
	va_start(ap, defstr);
  	const char* r = input_innards(fmt, ap, defstr, FL_NORMAL_INPUT);
  	va_end(ap);
  
	return r;
}

const char *JM_password(const char *fmt, const char *defstr, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;
  	va_start(ap, defstr);
  	const char* r = input_innards(fmt, ap, defstr, FL_SECRET_INPUT);
  	va_end(ap);
  
	return r;
}

