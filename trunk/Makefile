CD=cd
PARSER=Parser
FUNCTION=Function
MV=move
RM=del

all: 
	$(CD) $(PARSER) && $(MAKE)
	$(MV) "$(FUNCTION)\libFunction.dll" .
	$(MV) "$(PARSER)\libParserEffex.dll" .
	
test: all
	$(CD) $(PARSER) && $(MAKE) test
	$(MV) "Parser\Exemple.exe" .
	
clean: 
	$(CD) $(PARSER) && $(MAKE) clean
	$(CD) $(FUNCTION) && $(MAKE) clean
	
mproper: clean
	$(RM) "libFunction.dll"
	$(RM) "libParserEffex.dll"
	$(RM) "Exemple.exe"

