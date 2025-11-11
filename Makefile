CC      := gcc
CFLAGS  := -O2 -Wall -Wextra -std=c11
LDFLAGS := -ljansson

TARGET  := bot
SRC     := bot.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
