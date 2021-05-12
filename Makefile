SRC = src/*.c
OBJS = *.o
COMP = gcc -std=c99
debug : *.o
	$(COMP) -o debug -g3 $(OBJS)
	rm $(OBJS)
$(OBJS) : $(SRC)
	$(COMP) -c -g3 $(SRC)
clean :
	rm *.o CServer debug
	clear
production :
	$(COMP) -o2 -c $(SRC)
	$(COMP) -o CServer -o2 $(OBJS)
	rm $(OBJS)
run:
	make
	gdb -q ./debug