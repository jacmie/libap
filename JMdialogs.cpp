#include "JMdialogs.h"

#include <iostream>

using namespace std;

void DIALOG_FORM::button_cb_i(Fl_Button*, void *) 
{
	clog << "b 0" << endl;
  	//ret_val = (long)v;
	clog << "b 1" << endl;
  	//win_closed = 0;
	clog << "b 2" << endl;
	clog << &message_form << "\t" << message_form << endl;
  	message_form->hide();
	clog << "b 3" << endl;
}

void DIALOG_FORM::button_cb(Fl_Button *o, void *v)
{
	clog << o << "\t" << v << endl;
  	clog << ((DIALOG_FORM*)(o->parent()->user_data())) << endl;
  	//clog << ((DIALOG_FORM*)(o->parent()->user_data()))->button[0] << endl;
  	clog << ((DIALOG_FORM*)(o->parent()->user_data()))->message_form << endl;
  	((DIALOG_FORM*)(o->parent()->user_data()))->button_cb_i(o,v);
}

void DIALOG_FORM::window_cb_i(Fl_Widget *, void *) 
{
	clog << "w 0" << endl;
  //	ret_val = 0;
	clog << "w 1" << endl;
  	
	if ((Fl::event() == FL_KEYBOARD || Fl::event() == FL_SHORTCUT) && (Fl::event_key() == FL_Escape))	win_closed = -1;
  	else																								win_closed = -2;
	
	clog << "w 2" << endl;
	message_form->hide();
	clog << "w 3" << endl;
}

void DIALOG_FORM::window_cb(Fl_Widget *o, void *v) 
{
  	((DIALOG_FORM*)(o->parent()->user_data()))->window_cb_i(o,v);
}

DIALOG_FORM::DIALOG_FORM() 
{
  { 
 	// make sure that the dialog does not become the child of some
 	// current group
 	Fl_Group *previously_current_group = Fl_Group::current();
 	Fl_Group::current(0);
 
	// create a new top level window
 	message_form = new Fl_Window(410, 103);
 	message_form->user_data((void*)(this));
	//message_form->box(FL_THIN_UP_BOX);
	message_form->callback((Fl_Callback*)window_cb);
 	
	message = new Fl_Box(65, 25, 335, 20);
	message->box(FL_THIN_UP_BOX);
	message->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
 	
	input = new Fl_Input(65, 37, 335, 23);
	input->box(FL_THIN_DOWN_BOX);
	input->textsize(fl_message_size_);
	input->hide();
 	
	icon = new Fl_Box(10, 10, 50, 50);
  	icon->box(FL_THIN_UP_BOX);
  	icon->labelfont(FL_TIMES_BOLD);
  	icon->labelsize(34);
  	icon->color(FL_WHITE);
  	icon->labelcolor(FL_BLUE);

 	message_form->end(); // don't add the buttons automatically
 
	// create the buttons (right to left)
 	
   	for (int b=0, x=310; b<3; b++, x-=100) 
	{
    	//if (b==1)	button[b] = new Fl_Return_Button(x, 70, 80, 20);
    	/*else*/	button[b] = new Fl_Button(x, 70, 80, 20);
    	
		button[b]->box(FL_GLEAM_THIN_UP_BOX);
		button[b]->labelsize(fl_message_size_);
		button[b]->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
    	button[b]->callback((Fl_Callback*)button_cb);
   	}

 	// add the buttons (left to right)
 	{
   		for (int b=2; b>=0; b--)
     		message_form->add(button[b]);
 	}

 	message_form->begin();
 	//message_form->resizable(new Fl_Box(65, 10, 110-65, 27));
 	message_form->end();
 	message_form->set_modal();

	Fl_Group::current(previously_current_group);
  }

  //--- Initialize ---
}

void DIALOG_FORM::set_message(const char* fmt, va_list ap, Fl_Font font, Fl_Fontsize size, Fl_Color color) 
{
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

  	message->labelfont(font);
  	message->labelsize(size);
  	message->labelcolor(color);
}

void DIALOG_FORM::set_buttons(const char *b0, const char *b1, const char *b2, Fl_Font font, Fl_Fontsize size, Fl_Color color, Fl_Boxtype boxtype) 
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

	for (int b=0; b<3; b++) 
	{
  		button[b]->labelfont(font);
  		button[b]->labelsize(size);
  		button[b]->labelcolor(color);
		button[b]->box(boxtype);
   	}
}

void DIALOG_FORM::show() 
{
	message_form->show();	
}

Fl_Window* DIALOGS::makeform() 
{
 	/*if (message_form) return message_form;

 	// make sure that the dialog does not become the child of some
 	// current group
 	Fl_Group *previously_current_group = Fl_Group::current();
 	Fl_Group::current(0);
 
	// create a new top level window
 	/// *Fl_Window *w =* / message_form = new Fl_Window(410, 103);
  	//message_form->size(410, 103);
 	//message_form->box(FL_THIN_UP_BOX);
	//message_form->callback((Fl_Callback*)window_cb);
 	
	//message = new Fl_Box(65, 25, 335, 20);
	//message->box(FL_THIN_UP_BOX);
	message->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
 	
	//input = new Fl_Input(65, 37, 335, 23);
	input->box(FL_THIN_DOWN_BOX);
	input->textsize(fl_message_size_);
	input->hide();
 	
	{
		//Fl_Box* o = icon = new Fl_Box(10, 10, 50, 50);
  		icon->box(FL_THIN_UP_BOX);
  		icon->labelfont(FL_TIMES_BOLD);
  		icon->labelsize(34);
  		icon->color(FL_WHITE);
  		icon->labelcolor(FL_BLUE);
 	}

 	message_form->end(); // don't add the buttons automatically
 
	// create the buttons (right to left)
 	{
   		for (int b=0, x=310; b<3; b++, x-=100) 
		{
     		//if (b==1)	button[b] = new Fl_Return_Button(x, 70, 80, 20);
//     		/ *else* /	button[b] = new Fl_Button(x, 70, 80, 20);
     		
			button[b]->box(FL_GLEAM_THIN_UP_BOX);
			button[b]->labelsize(fl_message_size_);
			button[b]->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
     		//button[b]->callback((Fl_Callback*)button_cb, &b);
   		}
 	}

 	// add the buttons (left to right)
 	{
   		for (int b=2; b>=0; b--)
     		message_form->add(button[b]);
 	}

 	message_form->begin();
 	//message_form->resizable(new Fl_Box(70, 10, 110-70, 27));
 	message_form->end();
 	message_form->set_modal();

	Fl_Group::current(previously_current_group);
 
  	message_form->size(410, 103);

	return message_form;*/
}

void DIALOGS::resizeform() 
{
  	int	i;
  	int	message_w, message_h;
  	int	text_height;
  	int	button_w[3], button_h[3];
  	int	x, w, h, max_w, max_h=20;
	const int icon_size = 50;

  	//message_form->size(410, 103);

  	//fl_font(message->labelfont(), message->labelsize());
 // 	message_w = message_h = 0;
 // 	fl_measure(message->label(), message_w, message_h);
/*
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
			/ *
      		if (i == 1) button_w[1] += 20;

      		button_w[i] += 30;
      		button_h[i] += 10;

      		if (button_h[i] > max_h) max_h = button_h[i];* /
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
      		button[i]->resize(x, h - 10 - max_h, 80 / *button_w[i]-10* /, 20/ *max_h* /);

			//printf("button %d (%s) is %dx%d+%d,%d\n", i, button[i]->label(),
			//button[i]->w(), button[i]->h(),
			//button[i]->x(), button[i]->y());
		}
    }*/
}

int DIALOGS::innards(const char* fmt, va_list ap, const char *b0, const char *b1, const char *b2)
{
  	Fl::pushed(0); // stop dragging (STR #2159)

  	avoidRecursion = 1;
 	
//	Fl_Window *message_form;
/*	Fl_Box *message;
	Fl_Box *icon;
	Fl_Button *button[3];
	Fl_Input *input;
*/	
	// make sure that the dialog does not become the child of some
 	// current group
 	Fl_Group *previously_current_group = Fl_Group::current();
 	Fl_Group::current(0);
 
	// create a new top level window
 	//Fl_Window *message_form = new Fl_Window(410, 103);
	
	/*DIALOG_FORM */message_win = new DIALOG_FORM();
  	
	//message_form->size(410, 103);
 	//message_form->box(FL_THIN_UP_BOX);
	//message_form->callback((Fl_Callback*)window_cb);
 	/*
	message = new Fl_Box(65, 25, 335, 20);
	//message->box(FL_THIN_UP_BOX);
	message->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
 	
	input = new Fl_Input(65, 37, 335, 23);
	input->box(FL_THIN_DOWN_BOX);
	input->textsize(fl_message_size_);
	input->hide();
 	
	{
		//Fl_Box* o = icon = new Fl_Box(10, 10, 50, 50);
  		icon->box(FL_THIN_UP_BOX);
  		icon->labelfont(FL_TIMES_BOLD);
  		icon->labelsize(34);
  		icon->color(FL_WHITE);
  		icon->labelcolor(FL_BLUE);
 	}

 	message_form->end(); // don't add the buttons automatically
 
	// create the buttons (right to left)
 	{
   		for (int b=0, x=310; b<3; b++, x-=100) 
		{
     		//if (b==1)	button[b] = new Fl_Return_Button(x, 70, 80, 20);
     		/*else* /	button[b] = new Fl_Button(x, 70, 80, 20);
     		
			button[b]->box(FL_GLEAM_THIN_UP_BOX);
			button[b]->labelsize(fl_message_size_);
			button[b]->align(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
     		//button[b]->callback((Fl_Callback*)button_cb, &b);
   		}
 	}

 	// add the buttons (left to right)
 	{
   		for (int b=2; b>=0; b--)
     		message_form->add(button[b]);
 	}

 	message_form->begin();
 	message_form->resizable(new Fl_Box(70, 10, 110-70, 27));
 	message_form->end();
 	message_form->set_modal();

	Fl_Group::current(previously_current_group);
*/ 
  	//message_form->size(410, 103);
/*
 	/ *Fl_Window *w =* / message_form = new Fl_Window(410, 103);
	message = new Fl_Box(65, 25, 335, 20);
   		
	icon = new Fl_Box(10, 10, 50, 50);
	input = new Fl_Input(65, 37, 335, 23);
 	message_form->resizable(new Fl_Box(70, 10, 110-70, 27));

	for (int b=0, x=310; b<3; b++, x-=100) 
	{
     		//if (b==1)	button[b] = new Fl_Return_Button(x, 70, 80, 20);
     		/ *else* /	button[b] = new Fl_Button(x, 70, 80, 20);
	}

	clog << &message_form << endl;
  	message_form = makeform();
	clog << &message_form << endl;*/
  	/*message_form->size(410, 103);
	clog << &message_form << endl;
	*/
 	
	/*char buffer[1024];
  
	if (!strcmp(fmt,"%s")) 
	{
    	message->label(va_arg(ap, const char*));
  	} 

	else 
	{
    	::vsnprintf(buffer, 1024, fmt, ap);
    	message->label(buffer);
  	}

  	message->labelfont(fl_message_font_);*/
	
	message_win -> set_message(fmt, ap, message_font, message_size, message_textcolor);
	/*
	if (fl_message_size_ == -1) message->labelsize(FL_NORMAL_SIZE);
  	else						message->labelsize(fl_message_size_);
  
	if (b0) {button[0]->show(); button[0]->label(b0); button[1]->position(210, 70);}
  	else {button[0]->hide(); button[1]->position(310, 70);}
  
	if (b1) {button[1]->show(); button[1]->label(b1);}
  	else button[1]->hide();
  
	if (b2) {button[2]->show(); button[2]->label(b2);}
  	else button[2]->hide();
	*/
	message_win -> set_buttons(b0, b1, b2, buttons_font, buttons_size, buttons_textcolor, buttons_boxtype);
/*  
	const char* prev_icon_label = icon->label();
  	
	if (!prev_icon_label) icon->label(iconlabel);

  	resizeform();*/
/*
  	if (button[1]->visible() && !input->visible())	button[1]->take_focus();
  	if (enableHotspot)								message_form->hotspot(button[0]);
  	if (b0 && Fl_Widget::label_shortcut(b0))		button[0]->shortcut(0);

  	// set default window title, if defined and a specific title is not set
  	if (!message_form->label() && message_title_default)
    	message_form->label(message_title_default);
*/
  	// deactivate Fl::grab(), because it is incompatible with modal windows
  	Fl_Window* g = Fl::grab();
  	if (g) Fl::grab(0);
  	Fl_Group *current_group = Fl_Group::current(); // make sure the dialog does not interfere with any active group
  	//message_form->show();
  	//message_win->message_form->show();
  	message_win->show();
  	Fl_Group::current(current_group);
	clog << "0 innard" << endl;
	clog << message_win->message_form << endl;
	clog << message_win->button[0] << endl;
	clog << message_win->button[1] << endl;
	clog << message_win->button[2] << endl << endl;
  	
	while( message_win->message_form->shown() ) 
	{
		Fl::wait();
	}

  	//message_win->message_form->hide();
	
	clog << "1 innard" << endl;
	if(g) Fl::grab(g); // regrab the previous popup menu, if there was one
//  	icon->label(prev_icon_label);
//  	message_form->label(0); // reset window title
	clog << "2 innard" << endl;

  	avoidRecursion = 0;

	clog << "END innard" << endl;

  	return message_win->ret_val;
}

const char* DIALOGS::input_innards(const char* fmt, va_list ap, const char* defstr, uchar type) 
{
  	/*makeform();
  	message_form->size(410, 103);
  	message->position(65, 10);
  	input->type(type);
  	input->show();
  	input->value(defstr);
  	input->take_focus();

  	int r = innards(fmt, ap, fl_cancel, fl_ok, 0);
  	input->hide();
  	message->position(65,25);
  	return r ? input->value() : 0;*/
}

void DIALOGS::JM_message(const char *fmt, ...) 
{
    if(avoidRecursion) return;

    va_list ap;
    va_start(ap, fmt);
    iconlabel = "i";
    innards(fmt, ap, 0, fl_close, 0);
    va_end(ap);
    iconlabel = "?";
}

void DIALOGS::JM_alert(const char *fmt, ...) 
{
  	if(avoidRecursion) return;

  	va_list ap;
  	va_start(ap, fmt);
  	iconlabel = "!";
  	innards(fmt, ap, 0, fl_close, 0);
  	va_end(ap);
  	iconlabel = "?";
}

int DIALOGS::JM_choice(const char *fmt, const char *b0, const char *b1, const char *b2, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;
  	va_start(ap, b2);
  	int r = innards(fmt, ap, b0, b1, b2);
  	va_end(ap);
  
	return r;
}

int DIALOGS::JM_choice_n(const char *fmt, const char *b0, const char *b1, const char *b2, ...) 
{
  	if (avoidRecursion) return -3;
/*
  	va_list ap;
  	va_start(ap, b2);
  	int r = innards(fmt, ap, b0, b1, b2);
  	va_end(ap);

  	if (win_closed != 0 && r == 0) return win_closed;
*/
  	return 0;//r;
}

const char* DIALOGS::JM_input(const char *fmt, const char *defstr, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;  
	va_start(ap, defstr);
  	const char* r = input_innards(fmt, ap, defstr, FL_NORMAL_INPUT);
  	va_end(ap);
  
	return r;
}

const char* DIALOGS::JM_password(const char *fmt, const char *defstr, ...) 
{
  	if (avoidRecursion) return 0;

  	va_list ap;
  	va_start(ap, defstr);
  	const char* r = input_innards(fmt, ap, defstr, FL_SECRET_INPUT);
  	va_end(ap);
  
	return r;
}

