CXX = g++
CXXFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra

EXECUTABLE = test
SOURCE = ./Tests/*.cc

UNAME = $(shell uname)
ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += valgrind --leak-check=full -s -q --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
endif

all: clean test

clean:
	rm -rf *.a *.o $(EXECUTABLE) *.a *.gcno *.gcda *.gcov *.info report

test:
	$(CXX) $(CXXFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	./$(EXECUTABLE)
	lcov --rc lcov_branch_coverage=1 -o coverage.info -c -d .
	genhtml coverage.info --output-directory report
	$(OPEN_REPORT) ./report/index.html
	rm -rf *.gcno *.gcda *.gcov

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n */*.cc */*.h
	rm .clang-format

leaks: test
	$(LEAKS) ./$(EXECUTABLE)

# fsanitize_check:
# 	$(CXX) -fsanitize=address $(CXXFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) && ./$(EXECUTABLE)

.PHONY: all clean test gcov_report style clang_format leaks_check run
