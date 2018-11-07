/*
 * utils/gtk.h - GTK utils
 *
 * Copyright (C) 2018 Alexandros Theodotou
 *
 * This file is part of Zrythm
 *
 * Zrythm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zrythm is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zrythm.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __UTILS_GTK_H__
#define __UTILS_GTK_H__

#include <gtk/gtk.h>

/**
 * For readability, instead of using 0s and 1s.
 */
enum ZGtkFill
{
  Z_GTK_NO_FILL,
  Z_GTK_FILL
};

enum ZGtkResize
{
  Z_GTK_NO_RESIZE,
  Z_GTK_RESIZE
};

enum ZGtkExpand
{
  Z_GTK_NO_EXPAND,
  Z_GTK_EXPAND
};

enum ZGtkShrink
{
  Z_GTK_NO_SHRINK,
  Z_GTK_SHRINK
};

void
z_gtk_container_remove_all_children (GtkContainer * container);

#endif
