CC=gcc
EXEC=solver
OBJS=main.o structure.o
CFLAGS=-std=c99 -lm -Wextra -Wall -pedantic -fopenmp

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
endif

$(EXEC) : ./obj/$(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
	@mv *.o ./obj

./obj/%.o : %.c
	@mkdir -p obj
	@$(CC) -c $(CFLAGS) $< -o $@

main.o : $(OBJS)

clean:
	rm -fr ./obj
clear:
	rm -fr $(EXEC)