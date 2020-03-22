CC		:= gcc
CFLAGS	:= -g  -lm -lSDL_image
LDFLAGS := `sdl-config --libs --cflags`
BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
EXECUTABLE := main

all:$(BIN)/SDL_base.o $(BIN)/SDL_env.o $(BIN)/main.o $(BIN)/$(EXECUTABLE)

#$(BIN)/blockchain.o : $(LIB)/blockchain.c $(LIB)/blockchain.h
#	$(CC) $(CFLAGS) $(LDFLAGS) -c $(LIB)/blockchain.c 

$(BIN)/SDL_base.o : $(LIB)/SDL_base.c $(LIB)/SDL_base.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(LIB)/SDL_base.c 
	
$(BIN)/SDL_env.o : $(LIB)/SDL_env.c $(LIB)/SDL_env.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(LIB)/SDL_env.c

 $(BIN)/main.o : $(SRC)/main.c $(LIB)/SDL_env.h $(LIB)/SDL_base.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRC)/main.c

$(BIN)/$(EXECUTABLE) : $(BIN)/SDL_env.o $(BIN)/SDL_base.o $(BIN)/main.o
	$(CC) SDL_env.o SDL_base.o main.o $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE)