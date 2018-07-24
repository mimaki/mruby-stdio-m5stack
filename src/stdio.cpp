#include "mruby.h"
#include "mruby/class.h"

static extern "C" mrb_value
mrb_stdout_putc(mrb_state *mrb, mrb_value self)
{
  mrb_int c;
  mrb_get_args(mrb, "i", &c);
  Serial.write((char)c);
  return mrb_nil_value();
}

static extern "C" mrb_value
mrb_stdin_getc(mrb_state *mrb, mrb_value self)
{
  mrb_int c = -1;
  if (Serial.available() > 0) {
    c = Serial.read();
  }
  return mrb_fixnum_value(c);
}

extern "C" void
mrb_mruby_stdio_m5stack_gem_init(mrb_state *mrb)
{
  struct RClass *cin  = mrb_define_class(mrb, "STDIN",  mrb->object_class);
  struct RClass *cout = mrb_define_class(mrb, "STDOUT", mrb->object_class);

  mrb_define_class_method(mrb, cin,   "_getc", mrb_stdin_getc,  MRB_ARGS_NONE());
  mrb_define_class_method(mrb, cout,  "_putc", mrb_stdout_putc, MRB_ARGS_REQ(1));
}

extern "C" void
mrb_mruby_stdio_m5stack_gem_final(mrb_state *mrb)
{
}
