all: client server

qt: client
	make -C Server qt
	mv Server/server ./

client:
	make -C Client
	mv Client/client ./

server:
	make -C Server
	mv Server/server ./

clean:
	make -C Client clean
	make -C Server clean

fclean: clean
	make -C Client fclean
	make -C Server fclean
	rm -f client
	rm -f server

re: fclean all

.PHONY: all clean fclean re client server qt
