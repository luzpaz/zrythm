/*
 * project.c - A project (or song), containing all the project data
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


#include <gtk/gtk.h>

typedef struct _Audio_Engine Audio_Engine;
typedef struct _Plugin_Manager Plugin_Manager;
typedef struct _Timeline Timeline;

typedef struct _Project
{
  GString *         title;
  Audio_Engine *    audio_engine;
  Plugin_Manager *  plugin_manager;
  Timeline *        timeline;
  GSettings *       settings;
} Project;

extern Project * project;

/**
 * The project global variable, containing all the information that
 * should be available to all files.
 */
Project * project;

/**
 * Creates a project with default or given variables
 */
void
create_project (char * filename);

/**
 * Loads project from a file TODO
 */
void
open_project (GString * filename);

/**
 * Saves project to a file TODO
 */
void
save_project (GString * filename);
