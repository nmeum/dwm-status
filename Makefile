# See LICENSE for license details.
BIN_NAME = dwm-status

OBJECTS = $(BIN_NAME).o
HEADERS = config.h

X11INC ?= /usr/include/X11
X11LIB ?= /usr/lib/X11

CFLAGS ?= -Os -fomit-frame-pointer -pedantic -Wall
CFLAGS += -D_BSD_SOURCE -std=c99 -I$(X11INC)

CC      ?= gcc
LDFLAGS += -L$(X11LIB) -lX11 -ltinyalsa

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(BIN_NAME)
$(BIN_NAME): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

config.h: config.def.h
	cp $< $@

clean:
	$(RM) $(BIN_NAME) $(OBJECTS)