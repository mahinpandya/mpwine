/*
 * Object Picker Dialog Includes
 *
 * Copyright 2005 Thomas Weidenmueller <w3seek@reactos.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define COBJMACROS

#include "objidl.h"
#include "objsel.h"

/**********************************************************************
 * ClassFactory declaration for objsel.dll
 */
typedef struct
{
    IClassFactory IClassFactory_iface;
    LONG ref;
} ClassFactoryImpl;

typedef struct
{
    IDsObjectPicker IDsObjectPicker_iface;
    LONG ref;
} IDsObjectPickerImpl;

HRESULT WINAPI OBJSEL_IDsObjectPicker_Create(LPVOID *ppvObj) DECLSPEC_HIDDEN;

extern ClassFactoryImpl OBJSEL_ClassFactory DECLSPEC_HIDDEN;
