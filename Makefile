# Project: CommonTest

.SILENT:
.SUFFIXES: .cpp .c .o .h

SOURCES = 	CommonTest.cpp\
			JMairfoil.cpp\
			JMmath.cpp\
			JMbezier.cpp\
			JMbezierAirfoil.cpp\
			JMconvert.cpp\
			JMdiscretization.cpp\
			JMGnuPlotPipe.cpp\
			JMexternalExe.cpp\
			JMsubstitute.cpp\
			JMxfoil.cpp\
			JMfilter.cpp\
			itoa.cpp

OBJECTS = $(SOURCES:.cpp=.o)

#--------------------------  Static libraries  ----------------------------

DIRS_INC  = -I/local/include/
STAT_LIBS = -L. -L/usr/local/lib $(FLTK_LIBS) -lJMcommon
FLTK_LIBS = -lfltk -lfltk_forms -lfltk_gl -lfltk_images -lfltk_jpeg
#-lfltk_png  -lfltk_z

#-----------------------  system depend options  --------------------------

OSTYPE = $(shell uname -s)

ifeq ($(OSTYPE),Linux)
  SYSTEM   = -D_LINUX_ -DLinux -DLNX
  DYN_LIBS = -L/usr/X11R6/lib -lX11 -lXext -lXft -lXpm -ldl -lfontconfig -lXcursor -lXfixes -lXinerama -lXrender
  PIC      = -fPIC
  INSTALL_DIR = /usr/local/
else
  SYSTEM   = -DWIN32 -mwindows
  DYN_LIBS = -mwindows  -lole32 -luuid -lcomctl32 -lwsock32 -lsupc++ -lwinmm -lgdi32 -lm
  INSTALL_DIR = /local/
endif

#-------------------------------  Targets  --------------------------------

.PHONY: clean

all: libJMcommon.a CommonTest

.cpp.o:
	echo --- compilation: $*.cpp ...
	g++ -c $(PIC) -Wall -O2 $(DIRS_INC) $< -o $@

libJMcommon.a: $(OBJECTS)
	@echo --- make library: $@
	ar rcs $@ $(OBJECTS)

CommonTest: $(OBJECTS)
	@echo --- make: $@
	g++ -static-libgcc -static-libstdc++ -Wl,-Bstatic $(STAT_LIBS) -Wl,-Bdynamic $(DYN_LIBS) -o $@
	rm -f CommonTest.o
	
clean:
	rm -f *.o libJMcommon.a CommonTest CommonTest.exe 

install: 
	if [ -d $(INSTALL_DIR)include/JMcommon ]; then rm -r $(INSTALL_DIR)include/JMcommon; fi
	mkdir $(INSTALL_DIR)include/JMcommon
	cp -f *.h $(INSTALL_DIR)include/JMcommon
	cp -f libJMcommon.a $(INSTALL_DIR)lib/libJMcommon.a
