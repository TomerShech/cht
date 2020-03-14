TARGET ?= ht
CC ?= cc
AR ?= ar

# change us if you like
PREFIX_LIB ?= /usr/local/lib
PREFIX_INC ?= /usr/local/include

CFLAGS ?= -g -Wall -Wextra -pedantic -Isrc
RM ?= -rm -f
MKDIR ?= mkdir -p
SRCDIR ?= src/$(TARGET)
BUILDDIR ?= build
LIBDIR ?= lib

.PHONY: default all clean install uninstall

LIBTARGET := lib$(TARGET).a
NAME := $(LIBDIR)/$(LIBTARGET)

default: $(NAME)
all: default

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(wildcard $(SRCDIR)/*.c))
HEADERS = $(wildcard *.h)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@

$(NAME): $(OBJECTS)
	@$(MKDIR) $(BUILDDIR)
	$(AR) rcs $@ $^

install: all
	$(MKDIR) $(PREFIX_INC)/cor && cd $(PREFIX_INC)/cor
	cp -f $(NAME) $(PREFIX_LIB)/$(LIBTARGET)
	cp -f src/$(TARGET)/$(TARGET).h $(PREFIX_INC)/cor/$(TARGET).h

uninstall:
	$(RM) $(NAME) $(PREFIX_LIB)/$(LIBTARGET)
	$(RM) $(PREFIX_INC)/cor/$(TARGET).h

clean:
	$(RM) $(BUILDDIR)/*.o $(LIBDIR)/*.a
