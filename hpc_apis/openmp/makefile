############
# COMPILER #
############

CMP     = clang++
FLAGS   = -std=c++11 -O2 -fopenmp -Wall -Wextra

###########
# SOURCES #
###########

HEADERS = matrix_dotproduct.hpp
SOURCES = matrix_test.cpp
EXEC    = exec

#########
# RULES #
#########

all: $(HEADERS) $(SOURCES)
	$(CMP) $(FLAGS) $(SOURCES) -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean: 
	rm $(EXEC)
