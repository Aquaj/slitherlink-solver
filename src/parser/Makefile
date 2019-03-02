CFLAGS += -g -Wall 

all		:	y.tab.h lex.yy.c y.tab.c parser

y.tab.h         :       parser.y
			bison -y -d -v parser.y
lex.yy.c	:	parser.l
			flex parser.l
y.tab.c		:	parser.y
			bison -d -v parser.y
y.tab.o	        :       y.tab.c
lex.yy.o	: 	lex.yy.c

server.o	: 	server.c

parser		:	lex.yy.o y.tab.o  server.o
			gcc  lex.yy.o y.tab.o  server.o -o parser
clean		:
			rm -f 	lex.yy.c *.o y.tab.h y.tab.c parser *~ y.output
