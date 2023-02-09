lib: commLib.c commLib.h
	gcc -g -c commLib.c -I./
	ar -ruv libcommLib.a commLib.o


server: server.c commLib.c commLib.h
	gcc -g -o server server.c -I./ -L./ -lcommLib -lpthread -lrt


client: client.c commLib.c commLib.h
	gcc -g -o client client.c -I./ -L./ -lcommLib -lpthread -lrt


clean:
	rm -f core.* *.o server client *.a

