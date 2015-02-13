
# Compiler

CC = g++

# Flags to the compiler

CFLAGS = -Wall

all: yuan

yuanhw3: yuan.cpp 
	${CC} ${CFLAGS} yuan.cpp -o yuan

clean:
	rm -rf \
	yuan



