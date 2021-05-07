SRC = src/*.c
OBJS = *.o
COMP = gcc --std=c99
C Server : *.o
	$(COMP) -o "C Server" $(OBJS)
	rm $(OBJS)
$(OBJS) : $(SRC)
	$(COMP) -c $(SRC)
clean :
	rm *.o "C Server"
	clear
debug :
	$(COMP) -g3 -c $(SRC)
	$(COMP) -o CServer-debug -g3 $(OBJS)
	rm $(OBJS)