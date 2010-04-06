CC=g++.exe
RM=del

OBJ= AbstractFunction.o Operation.o Polynomial.o NamedFunction.o

OUT=libFunction.dll

all: $(OBJ)
	$(CC) -shared $(OBJ) -o $(OUT)
	
AbstractFunction.o: AbstractFunction.cpp AbstractFunction.h
	$(CC) -c AbstractFunction.cpp

Operation.o : Operation.h Operation.cpp
	$(CC) -c Operation.cpp
	
Polynomial.o : Polynomial.h Polynomial.cpp
	$(CC) -c Polynomial.cpp
	
NamedFunction.o : NamedFunction.h NamedFunction.cpp
	$(CC) -c NamedFunction.cpp

clean: 
	$(RM) $(OBJ)

