CFLAGS =  -O3 -Dmain=SDL_main
LDFLAGS = -lm -lmingw32 -lSDL2main -lSDL2
SDL2_INCLUDE_DIR =C:\Users\patri\Desktop\TP_methodo\Tp_methodo_Durham_Beluche\SDL2\include
SDL2_LIBRARIES_DIR =C:\Users\patri\Desktop\TP_methodo\Tp_methodo_Durham_Beluche\SDL2\lib

INC = sdl2-light.h texture_data.h
SRC = main.c sdl2-light.c world_data.c texture_data.c
OBJ = $(SRC:%.c=%.o)

PROG = spacebattle.exe

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<  -I $(SDL2_INCLUDE_DIR)

$(PROG): $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@ -L $(SDL2_LIBRARIES_DIR)

doc: $(PROG)
	doxygen $(PROG)

.PHONY: clean
clean:
	del /f /q *.o *~ $(PROG)
	rd /s /q latex html
