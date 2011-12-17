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
#include <linux/sysrq.h>

void sysrq_handler(int key)
{
	pr_info("handler(%d)",key);
}

struct sysrq_key_op x_op = {
	.handler = sysrq_handler,
	.help_msg = "Help message",
	.action_msg = "Action message",
	.enable_mask = SYSRQ_ENABLE_KEYBOARD
};

void __exit sysrq_exit(void)
{
	unregister_sysrq_key('x', &x_op);
}
module_exit(sysrq_exit);

static int __init sysrq_init(void)
{
	register_sysrq_key('x', &x_op);
	return 0;
}
module_init(sysrq_init);

MODULE_AUTHOR("Frank Maker");
MODULE_LICENSE("Dual GPL/BSD");
