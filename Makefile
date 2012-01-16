# Compilator's variables
CC = g++
CXXFLAGS = -Wall

# Directories' variables
OUTPUT_DIRECTORY = ../bin/
HEADERS_DIRECTORY = ../headers/
OBJECT_DIRECTORY = ../bin/

# Files' variables
BIN = $(OUTPUT_DIRECTORY)Puissance4
OBJS = $(OBJECT_DIRECTORY)main.o $(OBJECT_DIRECTORY)grid.o $(OBJECT_DIRECTORY)node.o

#Additional variables
DEBUG = TRUE

# Build project
all: $(BIN)
	@echo ""
	@echo "Puissance4: Compilation rules"
ifeq ($(DEBUG),TRUE)
	@echo "	Compilation for debug"
	@echo "	Keeps all objects files created"
else
	@echo "	Compilation for release"
	@echo "	Deletes all objects files created"
endif
	@echo ""

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $(BIN)
ifneq ($(DEBUG), TRUE)
	rm $(OBJS)
	@echo "Removed object files"
endif

# Dependencies
$(OBJECT_DIRECTORY)main.o : main.h grid.h node.h
$(OBJECT_DIRECTORY)grid.o : main.h grid.h
$(OBJECT_DIRECTORY)node.o : main.h grid.h

# Build object's files
$(OBJECT_DIRECTORY)%.o: %.cpp
	$(CC) -c $< -o $@ $(CXXFLAGS)

# Clean project temporary files
cleanTmp:
	rm *~
	@echo ""
	@echo "Cleaning rules:"
	@echo "	Cleaned temporary files"
	@echo ""

# Clean previous compilation	
clean :
	rm $(BIN)
	rm $(OBJS)
	@echo ""
	@echo "Cleaning rules:"
	@echo "	Cleaned binary file"
	@echo "	Cleaned object's files"
	@echo ""
	
# Clean all the project
distclean:
	rm $(BIN)
	rm $(OBJS)
	rm *~
	@echo ""
	@echo "Cleaning rules:"
	@echo "	Cleaned binary file"
	@echo "	Cleaned object's files"
	@echo "	Cleaned temporary files"
	@echo ""
