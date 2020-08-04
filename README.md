Steps:
1.Run compile.sh file present inside Deserialization/
2. Run compile.sh present in RPC/ folder.
3. Execute ./server and ./client in 2 different terminals. First server then client.

# RPC
Build remote procedure calls from scratch using C language.

Data serialization : 
Mechanism to transform the internal data structures into a form that could be sent to remote machine.

Data de-serialization : 
Mechanism to transform the flat serialized data and reconstruct into original data structure form.
It helps in exchanging data b/w different processes running on heterogenous machines independent of OS,compiler,language and hardware architecture.

Note: 
1. While serializing the data structures, padding bytes are not captured in the serialized form.
2. Also note that for data structures having member vairables as pointer to another data struture, actual data pointed by pointer is copied instead of memory address while serializing the data.
3. Null pointers are serialized in the form of sentinel value(0xFFFFFFFF 4B). While deserializing the data, sentinal values are treated as NULL data.

