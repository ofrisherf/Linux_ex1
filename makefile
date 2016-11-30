all : select
clean :
	rm -rf selectclient selectserver
select: selectclient selectserver
selectserver: selectserver.c
	gcc -c selectserver.c -o selectserver
selectclient: selectclient.c
	gcc -c selectclient.c -o selectclient
