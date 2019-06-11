/*
 * Copyright (C) 2018-2019 Alexandros Theodotou <alex at zrythm dot org>
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

#include <stdlib.h>

#include "audio/chord_descriptor.h"

/* see chord_desriptor.h */
NOTE_LABELS;
CHORD_TYPES;

/**
 * Creates a ChordDescriptor.
 */
ChordDescriptor *
chord_descriptor_new (
  MusicalNote            root,
  uint8_t                has_bass,
  MusicalNote            bass,
  ChordType              type,
  int                    inversion)
{
  ChordDescriptor * self =
    calloc (1, sizeof (ChordDescriptor));

  self->root_note = root;
  self->has_bass = has_bass;
  if (has_bass)
    self->bass_note = bass;
  self->type = type;
  self->inversion = inversion;

  /* add bass note */
  if (has_bass)
    {
      self->notes[bass] = 1;
    }

  /* add root note */
  self->notes[12 + root] = 1;

  /* add rest of chord notes */
  switch (type)
    {
    case CHORD_TYPE_MAJ:
      self->notes[12 + root + 4] = 1;
      self->notes[12 + root + 4 + 3] = 1;
      break;
    case CHORD_TYPE_MIN:
      self->notes[12 + root + 3] = 1;
      self->notes[12 + root + 3 + 4] = 1;
      break;
    case CHORD_TYPE_DIM:
      self->notes[12 + root + 3] = 1;
      self->notes[12 + root + 3 + 3] = 1;
      break;
    case CHORD_TYPE_AUG:
      self->notes[12 + root + 4] = 1;
      self->notes[12 + root + 4 + 4] = 1;
      break;
    case CHORD_TYPE_SUS2:
      self->notes[12 + root + 2] = 1;
      self->notes[12 + root + 2 + 5] = 1;
      break;
    case CHORD_TYPE_SUS4:
      self->notes[12 + root + 5] = 1;
      self->notes[12 + root + 5 + 2] = 1;
      break;
    default:
      g_warning ("chord unimplemented");
      break;
    }

  /* TODO invert */

  return self;
}

/**
 * Clones the given ChordDescriptor.
 */
ChordDescriptor *
chord_descriptor_clone (
  ChordDescriptor * src)
{
  ChordDescriptor * cd =
    chord_descriptor_new (
      src->root_note, src->has_bass, src->bass_note,
      src->type, src->inversion);

  return cd;
}

/**
 * Returns the musical note as a string (eg. "C3").
 */
const char *
chord_descriptor_note_to_string (
MusicalNote note)
{
  (void) note_labels;
  return note_labels[note];
}

/**
 * Returns the chord type as a string (eg. "aug").
 */
const char *
chord_descriptor_chord_type_to_string (
  ChordType type)
{
  (void) chord_type_labels;
  return chord_type_labels[type];
}

/**
 * Returns if the given key is in the chord
 * represented by the given ChordDescriptor.
 *
 * @param key A note inside a single octave (0-11).
 */
int
chord_descriptor_is_key_in_chord (
  ChordDescriptor * chord,
  MusicalNote       key)
{
  if ((chord->has_bass &&
      chord->bass_note == key) ||
      chord->root_note == key)
    return 1;

  for (int i = 0; i < 36; i++)
    {
      if (chord->notes[i] == 1 &&
          i % 12 == key)
        return 1;
    }
  return 0;
}

/**
 * Returns the chord in human readable string.
 *
 * MUST be free'd by caller.
 */
char *
chord_descriptor_to_string (
  ChordDescriptor * chord)
{
  return g_strdup_printf (
    "%s%s",
    chord_descriptor_note_to_string (
      chord->root_note),
    chord_descriptor_chord_type_to_string (
      chord->type));
}

void
chord_descriptor_free (ChordDescriptor * self)
{
  free (self);
}
