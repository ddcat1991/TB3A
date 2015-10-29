#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define BUFSIZE 100

int main(int argc, char **argv) {
  int sfd, s, val, volume,port;
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  struct sockaddr *sa;
  socklen_t salen;
  char buf[BUFSIZE];
  ssize_t nsend;
  struct ip_mreqn group;
  struct sockaddr_in sin;

  sfd = socket(PF_INET,SOCK_DGRAM,0);
  if(sfd==-1){
    perror("can't use socket");
    exit(EXIT_FAILURE);
  }

  port = atoi(argv[1]);
  /*
  group.imr_multiaddr = inet_addr("224.2.2.77");
  group.imr_address = inet_addr("127.0.0.1");
  setsockopt(sfd,IPPROTO_IP,IP_MULTICAST_IF,&group,sizeof(group));
  */
  memset(&sin,0,sizeof(sin));
  gethostbyname("localhost");

  sin.sin_addr.s_addr = inet_addr("224.2.2.77");
  sin.sin_family = AF_INET;
  sin.sin_port=htons(port);

  /* Permettons le broadcast (IPv4 only) */
  /*
  val = 0;
  if (setsockopt(sfd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val)) < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }*/
group.imr_multiaddr.s_addr = inet_addr("224.2.2.77");
    group.imr_address.s_addr= inet_addr("10.12.13.18");

    if(setsockopt(sfd,IPPROTO_IP,IP_ADD_MEMBERSHIP, &group,sizeof(group))<0){
        perror("Adding multicast group error");
        exit(EXIT_FAILURE);
    }

  memset(&buf,'a',BUFSIZE);
  sendto(sfd,buf,BUFSIZE,0,(struct sockaddr *)&sin,sizeof(sin));

}
