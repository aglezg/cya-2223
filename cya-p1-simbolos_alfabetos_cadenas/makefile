IDIR =../include
CC = g++
CFLAGS = -I$(IDIR)
 
ODIR = .
LDIR = ../lib
 
LIBS = -lm
 
_DEPS = main.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
 
_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
 
 
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -std=c++14 -g -Wall -o $@ $^ $(CFLAGS) $(LIBS)
 
.PHONY: clean
 
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ *.txt