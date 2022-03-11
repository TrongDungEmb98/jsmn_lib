SOURCES = $(shell echo *.c)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.c=.o)

TARGET = simple_example

CC := gcc

all: $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)
$(OBJECTS):
	$(CC) -c $(SOURCES)

clean: 
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean all

