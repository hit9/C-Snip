# vim:set noet:

default: example

CC=cc -std=c99
CFLAGS=-Wall -I../src -D_GNU_SOURCE
LDFLAGS=-Wall

buf_example: buf_example.c ../src/buf.c
cfg_example: cfg_example.c ../src/buf.c ../src/cfg.c
datetime_example: datetime_example.c ../src/datetime.c
dict_example: dict_example.c ../src/dict.c
event_example: event_example.c ../src/event.c
event_timer_example: event_timer_example.c ../src/event.c
heap_example: heap_example.c ../src/heap.c
ketama_example: ketama_example.c ../src/md5.c ../src/ketama.c
list_example: list_example.c ../src/list.c
log_example: log_example.c ../src/log.c
map_example: map_example.c ../src/map.c
md5_example: md5_example.c ../src/md5.c
queue_example: queue_example.c ../src/queue.c
signals_example: signals_example.c ../src/event.c
skiplist_example: skiplist_example.c ../src/skiplist.c
stack_example: stack_example.c ../src/stack.c
strings_example: strings_example.c ../src/strings.c

example: buf_example\
	cfg_example\
	datetime_example\
	dict_example\
	event_example\
	event_timer_example\
	heap_example\
	ketama_example\
	list_example\
	log_example\
	map_example\
	md5_example\
	queue_example\
	signals_example\
	skiplist_example\
	stack_example\
	strings_example

clean:
	rm -f *_example
