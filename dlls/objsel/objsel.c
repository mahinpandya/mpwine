/*
 * Object Picker Dialog
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

#include "objsel_private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(objsel);

/***********************************************************************
 *		DllGetClassObject (OBJSEL.@)
 */
HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID iid, LPVOID *ppv)
{
    TRACE("(%s, %s, %p)\n", debugstr_guid(rclsid), debugstr_guid(iid), ppv);

    *ppv = NULL;

    if (IsEqualGUID(rclsid, &CLSID_DsObjectPicker))
        return IClassFactory_QueryInterface(&OBJSEL_ClassFactory.IClassFactory_iface, iid, ppv);

    FIXME("CLSID: %s, IID: %s\n", debugstr_guid(rclsid), debugstr_guid(iid));
    return CLASS_E_CLASSNOTAVAILABLE;
}


/**********************************************************************
 * OBJSEL_IDsObjectPicker_Destroy (also IUnknown)
 */
static VOID OBJSEL_IDsObjectPicker_Destroy(IDsObjectPickerImpl *This)
{
    HeapFree(GetProcessHeap(),
             0,
             This);
}


static inline IDsObjectPickerImpl *impl_from_IDsObjectPicker(IDsObjectPicker *iface)
{
    return CONTAINING_RECORD(iface, IDsObjectPickerImpl, IDsObjectPicker_iface);
}

/**********************************************************************
 * OBJSEL_IDsObjectPicker_AddRef (also IUnknown)
 */
static ULONG WINAPI OBJSEL_IDsObjectPicker_AddRef(IDsObjectPicker * iface)
{
    IDsObjectPickerImpl *This = impl_from_IDsObjectPicker(iface);

    TRACE("\n");

    if (This == NULL) return E_POINTER;

    return InterlockedIncrement(&This->ref);
}


/**********************************************************************
 * OBJSEL_IDsObjectPicker_Release (also IUnknown)
 */
static ULONG WINAPI OBJSEL_IDsObjectPicker_Release(IDsObjectPicker * iface)
{
    IDsObjectPickerImpl *This = impl_from_IDsObjectPicker(iface);
    ULONG ref;

    TRACE("\n");

    if (This == NULL) return E_POINTER;

    ref = InterlockedDecrement(&This->ref);

    if (ref == 0)
        OBJSEL_IDsObjectPicker_Destroy(This);

    return ref;
}


/**********************************************************************
 * OBJSEL_IDsObjectPicker_QueryInterface (also IUnknown)
 */
static HRESULT WINAPI OBJSEL_IDsObjectPicker_QueryInterface(
    IDsObjectPicker * iface,
    REFIID riid,
    LPVOID *ppvObj)
{
    TRACE("\n\tIID:\t%s\n",debugstr_guid(riid));

    if (ppvObj == NULL) return E_POINTER;

    if (IsEqualGUID(riid, &IID_IUnknown) ||
	IsEqualGUID(riid, &IID_IDsObjectPicker))
    {
        *ppvObj = iface;
	OBJSEL_IDsObjectPicker_AddRef(iface);
	return S_OK;
    }

    FIXME("- no interface IID: %s\n", debugstr_guid(riid));
    return E_NOINTERFACE;
}


/**********************************************************************
 * OBJSEL_IDsObjectPicker_Initialize
 */
static HRESULT WINAPI OBJSEL_IDsObjectPicker_Initialize(
    IDsObjectPicker * iface,
    PDSOP_INIT_INFO pInitInfo)
{
    FIXME("stub!\n");
    return S_OK;
}


/**********************************************************************
 * OBJSEL_IDsObjectPicker_InvokeDialog
 */
static HRESULT WINAPI OBJSEL_IDsObjectPicker_InvokeDialog(
    IDsObjectPicker * iface,
    HWND hwndParent,
    IDataObject** ppdoSelections)
{
    FIXME("stub!\n");
    return S_FALSE;
}


/**********************************************************************
 * IDsObjectPicker_Vtbl
 */
static IDsObjectPickerVtbl IDsObjectPicker_Vtbl =
{
    OBJSEL_IDsObjectPicker_QueryInterface,
    OBJSEL_IDsObjectPicker_AddRef,
    OBJSEL_IDsObjectPicker_Release,
    OBJSEL_IDsObjectPicker_Initialize,
    OBJSEL_IDsObjectPicker_InvokeDialog
};


/**********************************************************************
 * OBJSEL_IDsObjectPicker_Create
 */
HRESULT WINAPI OBJSEL_IDsObjectPicker_Create(LPVOID *ppvObj)
{
    IDsObjectPickerImpl *Instance = HeapAlloc(GetProcessHeap(),
                                              HEAP_ZERO_MEMORY,
                                              sizeof(IDsObjectPickerImpl));
    if (Instance != NULL)
    {
        Instance->IDsObjectPicker_iface.lpVtbl = &IDsObjectPicker_Vtbl;
        OBJSEL_IDsObjectPicker_AddRef(&Instance->IDsObjectPicker_iface);

        *ppvObj = Instance;
        return S_OK;
    }
    else
        return E_OUTOFMEMORY;
}
