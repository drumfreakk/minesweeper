CC = gcc
CFLAGS := -Wall -Wextra -g -Werror=missing-declarations -Werror=redundant-decls
#LFLAGS = -lncurses
# OUTPUT := output
SRC := src
INCLUDE := include
#	LIB := lib

MAIN := minesweeper
SOURCEDIRS := $(shell find $(SRC) -type d)
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
#	LIBDIRS := $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
# MD := mkdir -p

INCLUDES := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
#	LIBS := $(patsubst %,-L%, $(LIBDIRS:%/=%))
SOURCES := $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS := $(SOURCES:.c=.o)

all: $(MAIN)
	@echo Executing "all" complete!

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(LFLAGS) # $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(MAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	@echo Cleanup complete!

run: all
	./$(MAIN)
	@echo Executing "run: all" complete!
