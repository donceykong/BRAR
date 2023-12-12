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
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm -g
CLEAN=del /F /Q *.exe *.o *.a
else
# OSX
ifeq ($(shell uname),Darwin)
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
# Linux/Unix/Solaris
else
CFLG=-O0 -Wall -I/usr/include/freetype2 -g
LIBS=-lglut -lGLU -lGL -lm -lfreetype
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

# Create archive
$(OBJ)/CSCIx229.a: $(OBJ)/print.o $(OBJ)/projection.o
	ar -rcs $@ $^

$(OBJ)/keyHandler.a: $(OBJ)/keys.o
	ar -rcs $@ $^

$(OBJ)/matrixMath.a: $(OBJ)/matrixMath.o
	ar -rcs $@ $^

$(OBJ)/RRTStar.a: $(OBJ)/RRTStar.o
	ar -rcs $@ $^

$(OBJ)/screenInfo.a: $(OBJ)/screenInfo.o
	ar -rcs $@ $^

# Link
$(EXE): $(OBJ)/$(EXE).o $(OBJ)/CSCIx229.a $(OBJ)/keyHandler.a $(OBJ)/matrixMath.a $(OBJ)/RRTStar.a $(OBJ)/screenInfo.a
	$(CC) $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)
