#ifndef _CONNECTIONS_H_
#define _CONNECTIONS_H_

#include "header.h"
#include "my_sql.h"

#define H_TABLE_SIZE 200000

#define MEM_LIMIT  		1e9 
#define DUMP_PARA 		0.9

#define TRACEFILE_SIZE 	5e8 

#define TRACE_PATH "traces/day"

#define CON_CUTOFF_SIZE 1e9
#define CON_TIMEOUT 90

#define INT(x)  (*((const int *)&x))

class Connection;
class Connections;

unsigned int hash3elem(int a, int b, int c);

typedef struct PktBuff{
	struct pcap_pkthdr* hdr;
	unsigned char * pkt;
	struct PktBuff * prev;
	struct PktBuff * next;
}pkt_buff_t;

class Dumper
{
public:
	Dumper(MySQL * _sql,unsigned int _fileno);
	~Dumper();
	void dump(Connection* c);
	bool is_full();
	void close();
private:
	pcap_dumper_t * pdump;
	std::string filename;
	MySQL* sql;
	unsigned int fileno;
	unsigned int offset;
	unsigned int totsize;
};

class ConnectionID
{
public:
	ConnectionID( const ConnectionID& id){
		ip1 = id.srcIP();
		ip2 = id.dstIP();
		port1 = id.srcPort();
		port2 = id.dstPort();
		proto = id.protocol();
	}
	ConnectionID( struct in_addr sip,  struct in_addr dip, unsigned short sport,unsigned short dport, int protocol){
		ip1 = sip;
		ip2 = dip;
		port1 = sport;
		port2 = dport;
		proto = protocol;
	}

	unsigned int hash(){
		int a = INT(ip1) + INT(ip2);
		int b = INT(ip1) > INT(ip2) ? INT(ip1) - INT(ip2) : INT(ip2) - INT(ip1);
		int c = ( (port1 + port2)<<16 ) + ( port1 > port2 ? port1 - port2 : port2 - port1 );
		return (unsigned int)(hash3elem(a,b,c)+ proto);
	}

	bool equals(ConnectionID id);

	struct in_addr srcIP() const{ return ip1; }
	struct in_addr dstIP() const{ return ip2; }
	unsigned short srcPort() const{ return port1; }
	unsigned short dstPort() const{ return port2; }
	int protocol() const{ return proto; }
private:
	struct in_addr ip1;
	struct in_addr ip2;
	unsigned short port1;
	unsigned short port2;
	int  proto;
};

class Connection
{
public:
	Connection(ConnectionID _id);
	~Connection();
	ConnectionID getID(){ return id; }
	Connection* next(){ return c_next; }
	Connection* prev(){ return c_prev; }

	unsigned int addpkt(const struct pcap_pkthdr * header, const unsigned char * packet,double time);

	unsigned int freeMem();

	friend class Dumper;
	friend class Connections;
private:
	bool is_full(){ return tot_pkt_size >= CON_CUTOFF_SIZE ; }

	ConnectionID id;
	Connection* c_prev;
	Connection* c_next;

	Connection* t_older;
	Connection* t_newer;

	pkt_buff_t * p_first;
	pkt_buff_t * p_last;
	
	double time_oldest;
	double time_latest;

	unsigned int tot_pkt_size;  // for pkt size only

	unsigned int tot_mem_size;  // only for pcap_pkthdr and packets
};

class Connections
{
	typedef Connection* conn_t;
public:
	Connections(std::string& partoutfile);
	~Connections();
	void addpkt(struct in_addr sip, struct in_addr dip, unsigned short sport, unsigned short dport, int protocol,  double time, const struct pcap_pkthdr* pkthdr,const unsigned char* pkt);
private:
	Connection* addConn( ConnectionID id);
	void check4dump(double intval);
	void dumpConn(conn_t c);
	void mv2newest(conn_t c);
	void dumpAll();
	void incDumper();

	unsigned int hsize;

	unsigned int totmem; // only caculate the mem costed by ptkhdr and pkt 
	unsigned int maxmem; 

	unsigned int conn_num;

	double time_oldest;
	double time_latest;
	
	conn_t* htable;

	conn_t oldest_conn;
	conn_t newest_conn;

	Dumper* dumper;
	unsigned int dumpfileno;

	MySQL* sql;
};




#endif
