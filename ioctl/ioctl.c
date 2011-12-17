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
#include <linux/fs.h>
#include <linux/cdev.h>

static unsigned int major = 300;
static unsigned int minor = 0;

static struct cdev cdev;

long test_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "cmd = %d, arg = %lu\n",cmd,arg);
	switch(arg){
	case 0:
		printk("Major number is %d\n",major);
		break;
	case 1:
		printk("Minor number is %d\n",minor);
		break;
	case 2:
		printk("What?\n");
		break;
	case 3:
		printk("Really?\n");
		break;
	default:
		printk("Huh?\n");
	}
	return 0;
}

struct file_operations fops = 
{
	.owner =    THIS_MODULE,
	.unlocked_ioctl =    test_ioctl,
};

static int setup_cdev(dev_t *dev)
{
	int err, devno;
	
	devno = MKDEV(major, minor);
	cdev_init(&cdev, &fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &fops;
	err = cdev_add(&cdev, devno, 10);

	if(err)
		printk(KERN_NOTICE "Error %d adding ioctl char dev\n", err);
	else
		printk(KERN_NOTICE "Loaded ioctl module\n");
	       
	return 0;
}

static int __init ioctl_init(void)
{
//	int result;
	dev_t dev;

	/* Dynamically get major and minor device numbers */
	//result = alloc_chrdev_region(&dev, minor, nr_devs, "ioctl");
	//major = MAJOR(dev);

	/* if(result < 0){
	 * 	printk(KERN_WARNING "ioctl: can't get major %d\n", major);
	 * 	return result;
	 * }
	 * else{ */
		setup_cdev(&dev);
//	}

	
	
	return 0;
}
module_init(ioctl_init);

static void __exit ioctl_exit(void)
{

}
module_exit(ioctl_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");


