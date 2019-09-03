/*
 * gui/widgets/center_dock.c - Main window widget
 *
 * Copyright (C) 2018 Alexandros Theodotou
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

#include "audio/transport.h"
#include "gui/widgets/bot_dock_edge.h"
#include "gui/widgets/center_dock.h"
#include "gui/widgets/center_dock_bot_box.h"
#include "gui/widgets/clip_editor.h"
#include "gui/widgets/clip_editor_inner.h"
#include "gui/widgets/left_dock_edge.h"
#include "gui/widgets/editor_ruler.h"
#include "gui/widgets/right_dock_edge.h"
#include "gui/widgets/ruler.h"
#include "gui/widgets/pinned_tracklist.h"
#include "gui/widgets/timeline_arranger.h"
#include "gui/widgets/timeline_minimap.h"
#include "gui/widgets/timeline_ruler.h"
#include "gui/widgets/timeline_selection_info.h"
#include "gui/widgets/timeline_toolbar.h"
#include "gui/widgets/tracklist.h"
#include "gui/widgets/tracklist_header.h"
#include "project.h"
#include "utils/resources.h"

G_DEFINE_TYPE (CenterDockWidget,
               center_dock_widget,
               DZL_TYPE_DOCK_BIN)

static gboolean
key_release_cb (GtkWidget      * widget,
                 GdkEventKey * event,
                 gpointer       data)
{
  if (event && event->keyval == GDK_KEY_space)
    {
      if (TRANSPORT->play_state == PLAYSTATE_ROLLING)
        transport_request_pause (TRANSPORT);
      else if (TRANSPORT->play_state == PLAYSTATE_PAUSED)
        transport_request_roll (TRANSPORT);
    }

  return FALSE;
}

void
on_hadj_value_changed (GtkAdjustment *adjustment,
                       gpointer       user_data)
{
  /*CenterDockWidget * self =*/
    /*Z_CENTER_DOCK_WIDGET (user_data);*/

  EVENTS_PUSH (ET_TIMELINE_VIEWPORT_CHANGED, NULL);
}

static void
on_pinned_timeline_scroll_allocate (
  GtkWidget    *widget,
  GdkRectangle *allocation,
  CenterDockWidget * self)
{
  if (gtk_paned_get_position (
        self->tracklist_paned) !=
      allocation->height)
    gtk_paned_set_position (
      self->tracklist_paned,
      allocation->height);
}

static void
on_divider_pos_changed (
  GObject    *gobject,
  GParamSpec *pspec,
  GtkPaned * paned)
{
  g_settings_set_int (
    S_UI, "bot-panel-divider-position",
    gtk_paned_get_position (paned));
}

void
center_dock_widget_setup (
  CenterDockWidget * self)
{

  tracklist_widget_setup (
    self->tracklist,
    TRACKLIST);
  pinned_tracklist_widget_setup (
    self->pinned_tracklist,
    TRACKLIST);

  /* set tracklist header size */
  GtkRequisition req;
  gtk_widget_get_preferred_size (
    GTK_WIDGET (self->ruler_scroll),
    &req, NULL);
  gtk_widget_set_size_request (
    GTK_WIDGET (self->tracklist_header), -1,
    req.height);

  gtk_paned_set_position (
    self->main_paned,
    2000);

  /* setup ruler */
  gtk_scrolled_window_set_hadjustment (
    self->ruler_scroll,
    gtk_scrolled_window_get_hadjustment (
      self->timeline_scroll));

  /* set pinned timeline to follow main timeline's
   * hscroll */
  gtk_scrolled_window_set_hadjustment (
    self->pinned_timeline_scroll,
    gtk_scrolled_window_get_hadjustment (
      self->timeline_scroll));

  ruler_widget_refresh (
    Z_RULER_WIDGET (MW_RULER));
  ruler_widget_refresh (
    Z_RULER_WIDGET (EDITOR_RULER));

  /* setup timeline */
  arranger_widget_setup (
    Z_ARRANGER_WIDGET (self->timeline),
    SNAP_GRID_TIMELINE);
  self->pinned_timeline->is_pinned = 1;
  arranger_widget_setup (
    Z_ARRANGER_WIDGET (self->pinned_timeline),
    SNAP_GRID_TIMELINE);

  /* link vertical scroll of timeline to
   * tracklist */
  gtk_scrolled_window_set_vadjustment (
    self->timeline_scroll,
    gtk_scrolled_window_get_vadjustment (
      self->tracklist_scroll));

  gtk_widget_show_all (
    GTK_WIDGET (self->timeline));
  gtk_widget_show_all (
    GTK_WIDGET (self->pinned_timeline));

  GtkAdjustment * adj =
    gtk_scrollable_get_hadjustment (
      GTK_SCROLLABLE (self->ruler_viewport));

  g_signal_connect (
    G_OBJECT (adj), "value-changed",
    G_CALLBACK (on_hadj_value_changed), self);
  g_signal_connect (
    G_OBJECT (self->pinned_timeline_scroll),
    "size-allocate",
    G_CALLBACK (on_pinned_timeline_scroll_allocate),
    self);

  bot_dock_edge_widget_setup (
    self->bot_dock_edge);
  left_dock_edge_widget_setup (
    self->left_dock_edge);
  right_dock_edge_widget_setup (
    self->right_dock_edge);

  /* remember divider position */
  gtk_paned_set_position (
    self->main_paned,
    g_settings_get_int (
      S_UI, "bot-panel-divider-position"));
  g_signal_connect (
    G_OBJECT (self->main_paned), "notify::position",
    G_CALLBACK (on_divider_pos_changed),
    self->main_paned);
}

static void
center_dock_widget_init (CenterDockWidget * self)
{
  g_type_ensure (BOT_DOCK_EDGE_WIDGET_TYPE);
  g_type_ensure (RIGHT_DOCK_EDGE_WIDGET_TYPE);
  g_type_ensure (LEFT_DOCK_EDGE_WIDGET_TYPE);
  g_type_ensure (TIMELINE_ARRANGER_WIDGET_TYPE);
  g_type_ensure (CENTER_DOCK_BOT_BOX_WIDGET_TYPE);
  g_type_ensure (TIMELINE_RULER_WIDGET_TYPE);
  g_type_ensure (TRACKLIST_HEADER_WIDGET_TYPE);
  g_type_ensure (TRACKLIST_WIDGET_TYPE);
  g_type_ensure (
    TIMELINE_SELECTION_INFO_WIDGET_TYPE);
  g_type_ensure (PINNED_TRACKLIST_WIDGET_TYPE);
  g_type_ensure (TIMELINE_TOOLBAR_WIDGET_TYPE);

  gtk_widget_init_template (GTK_WIDGET (self));

  GValue a = G_VALUE_INIT;
  g_value_init (&a, G_TYPE_BOOLEAN);
  g_value_set_boolean (&a, 1);
  g_object_set_property (
    G_OBJECT (self), "left-visible", &a);
  g_object_set_property (
    G_OBJECT (self), "right-visible", &a);
  g_object_set_property (
    G_OBJECT (self), "bottom-visible", &a);
  g_object_set_property (
    G_OBJECT (self), "top-visible", &a);

  /* set events */
  g_signal_connect (
    G_OBJECT (self), "key_release_event",
    G_CALLBACK (key_release_cb), self);
}


static void
center_dock_widget_class_init (CenterDockWidgetClass * _klass)
{
  GtkWidgetClass * klass =
    GTK_WIDGET_CLASS (_klass);
  resources_set_class_template (
    klass, "center_dock.ui");

  gtk_widget_class_set_css_name (
    klass, "center-dock");

  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    main_paned);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    selection_info);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    editor_top);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist_timeline);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist_top);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist_scroll);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist_viewport);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist_header);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    ruler);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    ruler_scroll);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    ruler_viewport);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    timeline_scroll);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    timeline_viewport);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    timeline);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    ruler);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    pinned_tracklist);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    timeline_divider_pane);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    pinned_timeline_scroll);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    pinned_timeline_viewport);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    pinned_timeline);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    timeline_toolbar);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    bot_box);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    left_dock_edge);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    bot_dock_edge);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    right_dock_edge);
  gtk_widget_class_bind_template_child (
    klass,
    CenterDockWidget,
    tracklist_paned);
}
