CC := gcc

DIR_SRC := ./src
DIR_INC := ./inc
DIR_OUT := ./out
SO := $(DIR_SRC)/gui/bmp.so

FLAGS := -Wall -Werror -std=c99 -pedantic -Wextra -Wfloat-equal -Wfloat-conversion -lm -Iinc

DEBUG := -O0 --debug -ggdb
RELEASE := -O2

MODE_FLAGS := $(RELEASE)

SRCS_ALL := $(wildcard $(DIR_SRC)/*.c)
SRCS := $(filter-out $(DIR_SRC)/main.c, $(SRCS_ALL))
OBJS := $(SRCS:$(DIR_SRC)/%.c=$(DIR_OUT)/%.o)
OBJS_ALL := $(OBJS)
OBJS_ALL += $(DIR_OUT)/main.o


DEPEND := $(wildcard $(DIR_INC)/*.h)

ifeq ($(mode), release)
	MODE_FLAGS += $(RELEASE)
endif

FLAGS += $(MODE_FLAGS)

.PHONY : clean

$(SO) : $(DIR_OUT) $(OBJS) $(DEPEND)
	$(CC) -shared -Wl,-soname,adder $(OBJS) -fPIC -lm -o $@

app.exe : $(DIR_OUT) $(OBJS_ALL) $(DEPEND)
	$(CC) $(OBJS_ALL) -o $@ -lm

$(DIR_OUT)/%.o : $(DIR_SRC)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(DIR_OUT) :
	@mkdir -p $@

clean :
	rm -rf $(DIR_OUT) *.exe ./func_tests/data/.temp *.gcda *.gcno *.so
