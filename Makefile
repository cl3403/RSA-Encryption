OPTS = -Wall

keygen: keygen.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o

decrypt: decrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o

encrypt: encrypt.cc numberTheory.h ReallyLongInt.o
	g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o
 
ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	g++ ${OPTS} -c ReallyLongInt.cc

all: keygen decrypt encrypt
