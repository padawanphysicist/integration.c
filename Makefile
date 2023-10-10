CC = gcc
CFLAGS:= -std=c99 \
	-Wall \
	-Wextra \
	-pedantic

# For logging
LOGGING_CFLAGS = -DLOG_USE_COLOR
LOGGING_SRCS=./logging/src/log.c
LOGGING_INCDIR=./logging/src

# For Unity
UNITY_CFLAGS = -DUNITY_INCLUDE_DOUBLE
UNITY_SRCS=./unity/src/unity.c
UNITY_INCDIR=./unity/src/

# For numeric
NUMERIC_CFLAGS = -DM_PI=3.14159265358979323846 -D_TOLERANCE=1e-7
NUMERIC_SRCS=$(shell find ./numeric/src/ -type f -name '*.c')
NUMERIC_INCDIR=./numeric/src/
NUMERIC_LDFLAGS = -lm

# For integration
INTEGRATION_CFLAGS =
INTEGRATION_SRCS=$(shell find ./src/ -type f -name '*.c')
INTEGRATION_INCDIR=./src/

INCDIR = $(LOGGING_INCDIR) $(UNITY_INCDIR) $(NUMERIC_INCDIR) $(INTEGRATION_INCDIR)
INCFLAGS=$(foreach d,$(INCDIR),-I$d)
CFLAGS+=$(LOGGING_CFLAGS) $(UNITY_CFLAGS) $(NUMERIC_CFLAGS) $(INTEGRATION_CFLAGS)
LDFLAGS+=$(NUMERIC_LDFLAGS)

all: test.out

SRCS := $(LOGGING_SRCS) $(UNITY_SRCS) $(NUMERIC_SRCS) $(INTEGRATION_SRCS) ./test/test.c
OBJS := $(SRCS:%.c=%.o)

.PHONY: test
test: test.out
	./test.out

test.out: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(INCFLAGS) $(CFLAGS) -c $^ -o $@

.PHONY: doc
doc: Doxyfile
	doxygen

.PHONY: clean
clean:
	find . -iname "*.o" -type f -delete
clean-all: clean
	find . -iname "*.out" -type f -delete
