all: store query

store: store_main.c my_sql.o header.h
	g++ -o store store_main.c my_sql.o -lpcap
my_sql.o: my_sql.c header.h
	g++ -o my_sql.o -c my_sql.c
query: query_main.c  header.h
	g++ -o query query_main.c  -lpcap 
install: query store
	cp query ../
	cp store ../
