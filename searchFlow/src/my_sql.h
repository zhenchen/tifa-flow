#ifndef _MY_SQL_
#define _MY_SQL_

#include "header.h"

#define ROW_PER_PART 10000000
#define ROW_PER_DUMP 500000

typedef struct{
	double time_oldest;
	double time_latest;
	std::string part_name;
}PartAttribute;

class MySQL
{
public:
	MySQL(std::string& partinfo_outfile);
	~MySQL();
	void addRec(struct in_addr sip,struct in_addr dip,unsigned short sport,unsigned short dport,int protocol, double time_start,double time_end,int fileno, int offset, int len);
private:
	void onInit();
	void processDump();
	void dump(char * dst, char * src);
	void getTmpFileName(char * filename);
	void getPartDirNow(char* filename);

	std::vector<PartAttribute> parts;
	std::string partoutfile;
	FILE * fp;
	unsigned int tmp_file;
	unsigned int tmp_rows;
	unsigned int pcap_file;

	unsigned int part_name;
	unsigned int rows_thispart;
	double time_part_oldest;

	long long tot_rows;
	double time_oldest;
	double time_latest;

};
#endif
