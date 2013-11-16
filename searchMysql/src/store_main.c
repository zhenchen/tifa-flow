#include "header.h"
#include "my_sql.h"

//#define _DEBUG_

#ifdef _DEBUG_ALL_
#ifndef _DEBUG_
#define _DEBUG_
#endif
#endif

struct RuningSettings{
	std::string pcap_file;
	std::string pcap_filename_file;
	std::string pcap_intf;
} _run_settings;

struct GlobalValue{
	long long pkts_number;
	long long pkts_capsize;
	long long pkts_size;
	double time_start;
	double time_end;
	int offset;
	int pcapfilenow;
	pcap_t * _pcap_h;	
	pthread_t _pcap_thread;
	MySQL * _sql;
} _global;


void printHelpInfo()
{
	printf("\n");
	printf("Usage: test (-F pcap_files_file or -f pcap_file) -p index_part_output\n");
	printf("-h\t      \t\t show this help         \n");
	printf("-f\t<file>\t\t choose capture file to read from \n");
	printf("-F\t<file>\t\t choose file to read files names from\n");
	printf("-i\t<interface>\t\t choose pcap interface\n");
	printf("-p\t<file>\t\t choose index part info output file\n");
	printf("\n");
	exit(0);
}


void parseOptions(int argc, char **argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "hf:o:F:i:p:")) != EOF) {
		switch (opt) {
			case 'h':
				printHelpInfo();
				break;
	/*		case 'f':
				_run_settings.pcap_file.assign(optarg);
				break;
	*/		case 'F':
				_run_settings.pcap_filename_file.assign(optarg);
				break;
			case 'i':
				_run_settings.pcap_intf.assign(optarg);
				break;
		}
	}

	// check if the options are setted
	if( _run_settings.pcap_filename_file.empty() && _run_settings.pcap_file.empty() && _run_settings.pcap_intf.empty() ){
		printf("No Input !\nPlease use -h to see help info.\n");
		exit(-1);
	}
}


void pcap_callback(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) 
{
	_global.pkts_number++;
	_global.pkts_size += header->len;
	_global.pkts_capsize += header->caplen;
	double time = TO_MYTIME(header->ts);
	if(_global.time_start < 1e-6 )_global.time_start = time;
	if( time > _global.time_end )_global.time_end = time;

	unsigned char protocol = IP(packet)->ip_p;
	unsigned char * pos = (unsigned char*)IP(packet)+IP_HDR_LEN(packet);
	unsigned short sport = pos[0]*256 + pos[1];
	unsigned short dport = pos[2]*256 + pos[3];
	struct in_addr sip,dip;
	memcpy(&sip,& IP(packet)->ip_src, 4);
	memcpy(&dip,& IP(packet)->ip_dst, 4);
#ifdef _DEBUG_
	switch (protocol) {
		case IPPROTO_UDP:{		// 17
			const unsigned char* p_sip = (unsigned char *)&sip; 
			const unsigned char* p_dip = (unsigned char *)&dip; 
			printf("UDP srcIP %d.%d.%d.%d dstIP %d.%d.%d.%d srcPort %d dstPort %d\n",p_sip[0],p_sip[1],p_sip[2],p_sip[3],p_dip[0],p_dip[1],p_dip[2],p_dip[3],sport,dport);
		}
		break;
		case IPPROTO_TCP:{		// 6
			const unsigned char* p_sip = (unsigned char *)&sip; 
			const unsigned char* p_dip = (unsigned char *)&dip; 
			printf("TCP srcIP %d.%d.%d.%d dstIP %d.%d.%d.%d srcPort %d dstPort %d\n",p_sip[0],p_sip[1],p_sip[2],p_sip[3],p_dip[0],p_dip[1],p_dip[2],p_dip[3],sport,dport);
		}
		break;
	
	}
#endif
	if(protocol != IPPROTO_TCP && protocol != IPPROTO_UDP){
		protocol = 0;
		sport = 0;
		dport = 0;
	}
	if(_global._sql)_global._sql->addRow(sip,dip,sport,dport,protocol,time,_global.pcapfilenow,_global.offset);
	_global.offset += (sizeof(struct pcap_pkthdr) + header->caplen);
}

/*void * pcap_capture_thread(void * arg)
{
	pcap_loop(_global._pcap_h, -1, (pcap_handler)pcap_callback, NULL);	
}*/

void runPcapBatchMode()
{
	
	char errbuf[PCAP_ERRBUF_SIZE]="\0";
	std::ifstream fin;
	fin.open(_run_settings.pcap_filename_file.c_str());
	if(!fin.is_open()){
		printf("Can't open filenames file: %s\n",_run_settings.pcap_filename_file.c_str());
		exit(-1);
	}

	std::vector<std::string> files;
	std::string file;
	fin >> file;
	while(!fin.eof())
	{
		files.push_back(file);
		fin >> file;
	}
	fin.close();

	for(int i = 0; i < files.size() ; i++)
	{
		_global._pcap_h = pcap_open_offline(files[i].c_str(),errbuf);
		if(!_global._pcap_h){
			printf("Error: PCAP OPEN ERROR! ErrMsg:%s file:|%s|\n",errbuf,files[i].c_str());
		}else{
			_global.pcapfilenow = i + 1;
			_global.offset = sizeof(struct pcap_file_header);
			printf("Processing file: %s \n",files[i].c_str());
			pcap_loop(_global._pcap_h, -1, (pcap_handler)pcap_callback, NULL);	
			pcap_close(_global._pcap_h);
			_global._pcap_h = NULL;
		}
	}
}

void runPcap()
{
	char errbuf[PCAP_ERRBUF_SIZE]="\n";
	if( !_run_settings.pcap_filename_file.empty() ){
			runPcapBatchMode();
			return;
	}else if( !_run_settings.pcap_file.empty() ){
		_global._pcap_h = pcap_open_offline(_run_settings.pcap_file.c_str(),errbuf);
	}else{
		if( _run_settings.pcap_intf.empty() ){
			printf("Error: No inputs!\n");
			exit(-1);
		}
		_global._pcap_h = pcap_open_live(_run_settings.pcap_intf.c_str(),MAXSNAPLEN,1,PCAPTIMEOUT,errbuf);
	}

	if(!_global._pcap_h){
		printf("Error: PCAP OPEN ERROR! ErrMsg:%s\n",errbuf);
		exit(-1);
	}

	pcap_loop(_global._pcap_h, -1, (pcap_handler)pcap_callback, NULL);	

	/*if( 0 != pthread_create(&_global._pcap_thread,NULL,pcap_capture_thread,NULL) ){
		pcap_close(_global._pcap_h);
		printf("Error: can't start pcap capture thread");
		exit(-1);
	}*/
}

void doExit()
{
	if( _global._pcap_h){
		pcap_close(_global._pcap_h);
		_global._pcap_h = NULL;
	}

	/*
	   delete _global._sql;
	 */
}	

void init()
{
	_global._pcap_h = NULL;
	_global.pkts_number = 0;
	_global.pkts_capsize = 0;
	_global.pkts_size = 0;
	_global.offset = sizeof(struct pcap_file_header);
	_global.pcapfilenow = 0;
	system("rm -rf index/*");
	system("mkdir index/index");
	system("mkdir index/tmp");
	_global._sql =  new MySQL();
}

int main(int argc, char** argv)
{
	parseOptions(argc,argv);
	init();

	struct timeval t_start,t_end;
    printf("Hello World! I'm starting working now!\n");

	gettimeofday(&t_start,NULL);
	runPcap();
	gettimeofday(&t_end,NULL);
	
	printf("---------trace statistic-----------\n");
	printf("Total Pkts: %lld, capsize: %lld, size: %lld\n",_global.pkts_number,_global.pkts_capsize,_global.pkts_size);
	printf("Trace start time: %f, end time %f, time last: %f\n",_global.time_start,_global.time_end,_global.time_end - _global.time_start);

	double dt_start = t_start.tv_sec + t_start.tv_usec/1000000.;
	double dt_end = t_end.tv_sec + t_end.tv_usec/1000000.;
	double dt_cost = dt_end - dt_start;
	printf("---------program statistic-----------\n");
	printf("program start time:%f\n",dt_start);
	printf("program end time:%f\n",dt_end);
	printf("program cost time:%f\n",dt_cost);

	doExit();
    return 0;
}
