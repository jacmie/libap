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

#/local/lib/libfltk.a

FLTK_LIBS = -lfltk_forms -lfltk -lfltk_gl -lfltk_images -lfltk_png -lfltk_jpeg -lfltk_z
STAT_LIBS = -L/usr/local/lib $(FLTK_LIBS)

BIN  = CommonTest

#-------------------  Linker, options and libraries  ----------------------

#FLTK_LIBS = -L/usr/local/lib -lfltk_forms -lfltk -lfltk_images -lfltk_png -lfltk_jpeg -lfltk_z
#STAT_LIBS = $(FLTK_LIBS) 
#/usr/local/lib/libfltk.a
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

all: $(BIN)

.cpp.o:
	echo --- compilation: $*.cpp ...
	g++ -c -Wall -O2 -I/usr/local/include $< -o $@
	
$(BIN): $(OBJECTS)
	@echo --- make: $@
	g++ $(OBJECTS) -static-libgcc -static-libstdc++ -Wl,-Bstatic $(STAT_LIBS) -Wl,-Bdynamic $(DYN_LIBS) -o $(BIN)
#	g++ $(OBJS) -L./bin -static-libgcc -static-libstdc++ -Wl,-Bstatic $(STAT_LIBS) -Wl,-Bdynamic $(DYN_LIBS) -o ./bin/$(TARGET)	
	rm -f CommonTest.o
	
clean:
	rm -f *.o CommonTest CommonTest.exe 
