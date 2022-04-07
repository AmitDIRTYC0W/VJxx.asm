CFLAGS = -Wall -Wextra -O3

OBJS = \
 asm-face.o \
 bmp.o

.SUFFIXES: .o .c
.PHONY: default install clean

default: asm-face

asm-face: $(OBJS)
	$(CC) $(CFLAGS) -o asm-face $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDE) -o $@ $<

clean:
	$(RM) asm-face $(OBJS)
