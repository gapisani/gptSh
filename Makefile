.PHONY: all obj clean install uninstall

CC=cc
LDFLAGS=-lm
PREFIX=/usr/local

TAG=$(shell git describe --exact-match --tags 2>/dev/null)
COMMIT=$(shell echo "cloned commit: " && git rev-parse --short HEAD 2>/dev/null)

VER=$(or $(TAG),$(COMMIT))

SRC=$(shell find src -iname "*.c")
OBJ=$(subst src/,obj/,$(SRC:.c=.o))

TARGETS=ptls ptcp ptpwd
BIN=$(addprefix build/,$(TARGETS))

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $^

build/%: obj/%/*.o
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) obj/common/*.o -o $@ $^

all: obj
	$(MAKE) $(BIN) CC=$(CC) CFLAGS=$(CFLAGS) LDFLAGS=$(LDFLAGS) PREFIX="$(PREFIX)"
	mkdir -p build

obj: $(OBJ)

clean:
	rm -rf build/*
	rm -rf obj/*

install:
	cp $(BIN) $(PREFIX)/bin/

uninstall:
	rm $(PREFIX)/bin/ptls
	rm $(PREFIX)/bin/ptpwd
	rm $(PREFIX)/bin/ptcp
