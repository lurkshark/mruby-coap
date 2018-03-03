#include <mruby.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <coap.h>

static char buffer[COAP_MAX_PDU_SIZE];

static void
_handle_response_pdu(struct coap_context_t *ctx, const coap_endpoint_t *local_interface, 
    const coap_address_t *remote, coap_pdu_t *sent, coap_pdu_t *response, const coap_tid_t id)
{
  unsigned char *data;
	size_t data_length;

	if (COAP_RESPONSE_CLASS(response->hdr->code) == COAP_MESSAGE_ACK) {
		if (coap_get_data(response, &data_length, &data)) {
      data_length = data_length > COAP_MAX_PDU_SIZE - 1 ? COAP_MAX_PDU_SIZE - 1 : data_length;
      strncpy(buffer, (char *)data, data_length);
			buffer[data_length] = '\0';
		}
  }
}

static int
_resolve_hostname(const char *hostname, struct sockaddr *addr)
{
  struct addrinfo *res;
  struct addrinfo hints;
  int addr_length = -1;

  memset((char *)&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_family = AF_UNSPEC;

  getaddrinfo(hostname, NULL, &hints, &res);
  memcpy(addr, res->ai_addr, res->ai_addrlen);
  addr_length = res->ai_addrlen;
  freeaddrinfo(res);

  return addr_length;
}

mrb_value
mrb_coap_client_send(mrb_state *mrb, mrb_value self)
{
  /* libcoap */
  coap_context_t *ctx;
  coap_pdu_t *request;
  coap_address_t local, remote;

  /* for getting response */
  fd_set read_fds;  

  /* arguments from method call */
  mrb_int port;
  mrb_int method, type;
  char *remote_hostname;
  char *resource_path;
  char *payload;

  /* return data */
  mrb_value response;

  mrb_get_args(mrb, "iziziz!", &method, &remote_hostname, &port, &resource_path, &type, &payload);

  coap_address_init(&remote);
  /* resolve the destination first to figure out IPv6 or IPv4 */
  remote.size = _resolve_hostname(remote_hostname, &remote.addr.sa);
  remote.addr.sin.sin_port = htons(port);

  coap_address_init(&local);
  local.addr.sin.sin_port = htons(0);
  /* set an IPv6 source if needed, otherwise IPv4 */
  if (remote.addr.sa.sa_family == AF_INET6) {
    local.size = _resolve_hostname("::", &local.addr.sa);
  } else {
    local.size = _resolve_hostname("0.0.0.0", &local.addr.sa);
  }
  
  /* setup our coap client context */
  ctx = coap_new_context(&local);

  request = coap_pdu_init(type, method, coap_new_message_id(ctx), COAP_MAX_PDU_SIZE);
  coap_add_option(request, COAP_OPTION_URI_PATH, strlen(resource_path), (unsigned char *)resource_path);
  if (payload != NULL) {
    coap_add_data(request, strlen(payload), payload);
  }

  coap_register_response_handler(ctx, _handle_response_pdu);
  coap_send_confirmed(ctx, ctx->endpoint, &remote, request);

  while (!coap_can_exit(ctx)) {
    FD_ZERO(&read_fds);
    FD_SET(ctx->sockfd, &read_fds);
    if (select(FD_SETSIZE, &read_fds, 0, 0, NULL) > 0 && FD_ISSET(ctx->sockfd, &read_fds)) {
      coap_read(ctx);
    }
  }

  response = mrb_str_new(mrb, buffer, strlen(buffer));
  coap_free_context(ctx);
  return response;
}

void
mrb_mruby_coap_gem_init(mrb_state *mrb)
{
  struct RClass *module_coap = mrb_define_module(mrb, "CoAP");
  struct RClass *class_coap_client = mrb_define_class_under(mrb, module_coap, "Client", mrb->object_class);
  mrb_define_class_method(mrb, class_coap_client, "_send", mrb_coap_client_send, MRB_ARGS_REQ(6));

  mrb_define_const(mrb, class_coap_client, "CON", mrb_fixnum_value(COAP_MESSAGE_CON));
  mrb_define_const(mrb, class_coap_client, "GET", mrb_fixnum_value(COAP_REQUEST_GET));
  mrb_define_const(mrb, class_coap_client, "POST", mrb_fixnum_value(COAP_REQUEST_POST));
  mrb_define_const(mrb, class_coap_client, "DELETE", mrb_fixnum_value(COAP_REQUEST_DELETE));
}

void
mrb_mruby_coap_gem_final(mrb_state *mrb)
{
}
