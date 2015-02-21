// HTMLExtractImage2.cpp : Implementation of CHTMLExtractImage2

#include "stdafx.h"
#include "HTMLExtractImage2.h"

#include "MainDlg.h"

extern HINSTANCE g_hInstance;



DWORD CHTMLExtractImage2::ThreadProc(LPVOID lpData)
{
	OleInitialize(NULL);

	CHTMLExtractImage2* ptr = (CHTMLExtractImage2*)lpData;
	ptr->DoExtract();

	HANDLE h = ptr->threadHandle;
	ptr->threadHandle = NULL;

	OleUninitialize();

	CloseHandle(h);
	ExitThread(0);

	return 0;
}

void CHTMLExtractImage2::DoExtract()
{
	CMainDlg dlg;
	//dlg.Create(NULL);
	//dlg.ShowWindow(SW_SHOW);
	dlg.visitSite(fileName);
	//dlg.DestroyWindow();
	bmp = dlg.bmp.Detach();

	done = TRUE;
}

STDMETHODIMP CHTMLExtractImage2::Load( LPCOLESTR wszFile, DWORD /*dwMode*/ )
{ 
	// the shell gives the filename for which the image must be extracted
	// thru this function, so it needs to be saved in the object.
	fileName = wszFile;
	

	//DWORD tid = 0;
	//threadHandle = CreateThread(NULL, 0, ThreadProc, (LPVOID)this, 0, &tid);

    return S_OK;
}

STDMETHODIMP CHTMLExtractImage2::Extract(HBITMAP *phBmpImage)
{  
	HRESULT hRes = S_OK;

	bool isExternal = false;
	const WCHAR* ext = PathFindExtension(fileName);
	if(ext != NULL && _wcsicmp(ext, L".url") == 0)
	{
		WCHAR url[2000] = {0};
		GetPrivateProfileString(L"InternetShortcut", L"URL", L"", url, sizeof(url) / sizeof(url[0]), fileName);
		//MessageBox(0, url, 0, 0);
		isExternal = true;

		fileName = url;
	}

	done = FALSE;

	DWORD tid = 0;
	threadHandle = CreateThread(NULL, 0, ThreadProc, (LPVOID)this, 0, &tid);

	do
	{
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(0);
	}while(!done);

	
	*phBmpImage = bmp.Detach();

	return S_OK;





	/*

	

	try
	{
		HTMLite* html = new HTMLite();

		html->load(fileName);
		html->measure(1024, 768);
		

		if(isExternal)
		{
			Sleep(2000);
		}
		

		CDC dc;
		dc.CreateCompatibleDC();
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(CWindowDC(0), 1024, 768);
		dc.SelectBitmap(bmp);

		html->render(dc, 0, 0, 1024, 768);

		dc.SelectBitmap(NULL);
		*phBmpImage = bmp.Detach();

		delete html;

		hRes = S_OK;
	}
	catch(...)
	{
		hRes = E_FAIL;
	}
	
	return hRes;*/
}

STDMETHODIMP CHTMLExtractImage2::GetLocation(LPWSTR pszPathBuffer,DWORD cchMax,DWORD *pdwPriority, const SIZE *prgSize,DWORD dwRecClrDepth,DWORD *pdwFlags)
{

	if(NULL == pszPathBuffer)
		return E_INVALIDARG;

	if(NULL == prgSize)
		return E_INVALIDARG;

	// got to store the request-information for when Extract() is called
	colorDepth = dwRecClrDepth;
	size = *prgSize;
    lstrcpyn ( pszPathBuffer, fileName, cchMax - 1);

	if(pdwFlags != NULL)
	{
		// Explorer may happily cache our icon
		// For debugging purposes, this is best commented out.
		*pdwFlags |= IEIFLAG_CACHE;
		*pdwFlags |= IEIFLAG_ORIGSIZE;


		flags = *pdwFlags;
	}


	return S_OK;
}
STDMETHODIMP CHTMLExtractImage2::GetDateStamp(FILETIME *pDateStamp)
{
	if(NULL == pDateStamp)
		return E_INVALIDARG;

	FILETIME ftCreationTime = {0};
	FILETIME ftLastAccessTime = {0};
	FILETIME ftLastWriteTime = {0};

	HANDLE hFile = CreateFile(fileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(NULL == hFile)
		return E_FAIL;


	GetFileTime(hFile,&ftCreationTime,&ftLastAccessTime,&ftLastWriteTime);
	CloseHandle(hFile);

	// the last time of writing (editing) will be used
	// as the datestamp for this thumbnail.
	*pDateStamp = ftLastWriteTime;

	return NOERROR; 
}