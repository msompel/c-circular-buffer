TARGET=run

# compiler config
CC=gcc
CCFLAGS=-c -Wall
LDFLAGS=-lm

# directories
SDIR=./src
IDIR=./inc
ODIR=./build

# build source and object lists
EXT=c
ifeq ($(CC),g++)
	EXT=cpp
endif
SOURCES = $(notdir $(wildcard $(SDIR)/*.$(EXT)))
OBJECTS = $(patsubst %, $(ODIR)/%, $(SOURCES:.$(EXT)=.o))

# makefile
.PHONY: all clean
all: $(TARGET)

# create .exe using .o files
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo Executable Created: ./$(TARGET)

# create .o files
$(ODIR)/%.o: $(SDIR)/%.$(EXT) 
	@[ -d $(ODIR) ] || mkdir $(ODIR)
	$(CC) $(CCFLAGS) $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR) $(TARGET)
