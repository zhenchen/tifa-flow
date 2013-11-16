#include "header.h"

//#define _DEBUG_


#ifdef _DEBUG_ALL_
#ifndef _DEBUG_
#define _DEBUG_
#endif
#endif

unsigned char pktbuff[MAXSNAPLEN];

#define MAX_PEREQUI_LEN		100
#define	MAX_QUERY_LEN		1000
#define MAX_CMD_LEN			2000
#define MAX_FILENAME_LEN 	50

char perequisite[MAX_PEREQUI_LEN]="\0";
char querystr[MAX_QUERY_LEN]="\0";
char cmd[MAX_CMD_LEN]="\0";
char filename[MAX_FILENAME_LEN]="\0";

struct PartAttribute
{
	double time_oldest;
	double time_latest;
	std::string dir_name;
};

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
	std::string part_file;
	std::string query_file;
} _run_settings;

struct GlobalValue{
	std::vector<std::string> pcap_files;
	std::vector<struct PartAttribute> part_dirs;
	std::vector<struct Query> queries;
} _global;

void printHelpInfo()
{
	printf("Usage: test -f pcap_files_file -q querrt_file -p part_file\n");
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
			case 'p':
				_run_settings.part_file.assign(optarg);
				break;
		}
	}

	// check if the options are setted
	if( _run_settings.pcap_files_file.empty() || _run_settings.query_file.empty() ||  _run_settings.part_file.empty() ){
		printf("Lack option ! Please use -h to see help info.\n");
		exit(-1);
	}
}

#define ETHERNET(packet)    ((struct ether_header *)packet)
#define IP(packet)          ((struct ip *)(packet+ETHER_HDR_LEN))
#define IP_HDR_LEN(packet)	(IP(packet)->ip_hl*4)
#define TCP(packet)         ((struct tcphdr *)((char*)IP(packet)+IP_HDR_LEN(packet)))
#define UDP(packet)         ((struct udphdr *)((char*)IP(packet)+IP_HDR_LEN(packet)))


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

void doExit()
{
}

void load_index_parts()
{
	std::ifstream fin;
	fin.open(_run_settings.part_file.c_str());
	if(!fin.is_open()){
		printf("Can't open filenames file: %s\n",_run_settings.part_file.c_str());
		exit(-1);
	}
	
	struct PartAttribute pa;
	fin>>pa.time_oldest>>pa.time_latest>>pa.dir_name;
	while(!fin.eof())
	{
		_global.part_dirs.push_back(pa);
		fin>>pa.time_oldest>>pa.time_latest>>pa.dir_name;
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
	load_index_parts();
	load_queries();
#ifdef _DEBUG_
	int size = _global.pcap_files.size();
	printf("There are %d pcap files. They are:\n",size);
	for(int i = 0 ; i < size ; i++ )printf("pcap file:%s\n",_global.pcap_files[i].c_str());
	size = _global.part_dirs.size();
	printf("There are %d index part dirs. They are:\n",size);
	for(int i = 0 ; i < size ; i++ )printf("index part dir:%s\n",_global.part_dirs[i].dir_name.c_str());
	size = _global.queries.size();
	printf("There are %d queries. They are:\n",size);
	for(int i = 0 ; i < size ; i++ )printf("query:%s\n",_global.queries[i].filter.c_str());
#endif
}

void doQuery(const query_t& q,int& tmpfile)
{
	int tmpfile_oldest = tmpfile;

	perequisite[MAX_PEREQUI_LEN]='\0';
	querystr[MAX_QUERY_LEN]='\0';
	cmd[MAX_CMD_LEN]='\0';
	filename[MAX_FILENAME_LEN]='\0';

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
						sprintf(querystr,"select pcapfile,offset where %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 = %d and sport = %d and dport = %d or %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d and sport= %d and dport = %d \0", perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],q.port1,q.port2,perequisite,pos2[0],pos2[1],pos2[2],pos2[3],pos1[0],pos1[1],pos1[2],pos1[3],q.port2,q.port1);
				}else{ // connection3
					sprintf(querystr,"select pcapfile,offset where %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 = %d and sport = %d or %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d and dport = %d \0", perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],q.port1,perequisite,pos2[0],pos2[1],pos2[2],pos2[3],pos1[0],pos1[1],pos1[2],pos1[3],q.port1);
				}
			}else{//connection2
				sprintf(querystr,"select pcapfile,offset where %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 = %d or %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d and dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d \0", perequisite,pos1[0],pos1[1],pos1[2],pos1[3],pos2[0],pos2[1],pos2[2],pos2[3],perequisite,pos2[0],pos2[1],pos2[2],pos2[3],pos1[0],pos1[1],pos1[2],pos1[3]);
			}
		}else{// connection1
			sprintf(querystr,"select pcapfile,offset where %s sip1 = %d and sip2 = %d and sip3 = %d and sip4 = %d or %s dip1 = %d and dip2 = %d and dip3 = %d and dip4 =%d \0", perequisite,pos1[0],pos1[1],pos1[2],pos1[3],perequisite,pos1[0],pos1[1],pos1[2],pos1[3]);
		}
	}else{
		printf("Error: empty query. at least connection1 !\n");
		return;
	}

	cmd[MAX_CMD_LEN]='\0';
	if(strlen(cmd) >= MAX_CMD_LEN -1){
		printf("Error: cmd exceeds MAX_CMD_LEN, which is set %d, in doQuery() !\n",MAX_CMD_LEN);
		return;
	}

	for(int i = 0 ; i < _global.part_dirs.size(); i++ )
	{
		if( (q.time_start < 1e-3 + _global.part_dirs[i].time_latest ) && (( q.time_end + 1e-3 > _global.part_dirs[i].time_oldest) || (q.time_end < 1e-3)) ){
			sprintf(filename,"query_result/tmp/tmp%08xraw\0",tmpfile);

			sprintf(cmd,"./ibis -d %s -q '%s' -output %s > /dev/null\0",_global.part_dirs[i].dir_name.c_str(),querystr,filename);
#ifdef _DEBUG_
			printf("SYSTEM CMD:\n|%s|\n",cmd);
#endif
			system(cmd);

			if(0 == access(filename,F_OK)){
				sprintf(cmd,"sed -i '1d' %s\0",filename);
#ifdef _DEBUG_
				printf("SYSTEM CMD:\n|%s|\n",cmd);
#endif
				system(cmd);

				sprintf(cmd,"cut -d ',' -f 1 %s > %s1\0",filename,filename);
#ifdef _DEBUG_
				printf("SYSTEM CMD:\n|%s|\n",cmd);
#endif
				system(cmd);

				sprintf(cmd,"cut -d ',' -f 2 %s > %s2\0",filename,filename);
#ifdef _DEBUG_
				printf("SYSTEM CMD:\n|%s|\n",cmd);
#endif
				system(cmd);

				sprintf(filename,"query_result/tmp/tmp%08x\0",tmpfile);
				sprintf(cmd,"paste %sraw1 %sraw2 > %s\0",filename,filename,filename);
#ifdef _DEBUG_
				printf("SYSTEM CMD:\n|%s|\n",cmd);
#endif
				system(cmd);

				system("rm query_result/tmp/*raw*");
				tmpfile++;
			}
		}
	}
}

void produceResult(const std::string& filename, int tmpfileold,int tmpfilenow)
{
	char indexfile[64] = "\0";
	std::ifstream fin;
	std::vector<int> pcapfileno;
	std::vector<int> pcapoffset;

#ifdef _DEBUG_
	printf("tmpfileold: %d, tmpfilenow: %d \n",tmpfileold,tmpfilenow);
#endif
	for(;tmpfileold < tmpfilenow; tmpfileold++)
	{
		sprintf(indexfile,"query_result/tmp/tmp%08x\0",tmpfileold);
		fin.open(indexfile);
		if(!fin.is_open()){
			printf("Error: Can't open filenames file: %s\n",indexfile);
			continue;
		}
		int tmp1,tmp2;
		fin >> tmp1 >> tmp2;
		while(!fin.eof())
		{
			pcapfileno.push_back(tmp1);
			pcapoffset.push_back(tmp2);
			fin >> tmp1 >> tmp2;
		}
		fin.close();
	}

	if(pcapfileno.size() != pcapoffset.size()){
		printf("Error: size don't match. This may not happen!\n");
		return;
	}
	
	char errbuf[PCAP_ERRBUF_SIZE]="\n";
	pcap_t * ph = pcap_open_offline(_global.pcap_files[0].c_str(),errbuf);
	pcap_close(ph);
	pcap_dumper_t * pdp = NULL;

	pdp = pcap_dump_open(ph, filename.c_str());
	if(NULL == pdp)printf("ERROR: can'nt open dump file |%s|\n",filename.c_str());

	int size = pcapfileno.size();
	FILE * fp = NULL;
	int openfileno = 0;
	struct pcap_pkthdr hdr;	
	int readnum;
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
	system("mkdir  query_result/tmp");
	int tmpfile = 1;
	int tmpfilenow = 1;

	double query_time = 0;
	double pcap_time = 0;

	struct timeval t_start,t_end;
	for(int i = 0 ; i < _global.queries.size(); i++ )
	{
		printf("query: %d\n",i+1);
		gettimeofday(&t_start,NULL);
		doQuery(_global.queries[i].query,tmpfilenow);
		gettimeofday(&t_end,NULL);
		query_time += ( TO_MYTIME(t_end) - TO_MYTIME(t_start) );
		printf("time for querying         : %f\n",( TO_MYTIME(t_end) - TO_MYTIME(t_start) ));

		gettimeofday(&t_start,NULL);
		produceResult(_global.queries[i].result_filename,tmpfile,tmpfilenow);
		gettimeofday(&t_end,NULL);
		pcap_time += ( TO_MYTIME(t_end) - TO_MYTIME(t_start) );
		printf("time for generating result: %f\n",( TO_MYTIME(t_end) - TO_MYTIME(t_start) ));

		tmpfile = tmpfilenow;
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
