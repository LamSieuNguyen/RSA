CXX = g++
OPTS = -Wall 

decrypt: decrypt.cc ReallyLongInt.o numberTheory.o
	${CXX} ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o  numberTheory.o

encrypt: encrypt.cc ReallyLongInt.o numberTheory.o
	${CXX} ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o  numberTheory.o

keygen: keygen.cc ReallyLongInt.o numberTheory.o
	${CXX} ${OPTS} -o keygen keygen.cc ReallyLongInt.o  numberTheory.o

factorial: factorial.cc ReallyLongInt.o numberTheory.o
	${CXX} ${OPTS} -o factorial factorial.cc ReallyLongInt.o  numberTheory.o

numberTheory.o: numberTheory.cc numberTheory.h
	${CXX} ${OPTS} -c numberTheory.cc

ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	${CXX} ${OPTS} -c ReallyLongInt.cc  


all: decrypt encrypt keygen factorial

clean:
	rm *.o
	rm decrypt
	rm encrypt
	rm keygen
	rm factorial

cleanemacs:
	rm *~
