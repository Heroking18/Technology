PRODUCT=myQueue

CPPFLAGS=-Iproduct -Itest -I../stack_cpp/product
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 $(CPPFLAGS)

SOURCES=$(wildcard product/*.cpp) \
		$(wildcard ../stack_cpp/product/*.cpp) \
        $(wildcard test/*.cpp)	

HEADERS=$(wildcard product/*.h) \
		$(wildcard ../stack_cpp/product/*.h) \
        $(wildcard test/*.h)	

LDFLAGS=-lgtest  -lgmock -lgmock_main -lpthread

CXX=g++

.PHONY: all clean test

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	@rm -rf $(PRODUCT)
	@rm -rf kwinject.out .kwlp .kwps

klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run

test: $(PRODUCT)
	@./$(PRODUCT)
