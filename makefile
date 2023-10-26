# Variables
SRC = src
OBJ = obj
BIN = bin
INC = include

# Compiler
CC = gcc

#MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32
CLEAN=rm -f $(BIN)/* $(OBJ)/*.o
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=2
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(BIN)/robotarm $(OBJ)/*.o
endif

# Rules
$(BIN)/robotarm: $(OBJ)/robotarm.o
	$(CC) $(CFLG) -o $@ $^ $(LIBS)

$(OBJ)/robotarm.o: $(SRC)/robotarm.c
	$(CC) $(CFLG) -I$(INC) -c $< -o $@

# Clean
clean:
	$(CLEAN)
