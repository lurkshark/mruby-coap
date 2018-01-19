#include <mruby.h>

static mrb_value
mrb_coap_ping(mrb_state *mrb, mrb_value self)
{
    /* method */
    return self;
}

void
mrb_mruby_coap_gem_init(mrb_state *mrb) {
    struct RClass *module_coap = mrb_define_module(mrb, "Coap");
    mrb_define_class_method(mrb, module_coap, "ping", mrb_coap_ping, MRB_ARGS_NONE());
}

void
mrb_mruby_coap_gem_final(mrb_state *mrb) {
    /* finalizer */
}
