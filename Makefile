.PHONY: all

PROJ = 3d

# CC = gcc -std=c11
CC = clang -std=c11 -v -g
CFLAGS = -Wall -Wextra -pedantic -c -g \
		 -Wno-declaration-after-statement \
		 -Wno-c++98-compat \
		 -Wno-c++98-compat-pedantic \
		 -Wno-c++98-c++11-compat-pedantic \
		 -Wno-c23-compat \
		 -Wno-reserved-identifier \
		 -Wno-missing-braces \
		 -Wno-unused-variable \
		 -Wno-sizeof-pointer-div \
		 -Wno-unused-includes
# ------------------------------------------------------------------------------
# linking

# include dir
CFLAGS += -Iinclude/
CFLAGS += -Isrc/

# libs
LIBS = raylib

CFLAGS += $(shell pkgconf --cflags --static $(LIBS))
LFLAGS = $(shell pkgconf --libs --static   $(LIBS))
LFLAGS += -lm

# ------------------------------------------------------------------------------
# building

BUILD_DIR = bin
SRC_DIR = src
EXEC = $(PROJ).exe

SOURCES := $(wildcard $(SRC_DIR)/*.c)

OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

ifeq ($(OS),Windows_NT)
REMOVE_CMD := del /f /q
else
REMOVE_CMD := rm -rf
endif


all: clean build compiledb

build: dir $(BUILD_DIR)/$(EXEC)

ifeq ($(OS), Windows_NT)
dir:
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
dir:
	mkdir -p $(BUILD_DIR)
endif

$(BUILD_DIR)/$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(LFLAGS)

$(OBJ): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

run: 
	./$(BUILD_DIR)/$(EXEC)

clean:
	$(REMOVE_CMD) $(BUILD_DIR)

compiledb:
	compiledb -n make all
