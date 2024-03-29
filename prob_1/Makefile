CC = gcc
LD = gcc
RM = rm -rf

CFLAGS = -g -Wall -O0
LDFLAGS = $(CFLAGS)

OTHER_FLAGS = -MD

CFLAGS_COV  += -fprofile-arcs -ftest-coverage
LDFLAGS_COV += -lgcov

CFLAGS += $(CFLAGS_COV)
LDFLAGS += $(LDFLAGS_COV)

CFLAGS += $(OTHER_FLAGS)
LDFLAGS += $(OTHER_FLAGS)

TEST_SRC = bitset/tests/test.c
TEST_HEADER = bitset/tests/test.h
LIB_SRC  = bitset/src/bit_array.c
LIB_HEADER = bitset/include/bit_array.h

TEST_OBJS = $(TEST_SRC:.c=.o)
LIB_OBJS = $(LIB_SRC:.c=.o)

EXEC = bitset.out
TEST_EXEC = test.out

LCOV_OUT_FOLDER = out
%BROWSER = chromium

all: $(EXEC)

$(EXEC): $(LIB_OBJS) main.o
	$(CC) -o $@ $^ $(CFLAGS)

test: test_build
	./$(TEST_EXEC)

test_build: build_test_lib build_test_main build_utests
	$(LD) -o $(TEST_EXEC) $(LIB_OBJS) $(TEST_OBJS) main.o -DRUN_TESTS $(LDFLAGS)

build_test_lib:
	$(CC) $(LIB_SRC) -o $(LIB_OBJS) -c -DRUN_TESTS $(LDFLAGS)

build_test_main:
	$(CC) main.c -o main.o -c -DRUN_TESTS $(LDFLAGS)


build_utests:
	$(CC) $(TEST_SRC) -o $(TEST_OBJS) -c -DRUN_TESTS $(LDFLAGS)


view_coverage: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info -o $(LCOV_OUT_FOLDER)

valgrind: test_build
	valgrind ./$(TEST_EXEC)


clean:
	$(RM) 	$(LIB_OBJS) $(LIB_OBJS:.o=.gcno) $(LIB_OBJS:.o=.gcda) 	 \
			$(TEST_OBJS) $(TEST_OBJS:.o=.gcno) $(TEST_OBJS:.o=.gcda) \
			$(LIB_OBJS:.o=.d) $(TEST_OBJS:.o=.d)                     \
			$(LCOV_OUT_FOLDER) coverage.info						 \
			$(EXEC) $(TEST_EXEC) *.o *.gcno *.gcda *.d

-include $(TEST_OBJS:.o=.d) $(LIB_OBJS:.o=.d)

.PHONY: all clean
