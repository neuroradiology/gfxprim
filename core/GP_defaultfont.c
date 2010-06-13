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

#include "GP_font.h"

static uint8_t GP_default_console_font_data[] = {
	/* ' ' */ 	8, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/* '!' */	8, 0,	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0, 0, 0x08, 0,
	/* '"' */	8, 0,	0x24, 0x24, 0x48, 0, 0, 0, 0, 0, 0, 0, 0,
	/* '#' */	8, 0,	0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0,
	/* '$' */ 	8, 0,	0x08, 0x3e, 0x49, 0x48, 0x38, 0x0e, 0x09, 0x49, 0x3e, 0x08, 0,
	/* '%' */  	8, 0,	0x60, 0x91, 0x92, 0x64, 0x08, 0x10, 0x26, 0x49, 0x89, 0x06, 0,
	/* '&' */  	8, 0,	0x18, 0x24, 0x24, 0x24, 0x18, 0x2b, 0x44, 0x44, 0x44, 0x3b, 0,
	/* ''' */  	8, 0,	0x0c, 0x08, 0x10, 0, 0, 0, 0, 0, 0, 0, 0,
	/* '(' */  	8, 0,	0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0,
	/* ')' */  	8, 0,	0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0,
	/* '*' */  	8, 0,	0x08, 0x2a, 0x1c, 0x2a, 0x08, 0, 0, 0, 0, 0, 0,
	/* '+' */  	8, 0,	0, 0, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0, 0,
	/* ',' */  	8, 0,	0, 0, 0, 0, 0, 0, 0, 0x08, 0x08, 0x10, 0,
	/* '-' */  	8, 0,	0, 0, 0, 0, 0, 0x7f, 0, 0, 0, 0, 0,
	/* '.' */  	8, 0,	0, 0, 0, 0, 0, 0, 0, 0x18, 0x18, 0, 0,
	/* '/' */  	8, 0,	0, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0, 0,
	/* '0' */  	8, 0,	0, 0x3e, 0x43, 0x45, 0x49, 0x49, 0x51, 0x61, 0x3e, 0, 0,
	/* '1' */  	8, 0,	0, 0x08, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7f, 0, 0,
	/* '2' */  	8, 0,	0, 0x3e, 0x41, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7f, 0, 0,
	/* '3' */  	8, 0,	0, 0x3e, 0x41, 0x01, 0x0e, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* '4' */  	8, 0,	0, 0x0c, 0x14, 0x24, 0x44, 0x84, 0xff, 0x04, 0x04, 0, 0,
	/* '5' */  	8, 0,	0, 0x7f, 0x40, 0x40, 0x7e, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* '6' */  	8, 0,	0, 0x3f, 0x40, 0x40, 0x7e, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* '7' */ 	8, 0,	0, 0x7f, 0x41, 0x02, 0x04, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* '8' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* '9' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x41, 0x3f, 0x01, 0x41, 0x3e, 0, 0,
	/* ':' */  	8, 0,	0, 0, 0, 0x18, 0x18, 0, 0, 0x18, 0x18, 0, 0,
	/* ';' */  	8, 0,	0, 0, 0, 0x18, 0x18, 0, 0, 0x18, 0x08, 0x10, 0,
	/* '<' */  	8, 0,	0, 0, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0, 0,
	/* '=' */  	8, 0,	0, 0, 0, 0x7f, 0, 0, 0x7f, 0, 0, 0, 0,
	/* '>' */  	8, 0,	0, 0, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0, 0,
	/* '?' */  	8, 0,	0, 0x3e, 0x41, 0x02, 0x04, 0x08, 0x08, 0, 0, 0x08, 0,
	/* '@' */  	8, 0,	0, 0x3e, 0x41, 0x9d, 0xa5, 0xa5, 0xa5, 0x9e, 0x41, 0x3e, 0,
	/* 'A' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0, 0,
	/* 'B' */  	8, 0,	0, 0x7e, 0x41, 0x41, 0x7e, 0x41, 0x41, 0x41, 0x7e, 0, 0,
	/* 'C' */  	8, 0,	0, 0x3e, 0x41, 0x40, 0x40, 0x40, 0x40, 0x41, 0x3e, 0, 0,
	/* 'D' */  	8, 0,	0, 0x7c, 0x42, 0x41, 0x41, 0x41, 0x41, 0x42, 0x7c, 0, 0,
	/* 'E' */  	8, 0,	0, 0x7f, 0x40, 0x40, 0x7e, 0x40, 0x40, 0x40, 0x7f, 0, 0,
	/* 'F' */  	8, 0,	0, 0x7f, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 0, 0,
	/* 'G' */  	8, 0,	0, 0x3e, 0x41, 0x40, 0x40, 0x4f, 0x41, 0x41, 0x3e, 0, 0,
	/* 'H' */  	8, 0,	0, 0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x41, 0, 0,
	/* 'I' */  	8, 0,	0, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0, 0,
	/* 'J' */  	8, 0,	0, 0x3f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* 'K' */  	8, 0,	0, 0x41, 0x46, 0x58, 0x60, 0x60, 0x58, 0x46, 0x41, 0, 0,
	/* 'L' */  	8, 0,	0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f, 0, 0,
	/* 'M' */  	8, 0,	0, 0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x41, 0, 0,
	/* 'N' */  	8, 0,	0, 0x41, 0x61, 0x51, 0x49, 0x49, 0x45, 0x43, 0x41, 0, 0,
	/* 'O' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* 'P' */  	8, 0,	0, 0x7e, 0x41, 0x41, 0x41, 0x7e, 0x40, 0x40, 0x40, 0, 0,
	/* 'Q' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x41, 0x41, 0x4d, 0x42, 0x3d, 0, 0,
	/* 'R' */  	8, 0,	0, 0x7e, 0x41, 0x41, 0x41, 0x7e, 0x44, 0x42, 0x41, 0, 0,
	/* 'S' */  	8, 0,	0, 0x3e, 0x41, 0x40, 0x3e, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* 'T' */  	8, 0,	0, 0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* 'U' */  	8, 0,	0, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* 'V' */  	8, 0,	0, 0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0, 0,
	/* 'W' */  	8, 0,	0, 0x41, 0x41, 0x41, 0x49, 0x49,0x49, 0x55, 0x22, 0, 0,
	/* 'X' */  	8, 0,	0, 0x41, 0x22, 0x14, 0x08, 0x08, 0x14, 0x22, 0x41, 0, 0,
	/* 'Y' */  	8, 0,	0, 0x41, 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* 'Z' */  	8, 0,	0, 0x7f, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7f, 0, 0,
	/* '[' */  	8, 0,	0x3c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0,
	/* '\' */  	8, 0,	0, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0, 0,
	/* ']' */  	8, 0,	0x1e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x1e, 0,
	/* '^' */  	8, 0,	0x08, 0x14, 0x22, 0x41, 0, 0, 0, 0, 0, 0, 0,
	/* '_' */  	8, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7f, 0,
	/* '`' */  	8, 0,	0x30, 0x10, 0x08, 0, 0, 0, 0, 0, 0, 0, 0,
	/* 'a' */  	8, 0,	0, 0, 0x3c, 0x02, 0x02, 0x3e, 0x42, 0x42, 0x3e, 0, 0,
	/* 'b' */  	8, 0,	0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0, 0,
	/* 'c' */  	8, 0,	0, 0, 0x3c, 0x42, 0x40, 0x40, 0x40, 0x42, 0x3c, 0, 0,
	/* 'd' */  	8, 0,	0x02, 0x02, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0, 0,
	/* 'e' */  	8, 0,	0, 0, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x3e, 0, 0,
	/* 'f' */  	8, 0,	0x1e, 0x20, 0x20, 0xfc, 0x20, 0x20, 0x20, 0x20, 0x20, 0, 0,
	/* 'g' */  	8, 0,	0, 0, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02, 0x3c,
	/* 'h' */  	8, 0,	0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0, 0,
	/* 'i' */  	8, 0,	0x08, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0, 0,
	/* 'j' */  	8, 0,	0x08, 0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x70,
	/* 'k' */  	8, 0,	0x40, 0x40, 0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0, 0,
	/* 'l' */  	8, 0,	0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0e, 0, 0,
	/* 'm' */  	8, 0,	0, 0, 0x7e, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0, 0,
	/* 'n' */  	8, 0,	0, 0, 0x5e, 0x61, 0x41, 0x41, 0x41, 0x41, 0x41, 0, 0,
	/* 'o' */  	8, 0,	0, 0, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0, 0,
	/* 'p' */  	8, 0,	0, 0, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40,
	/* 'q' */       8, 0,	0, 0, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02,
	/* 'r' */       8, 0,	0, 0, 0x5e, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0, 0,
	/* 's' */	8, 0,	0, 0, 0x3e, 0x40, 0x40, 0x3e, 0x01, 0x01, 0x3e, 0, 0,
	/* 't' */       8, 0,	0, 0x10, 0x7c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0e, 0, 0,
	/* 'u' */	8, 0,	0, 0, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0, 0,
	/* 'v' */	8, 0,	0, 0, 0x42, 0x42, 0x42, 0x24, 0x24, 0x24, 0x18, 0, 0,
	/* 'w' */	8, 0,	0, 0, 0x82, 0x82, 0x92, 0x92, 0x92, 0x92, 0x7c, 0, 0,
	/* 'x' */	8, 0,	0, 0, 0x42, 0x42, 0x24, 0x18, 0x24, 0x42, 0x42, 0, 0,
	/* 'y' */	8, 0,	0, 0, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02, 0x3c,
	/* 'z' */	8, 0,	0, 0, 0x7e, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7e, 0, 0,
	/* '{' */	8, 0,	0x0c, 0x10, 0x10, 0x10, 0x60, 0x10, 0x10, 0x10, 0x0c, 0, 0,
	/* '|' */	8, 0,	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* '}' */	8, 0,	0x30, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x08, 0x30, 0, 0,
	/* '~' */	8, 0,	0x32, 0x4c, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

struct GP_Font GP_default_console_font = {
	.charset = GP_CHARSET_7BIT,
	.data = GP_default_console_font_data,
	.char_width = 8,
	.hspace = 1,
	.height = 11,
	.bytes_per_line = 1,
};

static uint8_t GP_default_proportional_font_data[] = {
	/* ' ' */ 	6, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	/* '!' */	4, 0,	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0, 0, 0x20, 0,
	/* '"' */	8, 0,	0x24, 0x24, 0x48, 0, 0, 0, 0, 0, 0, 0, 0,
	/* '#' */	8, 0,	0x24, 0x24, 0xff, 0x24, 0x24, 0x24, 0x24, 0xff, 0x24, 0x24, 0,
	/* '$' */ 	8, 0,	0x08, 0x3e, 0x49, 0x48, 0x38, 0x0e, 0x09, 0x49, 0x3e, 0x08, 0,
	/* '%' */  	8, 0,	0x60, 0x91, 0x92, 0x64, 0x08, 0x10, 0x26, 0x49, 0x89, 0x06, 0,
	/* '&' */  	8, 0,	0x18, 0x24, 0x24, 0x24, 0x18, 0x2b, 0x44, 0x44, 0x44, 0x3b, 0,
	/* ''' */  	4, 2,	0x0c, 0x08, 0x10, 0, 0, 0, 0, 0, 0, 0, 0,
	/* '(' */  	4, 0,	0x20, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x20, 0,
	/* ')' */  	4, 0,	0x80, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0,
	/* '*' */  	6, 2,	0, 0x08, 0x2a, 0x1c, 0x2a, 0x08, 0, 0, 0, 0, 0,
	/* '+' */  	8, 0,	0, 0, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0, 0,
	/* ',' */  	4, 0,	0, 0, 0, 0, 0, 0, 0, 0x20, 0x20, 0x40, 0,
	/* '-' */  	4, 0,	0, 0, 0, 0, 0, 0xf0, 0, 0, 0, 0, 0,
	/* '.' */  	4, 0,	0, 0, 0, 0, 0, 0, 0, 0x60, 0x60, 0, 0,
	/* '/' */  	4, 0,	0, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0, 0,
	/* '0' */  	8, 0,	0, 0x3e, 0x43, 0x45, 0x49, 0x49, 0x51, 0x61, 0x3e, 0, 0,
	/* '1' */  	8, 0,	0, 0x08, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x7f, 0, 0,
	/* '2' */  	8, 0,	0, 0x3e, 0x41, 0x02, 0x04, 0x08, 0x10, 0x20, 0x7f, 0, 0,
	/* '3' */  	8, 0,	0, 0x3e, 0x41, 0x01, 0x0e, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* '4' */  	8, 0,	0, 0x0c, 0x14, 0x24, 0x44, 0x84, 0xff, 0x04, 0x04, 0, 0,
	/* '5' */  	8, 0,	0, 0x7f, 0x40, 0x40, 0x7e, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* '6' */  	8, 0,	0, 0x3f, 0x40, 0x40, 0x7e, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* '7' */ 	8, 0,	0, 0x7f, 0x41, 0x02, 0x04, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* '8' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* '9' */  	8, 0,	0, 0x3e, 0x41, 0x41, 0x41, 0x3f, 0x01, 0x41, 0x3e, 0, 0,
	/* ':' */  	4, 0,	0, 0, 0, 0x60, 0x60, 0, 0, 0x60, 0x60, 0, 0,
	/* ';' */  	4, 0,	0, 0, 0, 0x60, 0x60, 0, 0, 0x60, 0x20, 0x40, 0,
	/* '<' */  	4, 1,	0, 0, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0, 0,
	/* '=' */  	7, 1,	0, 0, 0, 0x7f, 0, 0, 0x7f, 0, 0, 0, 0,
	/* '>' */  	4, 3,	0, 0, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0, 0,
	/* '?' */  	6, 1,	0x3c, 0x42, 0x02, 0x02, 0x04, 0x08, 0x08, 0, 0, 0x08, 0,
	/* '@' */  	8, 0,	0, 0x3e, 0x41, 0x9d, 0xa5, 0xa5, 0xa5, 0x9e, 0x41, 0x3e, 0,
	/* 'A' */  	7, 1,	0, 0x3e, 0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0, 0,
	/* 'B' */  	7, 1,	0, 0x7e, 0x41, 0x41, 0x7e, 0x41, 0x41, 0x41, 0x7e, 0, 0,
	/* 'C' */  	7, 1,	0, 0x3e, 0x41, 0x40, 0x40, 0x40, 0x40, 0x41, 0x3e, 0, 0,
	/* 'D' */  	7, 1,	0, 0x7c, 0x42, 0x41, 0x41, 0x41, 0x41, 0x42, 0x7c, 0, 0,
	/* 'E' */  	7, 1,	0, 0x7f, 0x40, 0x40, 0x7e, 0x40, 0x40, 0x40, 0x7f, 0, 0,
	/* 'F' */  	7, 1,	0, 0x7f, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 0, 0,
	/* 'G' */  	7, 1,	0, 0x3e, 0x41, 0x40, 0x40, 0x4f, 0x41, 0x41, 0x3e, 0, 0,
	/* 'H' */  	7, 1,	0, 0x41, 0x41, 0x41, 0x7f, 0x41, 0x41, 0x41, 0x41, 0, 0,
	/* 'I' */  	7, 1,	0, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0, 0,
	/* 'J' */  	7, 1,	0, 0x3f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* 'K' */  	7, 1,	0, 0x41, 0x46, 0x58, 0x60, 0x60, 0x58, 0x46, 0x41, 0, 0,
	/* 'L' */  	7, 1,	0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7f, 0, 0,
	/* 'M' */  	7, 1,	0, 0x41, 0x63, 0x55, 0x49, 0x41, 0x41, 0x41, 0x41, 0, 0,
	/* 'N' */  	7, 1,	0, 0x41, 0x61, 0x51, 0x49, 0x49, 0x45, 0x43, 0x41, 0, 0,
	/* 'O' */  	7, 1,	0, 0x3e, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* 'P' */  	7, 1,	0, 0x7e, 0x41, 0x41, 0x41, 0x7e, 0x40, 0x40, 0x40, 0, 0,
	/* 'Q' */  	7, 1,	0, 0x3e, 0x41, 0x41, 0x41, 0x41, 0x4d, 0x42, 0x3d, 0, 0,
	/* 'R' */  	7, 1,	0, 0x7e, 0x41, 0x41, 0x41, 0x7e, 0x44, 0x42, 0x41, 0, 0,
	/* 'S' */  	7, 1,	0, 0x3e, 0x41, 0x40, 0x3e, 0x01, 0x01, 0x41, 0x3e, 0, 0,
	/* 'T' */  	7, 1,	0, 0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* 'U' */  	7, 1,	0, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x3e, 0, 0,
	/* 'V' */  	7, 1,	0, 0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0, 0,
	/* 'W' */  	7, 1,	0, 0x41, 0x41, 0x41, 0x49, 0x49,0x49, 0x55, 0x22, 0, 0,
	/* 'X' */  	7, 1,	0, 0x41, 0x22, 0x14, 0x08, 0x08, 0x14, 0x22, 0x41, 0, 0,
	/* 'Y' */  	7, 1,	0, 0x41, 0x41, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* 'Z' */  	7, 1,	0, 0x7f, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7f, 0, 0,
	/* '[' */  	4, 2,	0x3c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0,
	/* '\' */  	4, 0,	0, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0, 0,
	/* ']' */  	4, 3,	0x1e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x1e, 0,
	/* '^' */  	8, 0,	0x08, 0x14, 0x22, 0x41, 0, 0, 0, 0, 0, 0, 0,
	/* '_' */  	8, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, 0x7f, 0,
	/* '`' */  	4, 2,	0x30, 0x10, 0x08, 0, 0, 0, 0, 0, 0, 0, 0,
	/* 'a' */  	6, 1,	0, 0, 0x3c, 0x02, 0x02, 0x3e, 0x42, 0x42, 0x3e, 0, 0,
	/* 'b' */  	6, 1,	0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0, 0,
	/* 'c' */  	6, 0,	0, 0, 0x78, 0x84, 0x80, 0x80, 0x80, 0x84, 0x78, 0, 0,
	/* 'd' */  	6, 1,	0x02, 0x02, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0, 0,
	/* 'e' */  	6, 1,	0, 0, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x3e, 0, 0,
	/* 'f' */  	7, 0,	0x1e, 0x20, 0x20, 0xfc, 0x20, 0x20, 0x20, 0x20, 0x20, 0, 0,
	/* 'g' */  	6, 1,	0, 0, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02, 0x3c,
	/* 'h' */  	6, 1,	0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0, 0,
	/* 'i' */  	4, 0,	0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0, 0,
	/* 'j' */  	4, 0,	0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xc0,
	/* 'k' */  	8, 0,	0x40, 0x40, 0x42, 0x44, 0x48, 0x70, 0x48, 0x44, 0x42, 0, 0,
	/* 'l' */  	4, 0,	0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x30, 0, 0,
	/* 'm' */  	7, 1,	0, 0, 0x7e, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0, 0,
	/* 'n' */  	8, 0,	0, 0, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0, 0,
	/* 'o' */  	6, 1,	0, 0, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0, 0,
	/* 'p' */  	6, 1,	0, 0, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40,
	/* 'q' */       8, 0,	0, 0, 0x3e, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02,
	/* 'r' */       5, 0,	0, 0, 0xb8, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0, 0,
	/* 's' */	7, 1,	0, 0, 0x3e, 0x40, 0x40, 0x3e, 0x01, 0x01, 0x3e, 0, 0,
	/* 't' */       6, 0,	0, 0x20, 0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x1c, 0, 0,
	/* 'u' */	7, 1,	0, 0, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0, 0,
	/* 'v' */	7, 1,	0, 0, 0x42, 0x42, 0x42, 0x24, 0x24, 0x24, 0x18, 0, 0,
	/* 'w' */	8, 0,	0, 0, 0x82, 0x82, 0x92, 0x92, 0x92, 0x92, 0x7c, 0, 0,
	/* 'x' */	6, 1,	0, 0, 0x42, 0x42, 0x24, 0x18, 0x24, 0x42, 0x42, 0, 0,
	/* 'y' */	6, 1,	0, 0, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02, 0x3c,
	/* 'z' */	6, 1,	0, 0, 0x7e, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7e, 0, 0,
	/* '{' */	6, 1,	0x0c, 0x10, 0x10, 0x10, 0x60, 0x10, 0x10, 0x10, 0x0c, 0, 0,
	/* '|' */	3, 3,	0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0, 0,
	/* '}' */	6, 1,	0x30, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x08, 0x30, 0, 0,
	/* '~' */	8, 0,	0x32, 0x4c, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

struct GP_Font GP_default_proportional_font = {
	.charset = GP_CHARSET_7BIT,
	.data = GP_default_proportional_font_data,
	.char_width = 8,
	.hspace = 2,
	.height = 11,
	.bytes_per_line = 1,
};

