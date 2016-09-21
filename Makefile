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

STAT_LIBS = -L. -L/usr/local/lib $(FLTK_LIBS) -lJMcommon
FLTK_LIBS = -lfltk_forms -lfltk -lfltk_gl -lfltk_images -lfltk_png -lfltk_jpeg -lfltk_z

#-----------------------  system depend options  --------------------------

OSTYPE = $(shell uname -s)

ifeq ($(OSTYPE),Linux)
  SYSTEM   = -D_LINUX_ -DLinux -DLNX
  DYN_LIBS = -L/usr/X11R6/lib -lX11 -lXext -lXft -lXpm -ldl -lfontconfig -lXcursor -lXfixes -lXinerama
else
  SYSTEM   = -DWIN32 -mwindows
  DYN_LIBS = -mwindows  -lole32 -luuid -lcomctl32 -lwsock32 -lsupc++ -lwinmm -lgdi32 -lm
endif

.PHONY: clean

all: libJMcommon.a CommonTest

.cpp.o:
	echo --- compilation: $*.cpp ...
	g++ -c -Wall -O2 -I/usr/local/include $< -o $@

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
	@echo --- make: $@
	cp -f *.h /usr/local/include
	cp -f libJMcommon.a /usr/local/lib/libJMcommon.a
