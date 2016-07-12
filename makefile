# http://stackoverflow.com/questions/31176997/what-does-clang-check-do-without-analyze-option

FILES :=                            \
    Deque.h                         \
    Deque.log                       \
    html                            \
    TestDeque.c++                   \
    TestDeque.out					\
	deque-tests/asn579-TestDeque.c++ \
   	deque-tests/asn579-TestDeque.out \

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

ifeq ($(CC), clang)
    CLANG-CHECK  := clang-check
    CXX          := clang++
else
    CXX          := g++-4.8
    GCOV         := gcov-4.8
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
endif

ifeq ($(CI), true)
    CLANG-FORMAT := clang-format
else
    CLANG-FORMAT := clang-format-3.4
endif

deque-tests:
	git clone https://github.com/cs371g-summer-2016/deque-tests.git

html: Doxyfile Deque.h TestDeque.c++
	doxygen Doxyfile

Deque.log:
	git log > Deque.log

Doxyfile:
	doxygen -g
	# you must manually edit Doxyfile and
	# set EXTRACT_ALL     to YES
	# set EXTRACT_PRIVATE to YES
	# set EXTRACT_STATEIC to YES

TestDeque: Deque.h TestDeque.c++
ifeq ($(CC), clang)
	$(CXX) $(CXXFLAGS) TestDeque.c++ -o TestDeque $(LDFLAGS)
	-$(CLANG-CHECK) -extra-arg=-std=c++11          TestDeque.c++ --
	-$(CLANG-CHECK) -extra-arg=-std=c++11 -analyze TestDeque.c++ --
else
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) TestDeque.c++ -o TestDeque $(LDFLAGS)
endif

TestDeque.tmp: TestDeque
	$(VALGRIND) ./TestDeque                                       >  TestDeque.tmp 2>&1
ifeq ($(CC), gcc)
	$(GCOV) -b TestDeque.c++ | grep -A 5 "File 'TestDeque.c++'" >> TestDeque.tmp
endif
	cat TestDeque.tmp

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  *.plist
	rm -f  Deque.log
	rm -f  Doxyfile
	rm -f  gmon.out
	rm -f  TestDeque
	rm -f  TestDeque.tmp
	rm -rf deque-tests
	rm -rf html
	rm -rf latex

config:
	git config -l

format:
	$(CLANG-FORMAT) -i Deque.h
	$(CLANG-FORMAT) -i TestDeque.c++

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: html Deque.log TestDeque.tmp deque-tests check
