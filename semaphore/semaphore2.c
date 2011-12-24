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

extern struct semaphore my_sema;

int lock_result(int rc)
{
	if(rc == 0){
		printk("Acquired a lock, cnt = %d\n",my_sema.count);
		return 0;
	}
	else{
		printk("Couldn't acquire a lock, cnt = %d!\n",my_sema.count);
		return -1;
	}

}

static int __init my_semaphore2_init(void)
{
	int rc;
	
	printk("%s\n",__stringify(KBUILD_MODNAME));

	printk("cnt = %d!\n",my_sema.count);

	/* Should succeed */
	rc = down_trylock(&my_sema);
	lock_result(rc);

	/* Should succeed */
	rc = down_trylock(&my_sema);
	lock_result(rc);

	/* Should fail */
	rc = down_trylock(&my_sema);
	lock_result(rc);

	up(&my_sema);
	printk("Released lock, cnt = %d!\n",my_sema.count);

	up(&my_sema);
	printk("Released lock, cnt = %d!\n",my_sema.count);

	return 0;

}
module_init(my_semaphore2_init);

static void __exit my_semaphore2_exit(void)
{

}
module_exit(my_semaphore2_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


