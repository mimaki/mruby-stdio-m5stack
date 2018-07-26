#include <M5Stack.h>

#include "mruby.h"
#include "mruby/class.h"

#ifdef __cplusplus
extern "C" {
#endif

static mrb_value
mrb_stdout_putc(mrb_state *mrb, mrb_value self)
{
  mrb_int c;
  char s[2] = {0, 0};
  mrb_get_args(mrb, "i", &c);
  s[0] = (char)c;
  M5.Lcd.print(s);
  return mrb_nil_value();
}

static mrb_value
mrb_stderr_putc(mrb_state *mrb, mrb_value self)
{
  mrb_int c;
  mrb_get_args(mrb, "i", &c);
  Serial.write((char)c);
  return mrb_nil_value();
}

static mrb_value
mrb_stdin_getc(mrb_state *mrb, mrb_value self)
{
  mrb_int c = -1;
  if (Serial.available() > 0) {
    c = Serial.read();
  }
  return mrb_fixnum_value(c);
}

void
mrb_mruby_stdio_m5stack_gem_init(mrb_state *mrb)
{
  struct RClass *cin  = mrb_define_class(mrb, "STDIN",  mrb->object_class);
  struct RClass *cout = mrb_define_class(mrb, "STDOUT", mrb->object_class);
  struct RClass *cerr = mrb_define_class(mrb, "STDERR", cout);

  mrb_define_class_method(mrb, cin,   "_getc", mrb_stdin_getc,  MRB_ARGS_NONE());
  mrb_define_class_method(mrb, cout,  "_putc", mrb_stdout_putc, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, cerr,  "_err_putc", mrb_stderr_putc, MRB_ARGS_REQ(1));
}

void
mrb_mruby_stdio_m5stack_gem_final(mrb_state *mrb)
{
}

#ifdef __cplusplus
}
#endif
