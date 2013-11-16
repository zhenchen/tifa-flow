#ifndef _MY_HEADER_
#define _MY_HEADER_

//#define _DEBUG_ALL_

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>

#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <pcap.h>

#include <vector>


#define MAXSNAPLEN 8192
#define PCAPTIMEOUT 60000

#define TO_MYTIME(X) ( (double)X.tv_sec + X.tv_usec/1000000. )

#endif
