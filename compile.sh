gcc -g -c person.c -I ./Serialization/
gcc -g -c app.c -I ./Serialization/
gcc -o exec app.o person.o -L ./Serialization/ -lserialize
