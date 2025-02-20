/*
 * Copyright (C) 2021 Alexandros Theodotou <alex at zrythm.org>
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * \file
 *
 * Memory utils.
 */

#ifndef __UTILS_MEM_H__
#define __UTILS_MEM_H__

#include <stddef.h>

/**
 * Reallocate and zero out newly added memory.
 */
void *
realloc_zero (void * pBuffer, size_t oldSize, size_t newSize);

#endif
