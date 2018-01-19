#include <mruby.h>
#include <stdio.h>

#include "yacoap/coap.h"

mrb_value
mrb_coap_ping(mrb_state *mrb, mrb_value self)
{
  return self;
}

mrb_value
mrb_coap_header_dump(mrb_state *mrb, mrb_value self)
{
  uint8_t ver   = mrb_funcall(mrb, self, "version", 0).value.i;
  uint8_t t     = mrb_funcall(mrb, self, "type", 0).value.i;
  uint8_t tkl   = mrb_funcall(mrb, self, "token_length", 0).value.i;
  uint8_t code  = mrb_funcall(mrb, self, "code", 0).value.i;
  uint16_t id   = mrb_funcall(mrb, self, "id", 0).value.i;
  
  coap_header_t header = { ver, t, tkl, code, id };
  fprintf(stdout, "CoAP Header: { ver: %d, t: %d, tkl: %d, code: %d, id: %d };",
      header.ver, header.t, header.tkl, header.code, header.id);
  return mrb_nil_value();
}

void
mrb_mruby_coap_gem_init(mrb_state *mrb)
{
  struct RClass *module_coap = mrb_define_module(mrb, "Coap");
  mrb_define_class_method(mrb, module_coap, "ping", mrb_coap_ping, MRB_ARGS_NONE());

  struct RClass *class_coap_header = mrb_define_class_under(mrb, module_coap, "Header", mrb->object_class);
  mrb_define_method(mrb, class_coap_header, "dump", mrb_coap_header_dump, MRB_ARGS_NONE());
}

void
mrb_mruby_coap_gem_final(mrb_state *mrb)
{
}
