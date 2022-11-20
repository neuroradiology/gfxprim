//SPDX-License-Identifier: LGPL-2.0-or-later

/*

   Copyright (c) 2014-2022 Cyril Hrubis <metan@ucw.cz>

 */

#ifndef GP_WIDGET_KEYS
#define GP_WIDGET_KEYS

#include <input/gp_event.h>

/**
 * @brief Utility function to check for modifier keys.
 *
 * @ev An input event.
 * @return Non-zero if any of modifier keys is pressed such as control or alt.
 */
static inline int gp_widget_key_mod_pressed(gp_event *ev)
{
	return gp_ev_any_key_pressed(ev, GP_KEY_LEFT_ALT, GP_KEY_RIGHT_ALT,
	                                    GP_KEY_LEFT_CTRL, GP_KEY_RIGHT_CTRL,
	                                    GP_KEY_LEFT_META, GP_KEY_RIGHT_META);
}

/* If defined widget focus can be moved with arrow keys when any of these keys is pressed */
#define GP_WIDGET_KEYS_MOD_FOCUS GP_KEY_LEFT_CTRL, GP_KEY_RIGHT_CTRL
/* Keys to move focus into a specified direction */
#define GP_WIDGET_KEY_FOCUS_LEFT GP_KEY_LEFT
#define GP_WIDGET_KEY_FOCUS_RIGHT GP_KEY_RIGHT
#define GP_WIDGET_KEY_FOCUS_UP GP_KEY_UP
#define GP_WIDGET_KEY_FOCUS_DOWN GP_KEY_DOWN

/* Key to move focus to a next widget */
#define GP_WIDGET_KEY_FOCUS_NEXT GP_KEY_TAB
/* Keys to reverse the direction of previous key if any of these keys is pressed */
#define GP_WIDGET_KEYS_MOD_FOCUS_PREV GP_KEY_LEFT_SHIFT, GP_KEY_RIGHT_SHIFT

/* Key to toggle color scheme */
#define GP_WIDGET_KEYS_MOD_COLOR_SCHEME GP_KEY_LEFT_CTRL, GP_KEY_RIGHT_CTRL
#define GP_WIDGET_KEY_COLOR_SCHEME GP_KEY_SPACE

/* Key to show about dialog */
#define GP_WIDGET_KEYS_MOD_ABOUT GP_KEY_LEFT_CTRL, GP_KEY_RIGHT_CTRL
#define GP_WIDGET_KEY_ABOUT GP_KEY_I

/* Keys to increase/decrease text size */
#define GP_WIDGET_KEYS_MOD_ZOOM GP_KEY_LEFT_CTRL, GP_KEY_RIGHT_CTRL
#define GP_WIDGET_KEY_ZOOM_IN GP_KEY_EQUAL
#define GP_WIDGET_KEY_ZOOM_OUT GP_KEY_MINUS

/* Key to quit the app */
#define GP_WIDGET_KEYS_MOD_QUIT GP_KEY_LEFT_ALT, GP_KEY_RIGHT_ALT
#define GP_WIDGET_KEY_QUIT GP_KEY_F4

#endif /* GP_WIDGET_KEYS */
