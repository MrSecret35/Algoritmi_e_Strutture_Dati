CFLAGS= -g -O0 -I include -I Resources/C/Unity/

all:app

clean:
	$(RM) hashMap.o
	$(RM) testo
	$(RM) app

hashMap: include/hashMap.h src/hashMap.c
	$(CC) $(CFLAGS) -c src/hashMap.c -o hashMap.o

test:hashMap test/HashMap_test.c
	$(CC) $(CFLAGS) test/HashMap_test.c hashMap.o Resources/C/Unity/unity.c -o testo


app: hashMap 
	$(CC) $(CFLAGS) application/map_app.c hashMap.o -o app

runTest: test
	./testo

run: app
	./app hashes.csv