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
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES) -Iinclude -I/opt/homebrew/Cellar/freetype/2.13.2/include/freetype2/
LIBS=-framework GLUT -framework OpenGL -L/opt/homebrew/Cellar/freetype/2.13.2/lib -lfreetype
# Linux/Unix/Solaris
else
CFLG=-O3 -Wall -I/usr/include/freetype2 -g
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

$(OBJ)/keys.a: $(OBJ)/keys.o
	ar -rcs $@ $^

$(OBJ)/matrixMath.a: $(OBJ)/matrixMath.o
	ar -rcs $@ $^

$(OBJ)/RRTStar.a: $(OBJ)/RRTStar.o
	ar -rcs $@ $^

$(OBJ)/screenInfo.a: $(OBJ)/screenInfo.o
	ar -rcs $@ $^

$(OBJ)/textureUtils.a: $(OBJ)/textureUtils.o
	ar -rcs $@ $^

$(OBJ)/draw.a: $(OBJ)/draw.o $(OBJ)/drawGround.o
	ar -rcs $@ $^

$(OBJ)/lighting.a: $(OBJ)/lighting.o
	ar -rcs $@ $^

$(OBJ)/robot.a: $(OBJ)/robotController.o $(OBJ)/robotDraw.o $(OBJ)/robotDrawArm.o $(OBJ)/robotDrawLegs.o $(OBJ)/robotStates.o
	ar -rcs $@ $^

$(OBJ)/views.a: $(OBJ)/views.o
	ar -rcs $@ $^

$(OBJ)/game.a: $(OBJ)/game.o
	ar -rcs $@ $^

$(OBJ)/mapManager.a: $(OBJ)/mapManager.o
	ar -rcs $@ $^

$(OBJ)/collision.a: $(OBJ)/collision.o
	ar -rcs $@ $^

$(OBJ)/controller.a: $(OBJ)/controller.o
	ar -rcs $@ $^

# Link
$(EXE): $(OBJ)/$(EXE).o $(OBJ)/CSCIx229.a $(OBJ)/keys.a $(OBJ)/matrixMath.a $(OBJ)/RRTStar.a $(OBJ)/screenInfo.a $(OBJ)/textureUtils.a $(OBJ)/draw.a $(OBJ)/lighting.a $(OBJ)/robot.a $(OBJ)/views.a $(OBJ)/game.a $(OBJ)/mapManager.a $(OBJ)/collision.a $(OBJ)/controller.a
	$(CC) $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)
