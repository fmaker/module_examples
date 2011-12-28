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
#include <sched.h>
#include <string.h>
#include <signal.h>
#include <malloc.h>
#include <unistd.h>

static char *shared_string;
static int *mutex;

enum sig{
	MASTER,
	CHILD,
	STOP
};

int child_thread(void *arg)
{
	printf("\tChild starting..\n");
	strcat(shared_string, "He told me enough! He told me you killed him!\n");
	strcat(shared_string, "No... that's not true! That's impossible!\n");
	printf("\tChild done...\n");
	*mutex = MASTER;
	return 0;
}

int main(int argc, char **argv)
{
	int rc;
	void **child_stack;
	int _mutex;
	char _shared_string[4096];

	/* Setting pointer to stack address which can only be seen if
         * child thread shared memory space */
	mutex = &_mutex;
	shared_string = &_shared_string[0];
	child_stack = (void*) malloc(16384);

	strcpy(shared_string, "Obi-Wan never told you what happened to your father.\n");

	printf("Launching child thread...\n");
	*mutex = CHILD;
	rc = clone(child_thread, &child_stack, CLONE_VM|CLONE_FILES, NULL);
	while(*mutex == CHILD);

	strcat(shared_string, "Luke, I am your father.\n");
	printf("%s",shared_string);

	free(child_stack);
	
	return 0;
}

