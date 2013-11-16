#include "connections.h"

//#define _DEBUG_

unsigned int hash3elem(int a, int b, int c)
{
	return a*b+a+b+c;
}

Dumper::Dumper(MySQL * _sql,unsigned int _fileno)
{
	sql = _sql;
	fileno = _fileno;
	totsize = 0;
	offset = 0;

	char file[50] = "\0";
	char errbuf[PCAP_ERRBUF_SIZE]="\n";

	sprintf(file,"%s/trace_%08x.pcap\0",TRACE_PATH,fileno);
	filename.assign(file);

	pcap_t * ph  = pcap_open_live("eth0",MAXSNAPLEN,1,PCAPTIMEOUT,errbuf);
	pcap_close(ph);

	pdump = pcap_dump_open(ph, filename.c_str());
	if(NULL == pdump)printf("ERROR: can'nt open dump file |%s|\n",filename.c_str());

}

Dumper::~Dumper()
{
	sleep(1);
	if(pdump) pcap_dump_close(pdump);
}

bool Dumper::is_full()
{
	if(offset >= TRACEFILE_SIZE)return true;
	else return false;
}

void Dumper::close()
{
	if(pdump){
		if( -1 == pcap_dump_flush(pdump) )printf("Error: pcap_dump_flush error\n");
		pcap_dump_close(pdump);
		pdump = NULL;
	}
}

void Dumper::dump(Connection* c)
{
#ifdef _DEBUG_
	//printf("dump():dump a conn!\n");
#endif
	ConnectionID cid = c->getID();
	int sectlen  = 0;
	pkt_buff_t * start = c->p_first;
	if(!start)printf("Error: Dumper::dump() empty connection received!\n");
	while(start){
		sectlen += (sizeof(struct pcap_pkthdr) + (start->hdr)->caplen );
		pcap_dump((unsigned char *)pdump,start->hdr,start->pkt);
		start = start->next;
	};
	sql->addRec(cid.srcIP(),cid.dstIP(),cid.srcPort(),cid.dstPort(),cid.protocol(),c->time_oldest,c->time_latest,fileno,offset,sectlen);
	offset += sectlen;
}

bool ConnectionID::equals(ConnectionID id)
{
	struct in_addr _ip1, _ip2;
	_ip1 = id.srcIP();
	_ip2 = id.dstIP();
	if( INT(ip1) == INT(_ip1) &&
		INT(ip2) == INT(_ip2) &&
		port1 == id.srcPort() &&
		port2 == id.dstPort() &&
		proto == id.protocol()
	)return true;

	if( INT(ip2) == INT(_ip1) &&
		INT(ip1) == INT(_ip2) &&
		port2 == id.srcPort() &&
		port1 == id.dstPort() &&
		proto == id.protocol()
	)return true;

	return false;
}

Connection::Connection(ConnectionID _id):id(_id)
{
	c_prev = c_next = NULL;
	t_older = t_newer = NULL;
	p_first = p_last = NULL;

	time_oldest = 0;
	time_latest = 0;

	tot_pkt_size = 0;

	tot_mem_size = 0;
}

Connection::~Connection()
{
}

unsigned int Connection::addpkt(const struct pcap_pkthdr * header, const unsigned char * packet,double time)
{
	if(time_oldest < 1e-3) time_oldest = time;
	if(time_latest < 1e-3) time_latest = time;
	if(time > time_latest) time_latest = time;

	unsigned int pktmem = 0;
	do{
		if(is_full())break;

		pktmem = (sizeof(struct pcap_pkthdr) + header->caplen);

		pkt_buff_t * newpkt = (pkt_buff_t *)malloc(sizeof(pkt_buff_t));

		newpkt->hdr = (struct pcap_pkthdr *)malloc(sizeof(struct pcap_pkthdr));
		newpkt->pkt = (unsigned char *)malloc(header->caplen);

		memcpy(newpkt->hdr,header,sizeof(struct pcap_pkthdr));
		memcpy(newpkt->pkt,packet,header->caplen);

		newpkt->prev = NULL;
		newpkt->next = NULL;

		if(!p_first){
			p_first = p_last = newpkt;
		}else{
			newpkt->prev = p_last;
			p_last->next = newpkt;
			p_last = newpkt;
		}

		tot_mem_size += pktmem;
	}while(0);

	tot_pkt_size += header->caplen;
	if(tot_pkt_size > 500000)printf("a connection is more than 500KB\n"); //--------------

	return pktmem;
}

unsigned int Connection::freeMem()
{
	pkt_buff_t * tmp1 = p_first;
	pkt_buff_t * tmp2 = p_first->next;
	while(tmp1)
	{
		tmp2 = tmp1->next;
		free(tmp1->hdr);
		free(tmp1->pkt);
		free(tmp1);
		tmp1 = tmp2;
	}
	p_first = p_last = NULL;
	unsigned int freesize = tot_mem_size;
	tot_mem_size = 0;
	tot_pkt_size = 0;
	return freesize;
}

Connections::Connections(std::string& partoutfile)
{
	hsize = H_TABLE_SIZE;

	totmem = 0;
	maxmem = 0;

	htable = new conn_t[hsize];
	for(unsigned int i = 0 ; i< hsize; i++)htable[i] = NULL;

	time_oldest = time_latest = 0;

	oldest_conn = newest_conn = NULL;

	conn_num = 0;

	sql = new MySQL(partoutfile);
	dumper = new Dumper(sql,dumpfileno);
}

Connections::~Connections()
{
	dumpAll();
	if(dumper){
		dumper->close();
		delete dumper;
	}
	if(htable)delete [] htable;
	if(sql)delete sql;
	if( totmem != 0 )printf("Error: Something nasty happens. mem not fully realeased!\n");
	printf("Connections's max mem usage: %u\n",maxmem);
}

void Connections::incDumper()
{
	if(dumper){
		dumper->close();
		delete dumper;
	}
	dumpfileno ++;
	dumper = new Dumper(sql,dumpfileno);

}

void Connections::addpkt(struct in_addr sip, struct in_addr dip, unsigned short sport, unsigned short dport, int protocol,  double time, const struct pcap_pkthdr* pkthdr,const unsigned char* pkt)
{
	ConnectionID id = ConnectionID(sip,dip,sport,dport,protocol);
	conn_t target = htable[id.hash()%hsize];

#ifdef _DEBUG_
	//if(!target)printf("not in hash table, pos: %d \n",id.hash()%hsize);
#endif

	while(target){
#ifdef _DEBUG_
		//printf("hit in hash table\n");
#endif
		if( id.equals(target->getID()) )break;
		target = target->c_next;
	};

	if(time_oldest < 1e-3) time_oldest = time;
	if(time_latest < 1e-3) time_latest = time;
	if(time > time_latest) time_latest = time;

	if(!target){
		target = addConn(id);
#ifdef _DEBUG_
		if(!target)printf("Error:addpkt(): add new conn failed!!!\n");
#endif
	}
	totmem += target->addpkt(pkthdr,pkt,time);
	if(totmem > maxmem) maxmem = totmem;

	mv2newest(target);	
}

void Connections::mv2newest(conn_t c)
{
	// either c is new added conn or c receives new pkt
	// this method will be called
	if(NULL == c)printf("Error: mv2newest() - NULL connection* received!\n");

	// remove it from old place
	if( oldest_conn == c) oldest_conn = c->t_newer;
	if( newest_conn == c) newest_conn = c->t_older;
	if( c->t_newer ) c->t_newer->t_older = c->t_older;
	if( c->t_older ) c->t_older->t_newer = c->t_newer;
	
	// add it to newest
	if( !oldest_conn )oldest_conn = c;
	if( !newest_conn )newest_conn = c;

	c->t_older = newest_conn;
	c->t_newer = NULL;
	if( newest_conn ) newest_conn->t_newer = c;
	newest_conn = c;

	if( oldest_conn )oldest_conn->t_older = NULL;
	if( newest_conn )newest_conn->t_newer = NULL;
}

Connection * Connections::addConn( ConnectionID id)
{
	conn_num++;
	check4dump( time_latest - (double)CON_TIMEOUT );
	unsigned int pos = id.hash()%hsize;

	conn_t tmp1 = htable[pos];
	conn_t tmp2;

	// insert it to hash tables
	if(NULL == tmp1){
		htable[pos] = new Connection(id);
#ifdef _DEBUG_
		printf("addConn():add new conn first in queue hash %u mempos %09x\n",htable[pos]->getID().hash(),(int)htable[pos]);
#endif
		return htable[pos];
	}else{
		tmp2 = tmp1->c_next;
		while(tmp2){
			tmp1 = tmp2;
			tmp2 = tmp2->c_next;
		}
		tmp2 = new Connection(id);
		tmp1->c_next = tmp2;
		tmp2->c_prev = tmp1;
#ifdef _DEBUG_
		printf("addConn():add new conn to collision queue hash %u mempos %09x\n",tmp2->getID().hash(),(int)tmp2);
#endif
		return tmp2;
	}


}

void Connections::dumpConn(conn_t c){
	if(NULL == c)printf("Error: rmConn() - NULL connection* received!\n");
#ifdef _DEBUG_
		printf("dumpConn():dele conn,hash %u mempos %09x\n",c->getID().hash(),(int)c);
#endif

	if(!dumper || dumper->is_full())incDumper();
	dumper->dump(c);

	unsigned int pos = c->getID().hash()%hsize;
	conn_t tmp = htable[pos];

#ifdef _DEBUG_
	//printf("dumpConn():rm from hash table hash: %d pos :%d\n",c->getID().hash(),pos);
#endif

	if(NULL == tmp){
		printf("Error: this could not happen, connection disappear, nothing in this pos!\n");
		if( oldest_conn == c) oldest_conn = c->t_newer;
		if( newest_conn == c) newest_conn = c->t_older;
		if( c->t_newer ) c->t_newer->t_older = c->t_older;
		if( c->t_older ) c->t_older->t_newer = c->t_newer;
		return;
	}
	else{
		//remove it from hash table
		if( tmp == c ){ //first in the collision queue
			htable[pos] = c->c_next;
			if( c->c_next ) c->c_next->c_prev = NULL;
		}else{	// not the first
			while(tmp->c_next != c){
				tmp = tmp->c_next;
				if(NULL == tmp)printf("Error: this could not happen, connection disappear, not in collision queue!\n");
			}
#ifdef _DEBUG_
				printf("dumpConn():rm from hash table pos :%d in collision queue!\n",pos);
#endif
			tmp->c_next = c->c_next;
			if( c->c_next ) c->c_next->c_prev = tmp; 
		}
	}

#ifdef _DEBUG_
	//printf("dumpConn():rm from time queue\n");
#endif
	//remove it from time queue
	if( oldest_conn == c) oldest_conn = c->t_newer;
	if( newest_conn == c) newest_conn = c->t_older;
	if( c->t_newer ) c->t_newer->t_older = c->t_older;
	if( c->t_older ) c->t_older->t_newer = c->t_newer;
	
#ifdef _DEBUG_
	//printf("dumpConn():free mem\n");
#endif
	//free mem
	totmem -= c->freeMem();
	//delete the node
#ifdef _DEBUG_
	//printf("dumpConn():delete object\n");
#endif
	delete c;
	conn_num--;
	
#ifdef _DEBUG_
	printf("dumpConn():a conn dumped!\n");
#endif
}

void Connections::check4dump(double timeline)
{
	//if a connection's latest pkt arrival time is earlier than timeline, it will be dumped
	//if the totmem exceeds MEM_LIMIT, the oldest connections will be dumper to allow new pkts
	
#ifdef _DEBUG_
	//if(oldest_conn)printf("check4dump(): oldest:%f timeline:%f\n",oldest_conn->time_latest,timeline);
#endif

	while(oldest_conn && oldest_conn->time_latest <= timeline){
#ifdef _DEBUG_
		//printf("dump 1 conn for timeout, timeline:%f time:%f, diff:%f\n",timeline,oldest_conn->time_latest,timeline-oldest_conn->time_latest);
#endif
		dumpConn(oldest_conn);
	}

	if(oldest_conn && totmem >= MEM_LIMIT){
		while(totmem >= MEM_LIMIT*DUMP_PARA){
#ifdef _DEBUG_
		printf("dump 1 conn for mem shortage\n");
#endif
			dumpConn(oldest_conn);
		}
	}
}

void Connections::dumpAll()
{
	while(oldest_conn)dumpConn(oldest_conn);
}
