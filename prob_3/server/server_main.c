#include "../clc_core/info.h"

struct sockaddr* sockaddr_new() {
  return malloc(sizeof(struct sockaddr_in));
}

socklen_t sockaddr_sizeof() {
  return sizeof(struct sockaddr_in);
}

int main(int argc, char** argv) {

  // ----------- 1. Create socket object ------------------
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1) {
    fprintf(stderr, "Could not create socket: %s\n",
            strerror(errno));
    exit(1);
  }

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
  addr.sin_addr = *((struct in_addr*)host_entry->h_addr);
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
  accept_forever(listen_fd);

  return 0;

}

void accept_forever(int server_sd) {
  while (1) {
    int client_sd = accept(server_sd, NULL, NULL);
    if (client_sd == -1) {
      close(server_sd);
      fprintf(stderr, "Could not accept the client: %s\n",
              strerror(errno));
      exit(1);
    }
    pthread_t client_handler_thread;
    int* arg = (int *)malloc(sizeof(int));
    *arg = client_sd;
    int result = pthread_create(&client_handler_thread, NULL,
            &client_handler, arg);
    if (result) {
      close(client_sd);
      close(server_sd);
      free(arg);
      fprintf(stderr, "Could not start the client handler thread.\n");
      exit(1);
    }
  }
}

void* client_handler(void *arg){

}

