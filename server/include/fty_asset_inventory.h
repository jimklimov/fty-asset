/*  =========================================================================
    fty_asset_inventory - Inventory server: process inventory ASSET messages and update extended attributes

    Copyright (C) 2014 - 2020 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef FTY_ASSET_INVENTORY_H_INCLUDED
#define FTY_ASSET_INVENTORY_H_INCLUDED

#include <czmq.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _fty_asset_inventory_t fty_asset_inventory_t;

//  @interface
//  Destroy the fty_asset_inventory
 void
    fty_asset_inventory_server (zsock_t *pipe, void *args);

//  Self test of this class
 void
    fty_asset_inventory_test (bool verbose);

//  @end

#ifdef __cplusplus
}
#endif

#endif
