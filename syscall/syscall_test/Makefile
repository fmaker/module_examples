CC = gcc
OBJ = syscall_test.o
#C_INCLUDE_PATH = /root/linux-stable/include/

%.o: %.c 
	$(CC) -c -o $@ $<

syscall_test: $(OBJ)
	$(CC) -o $@ $^

