# Robot Arm Project
# Created by Doncey Albin

EXE=viewLeg

# Main target
all: $(EXE)

# Compiler
CC=gcc
CPP=g++

# Compiler Flags and Libraries
# Update these flags and libraries according to your system and requirements
CFLG=-O3 -Wall
LIBS=-lGL -lGLU -lglut -lm # Standard OpenGL libraries for Linux/Unix
# For MacOS, you might need: -framework OpenGL -framework GLUT
# For Windows with MinGW: -lfreeglut -lglew32 -lglu32 -lopengl32 -lm

# Compile rules
# Assuming object files are to be placed in the same directory as source files
%.o: %.c
	$(CC) $(CFLG) -c $< -o $@

%.o: %.cpp
	$(CPP) $(CFLG) -c $< -o $@

# Linking the executable with OpenGL libraries
$(EXE): $(EXE).o viewLeg.o
	$(CC) $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	# Update this according to your system (e.g., 'rm -f' for Unix/Linux)
	# For Windows, it might be: del /F /Q *.exe *.o
