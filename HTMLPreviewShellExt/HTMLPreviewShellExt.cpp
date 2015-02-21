// HTMLPreviewShellExt.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "HTMLPreviewShellExt.h"


class CHTMLPreviewShellExtModule : public CAtlDllModuleT< CHTMLPreviewShellExtModule >
{
public :
	DECLARE_LIBID(LIBID_HTMLPreviewShellExtLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HTMLPREVIEWSHELLEXT, "{F0FC0235-CE28-42F3-B956-4CC82B981116}")
};

CHTMLPreviewShellExtModule _AtlModule;

HINSTANCE g_hInstance;

static HMODULE GetHMod()
{
	return g_hInstance;
}





#ifdef _MANAGED
#pragma managed(push, off)
#endif




// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	g_hInstance = hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if(!CheckTimeBomb())
		return E_FAIL;

    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}

