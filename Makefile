CC = gcc
CFLAGS = -Wall -Wextra -g -I./

SRC_DIR = ./
BUILD_DIR = ./build
TARGET = myprogram
TARGET_TEST = testunits

SRCS = $(filter-out $(SRC_DIR)/testunits.c, $(wildcard $(SRC_DIR)/*.c))
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

SRCS_TEST = $(filter-out $(SRC_DIR)/exemple.c, $(wildcard $(SRC_DIR)/*.c))
OBJS_TEST = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS_TEST))

.PHONY: all clean

all: $(BUILD_DIR) $(TARGET)

test: $(BUILD_DIR) $(TARGET_TEST)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET_TEST): $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TARGET_TEST)





