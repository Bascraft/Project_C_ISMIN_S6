CC		:= gcc
CFLAGS	:=  -g  -lm
LDFLAGS := `sdl-config --libs --cflags`



SDL_base.o : SDL_base.c SDL_base.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c SDL_base.c 
	
SDL_env.o : SDL_env.c SDL_env.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c SDL_env.c

main.o : main.c 
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.c

$(EXECUTABLE) : SDL_env.o SDL_base.o blockchain.o main.o
	$(CC) SDL_env.o SDL_base.o blockchain.o main.o $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE)