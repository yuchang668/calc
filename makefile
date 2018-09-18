TARGET = calc

$(TARGET): main.o calc.o stack.o
	$(CC) -o $(TARGET) main.o calc.o stack.o

main.o:main.c calc.h
	$(CC) -c main.c

calc.o:calc.c calc.h
	$(CC) -c calc.c

stack.o:stack.c stack.h
	$(CC) -c stack.c

clean:
	$(RM) $(TARGET) *.o
