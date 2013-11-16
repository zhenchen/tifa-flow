#include "header.h"

//#define _DEBUG_


#ifdef _DEBUG_ALL_
#ifndef _DEBUG_
#define _DEBUG_
#endif
#endif

char qrybuff[MAX_QUERY_LEN];
unsigned char pktbuff[MAXSNAPLEN];

struct query_t
{
	std::string proto;
	std::string ip1;
	unsigned short port1;
	std::string ip2;
	unsigned short port2;
	double time_start;
	double time_end;
};

struct Query
{
	struct query_t query;
	std::string filter;
	std::string result_filename;
};

struct RuningSettings{
	std::string pcap_files_file;
	std::string query_file;
} _run_settings;

struct GlobalValue{
	std::vector<std::string> pcap_files;
	std::vector<struct Query> queries;
    MYSQL mysql;
    MYSQL_RES * res;
} _global;

void printHelpInfo()
{
	printf("Usage: test -f pcap_files_file -q querrt_file\n");
	exit(0);
}


void parseOptions(int argc, char **argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "hf:q:p:")) != EOF) {
		switch (opt) {
			case 'h':
				printHelpInfo();
				break;
			case 'f':
				_run_settings.pcap_files_file.assign(optarg);
				break;
			case 'q':
				_run_settings.query_file.assign(optarg);
				break;
		}
	}

	// check if the options are setted
	if( _run_settings.pcap_files_file.empty() || _run_settings.query_file.empty() ){
		printf("Lack option ! Please use -h to see help info.\n");
		exit(-1);
	}
}


void load_pcapfiles()
{
	std::ifstream fin;
	fin.open(_run_settings.pcap_files_file.c_str());
	if(!fin.is_open()){
		printf("Can't open filenames file: %s\n",_run_settings.pcap_files_file.c_str());
		exit(-1);
	}

	std::string file;
	fin >> file;
	while(!fin.eof())
	{
		if(!file.empty())_global.pcap_files.push_back(file);
		fin >> file;
	}
	fin.close();
}

void load_queries()
{
	std::ifstream fin;
	fin.open(_run_settings.query_file.c_str());
	if(!fin.is_open()){
		printf("Can't open filenames file: %s\n",_run_settings.query_file.c_str());
		exit(-1);
	}
	
	struct Query q;
	char buff[512];
	fin>>q.query.proto>>q.query.ip1>>q.query.port1>>q.query.ip2>>q.query.port2>>q.query.time_start>>q.query.time_end>>q.result_filename;
	while(!fin.eof())
	{	
		q.result_filename = "query_result/" + q.result_filename;
		sprintf(buff,"proto %s ip1 %s port1 %d ip2 %s port2 %d start %f end %f\0",q.query.proto.c_str(),q.query.ip1.c_str(),
				q.query.port1,q.query.ip2.c_str(),q.query.port2,q.query.time_end,q.query.time_end);
		q.filter.assign(buff);
		_global.queries.push_back(q);
		fin>>q.query.proto>>q.query.ip1>>q.query.port1>>q.query.ip2>>q.query.port2>>q.query.time_start>>q.query.time_end>>q.result_filename;
	}
	fin.close();
}	

void init()
{
	load_pcapfiles();
	load_queries();
    mysql_init(&_global.mysql);
    if( NULL == mysql_real_connect(&_global.mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PASSWD,MYSQL_DB,0,NULL,0)){
        printf("ERROR: MYSQL CAN'T GET CONNECTED! mysql_real_connect()\n");
        exit(-1);
    }
#ifdef _DEBUG_
	int size = _global.pcap_files.size();
	printf("There are %d pcap files. They are:\n",size);
	for(int i = 0 ; i < size ; i++ )printf("pcap file:%s\n",_global.pcap_files[i].c_str());
	size = _global.queries.size();
	printf("There are %d queries. They are:\n",size);
	for(int i = 0 ; i < size ; i++ )printf("query:%s\n",_global.queries[i].filter.c_str());
#endif
}

void doExit()
{
    if(_global.res != NULL)mysql_free_result(_global.res);
    _global.res = NULL;
    mysql_close(&_global.mysql);
}

void doQuery(const query_t& q)
{

  	_global.res = NULL;

	char perequisite[100]="\0";

	int proto = 0;
	if(q.proto == "tcp")proto = 6;
	else if(q.proto == "udp")proto = 17;

	struct in_addr ip1;
	if( q.ip1 == "0")memset(&ip1,0,sizeof(struct in_addr));
	else if( ! inet_aton(q.ip1.c_str(),&ip1) )printf("Error: ip1 |%s| \n",q.ip1.c_str());

	struct in_addr ip2;
	if( q.ip2 == "0")memset(&ip2,0,sizeof(struct in_addr));
	else if( ! inet_aton(q.ip2.c_str(),&ip2) )printf("Error: ip2 |%s| \n",q.ip2.c_str());

	if(proto){
		if(q.time_start > 1e-3){
			if(q.time_end > 1e-3){
				sprintf(perequisite," proto = %d and %f <= time <= %f and ",proto,q.time_start,q.time_end);
			}else{
				sprintf(perequisite," proto = %d and %f <= time and ",proto,q.time_start);
			}
		}else{
			if(q.time_end > 1e-3){
				sprintf(perequisite," proto = %d and time <= %f and ",proto,q.time_end);
			}
		}	
	}else{
		if(q.time_start > 1e-3){
			if(q.time_end > 1e-3){
				sprintf(perequisite," %f <= time <= %f and ",q.time_start,q.time_end);
			}else{
				sprintf(perequisite," %f <= time and ",q.time_start);
			}
		}else{
			if(q.time_end > 1e-3){
				sprintf(perequisite,"  time <= %f and ",q.time_end);
			}
		}	
	}

	unsigned char *pos1 = (unsigned char *)&ip1;
	unsigned char *pos2 = (unsigned char *)&ip2;
	
	if( q.ip1 != "0" )
	{
		if( q.ip2 != "0")
		{
			if(q.port1)
			{
				if(q.port2)
				{//connection4
						sprintf(qrybuff,"select pcapfile,offset from %s where %s (sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 = %d and sport = %d and dport = %d or sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d and sport= %d and dport = %d )\0", MYSQL_TABLE, perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],q.port1,q.port2,pos2[0],pos2[1],pos2[2],pos2[3],pos1[0],pos1[1],pos1[2],pos1[3],q.port2,q.port1);
				}else{ // connection3
					sprintf(qrybuff,"select pcapfile,offset from %s where %s (sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 = %d and sport = %d or sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d and dport = %d) \0", MYSQL_TABLE,perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],q.port1,pos2[0],pos2[1],pos2[2],pos2[3],pos1[0],pos1[1],pos1[2],pos1[3],q.port1);
				}
			}else{//connection2
				sprintf(qrybuff,"select pcapfile,offset from %s where %s (sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 = %d or sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d )\0", MYSQL_TABLE,perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],pos2[0],pos2[1],pos2[2],pos2[3],pos1[0],pos1[1],pos1[2],pos1[3]);
			}
		}else{// connection1
			sprintf(qrybuff,"select pcapfile,offset from %s where %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d or dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d )\0", MYSQL_TABLE,perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos1[0],pos1[1],pos1[2],pos1[3]);
		}
	}else{
		printf("Error: empty query. at least connection1 !\n");
		return;
	}
   	qrybuff[MAX_QUERY_LEN] = '\0';
	if( strlen(qrybuff) >= MAX_QUERY_LEN - 1 ){
		printf("ERROR: query len exceeds MAX_QUERY_LEN, which is set %d\n",MAX_QUERY_LEN);
		return;
	}
    mysql_real_query(&_global.mysql,qrybuff,strlen(qrybuff));
    _global.res = mysql_store_result(&_global.mysql); 
    if(_global.res == NULL){
		printf("WARNING: a query without results! \nERRORMSG: |%s|\nQUERY:|%s|\n",mysql_error(&_global.mysql),qrybuff);
		return;
	}
}

void produceResult(const std::string& filename)
{
    if(_global.res == NULL)return;

	std::vector<int> pcapfileno;
	std::vector<int> pcapoffset;
	MYSQL_ROW row;

	do{
		if( mysql_num_fields(_global.res) != 2 ){
			printf("ERROR: really strange things happen, mysql give result that has not 2 fields!\n");
			break;
		}
		while(row   =   mysql_fetch_row(_global.res))
		{
			pcapfileno.push_back(atoi(row[0]));
			pcapoffset.push_back(atof(row[1]));
		}
	}while(0);

    mysql_free_result(_global.res);
    _global.res = NULL;


	if(pcapfileno.size() != pcapoffset.size()){
		printf("Error: size don't match. This may not happen!\n");
		return;
	}

#ifdef _DEBUG_
	printf("SQL gives %d results.\n",pcapfileno.size());
	for(int i = 0;i<pcapfileno.size();i++)printf("file: %d offset:%d\n",pcapfileno[i],pcapoffset[i]);
#endif
	
	char errbuf[PCAP_ERRBUF_SIZE]="\n";
	pcap_t * ph = pcap_open_offline(_global.pcap_files[0].c_str(),errbuf);
	pcap_close(ph);
	pcap_dumper_t * pdp = NULL;

	pdp = pcap_dump_open(ph, filename.c_str());

	if(NULL == pdp)printf("ERROR: can'nt open dump file |%s|\n",filename.c_str());

	int readnum;
	int size = pcapfileno.size();
	FILE * fp = NULL;
	int openfileno = 0;
	struct pcap_pkthdr hdr;	
	const unsigned char * pkt = NULL;
	for( int i = 0 ; i < size ; i++ )
	{
		if(NULL == fp || openfileno != pcapfileno[i]){
			if(fp)fclose(fp);
			openfileno = pcapfileno[i];
			fp = fopen(_global.pcap_files[openfileno - 1].c_str(),"rb");
			if(NULL == fp){
				printf("Error: fopen can't open filenames file: %s\n",_global.pcap_files[openfileno - 1].c_str());
				//while( openfileno == pcapfileno[i])i++;
				continue;
			}
		}
		
		pkt = NULL;
		if( 0 != fseek(fp,pcapoffset[i],SEEK_SET) ){
#ifdef _DEBUG_
			printf("Error: fseek can't move to offset %d\n",pcapoffset[i]);
#endif
		}else{
			readnum = fread(&hdr,1,sizeof(struct pcap_pkthdr),fp);
			if( readnum != sizeof(struct pcap_pkthdr) ){
#ifdef _DEBUG_
				printf("Error: fread can't read enough bytes of a pcap_pkthdr. want %d read %d\n",sizeof(struct pcap_file_header),readnum);
#endif
			}else{
				readnum = fread(pktbuff,1,hdr.caplen,fp);
				if( hdr.caplen != readnum ){
#ifdef _DEBUG_
					printf("Error: fread can't read enough bytes of a packet. want %d read %d\n",hdr.caplen,readnum);
#endif
				}else{
					pkt = pktbuff;
				}
			}
		}

		if(pkt)pcap_dump((unsigned char *)pdp,&hdr,pkt);
		else printf("Error: no paket in offset %d in %s\n",pcapoffset[i],_global.pcap_files[openfileno - 1].c_str());

	}
	pcap_dump_close(pdp);
	if(fp)fclose(fp);
}

void runQuery()
{
	system("rm query_result/* -rf");

	double query_time = 0;
	double pcap_time = 0;

	struct timeval t_start,t_end;
	for(int i = 0 ; i < _global.queries.size(); i++ )
	{
		printf("query: %d\n",i+1);
		gettimeofday(&t_start,NULL);
		doQuery(_global.queries[i].query);
		gettimeofday(&t_end,NULL);
		query_time += ( TO_MYTIME(t_end) - TO_MYTIME(t_start) );
		printf("time for querying         : %f\n",( TO_MYTIME(t_end) - TO_MYTIME(t_start) ));

		gettimeofday(&t_start,NULL);
		produceResult(_global.queries[i].result_filename);
		gettimeofday(&t_end,NULL);
		pcap_time += ( TO_MYTIME(t_end) - TO_MYTIME(t_start) );
		printf("time for generating result: %f\n",( TO_MYTIME(t_end) - TO_MYTIME(t_start) ));

	}

	printf("---------program statistic-----------\n");
	printf("time for querying         : %f\n",query_time);
	printf("time for generating result: %f\n",pcap_time);

}

int main(int argc, char** argv)
{
	parseOptions(argc,argv);
	init();
	struct timeval t_start,t_end;
    printf("Hello World! I'm starting working now!\n");

	gettimeofday(&t_start,NULL);
	runQuery();
	gettimeofday(&t_end,NULL);
	
	double dt_start = TO_MYTIME(t_start);
	double dt_end = TO_MYTIME(t_end);
	double dt_cost = dt_end - dt_start;
	printf("program start time:%f\n",dt_start);
	printf("program end time:%f\n",dt_end);
	printf("program cost time:%f\n",dt_cost);

	doExit();
    return 0;
}
