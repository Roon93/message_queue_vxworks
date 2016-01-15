objects := $(patsubst %.c, %.o, $(wildcard *.c))
CC := cc

common.a: $(objects)
	ar rvs $@ $(filter-out common_log.o, $(objects))
.PHONY: clean
clean:
	rm $(objects)
