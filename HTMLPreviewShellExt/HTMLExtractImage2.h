// HTMLExtractImage2.h : Declaration of the CHTMLExtractImage2

#pragma once
#include "resource.h"       // main symbols

#include "HTMLPreviewShellExt.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CHTMLExtractImage2

class ATL_NO_VTABLE CHTMLExtractImage2 :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHTMLExtractImage2, &CLSID_HTMLExtractImage2>,
	public IHTMLExtractImage2,
	public IPersistFile,
	public IExtractImage2
{
public:
	CString fileName;
	DWORD colorDepth;
	DWORD flags;
	SIZE size;
	CBitmap bmp;
	BOOL done;
	HANDLE threadHandle;
	static DWORD WINAPI ThreadProc(LPVOID lpData);

	void DoExtract();
public:
	CHTMLExtractImage2()
	{
		threadHandle = NULL;
		done = FALSE;
		colorDepth = 24;
		size.cx = 0;
		size.cy = 0;
		flags = 0;
		state = IRTIR_TASK_NOT_RUNNING;
	}

	ULONG state;


DECLARE_REGISTRY_RESOURCEID(IDR_HTMLEXTRACTIMAGE2)


BEGIN_COM_MAP(CHTMLExtractImage2)
	COM_INTERFACE_ENTRY(IHTMLExtractImage2)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IExtractImage)
	COM_INTERFACE_ENTRY(IExtractImage2)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(GetClassID)( CLSID* )       { return E_NOTIMPL; }
    STDMETHOD(IsDirty)()                  { return E_NOTIMPL; }
    STDMETHOD(Save)( LPCOLESTR, BOOL )    { return E_NOTIMPL; }
    STDMETHOD(SaveCompleted)( LPCOLESTR ) { return E_NOTIMPL; }
    STDMETHOD(GetCurFile)( LPOLESTR* )    { return E_NOTIMPL; }
    STDMETHOD(Load)( LPCOLESTR wszFile, DWORD /*dwMode*/ );

	STDMETHOD(Extract)    (HBITMAP *phBmpImage);
	STDMETHOD(GetLocation)(LPWSTR pszPathBuffer,DWORD cchMax,DWORD *pdwPriority, const SIZE *prgSize,DWORD dwRecClrDepth,DWORD *pdwFlags);

	STDMETHOD(GetDateStamp)(FILETIME *pDateStamp);


    
};

OBJECT_ENTRY_AUTO(__uuidof(HTMLExtractImage2), CHTMLExtractImage2)
