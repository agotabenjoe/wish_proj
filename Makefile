# Solaris (ural2) es Linux ala.

# forditando obj. fajlok

objs = test.o memtrace.o List.o ListElement.o String.o User.o UserList.o Wish.o WishList.o

# headerek, melyektol az egyszeruseg kedveert minden fugg
heads = Array.hpp memtrace.h gtest_lite.h List.hpp ListElement.hpp String.hpp User.hpp UserList.hpp Wish.hpp WishList.hpp

prog = user_and_wish_test     # a program neve

CXX = g++                           # a C++ fordito neve
CXXFLAGS = -pedantic -Wall -std=c++11 # C++ kapcsolok: legyen bobeszedu, 
CXXFLAGS += -g                      # ... es forduljon debug info is

# alapertelmezett cel: tesztprogram linkelese
all: $(prog)

$(prog): $(objs) $(objs2)
	$(CXX) $(objs) $(objs2) -o $@

$(objs): $(heads)

# takaritas igeny szerint
clean:
	rm -f $(objs) $(prog)
