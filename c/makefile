default:
	echo no default action.  please specify build_exec, build_lib, clean
build_exec:
	gcc -o pack2d libpack2d.c pack2d.c
build_lib:
	gcc -c -fPIC libpack2d.c -o libpack2d.o
	gcc -shared -Wl,-soname,libpack2d.so.1 -o libpack2d.so libpack2d.o
	rm libpack2d.o
clean:
	rm -f pack2d
	rm -f libpack2d.so
