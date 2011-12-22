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
#include <linux/list.h>
#include <linux/slab.h>

static LIST_HEAD(head);

struct int_node{
	struct list_head list;
	int value;
};

static int __init linked_list_init(void)
{
	int i;
	struct int_node *node;

	for(i=0;i<100;i++){
		printk(KERN_INFO "Adding %d...",i);
		node = kmalloc(sizeof(struct int_node), GFP_KERNEL);
		/* printk(KERN_INFO "Node is %p...",node); */
		node->value = i;
		list_add(&node->list, &head);
	}
	
	return 0;
}
module_init(linked_list_init);

static void __exit linked_list_exit(void)
{
	int i;
	struct list_head *p,*n;
	struct int_node *node;

	/* printk(KERN_INFO "==========START_EXIT============");
	 * printk(KERN_INFO "head = %p...\n",&head);
	 * printk(KERN_INFO "head->next = %p...\n",head.next); */

	i=0;
	list_for_each(p, &head){
		struct int_node *node;
		node = list_entry(p, struct int_node, list);
		/* printk(KERN_INFO "Node[%d] = %p...\n",i,node); */
		i++;
	}

	i=0;
	list_for_each_safe(p, n, &head){ 

		/* printk(KERN_INFO "Head is: %p...\n",&head);
		 * printk(KERN_INFO "Head->next is: %p...\n",head.next); */
		node = list_entry(p, struct int_node, list);

		/* printk(KERN_INFO "Removing node[%d] = %p...\n",i,node); */
		list_del(&node->list);

		printk(KERN_INFO "Freeing node[%d] = %p...\n",i,node);
		kfree(node);

		/* printk(KERN_INFO "Head is now: %p...\n",&head);
		 * printk(KERN_INFO "Head->next is now: %p...\n",head.next); */

		i++;
	}

	if(list_empty(&head))
		printk(KERN_INFO "list is empty");
	else
		printk(KERN_INFO "list is NOT empty");
}
module_exit(linked_list_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


