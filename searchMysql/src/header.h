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


#include <mysql/mysql.h>

#define MAXSNAPLEN 8192
#define PCAPTIMEOUT 60000

#define MYSQL_HOST      "localhost"
#define MYSQL_USER      ""
#define MYSQL_PASSWD    ""
#define MYSQL_DB        "traceinfo"
#define MYSQL_TABLE     "day"

#define MAX_QUERY_LEN   2000

#define TO_MYTIME(X) ( (double)X.tv_sec + X.tv_usec/1000000. )

#define ETHERNET(packet)    ((struct ether_header *)packet)
#define IP(packet)          ((struct ip *)(packet+ETHER_HDR_LEN))
#define IP_HDR_LEN(packet)	(IP(packet)->ip_hl*4)
#define TCP(packet)         ((struct tcphdr *)((char*)IP(packet)+IP_HDR_LEN(packet)))
#define UDP(packet)         ((struct udphdr *)((char*)IP(packet)+IP_HDR_LEN(packet)))



#endif
