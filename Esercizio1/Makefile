CFLAGS= -g -O0 -I include -I Resources/C/Unity/

all: testoo sorting_G_app

clean:
	$(RM) testoo
	$(RM) sorting_G.o
	$(RM) sorting_G_app

sorting_G.o: src/sorting_G.c include/sorting_G.h
	$(CC) $(CFLAGS) -c src/sorting_G.c -o sorting_G.o

testoo: test/sorting_G_test.c sorting_G.o include/sorting_G.h
	$(CC) $(CFLAGS) test/sorting_G_test.c sorting_G.o Resources/C/Unity/unity.c -o testoo

sorting_G_app: sorting_G.o include/sorting_G.h Sorting_G_app/sorting_G_app.c
	$(CC) $(CFLAGS) Sorting_G_app/sorting_G_app.c sorting_G.o -o sorting_G_app

run: sorting_G_app
	./sorting_G_app records.csv
