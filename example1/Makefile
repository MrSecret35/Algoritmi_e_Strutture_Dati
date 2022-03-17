CFLAGS= -g -O0 -I include -I Resources/C/Unity/

all: testoo sorted_array_app

clean:
	$(RM) testoo
	$(RM) sorted_array.o
	$(RM) sorted_array_app

sorted_array.o: src/sorted_array.c include/sorted_array.h
	$(CC) $(CFLAGS) -c src/sorted_array.c -o sorted_array.o

sorted_array_app: include/sorted_array.h sorted_array.o SortedArrayApp/sorted_array_app.c
	$(CC) $(CFLAGS) -o sorted_array_app sorted_array.o SortedArrayApp/sorted_array_app.c

testoo: test/sorted_array_test.c sorted_array.o include/sorted_array.h
	$(CC) $(CFLAGS) test/sorted_array_test.c sorted_array.o Resources/C/Unity/unity.c -o testoo