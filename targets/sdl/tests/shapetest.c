/*****************************************************************************
 * This file is part of gfxprim library.                                     *
 *                                                                           *
 * Gfxprim is free software; you can redistribute it and/or                  *
 * modify it under the terms of the GNU Lesser General Public                *
 * License as published by the Free Software Foundation; either              *
 * version 2.1 of the License, or (at your option) any later version.        *
 *                                                                           *
 * Gfxprim is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public          *
 * License along with gfxprim; if not, write to the Free Software            *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,                        *
 * Boston, MA  02110-1301  USA                                               *
 *                                                                           *
 * Copyright (C) 2009-2010 Jiri "BlueBear" Dluhos                            *
 *                         <jiri.bluebear.dluhos@gmail.com>                  *
 *                                                                           *
 * Copyright (C) 2009-2010 Cyril Hrubis <metan@ucw.cz>                       *
 *                                                                           *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "GP.h"
#include "GP_SDL.h"

/* The surface used as a display (in fact it is a software surface). */
SDL_Surface *display = NULL;
GP_Context context;

/* Timer used for refreshing the display */
SDL_TimerID timer;

/* An event used for signaling that the timer was triggered. */
SDL_UserEvent timer_event;

Uint32 timer_callback(__attribute__((unused)) Uint32 interval,
			__attribute__((unused)) void * param)
{
	timer_event.type = SDL_USEREVENT;
	SDL_PushEvent((SDL_Event *) &timer_event);
	return 60;
}

/* Basic colors in display-specific format. */
GP_Color black    = GP_COLNAME_PACK(GP_COL_BLACK);
GP_Color white    = GP_COLNAME_PACK(GP_COL_WHITE);
GP_Color yellow   = GP_COLNAME_PACK(GP_COL_YELLOW);
GP_Color red      = GP_COLNAME_PACK(GP_COL_RED);
GP_Color gray     = GP_COLNAME_PACK(GP_COL_GRAY_LIGHT);
GP_Color darkgray = GP_COLNAME_PACK(GP_COL_GRAY_DARK);

/* Radius of the shape being drawn */
static int xradius = 5;
static int yradius = 5;

/* Draw outline? 0=none, 1=before filling, 2=after filling */
static int outline = 0;

/* Fill the shape? */
static int fill = 1;

/* Show axes? */
static int show_axes = 1;

/* Shape to be drawn */
#define SHAPE_FIRST	1
#define SHAPE_TRIANGLE	1
#define SHAPE_CIRCLE    2
#define SHAPE_ELLIPSE	3
#define SHAPE_RECTANGLE	4
#define SHAPE_LAST	4
static int shape = SHAPE_FIRST;

/* Variants in coordinates, if applicable */
static int variant = 1;

/* Increments added to radii in every timeframe (0 = no change). */
static int xradius_add = 0;
static int yradius_add = 0;

void draw_testing_triangle(int x, int y, int xradius, int yradius)
{
	int x0, y0, x1, y1, x2, y2;
	switch (variant) {
	case 1:
		x0 = x;
		y0 = y - yradius;
		x1 = x - xradius;
		y1 = y;
		x2 = x + xradius;
		y2 = y + yradius;
		break;
	case 2:
		x0 = x - xradius;
		y0 = y - yradius;
		x1 = x + xradius;
		y1 = y;
		x2 = x + xradius;
		y2 = y + yradius;
		break;
	
	case 3:
	default:
		x0 = x;
		y0 = y - yradius;
		x1 = x + xradius;
		y1 = y + yradius;
		x2 = x - xradius;
		y2 = y + yradius;
		break;
	}

	if (outline == 1) {
		GP_Triangle(&context, x0, y0, x1, y1, x2, y2, yellow);
	}

	if (fill) {
		GP_FillTriangle(&context, x0, y0, x1, y1, x2, y2, red);
	}

	if (outline == 2) {
		GP_Triangle(&context, x0, y0, x1, y1, x2, y2, white);
	}
}

void draw_testing_circle(int x, int y, int xradius,
			__attribute__((unused)) int yradius)
{
	if (outline == 1) {
		GP_Circle(&context, x, y, xradius, yellow);
	}
	if (fill) {
		GP_FillCircle(&context, x, y, xradius, red);
	}
	if (outline == 2) {
		GP_Circle(&context, x, y, xradius, white);
	}
}

void draw_testing_ellipse(int x, int y, int xradius, int yradius)
{
	if (outline == 1) {
		GP_Ellipse(&context, x, y, xradius, yradius, yellow);
	}
	if (fill) {
		GP_FillEllipse(&context, x, y, xradius, yradius, red);
	}
	if (outline == 2) {
		GP_Ellipse(&context, x, y, xradius, yradius, white);
	}
}

void draw_testing_rectangle(int x, int y, int xradius, int yradius)
{
	if (outline == 1) {
		GP_Rect(&context, x - xradius, y - yradius, x + xradius, y + yradius, yellow);
	}
	if (fill) {
		GP_FillRect(&context, x - xradius, y - yradius, x + xradius, y + yradius, red);
	}
	if (outline == 2) {
		GP_Rect(&context, x - xradius, y - yradius, x + xradius, y + yradius, white);
	}
}

void redraw_screen(void)
{
	int x = 320;
	int y = 240;

	/* text style for the label */
	struct GP_TextStyle style = {
		.font = &GP_default_console_font,
		.pixel_xmul = 2,
		.pixel_ymul = 1,
		.pixel_xspace = 0,
		.pixel_yspace = 1,
	};

	SDL_LockSurface(display);
	GP_FillRect(&context, 0, 0, context.rows, context.columns, black);

	/* axes */
	if (show_axes) {
		GP_HLine(&context, 0, 640, y, gray);
		GP_HLine(&context, 0, 640, y-yradius, darkgray);
		GP_HLine(&context, 0, 640, y+yradius, darkgray);
		GP_VLine(&context, x, 0, 480, gray);
		GP_VLine(&context, x-xradius, 0, 480, darkgray);
		GP_VLine(&context, x+xradius, 0, 480, darkgray);
	}

	/* the shape */
	const char *title = NULL;
	switch (shape) {
	case SHAPE_TRIANGLE:
		draw_testing_triangle(x, y, xradius, yradius);
		title = "TRIANGLE";
		break;
	case SHAPE_CIRCLE:
		draw_testing_circle(x, y, xradius, yradius);
		title = "CIRCLE";
		break;
	case SHAPE_ELLIPSE:
		draw_testing_ellipse(x, y, xradius, yradius);
		title = "ELLIPSE";
		break;
	case SHAPE_RECTANGLE:
		draw_testing_rectangle(x, y, xradius, yradius);
		title = "RECTANGLE";
		break;
	}
	GP_Text(&context, &style, 16, 16, title, white);

	SDL_UnlockSurface(display);
}

void event_loop(void)
{
	SDL_Event event;

	while (SDL_WaitEvent(&event) > 0) {

		switch (event.type) {
		case SDL_USEREVENT:

			if (xradius + xradius_add > 1 && xradius + xradius_add < 400)
				xradius += xradius_add;
			if (yradius + yradius_add > 1 && yradius + yradius_add < 400)
				yradius += yradius_add;
			
			redraw_screen();
			SDL_Flip(display);
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {

			case SDLK_f:
				fill = !fill;
				if (!fill && !outline) {
					outline = 1;
				}
				break;

			case SDLK_o:
				outline++;
				if (outline == 3) { outline = 0; }
				if (!fill && outline == 0) {
					fill = 1;
				}
				break;

			case SDLK_x:
				show_axes = !show_axes;
				break;

			case SDLK_ESCAPE:
				return;

			case SDLK_LEFT:
				xradius_add = -1;
				break;

			case SDLK_RIGHT:
				xradius_add = 1;
				break;

			case SDLK_UP:
				yradius_add = 1;
				break;

			case SDLK_DOWN:
				yradius_add = -1;
				break;

			case SDLK_PAGEUP:
				xradius_add = 1;
				yradius_add = 1;
				break;

			case SDLK_PAGEDOWN:
				xradius_add = -1;
				yradius_add = -1;
				break;

			case SDLK_1:
				variant = 1;
				break;

			case SDLK_2:
				variant = 2;
				break;

			case SDLK_3:
				variant = 3;
				break;

			case SDLK_SPACE:
				shape++;
				if (shape > SHAPE_LAST)
					shape = SHAPE_FIRST;
				break;

			case SDLK_EQUALS:
				if (xradius > yradius)
					yradius = xradius;
				else
					xradius = yradius;
				break;

			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {

			/* Stop incrementing as soon as the key is released. */
			case SDLK_LEFT:
			case SDLK_RIGHT:
				xradius_add = 0;
				break;
			case SDLK_UP:
			case SDLK_DOWN:
				yradius_add = 0;
				break;

			case SDLK_PAGEUP:
			case SDLK_PAGEDOWN:
				xradius_add = 0;
				yradius_add = 0;
				break;

			default:
				break;
			}
		break;
		case SDL_QUIT:
			return;
		}
	}
}

void print_instructions(void)
{
	printf("Use the following keys to control the test:\n");
	printf("    Esc ......... exit\n");
	printf("    Space ....... change shapes\n");
	printf("    O ........... draw outlines (none/before/after fill)\n");
	printf("    F ........... toggle filling\n");
	printf("    X ........... show/hide axes\n");
	printf("    left/right .. increase/decrease horizontal radius\n");
	printf("    up/down ..... increase/decrease vertical radius\n");
	printf("    PgUp/PgDn ... increase/decrease both radii\n");
	printf("    = ........... reset radii to the same value\n");
	printf("    1/2/3 ....... choose shape variant (if applicable)\n");
}

int main(int argc, char ** argv)
{
	int display_bpp = 0;

	int i;
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-16") == 0) {
			display_bpp = 16;
		}
		else if (strcmp(argv[i], "-24") == 0) {
			display_bpp = 24;
		}
	}

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	/* Create a window with a software back surface */
	display = SDL_SetVideoMode(640, 480, display_bpp, SDL_SWSURFACE);
	if (display == NULL) {
		fprintf(stderr, "Could not open display: %s\n", SDL_GetError());
		goto fail;
	}

	/* Set up a clipping rectangle to exercise clipping */
	SDL_Rect clip_rect = {10, 10, 620, 460};
	SDL_SetClipRect(display, &clip_rect);

	GP_SDL_ContextFromSurface(&context, display);

	/* Set up the refresh timer */
	timer = SDL_AddTimer(60, timer_callback, NULL);
	if (timer == 0) {
		fprintf(stderr, "Could not set up timer: %s\n", SDL_GetError());
		goto fail;
	}

	/* Print a short info how to use this test. */
	print_instructions();

	/* Enter the event loop */
	event_loop();

	/* We're done */
	SDL_Quit();
	return 0;

fail:
	SDL_Quit();
	return 1;
}

