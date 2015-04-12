CC       = gcc
CXX      = g++
CFLAGS   = -std=c11 -O2 -fomit-frame-pointer -Wall
CXXFLAGS = -std=c++11 -O2 -fomit-frame-pointer -Wall
LD       = g++
LFLAGS   = -s
OBJECTS  = spcpoint.o SPCFile.o
PROGRAM  = spcpoint

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
