cc `pkg-config --static --cflags libsodium libpq` -c -o $1.o $1.c
cc -static -o $1.cgi $1.o `pkg-config --static --libs libsodium libpq`

