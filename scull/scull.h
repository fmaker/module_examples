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
#ifndef SCULL_H
#define SCULL_H

#include <linux/cdev.h>

#define SCULL_MAJOR     0
#define SCULL_MINOR     0
#define SCULL_NR_DEVS   1
#define SCULL_QSET      1000
#define SCULL_QUANTUM   4000

struct scull_qset
{
    void **data;
    struct scull_qset *next;
};

struct scull_dev
{
        struct scull_qset *data; // Pointer to first quantum set 
        int quantum;             // the current quantum size 
        int qset;                // the current array size 
        unsigned long size;      // amount of data stored here 
        unsigned int access_key; // used by sculluid and scullpriv 
        struct semaphore sem;    // mutual exclusion semaphore 
        struct cdev cdev;        // Char device structure 
};


#endif
