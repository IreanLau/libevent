INCLUDE=-I /usr/include -lL/usr/lib -levent
test:test.c
	g++ -o $@ $^ -Wall -g -L/usr/lib -levent
.PHONY:clean
clean:
	rm -rf test
