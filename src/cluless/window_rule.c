#include "window_rule.h"
#include <config.h>
#include <stdbool.h>
#include <string.h>

static inline bool TryApplyWindowRule(Monitor *mon, const WindowRule *rule,
                                      const char *val)
{
  bool value_matches = strcmp(val, rule->value) == 0;
  if (value_matches)
    rule->action(mon, &rule->arg);
  return value_matches;
}

void window_rule_apply(Monitor *mon, Client *c)
{
  XClassHint class;
  XTextProperty wm_name;
  FOREACH(const WindowRule *rule, window_rules)
  {
    if (rule->res_type == ResTitle)
      if (core->get_window_title(c->window, &wm_name) && wm_name.nitems)
        if (TryApplyWindowRule(mon, rule, (char *)wm_name.value))
          break;

    if (rule->res_type == ResClass || rule->res_type == ResInstance)
      if (XGetClassHint(core->dpy, c->window, &class))
        if (TryApplyWindowRule(mon, rule,
                               rule->res_type == ResClass ? class.res_class
                                                          : class.res_name))
          break;
  }
}
