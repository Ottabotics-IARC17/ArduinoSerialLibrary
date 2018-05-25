##################################################
# Compiler settings
##################################################

# Set compiler to g++
CXX			:= g++

# Compiler flags
XFLAGS		:= -g -Wall -std=c++11

##################################################
# Directory macros
##################################################

IDIR		:= include/
OBJDIR		:= build/
SRCDIR		:= src/
OUTDIR		:= bin/
TESTDIR		:= test/

##################################################
# Required object dependencies
##################################################

# Update this line with list of objects to be compiled
_OBJECTS	:= Serial.o
OBJECTS		:= $(patsubst %,$(OBJDIR)/%,$(_OBJECTS))

##################################################
# Libraries
##################################################

# User-created headers
INC1		:= $(patsubst %,-I%,$(IDIR))
# All include directories and libraries
INCDIRS		:= $(INC1)

##################################################
# Compiler flags
##################################################

CXXFLAGS	:= $(INCDIRS) $(XFLAGS)

##################################################
# Make rules
##################################################

.PHONY: all
all: $(OBJECTS)
	@echo "\n----- Compiling main -----\n"
	@mkdir -p build
	@mkdir -p bin
	$(CXX) $(OBJECTS) $(SRCDIR)main.cpp -o $(OUTDIR)main $(CXXFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@echo "\n----- Compiling object file:" $@ "from" $< "-----\n"
	@mkdir -p build
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean
clean:
	@echo "\n----- Cleaning object files -----\n"
	rm -rf $(OBJDIR)*.o
