#include <mruby.h>

static mrb_value
mrb_tinydtls_ping(mrb_state *mrb, mrb_value self)
{
    /* method */
    return self;
}

void
mrb_mruby_tinydtls_gem_init(mrb_state *mrb) {
    struct RClass *module_tinydtls = mrb_define_module(mrb, "TinyDTLS");
    mrb_define_class_method(mrb, module_tinydtls, "ping", mrb_tinydtls_ping, MRB_ARGS_NONE());
}

void
mrb_mruby_tinydtls_gem_final(mrb_state *mrb) {
    /* finalizer */
}
