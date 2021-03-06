/*
 *  KernelEx
 *  Copyright (C) 2013, Ley0k
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

#pragma once

#include <stdio.h>
#include "common.h"
#include "thuni_layer.h"
#include "thuni_macro.h"
#include "thuni_thunk.h"
#include "listhead.h"
#include "kstructs.h"
#include "..\gdi32\GdiObjects.h"
#include "_user32_apilist.h"

#define K32OBJ_DESKTOP    0x16
#define K32OBJ_WINSTATION 0x17

#define WINSTA_ROOT_NAME "\\Windows\\WindowStations"
#define WINSTA_ROOT_NAME_LENGTH	23

#define WSS_LOCKED	(1)
#define WSS_NOINTERACTIVE	(2)

#define UOI_HEAPSIZE	5

/* DON'T DELETE USELESS FIELD BECAUSE THEY COULD BE USED LATER */

/* The desktop structure */
typedef struct _DESKTOP
{
	WORD Type;									// 00 K32OBJ_DESKTOP
	WORD cReferences;							// 02

    DWORD pDeskInfo;							// 04
	DWORD unused;								// 08
	PCHAR lpName;								// 0C
    LIST_ENTRY ListEntry;

	DWORD SessionId;

    struct _WINSTATION_OBJECT *rpwinstaParent; 
    DWORD dwDTFlags;
    PWND spwndForeground;
    PWND spwndTray;
    PWND spwndMessage;
    PWND spwndTooltip;
    DWORD hsectionDesktop;
    DWORD pheapDesktop;
    ULONG_PTR ulHeapSize;
    LIST_ENTRY PtiList;

    PWND spwndTrack;
    DWORD htEx;
    RECT rcMouseHover;
    DWORD dwMouseHoverTime;

    PVOID ActiveMessageQueue;

    HWND DesktopWindow;

    PVOID BlockInputThread;

	PDEVMODE pdev;
} DESKTOP, *PDESKTOP;

#define DESKTOP_READ       STANDARD_RIGHTS_READ      | \
                           DESKTOP_ENUMERATE         | \
                           DESKTOP_READOBJECTS

#define DESKTOP_WRITE       STANDARD_RIGHTS_WRITE    | \
                            DESKTOP_CREATEMENU       | \
                            DESKTOP_CREATEWINDOW     | \
                            DESKTOP_HOOKCONTROL      | \
                            DESKTOP_JOURNALPLAYBACK  | \
                            DESKTOP_JOURNALRECORD    | \
                            DESKTOP_WRITEOBJECTS

#define DESKTOP_EXECUTE     STANDARD_RIGHTS_EXECUTE  | \
                            DESKTOP_SWITCHDESKTOP

#define DESKTOP_ALL_ACCESS  STANDARD_RIGHTS_REQUIRED | \
                            DESKTOP_CREATEMENU       | \
                            DESKTOP_CREATEWINDOW     | \
                            DESKTOP_ENUMERATE        | \
                            DESKTOP_HOOKCONTROL      | \
                            DESKTOP_JOURNALPLAYBACK  | \
                            DESKTOP_JOURNALRECORD    | \
                            DESKTOP_READOBJECTS      | \
                            DESKTOP_SWITCHDESKTOP    | \
                            DESKTOP_WRITEOBJECTS

#define WINSTA_READ       STANDARD_RIGHTS_READ     | \
                          WINSTA_ENUMDESKTOPS      | \
                          WINSTA_ENUMERATE         | \
                          WINSTA_READATTRIBUTES    | \
                          WINSTA_READSCREEN

#define WINSTA_WRITE      STANDARD_RIGHTS_WRITE    | \
                          WINSTA_ACCESSCLIPBOARD   | \
                          WINSTA_CREATEDESKTOP     | \
                          WINSTA_WRITEATTRIBUTES

#define WINSTA_EXECUTE    STANDARD_RIGHTS_EXECUTE  | \
                          WINSTA_ACCESSGLOBALATOMS | \
                          WINSTA_EXITWINDOWS

#undef WINSTA_ALL_ACCESS
#define WINSTA_ALL_ACCESS STANDARD_RIGHTS_REQUIRED | \
                          WINSTA_ACCESSCLIPBOARD   | \
                          WINSTA_ACCESSGLOBALATOMS | \
                          WINSTA_CREATEDESKTOP     | \
                          WINSTA_ENUMDESKTOPS      | \
                          WINSTA_ENUMERATE         | \
                          WINSTA_EXITWINDOWS       | \
                          WINSTA_READATTRIBUTES    | \
                          WINSTA_READSCREEN        | \
                          WINSTA_WRITEATTRIBUTES

/* The Window station structure */
typedef struct _WINSTATION_OBJECT
{
	WORD Type;			// 00 K32OBJ_WINSTATION
	WORD cReferences;	// 02

	DWORD Lock;			// 04
	DWORD unused1;		// 08
	PCHAR lpName;		// 0C
    LIST_ENTRY DesktopListHead;
	LIST_ENTRY ListEntry;
    DWORD AtomTable;
    HANDLE SystemMenuTemplate;
    HANDLE ShellWindow;
    HANDLE ShellListView;

    ULONG Flags;
    struct _DESKTOP* ActiveDesktop;

    DWORD          ptiClipLock;
    DWORD          ptiDrawingClipboard;
    PWND           spwndClipOpen;
    PWND           spwndClipViewer;
    PWND           spwndClipOwner;
    DWORD          pClipBase;
    DWORD          cNumClipFormats;
    INT            iClipSerialNumber;
    INT            iClipSequenceNumber;
    INT            fClipboardChanged : 1;
    INT            fInDelayedRendering : 1;

} WINSTATION_OBJECT, *PWINSTATION_OBJECT;

typedef struct _PERPROCESSDATA
{
	DWORD SessionId;
	LPSTR lpSessionName;

	LIST_ENTRY WindowStationList;
	LIST_ENTRY ListEntry;

	PWINSTATION_OBJECT InputWindowStation;
	PDESKTOP gpdeskInputDesktop;
	PDESKTOP gpdeskScreenSaver;
	PDESKTOP gpdeskWinlogon;

	BOOL fNewDesktop;

} PERPROCESSDATA, *PPERPROCESSDATA;

typedef struct tagPDEVICE {
    short pdType;
} PDEVICE, *PPDEVICE, *LPPDEVICE;

extern LPCRITICAL_SECTION gpdeskLock;

extern LIST_ENTRY WindowStationList;

extern PWINSTATION_OBJECT InputWindowStation;
extern PDESKTOP gpdeskInputDesktop;
extern PDESKTOP gpdeskScreenSaver;
extern PDESKTOP gpdeskWinlogon;

extern BOOL fNewDesktop;

extern HANDLE gpdeskSwitchEvent;

extern PPDB98 ppdbKernelProcess;
extern PTDB98 gptdbDesktopThread;
extern DWORD gpidDesktopThread;
extern DWORD gpidKernelProcess;

extern DWORD gpidSession;

extern PWND pwndDesktop;

BOOL WINAPI CreateWindowStationAndDesktops();

DWORD WINAPI DesktopThread(PVOID lParam);

BOOL InitProcessWindowStation(VOID);
BOOL InitDesktops();

BOOL IntValidateDesktopHandle(HDESK hDesktop, PDESKTOP *DesktopObject);
BOOL IntValidateWindowStationHandle(HWINSTA hWindowStation, PWINSTATION_OBJECT *WindowStationObject);

VOID RepaintScreen(VOID);
VOID DisableOEMLayer();
VOID EnableOEMLayer();
VOID APIENTRY RedrawDesktop();

BOOL FASTCALL WTSInitializeSession(void);
BOOL WINAPI WTSCreateSession(PPERPROCESSDATA *Session);
BOOL WINAPI WTSGetSessionById(DWORD SessionId, PPERPROCESSDATA *Session);
BOOL WINAPI WTSDeleteSession(PPERPROCESSDATA Session);
