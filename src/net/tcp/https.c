/*
 * Copyright (C) 2007 Michael Brown <mbrown@fensystems.co.uk>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/**
 * @file
 *
 * Secure Hyper Text Transfer Protocol (HTTPS)
 *
 */

#include <stddef.h>
#include <gpxe/open.h>
#include <gpxe/tls.h>
#include <gpxe/http.h>

/**
 * Initiate an HTTPS connection
 *
 * @v xfer		Data transfer interface
 * @v uri		Uniform Resource Identifier
 * @ret rc		Return status code
 */
static int https_open ( struct xfer_interface *xfer, struct uri *uri ) {
	return http_open_filter ( xfer, uri, HTTPS_PORT, add_tls );
}

/** HTTPS URI opener */
struct uri_opener https_uri_opener __uri_opener = {
	.scheme	= "https",
	.open	= https_open,
};
