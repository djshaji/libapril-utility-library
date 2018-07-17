# libapril 1.0
# Heh :)

GTK_CFLAGS=`pkg-config gtk+-2.0 --cflags`
GTK_LIBS=`pkg-config gtk+-2.0 --libs`

ESD_CFLAGS=`esd-config --cflags`
ESD_LIBS=`esd-config --libs`

libapril:
	cc -c -g -fPIC -w -DXTHREADS -D_REENTRANT -DXUSE_MTSAFE_API april.c $(GTK_CFLAGS) $(ESD_CFLAGS)
	cc -shared -Wl,-soname,libapril.so.1 -o libapril.so.1.1.0 -w april.o $(GTK_LIBS) $(ESD_LIBS)
	ln -vs libapril.so.1.1.0 libapril.so.1.1
	ln -vs libapril.so.1.1.0 libapril.so.1
	ln -vs libapril.so.1.1.0 libapril.so
	
install:
	install *.so* /usr/lib/
	if ! test -e /usr/include/april ; then mkdir /usr/include/april ; fi
	install *.h /usr/include/april/
	install libapril-config /usr/bin/

clean:
	rm -v libapril.so*
	rm -v april.o
