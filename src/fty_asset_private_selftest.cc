/*  =========================================================================
    fty_asset_private_selftest.c - run private classes selftests

    Runs all private classes selftests.

    -------------------------------------------------------------------------
    Copyright (C) 2014 - 2018 Eaton

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

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
    =========================================================================
*/

#include "fty_asset_classes.h"


//  -------------------------------------------------------------------------
//  Run all private classes tests.
//

void
fty_asset_private_selftest (bool verbose, const char *subtest)
{
// Tests for stable private classes:
    if (streq (subtest, "$ALL") || streq (subtest, "topology_processor_test"))
        topology_processor_test (verbose);
    if (streq (subtest, "$ALL") || streq (subtest, "dbhelpers_test"))
        dbhelpers_test (verbose);
    if (streq (subtest, "$ALL") || streq (subtest, "total_power_test"))
        total_power_test (verbose);
    if (streq (subtest, "$ALL") || streq (subtest, "dns_test"))
        dns_test (verbose);
}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
