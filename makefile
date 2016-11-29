all : select
clean :
	rm -rf selectclient.o selectserver.o
select: selectclient.o selectserver.o
	gcc selectclient.c -o selectclient.o
	gcc selectserver.c -o selectserver.o
selectserver.o: selectserver.c
selectclient.o: selectclient.c
	gcc -c selectserver.c -o selectserver.o
	gcc -c selectclient.c -o selectclient.o
