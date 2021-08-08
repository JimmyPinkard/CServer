SRC = src/*.c
OBJS = *.o
COMP = gcc -std=c99
BIN = CServer
$(BIN) : $(OBJS)
	$(COMP) -o $(BIN) -g3 $(OBJS)
	rm $(OBJS)
$(OBJS) : $(SRC)
	$(COMP) -c -g3 $(SRC)
clean :
	rm *.o $(BIN)
	clear
production :
	$(COMP) -O2 -c $(SRC)
	$(COMP) -o $(BIN) -O2 $(OBJS)
	rm $(OBJS)
run:
	make
	./$(BIN)
run-debug:
	make
	gdb -q ./$(BIN)
