#include "my_sql.h"

void MySQL::onInit()
{
	part_name = 0;
	rows_thispart = 0;

	tot_rows = 0;

	time_oldest = 0;
	time_latest = 0;

	time_part_oldest = 0;

	pcap_file = 0;
	fp = NULL;
	tmp_file = 0;
	tmp_rows = 0;

	offset = sizeof(struct pcap_file_header);
}

MySQL::MySQL(std::string& partinfo_outfile)
{
	onInit();	
	partoutfile = partinfo_outfile;
}

MySQL::~MySQL()
{
	//TODO:
	if( 0 == access(partoutfile.c_str(),F_OK)){
		char cmd[1024];
		sprintf(cmd,"rm -rf %s\0",partoutfile.c_str());
	}
	FILE * fh = fopen(partoutfile.c_str(),"w");
	for(int i = 0; i < parts.size();i++)fprintf(fh,"%f %f %s\n",parts[i].time_oldest,parts[i].time_latest,parts[i].part_name.c_str());
	char filename[100];
	getPartDirNow(filename);
	fprintf(fh,"%f %f %s\n",time_part_oldest,time_latest,filename);
	fclose(fh);
}

void MySQL::setNowFile(int file)
{
	pcap_file = (unsigned int)file;
	offset = sizeof(struct pcap_file_header);
}


void MySQL::addRow(struct in_addr sip,struct in_addr dip,unsigned short sport,unsigned short dport, int protocol, double time,int len)
{
	if( time_oldest < 1e-6 )time_oldest = time;
	if( time_part_oldest < 1e-6)time_part_oldest = time;
	if( time > time_latest )time_latest = time;
	if(!fp){
		tmp_rows = 0;
		char filename[100];
		tmp_file++;
		getTmpFileName(filename);
		fp = fopen(filename,"w");
	}
	if(fp){
		unsigned char * pos = (unsigned char *)&sip;
		fprintf(fp,"%d,%d,%d,%d,",pos[0],pos[1],pos[2],pos[3]);	
		pos = (unsigned char *)&dip;
		fprintf(fp,"%d,%d,%d,%d,",pos[0],pos[1],pos[2],pos[3]);	
		fprintf(fp,"%d,%d,",sport,dport);
		fprintf(fp,"%d,%f,",protocol,time);
		fprintf(fp,"%d,%d\n",pcap_file,offset);
		offset += (sizeof(struct pcap_pkthdr) + len);
		tot_rows++;
		tmp_rows++;
		if(tmp_rows == ROW_PER_DUMP){
			fclose(fp);
			fp = NULL;
			processDump();
		}
	}
}

void MySQL::getTmpFileName(char * filename)
{
#ifdef _DEBUG_
	assert(filename);
#endif
	sprintf(filename,"index/tmp/tmp%08x\0",tmp_file);
}

void MySQL::getPartDirNow(char* filename)
{
#ifdef _DEBUG_
	assert(filename);
#endif
	sprintf(filename,"index/index/index%08x\0",part_name);
}

void MySQL::processDump()
{
	char sfile[100],dfile[100];
	if(rows_thispart == 0){
		part_name ++;
		getPartDirNow(dfile);
		if(!access(dfile,0))mkdir(dfile,0666);
	}
	getTmpFileName(sfile);
	getPartDirNow(dfile);
	dump(dfile,sfile);
	rows_thispart += ROW_PER_DUMP;
	if(rows_thispart >= ROW_PER_PART){
		PartAttribute pa;
		pa.time_oldest = time_part_oldest;
		pa.time_latest = time_latest;
		pa.part_name.assign(dfile);
		parts.push_back(pa);
		rows_thispart = 0;
		time_part_oldest = 0;
	}
}

void MySQL::dump(char * dst, char * src)
{
	char cmd[1024];
	sprintf(cmd,"./ardea -d %s -m 'sip1:unsigned byte,sip2:unsigned byte,sip3:unsigned byte,sip4:unsigned byte \
			,dip1:unsigned byte,dip2:unsigned byte,dip3:unsigned byte,dip4:unsigned byte,sport:unsigned short,dport:unsigned short \
			,proto:int,time:double,pcapfile:int,offset:int' -t %s >>storelog 2>&1\0",dst,src);
	system(cmd);
}
