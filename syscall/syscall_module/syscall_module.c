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

struct newstruct{
	void (*fp)(void);
};
extern struct newstruct newcall_struct;

void howdy(void)
{
	printk(KERN_INFO "Howdy partner! I reckon it worked.");
}

static int __init syscall_module_init(void)
{
	newcall_struct.fp = &howdy;
	return 0;
}
module_init(syscall_module_init);

static void __exit syscall_module_exit(void)
{
	newcall_struct.fp = NULL;
}
module_exit(syscall_module_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


