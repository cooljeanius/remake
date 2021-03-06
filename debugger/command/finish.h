/* Terminate execution. */
/* 
Copyright (C) 2004, 2005, 2007, 2008, 2009, 2011 R. Bernstein 
<rocky@gnu.org>
This file is part of GNU Make (remake variant).

GNU Make is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Make is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Make; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */
static debug_return_t 
dbg_cmd_finish(char *psz_amount)
{
  target_stack_node_t *p=p_stack;
  unsigned int i_amount=0;
  unsigned int i=0;
  if ('\0' != *psz_debugger_args) {
    if (!get_uint(psz_amount, &i_amount, true))
      return debug_readloop;
    
    if (p_stack_top) {
      /* We have a target stack  */
      
      for (i=0 ; p ; p = p->p_parent, i++ ) {
        if (i_amount == i) break;
      }
      
    }
  }
  if (p) {
    i_debugger_nexting  = 0;
    i_debugger_stepping = 0;
    p->p_shared_target->tracing |= (BRK_AFTER_CMD);
    return continue_execution;
  } else {
    if (i > i_amount)
      printf("Target level %d not found\n", i_amount);
    else
      printf("Level %d is too large; maximum value is %d.\n", 
             i_amount, i-1);
  }
  
  return debug_readloop;
}

static void
dbg_cmd_finish_init(unsigned int c) 
{
  short_command[c].func = &dbg_cmd_finish;
  short_command[c].use  = _("finish [AMOUNT]");
  short_command[c].doc  = 
    _("Run (step out) until finishing AMOUNT target levels up.\n"
      "The default value is 0, or after commands have been run.\n" 
      );
}


/* 
 * Local variables:
 * eval: (c-set-style "gnu")
 * indent-tabs-mode: nil
 * End:
 */
