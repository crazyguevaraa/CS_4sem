#include "../clc_core/info.h"

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
  addr.sin_port = htons(6666);

  int result = connect(conn_sd,
          (struct sockaddr*)&addr, sizeof(addr));
  if (result == -1) {
    close(conn_sd);
    fprintf(stderr, "Could no connect: %s\n", strerror(errno));
    exit(1);
  }

  stream_client_loop(conn_sd);

  return 0;
}