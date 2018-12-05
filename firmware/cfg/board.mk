# List of all the board related files.
BOARDSRC = $(CONFDIR)/board.c

# Required include directories
BOARDINC = $(CONFDIR)

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)