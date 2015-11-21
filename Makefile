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

DIRS_INC  = -I/usr/local/include
DIRS_LIB  = -L/usr/local/lib
FLTK_LIBS = -lfltk -lfltk_gl -lfltk_images -lfltk_png -lfltk_jpeg -lfltk_z /local/lib/libfltk.a

STAT_LIBS = $(DIRS_LIB) $(FLTK_LIBS)
DYN_LIBS  = -mwindows -lole32 -luuid -lcomctl32 -lstdc++ -lm -lglu32 -lopengl32

ifeq ($(shell uname -s),Linux)
	BIN  = CommonTest
else
	BIN  = CommonTest.exe
endif

.PHONY: clean

all: $(BIN)

.cpp.o:
	echo --- compilation: $*.cpp ...
	g++ -c -Wall -O2 $(DIRS_INC) $< -o $@
	
$(BIN): $(OBJECTS)
	@echo --- make: $@
	g++ $(OBJECTS) $(DIRS_INC) -static-libgcc -Wl,-Bstatic $(STAT_LIBS) -Bdynamic $(DYN_LIBS) -o $(BIN)
	rm -f CommonTest.o
	
clean:
	rm -f *.o CommonTest CommonTest.exe 
