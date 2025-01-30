CC=gcc
CFLAGS=-Wall -Wextra -g
OBJS=main.o paciente.o lista.o bd_paciente.o utils.o menu.o

all: healthsys

healthsys: $(OBJS)
	$(CC) $(OBJS) -o healthsys

main.o: main.c bd_paciente.h menu.h utils.h
	$(CC) $(CFLAGS) -c main.c

menu.o: menu.c menu.h bd_paciente.h utils.h
	$(CC) $(CFLAGS) -c menu.c

paciente.o: paciente.c paciente.h
	$(CC) $(CFLAGS) -c paciente.c

lista.o: lista.c lista.h paciente.h
	$(CC) $(CFLAGS) -c lista.c

bd_paciente.o: bd_paciente.c bd_paciente.h lista.h
	$(CC) $(CFLAGS) -c bd_paciente.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o healthsys