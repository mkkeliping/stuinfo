CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi scoreadd.cgi  scoresel.cgi scoremod.cgi scoredel.cgi courseadd.cgi coursesel.cgi coursemod.cgi coursedel.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx
		cp *.sql /usr/lib/cgi-bin/sx
		cp head.html /usr/lib/cgi-bin/sx
		cp *.html /var/www/html
