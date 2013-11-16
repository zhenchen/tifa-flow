all: store query

store: store_main.c my_sql.o header.h
	g++ -o store store_main.c my_sql.o -lpcap -lmysqlclient
my_sql.o: my_sql.c header.h my_sql.h
	g++ -o my_sql.o -c my_sql.c
query: query_main.c  header.h
	g++ -o query query_main.c  -lpcap -lmysqlclient
install: query store
	cp query ../
	cp store ../
clean:
	rm query
	rm store
	rm *.o
