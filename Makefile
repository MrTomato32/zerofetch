CC = gcc
CFLAGS = -Wall -Wextra -O2

zerofetch: main.c info.c logo.c info.h logo.h
	$(CC) $(CFLAGS) -o zerofetch main.c info.c logo.c

clean:
	rm -f zerofetch

install: zerofetch
	mkdir -p $(HOME)/.local/bin
	cp zerofetch $(HOME)/.local/bin/

uninstall:
	rm -f $(HOME)/.local/bin/zerofetch
