gcc -g -c person.c -I ./Serialization/
gcc -g -c server.c -I ./Serialization/
gcc -g -c client.c -I ./Serialization/
gcc -o server server.o person.o -L ./Serialization/ -lserialize
gcc -o client client.o person.o -L ./Serialization/ -lserialize
