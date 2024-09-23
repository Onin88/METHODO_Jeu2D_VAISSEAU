CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h texture_data.h
SRC = main.c sdl2-light.c texture_data.c world_data.c
OBJ = $(SRC:%.c=%.o)

PROG = spacebattle

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html

