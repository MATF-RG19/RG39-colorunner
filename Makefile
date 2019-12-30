CC = gcc
PROGRAM = colorunner
CFLAGS  = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o timer.o logika_igre.o staza.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^ $(LDLIBS)
	
main.o: main.c
	$(CC) $(CFLAGS) -c $^
	
timer.o: timer.c
	$(CC) $(CFLAGS) -c $^  
logika_igre.o: logika_igre.c
	$(CC) $(CFLAGS) -c $^  
staza.o: staza.c
	$(CC) $(CFLAGS) -c $^  

clean:
	@rm -f *.o *~ *#
