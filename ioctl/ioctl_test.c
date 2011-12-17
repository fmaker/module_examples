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
#include <stdio.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
	int fd, rc;

	fd = open("/dev/ioctl", 0);

	if(fd <0){
		printf("Error opening /dev/ioctl\n");
		return -1;
	}

	rc = ioctl(fd, IOC_INOUT, 0);
	rc = ioctl(fd, IOC_INOUT, 1);
	rc = ioctl(fd, IOC_INOUT, 2);
	rc = ioctl(fd, IOC_INOUT, 3);
	rc = ioctl(fd, IOC_INOUT, 55);

	printf("rc = %d\n",rc);

	close(fd);

	return 0;
}
