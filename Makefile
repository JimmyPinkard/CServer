SRC = src/*.c
OBJS = *.o
COMP = gcc -std=c99
debug : $(OBJS)
	$(COMP) -o debug -g3 $(OBJS)
	rm $(OBJS)
$(OBJS) : $(SRC)
	$(COMP) -c -g3 $(SRC)
clean :
	rm *.o CServer debug
	clear
production :
	$(COMP) -O2 -c $(SRC)
	$(COMP) -o CServer -O2 $(OBJS)
	rm $(OBJS)
run:
	make
	./debug
run-debug:
	make
	gdb -q ./debug
