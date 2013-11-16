all: store query

store: store_main.c my_sql.o connections.o header.h
	g++ -o store store_main.c my_sql.o connections.o -lpcap
my_sql.o: my_sql.c header.h
	g++ -o my_sql.o -c my_sql.c
connections.o: connections.h connections.c header.h
	g++ -o connections.o -c connections.c 
query: query_main.c  header.h
	g++ -o query query_main.c  -lpcap 
install: query store
	cp query ../
	cp store ../
clean:
	rm -f store
	rm -f query
	rm -f *.o
