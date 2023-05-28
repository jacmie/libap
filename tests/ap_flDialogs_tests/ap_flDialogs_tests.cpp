#include <gtest/gtest.h>

#include "ap_flDialogs.h"

#include <iostream>

#include <FL/Fl_Pixmap.H>
#include "./data/logo.h"
#include "./data/icon_res.h"

using namespace std;
using namespace ap;

TEST(ap_flDialogs_tests, dialogs) {
	DIALOGS dialog;

    dialog.alert("Alert ps!!!");
    dialog.alert("Alert %s_%i!!!", "Blab", 989);
    
	dialog.form_label("Kra_kra");
	dialog.message_box(FL_NO_BOX);
	dialog.message_color(FL_BLACK, 92);
	dialog.icon_image(&OM_logo);
    dialog.message("Hello World e 3e 3e3eeeeeeeeeeeeee3e3e3 %f 3e3 e3e3 e3e3e3e3eeee 3e3e3e3e\n3e3e3e3e3e3e 3e3eee3Hello World e 3e 3e3eeeeeeeeeeeeee3e3e3 3e3 e3e3 e3e3e3e3eeee 3e3e3e3e 3e3eee3!!!", 2.222222222);
	
	dialog.icon_label("?!?");
	dialog.icon_file("./data/FlowTree_40.xpm", 1);
    clog << dialog.choice_s("Simple %s/%s:", "Yes", "No") << endl;
	clog << dialog.choice("%s Asce3e3e %s e3e3e3e 3e 33e 3e3e3er2r2ttt 222       2r2r2r2rr2r2r  2r2r 2r2tt2t2?1?", "Cancel", "No", "Yes", "Terefere", "RERERE") << endl;
	
	dialog.icon_file("./data/IV_logo_gray_40.xpm");
    clog << dialog.input("Hello World e 3e 3e3eeeeeeeeeeeeee3e3e3 3e3 e3e3 e3e3e3e3eeee 3e3e3e3eee  3e3e3e3e3e3e 3e3eee3\n2r222r 22ty2t2t 2r r2r2r 22r2r 2 r2rr  2r22!!!", "BLAB") << endl; 
	
	dialog.form_color(FL_BLUE);
    clog << dialog.password("Hello World!!!", "BLOB") << endl;
}
