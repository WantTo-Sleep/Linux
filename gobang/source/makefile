gobang: gobang.cc
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient -ljsoncpp -lpthread -lboost_system -std=c++11

.PHONY:
clean:
	rm -f gobang
