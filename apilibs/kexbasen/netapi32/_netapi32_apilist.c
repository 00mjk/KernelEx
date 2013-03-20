/*
 *  KernelEx
 *  Copyright (C) 2008, Ley0k
 *
 *  This file is part of KernelEx source code.
 *
 *  KernelEx is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation; version 2 of the License.
 *
 *  KernelEx is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include "common.h"
#include "kexcoresdk.h"
#include "_netapi32_apilist.h"

BOOL init_netapi32()
{
	return TRUE;
}

static const apilib_named_api netapi32_named_apis[] = 
{
/*** AUTOGENERATED APILIST NAMED EXPORTS BEGIN ***/
	DECL_API("NetAlertRaise", NetAlertRaise_new),
	DECL_API("NetAlertRaiseEx", NetAlertRaiseEx_new),
	DECL_API("NetApiBufferAllocate", NetApiBufferAllocate_new),
	DECL_API("NetApiBufferFree", NetApiBufferFree_new),
	DECL_API("NetApiBufferReallocate", NetApiBufferReallocate_new),
	DECL_API("NetApiBufferSize", NetApiBufferSize_new),
	DECL_API("NetShareEnum", NetShareEnum_new),
	DECL_API("NetUserGetInfo", NetUserGetInfo_new),
/*** AUTOGENERATED APILIST NAMED EXPORTS END ***/
};

#if 0
static const apilib_unnamed_api netapi32_ordinal_apis[] =
{
/*** AUTOGENERATED APILIST ORDINAL EXPORTS BEGIN ***/
/*** AUTOGENERATED APILIST ORDINAL EXPORTS END ***/
};
#endif

const apilib_api_table apitable_netapi32 = DECL_TAB("NETAPI32.DLL", netapi32_named_apis, 0 /*netapi32_ordinal_apis*/);