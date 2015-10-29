#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 80000

int s;
int multicast_enabled = 1;
struct ip_mreqn group;

void drop_multicast(int n) {
  if (!multicast_enabled) {
    perror("Already quitted multicast!");
    return;
  }
  printf("Stop listening multicast!\n");
  if(setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, &group, sizeof(group)) < 0) {
    perror("Setting IP_DROP_MEMBERSHIP error");
    close(s);
    exit(1);
  }
  multicast_enabled = 0;
}

int main(int argc, char **argv) {
  int r, port, enabled;
  struct sockaddr_in sin, from;
  socklen_t fromlen;
  struct hostent *hp;
  char buf[BUFSIZE];

  if (argc != 2) {
    printf("Usage : %s port\n", argv[0]);
    exit(1);
  }

  port = atoi(argv[1]);
  if (port < 5000) {
    printf("donnez un numero de port superieur a 5000\n");
    exit(1);
  }

  /* Construction de l'adresse locale (pour bind) */
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);

  /* Creation de la socket, et bind */
  s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (s == -1) {
    perror("socket");
    exit(2);
  }
  enabled = 1;
  if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&enabled, sizeof(enabled)) < 0) {
    perror("Setting SO_REUSEADDR error");
    close(s);
    exit(1);
  }


  r = bind(s, (struct sockaddr *) &sin, sizeof(sin));
  if (r == -1) {
    perror("bind");
    exit(3);
  }

  group.imr_multiaddr.s_addr = inet_addr("226.1.1.1");
  group.imr_address.s_addr = inet_addr("10.29.230.196");
  if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &group, sizeof(group)) < 0) {
    perror("Adding multicast group error");
    close(s);
    exit(1);
  }

  if (signal(SIGINT, drop_multicast) == SIG_ERR) {
    perror("Error adding signal handler!");
    close(s);
    exit(1);
  }

  fromlen = sizeof(from);

  for (;;) {
    /* Reception donnees */
    r = recvfrom(s, buf, BUFSIZE, 0, (struct sockaddr *) &from,
        &fromlen);
    if (r == -1) {
      perror("recvfrom");
      exit(1);
    }
    buf[r] = 0;
    printf("Message received: %s\n", buf);

    /* Reconnaissance de la machine cliente */
    hp = gethostbyaddr(&from.sin_addr, sizeof(struct in_addr),
                       from.sin_family);
    if (hp == NULL) {
      fprintf(stderr, "Erreur gethostbyaddr\n");
      continue;
    } else
      printf("Machine emettrice: %s, %d octets recus\n", hp->h_name, r);
  }
}
