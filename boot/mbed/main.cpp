/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "platform/mbed_application.h"
#include "platform/mbed_toolchain.h"

#include "bootutil.h"

#if !DEVICE_FLASH
#error mcuboot requires FlashIAP functionality on the target!
#endif

/**
 * Hook for user app to initialize hardware/flash
 * @todo - better documentation (lol)
 */
MBED_WEAK void mbed_mcuboot_user_init(void) {

}

int main(void) {

	mbed_mcuboot_user_init();

	struct boot_rsp rsp;
	int rc;

	rc = boot_go(&rsp);
	if(rc != 0) {
		// Couldn't find a bootable image
		while(true)
			;
	}

	mbed_start_application(rsp.br_image_off);

}

