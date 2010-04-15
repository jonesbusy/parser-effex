CC=g++.exe
CP=copy
CD=cd
RM=del

OBJ= Scanner.o Parser.o ParserError.o FactoryNamedFunction.o FactoryPolynomial.o
INCLUDE= ..\FunctionEffex
LIB=libParserEffex.dll
OUT=Exemple.exe

all: $(OBJ)
	$(CD) $(INCLUDE) && $(MAKE)
	$(CC) -shared $(OBJ) -o $(LIB) -I $(INCLUDE) -L $(INCLUDE) -lFunctionEffex
	
test: $(OBJ) Exemple.o
	$(CD) $(INCLUDE) && $(MAKE)
	$(CC) $(OBJ) Exemple.o -o $(OUT) -I $(INCLUDE) -L $(INCLUDE) -lFunctionEffex
	
	
Scanner.o: Scanner.cpp Scanner.h
	$(CC) -c Scanner.cpp -I $(INCLUDE)
	
Parser.o: Parser.cpp Parser.h
	$(CC) -c Parser.cpp -I $(INCLUDE)
	
ParserError.o: ParserError.cpp ParserError.h
	$(CC) -c ParserError.cpp -I $(INCLUDE)
	
FactoryNamedFunction.o: FactoryNamedFunction.cpp FactoryNamedFunction.h
	$(CC) -c FactoryNamedFunction.cpp -I $(INCLUDE)
	
FactoryPolynomial.o: FactoryPolynomial.cpp FactoryPolynomial.h
	$(CC) -c FactoryPolynomial.cpp -I $(INCLUDE)
	
Exemple.o : Exemple.cpp
	$(CC) -c Exemple.cpp -I $(INCLUDE)

clean: 
	$(RM) $(OBJ) Exemple.o
	$(RM) libFunctionEffex.dll

