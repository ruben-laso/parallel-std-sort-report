CXX = g++

PEDANTICFLAGS = -pedantic -Wall -Wextra -Werror

LINKFLAGS = -ltbb

CXXFLAGS = -std=c++17 -O3 $(PEDANTICFLAGS)

TARGET = pstl_sort.out tbb_sort.out seq_sort.out
SRCS = main.cpp

all: $(TARGET)

pstl_sort.out: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINKFLAGS) -DPSTL_SORT

tbb_sort.out: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINKFLAGS) -DTBB_SORT

seq_sort.out: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINKFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean