/*
 * Copyright (c) 2011, Frank Maker <frank.maker@gmail.com>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL FRANK MAKER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
MODULE_LICENSE("Dual BSD/GPL");


