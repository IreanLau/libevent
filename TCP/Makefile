INCLUDE=-I /usr/include -lL/usr/lib -levent
.PHONY:all
all:tcp client

tcp:tcp.cpp
	g++ -o $@ $^ -g -levent
client:client.cpp
	g++ -o $@ $^ -g  -levent  

.PHONY:clean
clean:
	rm -rf tcp
	rm -rf client
