#process_control: process_control.c
#	gcc $^ -o $@
#
#.PHONY: clean
#clean:
#	rm -f process_control 

.PHONY: all
all: myexec mytest

myexec: myexec.c
	gcc $^ -o $@

mytest: mytest.c
	gcc $^ -o $@

.PHONY: clean
clean:
	rm -f myexec mytest 
