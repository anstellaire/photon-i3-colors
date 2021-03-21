############
# COMPILER #
############

CMP     = clang++
FLAGS   = -std=c++11 -O2 -fopenmp -Wall -Wextra

###########
# SOURCES #
###########

HEADERS = mat_mult.hpp
SOURCES = mat_mult_test.cpp
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
