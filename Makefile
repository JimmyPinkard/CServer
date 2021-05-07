SRC = src/*.c
OBJS = *.o
COMP = gcc -std=c99
C Server : *.o
	$(COMP) -o CServer $(OBJS)
	rm $(OBJS)
$(OBJS) : $(SRC)
	$(COMP) -c $(SRC)
clean :
	rm *.o CServer CServer-debug
	clear
debug :
	$(COMP) -g3 -c $(SRC)
	$(COMP) -o CServer-debug -g3 $(OBJS)
	rm $(OBJS)