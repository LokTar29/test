FLAG=-Wall -Werror msgq.c tools.c
STD=-std=gnu99
CC=gcc

all:
	$(CC) $(STD) $(FLAG) server.c -o server
	$(CC) $(STD) $(FLAG) open.c -o open
	$(CC) $(STD) $(FLAG) login.c -o login
	$(CC) $(STD) $(FLAG) destory.c -o destory
	$(CC) $(STD) $(FLAG) unlock.c -o unlock
	$(CC) $(STD) $(FLAG) save.c -o save
	$(CC) $(STD) $(FLAG) take.c -o take
	$(CC) $(STD) $(FLAG) transf.c -o transf
	$(CC) $(STD) $(FLAG) query.c -o query
	$(CC) $(STD) $(FLAG) client.c -o client
clean:
	rm server open login destory unlock save take transf query clent
