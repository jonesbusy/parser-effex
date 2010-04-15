CD=cd
PARSER=ParserEffex
FUNCTION=FunctionEffex
MV=move
RM=del

all: 
	$(CD) $(PARSER) && $(MAKE)
	$(MV) "$(FUNCTION)\libFunctionEffex.dll" .
	$(MV) "$(PARSER)\libParserEffex.dll" .
	
test: all
	$(CD) $(PARSER) && $(MAKE) test
	$(MV) "ParserEffex\Exemple.exe" .
	
clean: 
	$(CD) $(PARSER) && $(MAKE) clean
	$(CD) $(FUNCTION) && $(MAKE) clean
	
mproper: clean
	$(RM) "libFunctionEffex.dll"
	$(RM) "libParserEffex.dll"
	$(RM) "Exemple.exe"

