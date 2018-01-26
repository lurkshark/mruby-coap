#include <mruby.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <coap.h>

mrb_value
mrb_coap_ping(mrb_state *mrb, mrb_value self)
{
  coap_log(LOG_INFO, "CoAP::ping");
  return self;
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
  coap_address_t src, dst;
  
  /* arguments from method call */
  mrb_int port;
  mrb_sym method, type;
  char *remote_hostname;
  char *resource_path;

  mrb_get_args(mrb, "nzizn", &method, &remote_hostname, &port, &resource_path, &type);

  coap_address_init(&dst);
  /* resolve the destination first to figure out IPv6 or IPv4 */
  dst.size = _resolve_hostname(remote_hostname, &dst.addr.sa);
  dst.addr.sin.sin_port = htons(port);

  coap_address_init(&src);
  /* set an IPv6 source if needed, otherwise IPv4 */
  if (dst.addr.sa.sa_family == AF_INET6) {
    src.size = _resolve_hostname("::", &src.addr.sa);
  } else {
    src.size = _resolve_hostname("0.0.0.0", &src.addr.sa);
  }
  
  /* setup our coap client context */
  ctx = coap_new_context(&src);

  request = coap_new_pdu();
  request->hdr->type  = COAP_MESSAGE_CON;
	request->hdr->id    = coap_new_message_id(ctx);
	request->hdr->code  = 1;

  coap_add_option(request, COAP_OPTION_URI_PATH, strlen(resource_path), (unsigned char *)resource_path);
  coap_send_confirmed(ctx, ctx->endpoint, &dst, request);

  coap_free_context(ctx);
  return self;
}

void
mrb_mruby_coap_gem_init(mrb_state *mrb)
{
  struct RClass *module_coap = mrb_define_module(mrb, "CoAP");
  mrb_define_class_method(mrb, module_coap, "ping", mrb_coap_ping, MRB_ARGS_NONE());

  struct RClass *class_coap_client = mrb_define_class_under(mrb, module_coap, "Client", mrb->object_class);
  mrb_define_class_method(mrb, class_coap_client, "send", mrb_coap_client_send, MRB_ARGS_REQ(5));
}

void
mrb_mruby_coap_gem_final(mrb_state *mrb)
{
}
