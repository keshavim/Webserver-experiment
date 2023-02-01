

#include "common.h"
#include "HTTP_server.h"
#include "Binary_tree.h"

int main() {
  HTTP_Server server;
  server_init(&server, PORT);

  BinTree* router = binTree_init("/", "index.html");
  binTree_insert(router, "/about", "about.html");

  int32_t client_fd;
  while(true){
    printf("\nwaiting for connection in port %d\n", PORT);
    fflush(stdout);

    client_fd = accept(server.fd, NULL, NULL);

    server_handle_connection(client_fd, router);
  }

  return (0);
}