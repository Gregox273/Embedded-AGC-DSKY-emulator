CC = gcc
CXX = g++

CFLAGS = -g -Wall

BUILDDIR = build

CSRC = transcoder.c

OBJS = $(CSRC:%.c=$(BUILDDIR)/%.o)

MAIN = transcoder

all: $(BUILDDIR) $(BUILDDIR)/$(MAIN)

$(BUILDDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILDDIR)/$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@
	
$(BUILDDIR):
	mkdir $@
	
debug: CFLAGS += -O0
debug: $(BUILDDIR)/$(MAIN)
	gdb $(BUILDDIR)/$(MAIN)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)/*
