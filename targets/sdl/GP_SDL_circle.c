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

#include "GP_SDL.h"
#include "GP_SDL_backend.h"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_Circle_8bpp
#define SETPIXEL	GP_SDL_SetPixel
#include "generic/circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_Circle_16bpp
#define SETPIXEL	GP_SDL_SetPixel
#include "generic/circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_Circle_24bpp
#define SETPIXEL	GP_SDL_SetPixel
#include "generic/circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_Circle_32bpp
#define SETPIXEL	GP_SDL_SetPixel
#include "generic/circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_FillCircle_8bpp
#define HLINE		GP_SDL_HLine
#include "generic/fill_circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_FillCircle_16bpp
#define HLINE		GP_SDL_HLine
#include "generic/fill_circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_FillCircle_24bpp
#define HLINE		GP_SDL_HLine
#include "generic/fill_circle_generic.c"

#define FN_ATTR		static
#define FN_NAME		GP_SDL_FillCircle_32bpp
#define HLINE		GP_SDL_HLine
#include "generic/fill_circle_generic.c"

void GP_SDL_Circle(GP_TARGET_TYPE *target, GP_COLOR_TYPE color, int xcenter, int ycenter, int r)
{
	switch (GP_BYTES_PER_PIXEL(target)) {
	case 1:
		GP_SDL_Circle_8bpp(target, color, xcenter, ycenter, r);
		break;
	case 2:
		GP_SDL_Circle_16bpp(target, color, xcenter, ycenter, r);
		break;
	case 3:
		GP_SDL_Circle_24bpp(target, color, xcenter, ycenter, r);
		break;
	case 4:
		GP_SDL_Circle_32bpp(target, color, xcenter, ycenter, r);
		break;
	}
}

void GP_SDL_FillCircle(GP_TARGET_TYPE *target, GP_COLOR_TYPE color, int xcenter, int ycenter, int r)
{
	switch (GP_BYTES_PER_PIXEL(target)) {
	case 1:
		GP_SDL_FillCircle_8bpp(target, color, xcenter, ycenter, r);
		break;
	case 2:
		GP_SDL_FillCircle_16bpp(target, color, xcenter, ycenter, r);
		break;
	case 3:
		GP_SDL_FillCircle_24bpp(target, color, xcenter, ycenter, r);
		break;
	case 4:
		GP_SDL_FillCircle_32bpp(target, color, xcenter, ycenter, r);
		break;
	}
}

