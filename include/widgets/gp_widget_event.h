//SPDX-License-Identifier: LGPL-2.0-or-later

/*

   Copyright (c) 2014-2020 Cyril Hrubis <metan@ucw.cz>

 */

/**
 * @file gp_widget_event.h
 * @brief Widget event handling
 *
 * Widget events is an interface between the application and the widget
 * toolkit, typical event is a button press or a text edit. Each widget usually
 * has only one event callback and sends a subset of event types.
 */

#ifndef GP_WIDGET_EVENT_H
#define GP_WIDGET_EVENT_H

#include <stdarg.h>
#include <widgets/gp_widget_types.h>

/**
 * @brief Widget event type.
 *
 * We have 32bit mask so the maximal number of possible events is 32.
 */
enum gp_widget_event_type {
	/** Send right after widget has been allocated and initalized. */
	GP_WIDGET_EVENT_NEW,
	/** Send before widget is freed. */
	GP_WIDGET_EVENT_FREE,
	/** Widget specific event e.g. button has been pressed, details in sub_type */
	GP_WIDGET_EVENT_WIDGET,
	/** Raw user input event such as mouse movement or keypress. */
	GP_WIDGET_EVENT_INPUT,
	/** Send by pixmap widget when pixmap has has to be redrawn. */
	GP_WIDGET_EVENT_REDRAW,
	/** Send when widget was resized. */
	GP_WIDGET_EVENT_RESIZE,
	/** Color scheme has changed */
	GP_WIDGET_EVENT_COLOR_SCHEME,
	/** The number of events, i.e. last event + 1. */
	GP_WIDGET_EVENT_MAX,
};

/** @brief Default widget event mask */
#define GP_WIDGET_EVENT_DEFAULT_MASK ( \
	(1<<GP_WIDGET_EVENT_NEW) |     \
	(1<<GP_WIDGET_EVENT_FREE) |    \
	(1<<GP_WIDGET_EVENT_WIDGET)  \
)

/**
 * @brief Masks widget events
 *
 * Disables widget events.
 *
 * @param self The widget
 * @param ev_type Event type to disable
 */
void gp_widget_event_mask(gp_widget *self, enum gp_widget_event_type ev_type);

/**
 * @brief Unmasks widget events
 *
 * Enables widget events.
 *
 * @param self The widget
 * @param ev_type Event type to enable
 */
void gp_widget_event_unmask(gp_widget *self, enum gp_widget_event_type ev_type);

/**
 * @brief Returns string name for a given event type.
 *
 * @param ev_type Widget event type.
 * @return Widget event type name.
 */
const char *gp_widget_event_type_name(enum gp_widget_event_type ev_type);

/**
 * @brief Event structure passed to widget event handler.
 */
struct gp_widget_event {
	/** The widget the event is for */
	struct gp_widget *self;
	/** Generic event type, i.e. enum gp_widget_event_type */
	uint16_t type;
	/** Widget specific subtype defined by widgets */
	uint16_t sub_type;
	/* internal DO NOT TOUCH */
	const struct gp_widget_render_ctx *ctx;
	/** Optional pointer/value */
	union {
		void *ptr;
		long val;
		struct gp_bbox *bbox;
		struct gp_event *input_ev;
	};
};

/**
 * @brief Prints event details into stdout.
 *
 * @param ev Pointer to a widget event.
 */
void gp_widget_event_dump(gp_widget_event *ev);

/**
 * @brief Helper function to send a widget library event to application.
 *
 * This is called by the widget library when event should be send to the
 * widget.
 *
 * @param self Pointer to the widget sending this event.
 * @param type Event type see gp_widget_event_type enum.
 * @return The return value from application event handler.
 */
static inline int gp_widget_send_event(gp_widget *self,
				       enum gp_widget_event_type type,
				       ...)
{
	if (!self->on_event)
		return 0;

	if (!(self->event_mask & (1<<type)))
		return 0;

	const struct gp_widget_render_ctx *ctx = NULL;

	va_list va;
	va_start(va, type);
	if (type == GP_WIDGET_EVENT_INPUT ||
	    type == GP_WIDGET_EVENT_RESIZE ||
	    type == GP_WIDGET_EVENT_REDRAW ||
	    type == GP_WIDGET_EVENT_COLOR_SCHEME)
		ctx = va_arg(va, void*);
	long val = va_arg(va, long);
	va_end(va);

	gp_widget_event ev = {
		.self = self,
		.type = type,
		.ctx = ctx,
		.val = val,
	};

	return self->on_event(&ev);
}

/**
 * @brief Helper function to send a widget specific event to application.
 *
 * This is called by the widget library when event should be send to the
 * widget.
 *
 * @param self Pointer to the widget sending this event.
 * @param type Event type as defined by a particular widget.
 * @return The return value from application event handler.
 */
static inline int gp_widget_send_widget_event(gp_widget *self,
				              unsigned int sub_type,
				              ...)
{
	if (!self->on_event)
		return 0;

	va_list va;
	va_start(va, sub_type);
	long val = va_arg(va, long);
	va_end(va);

	gp_widget_event ev = {
		.self = self,
		.type = GP_WIDGET_EVENT_WIDGET,
		.sub_type = sub_type,
		.val = val,
	};

	return self->on_event(&ev);
}

/**
 * @brief A helper function to inject key and utf input events to a widget.
 *
 * Internal function used in widget tests.
 *
 * This function takes a widget event and if the event type is
 * GP_WIDGET_EVENT_INPUT the input event is injected to the widget input event
 * handler, i.e. the widget will get the input as if it was focused.
 *
 * This of course works only for key presses and unicode input events as
 * relative or absolute coordinates are normalized as events pass down the
 * widget tree, i.e. for any event widget receives the widget top level corner
 * has coordinate [0,0]. Hence these kinds of events are not injected.
 *
 * @param self A widget to inject the input event to.
 * @param ev A widget event.
 *
 * @return Non-zero if the event was handled, zero otherwise.
 */
int gp_widget_input_inject(gp_widget *self, gp_widget_event *ev);

#endif /* GP_WIDGET_EVENT_H */
