#ifndef _MY_SQL_
#define _MY_SQL_

#include "header.h"

#define DEBUG

#ifdef _DEBUG_ALL_
#ifndef _DEBUG_
#define DEBUG
#endif
#endif

class MySQL
{
public:
	MySQL();
	~MySQL();
	void addRow(struct in_addr sip,struct in_addr dip,unsigned short sport,unsigned short dport,int protocol, double time,int pcapfile, int offset);
private:
	void onInit();
    
	long long tot_rows;
	double time_oldest;
	double time_latest;
    
    MYSQL mysql;
    char q_buff[MAX_QUERY_LEN];
};
#endif
