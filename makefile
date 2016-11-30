.PHONY: all clean 
all : selectserver selectclient
clean :
	rm -rf bin/
selectserver: selectserver.c
	gcc selectserver.c -o bin/selectserver
selectclient: selectclient.c
	gcc selectclient.c -o bin/selectclient
