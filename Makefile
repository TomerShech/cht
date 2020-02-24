TARGET ?= cht
CC ?= cc
CFLAGS ?= -g -Wall -Wextra -pedantic
RM ?= -rm -f

SRCDIR ?= src
OBJDIR ?= build

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c))
HEADERS = $(wildcard *.h)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@
	./$(TARGET)

clean:
	$(RM) $(OBJDIR)/*.o
	$(RM) $(TARGET)
