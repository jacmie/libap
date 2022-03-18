#ifndef DIALOGS_H
#define DIALOGS_H

// Implementation of fl_message, fl_ask, fl_choice, fl_input etc.

#include <FL/fl_ask.H>

/*
#  ifdef __GNUC__
/ * the GNUC-specific attribute appearing below in prototypes with a variable list of arguments
 helps detection of mismatches between format string and argument list at compilation time * /
#    define __fl_attr(x) __attribute__ (x)
#  else
#    define __fl_attr(x)
#  endif // __GNUC__
*/

FL_EXPORT void JM_alert(const char *,...) __fl_attr((__format__ (__printf__, 1, 2)));
FL_EXPORT void JM_message(const char *,...) __fl_attr((__format__ (__printf__, 1, 2)));
FL_EXPORT int JM_choice(const char *q,const char *b0,const char *b1,const char *b2,...) __fl_attr((__format__ (__printf__, 1, 5)));
FL_EXPORT const char *JM_input(const char *label, const char *deflt = 0, ...) __fl_attr((__format__ (__printf__, 1, 3)));
FL_EXPORT const char *JM_password(const char *label, const char *deflt = 0, ...) __fl_attr((__format__ (__printf__, 1, 3)));
FL_EXPORT int JM_choice_n(const char *q,const char *b0,const char *b1,const char *b2,...) __fl_attr((__format__ (__printf__, 1, 5)));
/*
extern FL_EXPORT Fl_Font fl_message_font_;
extern FL_EXPORT Fl_Fontsize fl_message_size_;
inline void fl_message_font(Fl_Font f, Fl_Fontsize s) {fl_message_font_ = f; fl_message_size_ = s;}
*/
/*
// pointers you can use to change FLTK to a foreign language:
extern FL_EXPORT const char* fl_no;
extern FL_EXPORT const char* fl_yes;
extern FL_EXPORT const char* fl_ok;
extern FL_EXPORT const char* fl_cancel;
extern FL_EXPORT const char* fl_close;*/

#endif
