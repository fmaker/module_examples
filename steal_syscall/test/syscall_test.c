/* Copyright (c) 2011, Frank Maker <frank.maker@gmail.com>
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

#include <stdio.h>
#include <sys/syscall.h>
#include <asm/unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	long int rc = -99;
	rc = syscall(__NR_putpmsg);
	if(rc >= 0)
		printf("Return is: %li\n",rc);
	else
		printf("errno: %d\n",-errno);
	return 0;
}

