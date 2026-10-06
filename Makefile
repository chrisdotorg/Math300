CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
LDFLAGS = -lm

INCLUDES = -Iinclude
SRC = $(wildcard src/*.c)
APP_SRC = $(filter-out src/main.c,$(SRC))

TARGET = mth300
TEST_ROOT = test_root_finding

.PHONY: all clean test debug

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) -o $@

$(TEST_ROOT): tests/test_root_finding.c $(APP_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) tests/test_root_finding.c $(APP_SRC) $(LDFLAGS) -o $@

test: $(TEST_ROOT)
	./$(TEST_ROOT)

debug:
	$(CC) $(CFLAGS) -fsanitize=address,undefined $(INCLUDES) $(SRC) $(LDFLAGS) -o $(TARGET)-asan

clean:
	rm -f $(TARGET) $(TEST_ROOT) $(TARGET)-asan
