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

/*
 * Parameterized template for function for drawing horizontal lines.
 * Parameters that must be #defined outside:
 *
 *      FN_ATTR
 *      	(Optional.) Attributes of the function (e.g. "static")
 * 	FN_NAME
 * 		Name of the function.
 * 	BYTES_PER_PIXEL
 * 		Number of bytes per pixel of the target.
 */

#ifndef FN_ATTR
#define FN_ATTR
#endif

void FN_NAME(GP_TARGET_TYPE *target, GP_COLOR_TYPE color, int x0, int x1, int y)
{
	/* Ensure that x0 <= x1, swap coordinates if needed. */
	if (x0 > x1) {
		FN_NAME(target, color, x1, x0, y);
		return;
	}

	/* Get the clipping rectangle. */
	int xmin, xmax, ymin, ymax;
	GP_GET_CLIP_RECT(target, xmin, xmax, ymin, ymax);

	/* Check whether the line is not completely clipped out. */
	if (y < ymin || y > ymax || x0 > xmax || x1 < xmin)
		return;

	/* Clip the start and end of the line. */
	if (x0 < xmin) {
		x0 = xmin;
	}
	if (x1 > xmax) {
		x1 = xmax;
	}

	/* Number of pixels to draw (always at least one point). */
	size_t pixelcount = 1 + x1 - x0;

#if BYTES_PER_PIXEL == 4

	GP_WritePixels32bpp(GP_PIXEL_ADDR(target, x0, y), pixelcount,
				(uint32_t) color);

#elif BYTES_PER_PIXEL == 3

	GP_WritePixels24bpp(GP_PIXEL_ADDR(target, x0, y), pixelcount,
				(uint32_t) color);

#elif BYTES_PER_PIXEL == 2

	GP_WritePixels16bpp(GP_PIXEL_ADDR(target, x0, y), pixelcount,
				(uint16_t) color);

#elif BYTES_PER_PIXEL == 1

	GP_WritePixels8bpp(GP_PIXEL_ADDR(target, x0, y), pixelcount,
				(uint8_t) color);

#else
#error "Unsupported value of BYTES_PER_PIXEL"
#endif
}

#undef FN_ATTR
#undef FN_NAME
#undef BYTES_PER_PIXEL

