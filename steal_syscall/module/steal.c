/*
 * Copyright 2011 Frank Maker <frank.maker@gmail.com>
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the license, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>

static void** sys_call_table = (void**) 0xffffffff81393160UL;
static void* putmsg_orig; 

static asmlinkage long sys_putpmsg(void)
{
	printk(KERN_INFO "Grand theft syscall.");
	return 0;
}

static int __init steal_init(void)
{
	printk(KERN_INFO "Stealing sys_putmsg!");
	putmsg_orig = sys_call_table[__NR_putpmsg];
	printk(KERN_INFO "sys_putmsg was: 0x%p",sys_call_table[__NR_putpmsg]);
	sys_call_table[__NR_putpmsg] = &sys_putpmsg;
	printk(KERN_INFO "sys_putmsg now: 0x%p",sys_call_table[__NR_putpmsg]);
	return 0;
}
module_init(steal_init);

static void __exit steal_exit(void)
{
	printk(KERN_INFO "Restoring sys_putmsg...");
	printk(KERN_INFO "sys_putmsg is: 0x%p",sys_call_table[__NR_putpmsg]);
	sys_call_table[__NR_putpmsg] = putmsg_orig;
	printk(KERN_INFO "sys_putmsg now: 0x%p",sys_call_table[__NR_putpmsg]);
}
module_exit(steal_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


