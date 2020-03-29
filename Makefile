TARGET = run

# compiler config
CC = gcc
CCFLAGS = -g -c -Wall -std=c11
LDFLAGS = -lm -lpthread

# directories
SDIR = ./src
IDIR = ./src
ODIR = ./build

# build source and object lists
SRCS = $(notdir $(wildcard $(SDIR)/*.c))
INCS = $(foreach d, $(IDIR), -I $d)
OBJS = $(patsubst %, $(ODIR)/%, $(SRCS:.c=.o))

# makefile
.PHONY: all clean
all: $(TARGET)

# create .exe using .o files
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo Executable Created: ./$(TARGET)

# create .o files
$(ODIR)/%.o: $(SDIR)/%.c 
	@[ -d $(ODIR) ] || mkdir $(ODIR)
	$(CC) $(CCFLAGS) $< -o $@ $(INCS)

clean:
	rm -rf $(ODIR) $(TARGET)*
