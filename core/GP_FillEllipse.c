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

#include "GP.h"

#define CONTEXT_T GP_Context *
#define PIXVAL_T GP_Pixel
	#define HLINE GP_HLine8bpp
	#define FN_NAME GP_FillEllipse8bpp
		#include "algo/FillEllipse.algo.c"
	#undef FN_NAME
	#undef HLINE
	#define HLINE GP_HLine16bpp
	#define FN_NAME GP_FillEllipse16bpp
		#include "algo/FillEllipse.algo.c"
	#undef FN_NAME
	#undef HLINE
	#define HLINE GP_HLine24bpp
	#define FN_NAME GP_FillEllipse24bpp
		#include "algo/FillEllipse.algo.c"
	#undef FN_NAME
	#undef HLINE
	#define HLINE GP_HLine32bpp
	#define FN_NAME GP_FillEllipse32bpp
		#include "algo/FillEllipse.algo.c"
	#undef FN_NAME
	#undef HLINE
#undef PIXVAL_T
#undef CONTEXT_T

GP_RetCode GP_FillEllipse(GP_Context *context, int xcenter, int ycenter,
	unsigned int a, unsigned int b, GP_Color color)
{
	GP_CHECK_CONTEXT(context);

	GP_Pixel pixel;
	pixel.type = context->pixel_type;
	GP_RetCode ret = GP_ColorToPixel(color, &pixel);

	switch (context->bits_per_pixel) {
	case 8:
		GP_FillEllipse8bpp(context, xcenter, ycenter, a, b, pixel);
		break;
	case 16:
		GP_FillEllipse16bpp(context, xcenter, ycenter, a, b, pixel);
		break;
	case 24:
		GP_FillEllipse24bpp(context, xcenter, ycenter, a, b, pixel);
		break;
	case 32:
		GP_FillEllipse32bpp(context, xcenter, ycenter, a, b, pixel);
		break;
	default:
		return GP_ENOIMPL;
	}

	return ret;
}

GP_RetCode GP_TFillEllipse(GP_Context *context, int xcenter, int ycenter,
                           unsigned int a, unsigned int b, GP_Color color)
{
	GP_TRANSFORM_POINT(context, xcenter, ycenter);
	GP_TRANSFORM_SWAP(context, a, b);
	return GP_FillEllipse(context, xcenter, ycenter, a, b, color);
}
