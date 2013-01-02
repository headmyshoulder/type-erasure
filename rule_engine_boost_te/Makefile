TYPE_ERASURE_DIR = $(HOME)/boost/testing/type_erasure

CC = g++-4.7
CXX = g++-4.7
GCC = g++-4.7

CXXFLAGS += -I$(BOOST_ROOT) -I$(TYPE_ERASURE_DIR) -std=c++11


all : rule_engine
rule_engine : rule_engine.o
rule_engine.o : rule_engine.cpp rule_engine.h

clean :
	rm *.o rule_engine