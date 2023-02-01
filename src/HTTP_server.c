#include "HTTP_server.h"

static char *server_get_staticFile(char *filepath)
{
  FILE *file = fopen(filepath, "rb");
  if (file == NULL)
  {
    perror(filepath);
    return "";
  }

  fseek(file, 0, SEEK_END);
  int64_t fsize = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *data = calloc(fsize + 1, sizeof(char));
  char ch = ' ';
  int32_t i = 0;
  while ((ch = fgetc(file)) != EOF)
  {
    data[i] = ch;
    i++;
  }
  fclose(file);

  return data;
}

void server_init(HTTP_Server *self, int32_t port)
{
  self->port = port;

  self->fd = socket(AF_INET, SOCK_STREAM, 0);
  check(self->fd, "socket error");

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  check(bind(self->fd, (sockaddr *)&server_addr, sizeof server_addr), "bind error");
  check(listen(self->fd, 10), "listen error");

  printf("Server initalized, %d", port);
}

void server_handle_connection(int32_t fd, BinTree *router)
{
  char client_msg[4096] = "";
  int32_t read_stat;
  do
  {
    read_stat = read(fd, client_msg, sizeof client_msg - 1);
  } while (read_stat < 0);
  printf("msg: %s msglen:%ld", client_msg, strlen(client_msg));

  // gets the method from the client and the url to route the web pages
  char *method = "";
  char *urlRoute = "";
  char *client_html_header = strtok(client_msg, "\n");
  char *header_token = strtok(client_html_header, " ");

  int32_t header_parse_counter = 0;
  // parsing token
  while (header_token != NULL)
  {
    switch (header_parse_counter)
    {
    case 0:
      method = header_token;
      break;
    case 1:
      urlRoute = header_token;
      break;
    }
    header_token = strtok(NULL, " ");
    header_parse_counter++;
  }
  // printf("\nmethod:%s", method);
  // printf("\nurl:%s\n", urlRoute);

  // getting and sending file
  // pretends that web/ is root
  char filepath[128] = "web/";

  char response[10240] = "";
  int32_t data_len = 0, header_len = 0;

  if (strstr(urlRoute, "/img") != NULL)
  {
    //not implemented
  }
  else
  {
    if (strstr(urlRoute, "/css") != NULL)
    {
      strcat(filepath, urlRoute + 1);
    }
    else
    {
      strcat(filepath, "html/");
      strcat(filepath, binTree_search(router, urlRoute));
    }
    printf("\nfpath: %s\n", filepath);

    char *data = server_get_staticFile(filepath);
    data_len = strlen(data) + 1;
    header_len = snprintf(response, sizeof response, "HTTP/1.1 200 OK\r\n\r\n");
    strcat(response, data);

    int n = send(fd, response, data_len + header_len, 0);
    printf("n:%d", n);

    free(data);
  }
  close(fd);
}
