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
#include <linux/percpu.h>

static int __percpu *my_counter;

static int __init per_cpu_dyn_init(void)
{
	int proc_id;
	int *cnt;

	my_counter = (int *) alloc_percpu(int);

	preempt_disable();
	proc_id = smp_processor_id();
	cnt = (int *) per_cpu_ptr(my_counter, proc_id);
	preempt_enable();

	printk("=====INIT=====\n");
	printk("Howdy from CPU #%d\n",proc_id);
	*cnt += proc_id;
	printk("my_counter = %d\n",*cnt);


	return 0;
}
module_init(per_cpu_dyn_init);

static void __exit per_cpu_dyn_exit(void)
{
	int proc_id;
	int *cnt;

	preempt_disable();
	proc_id = smp_processor_id();
	cnt = (int *) per_cpu_ptr(my_counter, proc_id);
	preempt_enable();

	printk("=====EXIT=====\n");
	printk("Howdy from CPU #%d\n",proc_id);
	*cnt -= proc_id;
	printk("my_counter = %d\n\n",*cnt);

	free_percpu(my_counter);

}
module_exit(per_cpu_dyn_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


