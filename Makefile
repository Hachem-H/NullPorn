CC=gcc

SOURCES=src/Flood.c \
		src/DNS.c   \
		src/main.c
BINARY=NullPorn

build: $(SOURCES)
	$(CC) -Wvla -g $(SOURCES) -o $(BINARY) -
