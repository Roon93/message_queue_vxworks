objects := $(patsubst %.c, %.o, $(wildcard *.c))
CC := cc

mq: $(objects) memory.a common.a timer.a
	$(CC) -o $@ $^
mq_test: mq_queue.c mq_queue.h message_queue.h
	$(CC) -c $<
message_queue: message_queue.c message_queue.h mq_basic.h
	$(CC) -c $<
mq_queue.o: mq_queue.c mq_queue.h mq_basic.h
	$(CC) -c $<
mq_message: mq_message.c mq_message.h mq_basic.h
	$(CC) -c $<
mq_log: mq_log.c mq_log.h mq_basic.h
	$(CC) -c $<

.PHONY: clean lib memory.a timer.a common.a
clean:
	rm $(objects)
	rm memory.a
	rm common.a
	rm timer.a
lib: $(objects)
	ar rvs mq.a $(filter-out mq_test.o, $(objects))
memory.a:
	cp ../memory/memory.a .
timer.a:
	cp ../timer/timer.a .
common.a:
	cp ../common/common.a .
