#include "../clc_core/info.h"

struct sockaddr* sockaddr_new() {
  return malloc(sizeof(struct sockaddr_in));
}

socklen_t sockaddr_sizeof() {
  return sizeof(struct sockaddr_in);
}
#define h_addr  h_addr_list[0]
#define MAX_PC 10
double result[MAX_PC];

void* client_handler(void *arg);
void accept_forever(int server_sd, int no_threads);

int main(int argc, char** argv) {

  // ----------- 1. Create socket object ------------------
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }
/*
  int non_zero = 1;
  if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &non_zero, sizeof(non_zero)) != 0) {
    fprintf(stderr, "setsockopt : %s\n",
            strerror(errno));
    exit(1);  
  }

  struct timeval accept_timeout = {
            .tv_sec  = ACCEPT_TIMEOUT_SEC,
            .tv_usec = ACCEPT_TIMEOUT_USEC
    };

  if (setsockopt(listen_fd, SOL_SOCKET, SO_RCVTIMEO, &accept_timeout, sizeof(accept_timeout)) != 0) {
    fprintf(stderr, "setsockopt : %s\n",
            strerror(errno));
    exit(1);  
  }
  
  if (setsockopt(listen_fd, SOL_SOCKET, SO_KEEPALIVE, &non_zero, sizeof(non_zero)) != 0) {
    fprintf(stderr, "setsockopt : %s\n",
            strerror(errno));
    exit(1);  
  }

  int keep_cnt     = KEEP_CNT;
  int keep_idle    = KEEP_IDLE;
  int keep_intvl   = KEEP_INTVL;

  if (setsockopt(listen_fd, IPPROTO_TCP, TCP_KEEPCNT, &keep_cnt, sizeof(int)) != 0) {
    fprintf(stderr, "setsockopt : %s\n",
            strerror(errno));
    exit(1);  
  }

  if (setsockopt(listen_fd, IPPROTO_TCP, TCP_KEEPIDLE, &keep_idle, sizeof(int)) != 0) {
    fprintf(stderr, "setsockopt : %s\n",
            strerror(errno));
    exit(1);  
  }

  if (setsockopt(listen_fd, IPPROTO_TCP, TCP_KEEPINTVL, &keep_intvl, sizeof(int)) != 0) {
    fprintf(stderr, "setsockopt : %s\n",
            strerror(errno));
    exit(1);  
  }
*/
  struct hostent *svr;

  svr = gethostbyname(argv[2]);
    if (!svr) {
    fprintf(stderr, "Could not resolve the host '%s'\n", argv[2]);
    exit(1);
  }

  // ----------- 2. Bind the socket file ------------------

  // Prepare the address
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr = *((struct in_addr*)svr->h_addr);
  addr.sin_port = htons(SERV_PORT);

  int result = bind(listen_fd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(listen_fd);
    fprintf(stderr, "Could not bind the address: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 3. Prepare backlog ------------------
  result = listen(listen_fd, 1024);
  if (result == -1) {
    close(listen_fd);
    fprintf(stderr, "Could not set the backlog: %s\n",
            strerror(errno));
    exit(1);
  }

  // ----------- 5. Start accepting clients ---------
  accept_forever(listen_fd, argv[1]);
  double CLC_RES = 0;
  for(int i = 0; i > argv[1]; i++){
    double a = result + i;
    CLC_RES += a;
  }
  
  printf("CLC_RES = %f\n", CLC_RES);
  return 0;

}

void accept_forever(int server_sd, int no_threads) {
  double last_end = GENERAL_START_INT;
  double int_length = (double)(GENERAL_FINISH_INT - GENERAL_START_INT) / no_threads;
  struct arg arg;
  arg.NT = 0;
  while (1) {
    int client_sd = accept(server_sd, NULL, NULL);
    if (client_sd == -1) {
      close(server_sd);
      fprintf(stderr, "Could not accept the client: %s\n",
              strerror(errno));
      exit(1);
    } 
    double a = last_end;
    double b = a + int_length;
    last_end = b;
    arg.sd = client_sd;
    arg.a = a;
    arg.b = b;
    
    pthread_t client_handler_thread;
    
    int result = pthread_create(&client_handler_thread, NULL,
            client_handler, (void*) &arg);
    arg.NT++;

    if (result) {
      close(client_sd);
      close(server_sd);
      //free(arg);
      fprintf(stderr, "Could not start the client handler thread.\n");
      exit(1);
    }
  }
}

void* client_handler(void *arg){

  /* send info for calc*/
  struct sockaddr_in addrs;
  socklen_t addr_len = sizeof(addrs);
  struct arg* client_arg = (struct arg*) arg;
  int client_sd = client_arg->sd;

  double a = client_arg->a;
  double b = client_arg->b;
  char buf [2*sizeof(double)];
  memcpy(buf, (void*) &a, sizeof(double));
  memcpy(buf + sizeof(double), (void*) &b, sizeof(double));

  write(client_sd, buf, 2*sizeof(double));

  /* get results */
  int NT = client_arg->NT;
  read(client_sd, buf, sizeof(double));
  
  double pc_res;
  memcpy((void*) &pc_res, buf, sizeof(double));
  result[NT] = pc_res;
}

