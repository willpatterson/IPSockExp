all: tcp_splitter

client: ./src/basic_client_template.c
	mkdir -p ./bin
	gcc ./src/basic_client_template.c -o ./bin/client

server: ./src/basic_server_template.c
	mkdir -p ./bin
	gcc ./src/basic_server_template.c -o ./bin/server

tcp_splitter: ./src/tcp_splitting_proxy.c
	mkdir -p ./bin
	gcc ./src/tcp_splitting_proxy.c -o ./bin/tcp_splitting_proxy

connection_queue: ./src/connection_queue.c ./src/include/connection_queue.h
	mkdir -p ./bin
	gcc ./src/connection_queue.c -o ./bin/connection_queue_test

config_parser: ./src/config.c ./src/include/config.h ./src/include/common.h ./src/include/generic_list.h
	mkdir -p ./bin
	gcc ./src/config.c -o ./bin/config_parse

list: ./src/generic_list.c ./src/include/generic_list.h
	mkdir -p ./bin
	gcc ./src/generic_list.c -o ./bin/generic_list

clean:
	rm ./bin/*
