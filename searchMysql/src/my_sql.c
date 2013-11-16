#include "my_sql.h"

//#define _DEBUG_
#ifdef _DEBUG_ALL_
#ifndef _DEBUG_
#define _DEBUG_
#endif
#endif
void MySQL::onInit()
{

	tot_rows = 0;

	time_oldest = 0;
	time_latest = 0;

    mysql_init(&mysql);
    if( NULL == mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PASSWD,MYSQL_DB,0,NULL,0)){
        printf("ERROR: MYSQL CAN'T GET CONNECTED! mysql_real_connect()\n");
        exit(-1);
    }
}

MySQL::MySQL()
{
	onInit();	
}

MySQL::~MySQL()
{
    mysql_close(&mysql);
}


void MySQL::addRow(struct in_addr sip,struct in_addr dip,unsigned short sport,unsigned short dport, int protocol, double time,int pcapfile, int offset)
{
	if( time_oldest < 1e-6 )time_oldest = time;
	if( time > time_latest )time_latest = time;
    unsigned char * pos1 = (unsigned char *)&sip;
    unsigned char * pos2 = (unsigned char *)&dip;
    sprintf(q_buff,"insert into %s values(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f,%d,%d)\0",MYSQL_TABLE,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],sport,dport,protocol,time,pcapfile,offset);
#ifdef _DEBUG_
	printf("addRow: pos 1 file:%d offset:%d \n",pcapfile,offset);
	printf("QUERY:|%s|\n",q_buff);
#endif
    q_buff[MAX_QUERY_LEN] = '\0';
    if(strlen(q_buff) >= MAX_QUERY_LEN -1 ){
        printf("ERROR: QUERY SIZE EXCEEDS MAX_QUERY_LEN !\n");
    }else{
        if( 0 != mysql_real_query(&mysql,q_buff,strlen(q_buff)) ){
            printf("ERROR: MYSQL QUERY FAILED! mysql_real_query()\nERRMSG:|%s|\nQUERY:|%s|\n",mysql_error(&mysql),q_buff);
        }
    }
	tot_rows++;
}
