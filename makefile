# Makefile alterado.

CFLAGS = -Wall -g -mcmodel=large -march=native -mno-avx512f -O2 -Wshadow
OBJS = main.o ordenacao.o manipulaVetor.o deque.o# Todos os objetos
NAME = trab2grr20232364
CC = gcc# Compilador padrao
RM = rm -f

.PHONY: all clean

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(NAME)

