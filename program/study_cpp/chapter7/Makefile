all: lib

lex.yy.c: dbmParserLex.y dbmParser.h
	flex dbmParserLex.y

dbmParserGram.tab.c: dbmParserGram.y dbmParser.h
	bison -d dbmParserGram.y


sample: sample.c 
	gcc -g -o sample sample.c -I./ -L./  -ldbmst -ldbmCore -lpthread -lrt -lm


clean:
	rm -f lex.yy.c dbmParserGram.tab.c dbmParserGram.tab.h *.so core* test

