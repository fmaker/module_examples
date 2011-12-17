/*
 * Copyright 2011 Frank Maker <frank.maker@gmail.com>
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the license, or (at your option) any later
 * version.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Frank Maker BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/module.h>
#include <linux/sched.h>


static const char state_to_char[] = TASK_STATE_TO_CHAR_STR;

static int task_state_char(unsigned long state)
{
	int bit = state ? __ffs(state) + 1 : 0;

	return bit < sizeof(state_to_char) - 1 ? state_to_char[bit] : '?';
}

static void lsproc(void)
{
  struct task_struct *p;
  pr_info("PID\tSTATE\tCOMMAND");
  for_each_process(p)
  {
    char s;
    s = task_state_char(p->state);
    
    pr_info("%d\t%c\t%s",p->tgid,s,p->comm);
  }
}

static int __init lsproc_init(void)
{
  pr_info("lsproc module loaded.");
  lsproc();
  return 0;
}
module_init(lsproc_init);

static void __exit lsproc_exit(void)
{
  pr_info("lsproc module unloaded.");

}
module_exit(lsproc_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lists process information");

