CC = gcc
CFLAGS:= -std=c99 \
	-Wall \
	-Wextra \
	-pedantic

.PHONY: test
all: test
test:
	@mkdir --parents build_aux
	$(CC) $(DEV_CFLAGS) -I./module/log.c/src -DLOG_USE_COLOR -c ./module/log.c/src/log.c -o build_aux/log.o
	$(CC) $(DEV_CFLAGS) -I./module/Unity/src -DUNITY_INCLUDE_DOUBLE -c ./module/Unity/src/unity.c -o build_aux/unity.o
	$(CC) $(DEV_CFLAGS) -I./module/num.c/include -c ./module/num.c/src/new.c -o build_aux/new.o
	$(CC) $(DEV_CFLAGS) -I./module/num.c/include -c ./module/num.c/src/num.c -o build_aux/num.o
	$(CC) $(DEV_CFLAGS) -I./module/num.c/include -I./module/log.c/src -c $(DEV_INCDIR) -I./src/include -DM_PI=3.14159265359 -c ./src/qsimp.c -o build_aux/qsimp.o
	$(CC) $(DEV_CFLAGS) -I./module/num.c/include -I./module/log.c/src -c $(DEV_INCDIR) -I./src/include -DM_PI=3.14159265359 -c ./src/integration.c -o build_aux/integration.o
	$(CC) $(DEV_CFLAGS) $(DEV_INCDIR) \
	-I./module/log.c/src \
	-I./module/Unity/src  \
	-I./module/num.c/include -I./module/log.c/src \
	-I./src -I./test  \
	$(DEV_INCDIR) \
	-DLOGLEVEL=$(LOGLEVEL) -DUNITY_INCLUDE_DOUBLE -c ./test/test.c -o build_aux/test.o
	$(CC) $$(ls build_aux/*.o) -o test.out -lm -larb -lflint -lgsl -lgslcblas
	@valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
        --track-origins=yes \
        --verbose          \
        --log-file=valgrind-out.txt \
        ./test.out

# For logging
# LOGGING_CFLAGS = -DLOG_USE_COLOR
# LOGGING_SRCS=./logging/src/log.c
# LOGGING_INCDIR=./logging/src

# # For Unity
# UNITY_CFLAGS = -DUNITY_INCLUDE_DOUBLE
# UNITY_SRCS=./unity/src/unity.c
# UNITY_INCDIR=./unity/src/

# # For numeric
# NUMERIC_CFLAGS = -DM_PI=3.14159265358979323846 -D_TOLERANCE=1e-7
# NUMERIC_SRCS=$(shell find ./numeric/src/ -type f -name '*.c')
# NUMERIC_INCDIR=./numeric/src/
# NUMERIC_LDFLAGS = -lm

# # For integration
# INTEGRATION_CFLAGS =
# INTEGRATION_SRCS=$(shell find ./src/ -type f -name '*.c')
# INTEGRATION_INCDIR=./src/

# INCDIR = $(LOGGING_INCDIR) $(UNITY_INCDIR) $(NUMERIC_INCDIR) $(INTEGRATION_INCDIR)
# INCFLAGS=$(foreach d,$(INCDIR),-I$d)
# CFLAGS+=$(LOGGING_CFLAGS) $(UNITY_CFLAGS) $(NUMERIC_CFLAGS) $(INTEGRATION_CFLAGS)
# LDFLAGS+=$(NUMERIC_LDFLAGS)

#all: test.out


# SRCS := $(LOGGING_SRCS) $(UNITY_SRCS) $(NUMERIC_SRCS) $(INTEGRATION_SRCS) ./test/test.c
# OBJS := $(SRCS:%.c=%.o)

# .PHONY: test
# test: test.out
# 	./test.out

# test.out: $(OBJS)
# 	$(CC) $^ -o $@ $(LDFLAGS)

# %.o: %.c
# 	$(CC) $(INCFLAGS) $(CFLAGS) -c $^ -o $@

.PHONY: doc
doc: Doxyfile
	doxygen

.PHONY: clean
clean:
	find . -iname "*.o" -type f -delete
clean-all: clean
	find . -iname "*.out" -type f -delete
