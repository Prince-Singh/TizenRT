/****************************************************************************
 *
 * Copyright 2019 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#ifdef CONFIG_BINARY_MANAGER
#include <binary_manager/binary_manager.h>
#endif
#include "micomapp_internal.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/
#ifdef CONFIG_APP_BINARY_SEPARATION
int main(int argc, char **argv)
#else
int micomapp_main(int argc, char **argv)
#endif
{
	int ret;
#ifdef CONFIG_EXAMPLES_MICOM_TIMER_TEST
	char *timer_args[TIMER_ARG_NUM];
   	printf("just before this alloc_timer_args()\n");
	ret = alloc_timer_args(timer_args);
	printf("just after this alloc_timer_args()\n");
	if (ret != OK) {
		printf("TIMER TEST FAIL : out of memory.\n");
		return ERROR;
	}
	printf("just before this timer_example_main()\n");
	timer_example_main(TIMER_ARG_NUM, timer_args);
	printf("just after this timer_example_main()\n");
	free_timer_args(timer_args);
#else /* CONFIG_EXAMPLES_MICOM_TIMER_TEST */
#ifdef CONFIG_BINARY_MANAGER
	printf("just before this binary_manager_notify_binary_started()\n");
	ret = binary_manager_notify_binary_started();
	printf("just after this binary_manager_notify_binary_started()\n");
	if (ret < 0) {
		printf("MICOM notify 'START' state FAIL\n");
	}
#endif

#ifdef CONFIG_EXAMPLES_MESSAGING_TEST
	messaging_test();
#endif
#endif /* CONFIG_EXAMPLES_MICOM_TIMER_TEST */

	while (1) {
		sleep(10);
		printf("[%d] MICOM ALIVE\n", getpid());
	}

	return 0;

}
