/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _GUAC_MEMORY_H
#define _GUAC_MEMORY_H

/**
 * Provides functions for allocating and freeing up memory.
 *
 * @file memory.h
 */

#include <stddef.h>

 /**
  * Calls calloc for 1 item of given size. Ensures size is at least 1 byte.
  *
  * @param size
  */
void* xzalloc(size_t size);

/**
 * Free memory.
 *
 * @param ptr
 */
void xfree(void* ptr);

/**
 * Calls malloc with a lower bound of 1 byte and upper bound of 16mb.
 *
 * @param size
 * @return
 */
void* xmalloc(size_t size);

#endif

