default:
	gcc -c -fPIC libpack2d.c -o libpack2d.o
	gcc -shared -Wl,-soname,libpack2d.so.1 -o libpack2d.so libpack2d.o
	rm libpack2d.o
clean:
	rm libpack2d.so
