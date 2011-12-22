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


static int __init tainted_init(void)
{
	struct list_head *p;
	struct module *m;
	struct module *this = THIS_MODULE;

	list_for_each(p, (this->list).prev){
		m = list_entry(p, struct module, list);

		if(m->taints){
			printk("%s (T)\n",m->name);
		}
		else{
			printk("%s\n",m->name);
		}

	}

	return 0;
}
module_init(tainted_init);

static void __exit tainted_exit(void)
{

}
module_exit(tainted_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("Proprietary"); /* This will taint the module */


