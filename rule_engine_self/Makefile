# Date: 2012-11-27
# Author: Karsten Ahnert (karsten.ahnert@gmx.de)

CC = g++
CXX = g++

INCLUDES = -I$(BOOST_ROOT)
CXXFLAGS += $(INCLUDES) -std=c++0x

all : main test_condition test_consequence

main : main.o
main.o : main.cpp condition.h consequence.h

test_condition : test_condition.o
test_condition.o : test_condition.cpp condition.h generic_conditions.h condition_factory.h

test_consequence : test_consequence.o
test_consequence.o : test_consequence.cpp consequence.h


clean :
	rm *.o *~ main test_condition test_consequence
