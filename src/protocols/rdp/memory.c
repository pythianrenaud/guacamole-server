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

#include "config.h"

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Allocate memory initialized to zero.
 *
 * @param size
 */
void *xzalloc(size_t size) {
    void *mem;

    if (size < 1)
        size = 1;

    mem = calloc(1, size);

    if (mem == NULL) {
        perror("xzalloc");
        printf("xzalloc: failed to allocate memory of size: %d\n", (int) size);
    }

    return mem;
}

/**
 * Allocate memory.
 * @param size
 */
void *xmalloc(size_t size) {
    void *mem;

    if (size < 1) {
        printf("xmalloc: adjusting xmalloc bytes\n");
        size = 1;
    }
    if (size > 16 * 1024 * 1024) {
        printf("xmalloc: bad size\n");
        return NULL;
    }
    mem = malloc(size);
    if (mem == NULL) {
        perror("xmalloc");
        printf("xmalloc: failed to allocate memory of size: %d\n", (int) size);
    }
    return mem;
}

/**
 * Free memory.
 * @param mem
 */
void xfree(void *ptr) {
    if (ptr != NULL)
        free(ptr);
}

