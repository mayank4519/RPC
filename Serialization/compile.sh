gcc -fPIC -g -c serialize.c
gcc -shared -o libserialize.a serialize.o
