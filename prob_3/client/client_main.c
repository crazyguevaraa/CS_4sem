#include "../clc_core/info.h"
#include "../clc_core/calc.h"


double func(double x)
{
    // y = ...
    return x * x;
}

void stream_client_loop (int conn_sd, int numThreads);

int main(int argc, char** argv) {

  // ----------- 1. Create socket object ------------------

  int conn_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (conn_sd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

  // ------------ 2. Connect to server-- ------------------

  // Find the IP address behind the hostname

  struct hostent* host_entry;
  host_entry = gethostbyname(argv[2]);
  if (!host_entry) {
    fprintf(stderr, "Could not resolve the host '%s'\n", argv[2]);
    exit(1);
  }

  // Prepare the address
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr = *((struct in_addr*)host_entry->h_addr);
  addr.sin_port = htons(SERV_PORT);

  int result = connect(conn_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(conn_sd);
    fprintf(stderr, "Could no connect: %s\n", strerror(errno));
    exit(1);
  }
  char* cur_end = NULL;
  int numThreads = (int) strtol(argv[1], &cur_end, 10);
    if (errno || *cur_end != 0 || numThreads <= 0) {
        printf("incorrect number of threads: %s, (interpret as: %d(int))\n", argv[1], numThreads);
        exit(2);
    }

  stream_client_loop(conn_sd, numThreads);

  return 0;
}

void stream_client_loop (int conn_sd, int numThreads){
  /* reciv info from host*/
  char buf[2*sizeof(double)];
  read(conn_sd, buf, 2*sizeof(double));
  double a, b;
  memcpy((void*)&a, buf, sizeof(double));
  memcpy((void*)&b, buf + sizeof(double), sizeof(double));

  double res = icCalculateMT(numThreads, a, b, func);
  
  memcpy(buf, res, sizeof(double));

  write(conn_sd, buf, sizeof(double));

  
}