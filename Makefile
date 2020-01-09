.PHONY = all clean

CC = g++
CPPFLAGS     =
LDFLAGS      =
LIBS         = -lm

SRCDIR = ./src/

DESTDIR = ./bin/
TARGET  = main

OBJECTS := $(patsubst $(SRCDIR)%.cpp,$(SRCDIR)%.o,$(wildcard $(SRCDIR)*.cpp))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	@echo "Compiling..."
	$(CC) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(DESTDIR)$(TARGET)
	-rm -f *.tga

