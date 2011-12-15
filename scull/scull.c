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

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#include "scull.h"

/* Load time parameters */
unsigned int scull_major = SCULL_MAJOR;
unsigned int scull_minor = SCULL_MINOR;
unsigned int scull_nr_devs = SCULL_NR_DEVS;
unsigned int scull_quantum = SCULL_QUANTUM;
unsigned int scull_qset = SCULL_QSET;

module_param(scull_major, uint, S_IRUGO);
module_param(scull_minor, uint, S_IRUGO);
module_param(scull_nr_devs, uint, S_IRUGO);
module_param(scull_quantum, uint, S_IRUGO);
module_param(scull_qset, uint, S_IRUGO);

/* Pointer to scull device structs */
struct scull_dev *scull_devices;

loff_t scull_llseek(struct file *filp, loff_t off, int whence)
{
    return off;
}

ssize_t scull_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    return 0;
}

ssize_t scull_write(struct file *filp, const char __user *buf, size_t count, loff_t *fpos)
{
    return 0;
}

int scull_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
    return -1;
}

int scull_open(struct inode *inode, struct file *filp)
{
    return -1;
}

int scull_release(struct inode *inode, struct file *filp)
{
    return 0;
}

struct file_operations scull_fops = 
{
    .owner =    THIS_MODULE,
    .llseek =   scull_llseek,
    .read =     scull_read,
    .write =    scull_write,
    .ioctl =    scull_ioctl,
    .open =     scull_open,
    .release =  scull_release,
};

/* Iterate over quantums and free up memory */
int scull_trim(struct scull_dev *dev)
{
    struct scull_qset *next, *dptr;
    int qset = dev->qset;
    
    /* Iterate over quantum sets */
    for(dptr=dev->data; dptr; dptr=next)
    {
        /* If data is valid pointer */
        if(dptr->data)
        {
            /* Iterate over array */
            int i;
            for(i=0; i<qset; i++)
            {
                /* Free each array item */
                kfree(dptr->data[i]);
            }
            /* Free quantum set pointer array itself */
            kfree(dptr->data);
        }
        /* Save next reference and free pointer to quantum set */
        next = dptr->next;
        kfree(dptr);
    }
    
    /* Update scull_dev as empty */
    dev->size = 0;
    dev->quantum = scull_quantum;
    dev->qset = scull_qset;
    dev->data = NULL;

    return 0;
    
}

static void scull_setup_cdev(struct scull_dev *dev, int index)
{
    int err, devno = MKDEV(scull_major, scull_minor + index);

    /* Initialized character device struct */
    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 10); /* Driver live! */

    // Fail if we need to
    if(err)
        printk(KERN_NOTICE "Error %d adding scull%d", err, index);

}

void scull_cleanup_module(void)
{
    dev_t devno = MKDEV(scull_major, scull_minor);

    /* Clean up character device entries */
    if(scull_devices)
    {
        int i;
        for(i=0;i<scull_nr_devs;i++)
        {
            
            scull_trim(scull_devices+i);

            /* Remove kernel device entry */
            cdev_del(&scull_devices[i].cdev);
        }
        /* Free struct(s) memory */
        kfree(scull_devices);
    }

    /* Unregister character device */
    unregister_chrdev_region(devno, scull_nr_devs);

    /* Cleanup friend devices */
    #warning NO_FRIEND_CLEANUP

}
module_exit(scull_cleanup_module);

static int __init scull_init_module(void)
{
    /* Get major number */
    int result = -1;
    dev_t dev = 0;
    int i;

    /* Get minor numbers */
    if(scull_major)  /* Static */
    {
        dev = MKDEV(scull_major, scull_minor);
        result = register_chrdev_region(dev, scull_nr_devs, "scull");
    }
    else  /* Dynamic */
    {
        result = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs,
                                      "scull");
        scull_major = MAJOR(dev);
    }
    if (result < 0)
    {
        printk(KERN_WARNING "scull: can't get major %d\n", scull_major);
        return result;
    }

    /* Allocate memory for device structs */
    scull_devices = kmalloc(scull_nr_devs * sizeof(struct scull_dev), GFP_KERNEL);
    
    /* If null pointer, no memory allocated */
    if(!scull_devices)
    {
        result = -ENOMEM;
        goto fail;
    }

    /* Clear structs memory */
    memset(scull_devices, 0, scull_nr_devs * sizeof(struct scull_dev));
    
    /* Initialize each device */
    for(i=0; i<scull_nr_devs; i++)
    {
        scull_devices[i].quantum = scull_quantum;
        scull_devices[i].qset = scull_qset;
        init_MUTEX(&scull_devices[i].sem);
        scull_setup_cdev(&scull_devices[i], i);
        printk(KERN_INFO "Successfull initialization of scull: major:%d minor:%d\n",
               scull_major,scull_minor+i);        
    }

    return 0;

fail:
    scull_cleanup_module();
    return result;

}
module_init(scull_init_module);

MODULE_AUTHOR("Frank Maker");
MODULE_DESCRIPTION("Simple Character Utility for Loading Localities");
MODULE_LICENSE("GPL");
