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

#ifndef GP_H
#define GP_H

#include <stdint.h>

/* basic definitions and structures */
#include "GP_minmax.h"
#include "GP_bufferinfo.h"
#include "GP_clipinfo.h"
#include "GP_getcliplimits.h"

/* semi-public, low-level drawing API */
#include "GP_writepixel.h"
#include "GP_fillcolumn.h"
#include "GP_fillrow.h"

/* public drawing API */
#include "GP_putpixel.h"
#include "GP_hline.h"
#include "GP_vline.h"
#include "GP_line.h"
#include "GP_rect.h"
#include "GP_triangle.h"
#include "GP_filltriangle.h"

/* fonts */
#include "GP_font.h"
#include "GP_textstyle.h"
#include "GP_textmetric.h"

#endif /* GP_COMMON_H */
