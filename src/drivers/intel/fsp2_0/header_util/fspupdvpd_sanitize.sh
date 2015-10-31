#
# Convert the FspUpdVpd.h header file into a format usable by coreboot
# Usage:
#     fspupdvpd_sanitize.sh <path/to/FspUpdVpd.h>
#
# This file is part of the coreboot project.
#
# Copyright (C) 2015 Intel Corp.
# (Written by Alexandru Gagniuc <alexandrux.gagniuc@intel.com> for Intel Corp.)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

HOME=$(dirname "${BASH_SOURCE[0]}")
DEST=$HOME

SPATCH=spatch

$SPATCH -sp_file $HOME/fspupdvpd.spatch \
	-in_place $1
