# Robot Arm Project
# Created by Doncey Albin

EXE=final
SRC=src
OBJ=obj
INC=include

# Main target
all: $(EXE)

# Compiler
CC=gcc
CPP=g++

# Msys/MinGW
ifeq ($(OS),Windows_NT)
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=del /F /Q *.exe *.o *.a
else
# OSX
ifeq ($(shell uname),Darwin)
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
# Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
# OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) $(OBJ)/*.o $(OBJ)/*.a
endif

# Dependencies
DEPS = $(INC)/CSCIx229.h

# Compile rules
$(OBJ)/%.o: $(SRC)/%.c $(DEPS)
	@mkdir -p $(OBJ)
	$(CC) $(CFLG) -I$(INC) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(DEPS)
	@mkdir -p $(OBJ)
	$(CPP) $(CFLG) -I$(INC) -c $< -o $@

# Create archive
$(OBJ)/CSCIx229.a: $(OBJ)/print.o
	ar -rcs $@ $^

# Link
$(EXE): $(OBJ)/$(EXE).o $(OBJ)/CSCIx229.a
	$(CC) $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)
