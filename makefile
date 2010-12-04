CC=g++
CFLAGS=-c
INCLUDES=-I"C:\MinGW\freeglut\include"
LDFLAGS=-L"C:\MinGW\freeglut\lib"
SOURCES=main.cpp mglLine.cpp mglPrimitiveGroup.cpp mgl_util.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lfreeglut -lopengl32 -lglu32 -W1,subsystem,windows

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDES)
clean:
	rm -f *.o *~
	rm main.exe
