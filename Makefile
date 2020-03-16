CC=gcc
CFLAGS=-Isrc/
LIBS = -lncurses
SRC = src/digit.c src/screen.c src/main.c

default: pomodoro

pomodoro: $(SRC)
	mkdir build
	$(CC) $(CFLAGS) -o build/$@ $(SRC) $(LIBS)

clean:
	rm -rf build

install: pomodoro
	cp build/pomodoro /usr/local/bin/
	mkdir /usr/local/share/pomodoro
	cp data/digits.dat /usr/local/share/pomodoro/
	rm -rf build

uninstall:
	rm /usr/local/bin/pomodoro
	rm -rf /usr/local/share/pomodoro