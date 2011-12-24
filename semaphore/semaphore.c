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
#include <linux/semaphore.h>

struct semaphore my_sema;
EXPORT_SYMBOL(my_sema);

static int __init my_semaphore_init(void)
{
	printk("%s\n",__stringify(KBUILD_MODNAME));
	sema_init(&my_sema, 2);
	return 0;
}
module_init(my_semaphore_init);

static void __exit my_semaphore_exit(void)
{

}
module_exit(my_semaphore_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


