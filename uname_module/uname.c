/*
 * Copyright 2011 Frank Maker <frank.maker@gmail.com>
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the license, or (at your option) any later
 * version.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Frank Maker BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/module.h>
#include <linux/utsname.h>

static void uname(void)
{
  printk("%s %s %s %s %s %s",
         init_uts_ns.name.sysname,
         init_uts_ns.name.nodename,
         init_uts_ns.name.release,
         init_uts_ns.name.version,
         init_uts_ns.name.machine,
         init_uts_ns.name.domainname);

}

static int __init uname_init(void)
{
  pr_info("uname module loaded.\n");
  uname();
  return 0;
}
module_init(uname_init);

static void __exit uname_exit(void)
{
  pr_info("uname module unloaded.");

}
module_exit(uname_exit);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Lists machine information");

