# Source, Executable, Includes, Library Defines
INCL   = bitmap.h DCT.h
SRC    = main.c bitmap.c DCT.c
OBJ    = $(SRC:.c=.o)
LIBS   = -lm
EXE    = BMP_compressor

# Compiler, Linker Defines
CC      = gcc
CFLAGS  =
LIBPATH = -L.
LDFLAGS = -o $(EXE) $(LIBPATH)
CFDEBUG = -ansi -pedantic -Wall -g -DDEBUG $(LDFLAGS)
RM      = /bin/rm -f

# Compile and Assemble C Source Files into Object Files
%.o: %.c
	   $(CC) -c $(CFLAGS) $*.c $(LIBS)

# Link all Object Files with external Libraries into Binaries
$(EXE): $(OBJ)
	   $(CC) $(LDFLAGS) $(OBJ) $(LIBS)

# Objects depend on these Libraries
$(OBJ): $(INCL)

# Create a gdb/dbx Capable Executable with DEBUG flags turned on
debug:
	   $(CC) $(CFDEBUG) $(SRC)

# Clean Up Objects, Exectuables, Dumps out of source directory
clean:
	   $(RM) $(OBJ) $(EXE) core a.out