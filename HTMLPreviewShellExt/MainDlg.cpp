// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
	return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CRect rc(-1024,0, 0, 768);
	MoveWindow(&rc);


	UIAddChildWindowContainer(m_hWnd);

	  // Create the AX host window.
    wndIE.Create ( *this, rc, _T(""), 
                   WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN );

	//wndIE.SetExternalUIHandler((IDocHostUIHandlerDispatch*)(this));


	CComPtr<IUnknown> punkCtrl;
	CComVariant v;    // empty VARIANT
 
    // Create the browser control using its GUID.
    wndIE.CreateControlEx ( L"{8856F961-340A-11D0-A96B-00C04FD705A2}", NULL, NULL, &punkCtrl );
	//wndIE.SetParent(m_hWnd);

	CComQIPtr<IWebBrowser2> pWB2(punkCtrl);
	web = pWB2;

	web->put_Silent(VARIANT_TRUE);
	//web->Navigate (CComBSTR(L"about:blank") , &v, &v, &v, &v );
	//web->Navigate(CComBSTR(url), &v, &v, &v, &v);

	return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	wndIE.DestroyWindow();

	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	CloseDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CloseDialog(wID);
	return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	//::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnBnClickedAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	visitSite(L"www.nu.nl");
	/*
	CRect rc; 

	rc.SetRect(0,0, 1024, 768);
 
    // Create the AX host window.
    wndIE.Create ( *this, rc, _T(""), 
                   WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN );

	//wndIE.SetExternalUIHandler((IDocHostUIHandlerDispatch*)(this));


	CComPtr<IUnknown> punkCtrl;
CComQIPtr<IWebBrowser2> pWB2;
CComVariant v;    // empty VARIANT
 
    // Create the browser control using its GUID.
    wndIE.CreateControlEx ( L"{8856F961-340A-11D0-A96B-00C04FD705A2}", 
                            NULL, NULL, &punkCtrl );

 
    // Get an IWebBrowser2 interface on the control and navigate to a page.
    pWB2 = punkCtrl;
	PWB2->put_Silent(VARIANT_TRUE);
	pWB2->Navigate ( CComBSTR("http://gathering.tweakers.net"), &v, &v, &v, &v );

	BOOL didSetDocUIHandler = FALSE;
	VARIANT_BOOL busy = VARIANT_FALSE;
	do
	{
		pWB2->get_Busy(&busy);
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, 1))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
			
		if(!didSetDocUIHandler)
		{
			CComPtr<IDispatch> doc;
			pWB2->get_Document(&doc);
			if(doc)
			{
				CComQIPtr<ICustomDoc> customDoc(doc);
				customDoc->SetUIHandler(this);
				didSetDocUIHandler = TRUE;
			}
		}

	}while(busy);


	pWB2->Refresh();

	busy = VARIANT_FALSE;
	do
	{
		pWB2->get_Busy(&busy);
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, 1))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}while(busy);

	CComPtr<IDispatch> disp;
	pWB2->get_Document(&disp);
	CComQIPtr<IHTMLDocument2> doc (disp);
	if(NULL == doc)
		return 0;

	if(!didSetDocUIHandler)
	{
		CComQIPtr<ICustomDoc> customDoc(doc);
		customDoc->SetUIHandler(this);
	}

	long cx = 0;
	long cy = 0;

	CComPtr<IHTMLElement> elem;
	doc->get_body(&elem);
	CComQIPtr<IHTMLBodyElement> body(elem);
	if(elem)
	{
		elem->get_offsetWidth(&cx);
		elem->get_offsetHeight(&cy);

		wndIE.MoveWindow(0,0, cx, cy);
	}
	*/

	return 0;
}


void CMainDlg::visitSite(const WCHAR* url)
{
	DWORD waitTimeOut = 10000;

	DWORD dwVal = 0;
	DWORD type = REG_DWORD;
	DWORD size = sizeof(dwVal);
	LRESULT lRes = SHGetValue(HKEY_CURRENT_USER, L"AveSoftware/HTMLThumb", L"waitTimeOutMs", &type, &dwVal, &size);
	if(ERROR_SUCCESS == lRes)
	{
		waitTimeOut = dwVal;
	}

	CWindow win;
	win.Create(L"BUTTON", NULL);

	if(NULL == wndIE.m_hWnd)
	{
		CRect rc(-1024,0, 0, 768);
		wndIE.Create ( win, rc, _T(""), 
                   WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN );

		//wndIE.SetExternalUIHandler((IDocHostUIHandlerDispatch*)(this));


		CComPtr<IUnknown> punkCtrl;
		CComVariant v;    // empty VARIANT
 
		// Create the browser control using its GUID.
		wndIE.CreateControlEx ( L"{8856F961-340A-11D0-A96B-00C04FD705A2}", NULL, NULL, &punkCtrl );
		//wndIE.SetParent(m_hWnd);

		CComQIPtr<IWebBrowser2> pWB2(punkCtrl);
		web = pWB2;
	}

	CComVariant v;    // empty VARIANT

	BOOL isExternal  = !PathFileExists(url);

	this->url = url;

	WCHAR base[MAX_PATH] = {0};
	wcscpy_s(base, MAX_PATH, url);
	PathRemoveFileSpec(base);

	web->put_Silent(VARIANT_TRUE);

	const WCHAR* ext = PathFindExtension(url);
	if(ext != NULL && (_wcsicmp(ext, L".mht") == 0  || _wcsicmp(ext, L".mhtml") == 0))
	{
		WCHAR tmpFolder[MAX_PATH]  = {0};
		WCHAR tmpPath[MAX_PATH] = {0};

		GetTempPath(MAX_PATH, tmpFolder);

		GetTempFileName(tmpFolder, L"ave", 0, tmpPath);
		wcscat_s(tmpPath, MAX_PATH, L".mht");

		CopyFile(url, tmpPath, FALSE);
	
		if(PathFileExists(tmpPath))
			web->Navigate (CComBSTR(tmpPath) , &v, &v, &v, &v );
	}
	else
	{
		if(!isExternal)
		{
			web->Navigate (CComBSTR(L"about:blank") , &v, &v, &v, &v );

			CComPtr<IDispatch> docA;
			web->get_Document(&docA);

			
			CComPtr<IBindCtx> bindCtx;
			CreateBindCtx(0, &bindCtx);

			CComQIPtr< IPersistMoniker> ipm (docA);
			ipm->Load(TRUE, static_cast<IMoniker*>(this), bindCtx, STGM_READ);
		}
		else
		{
			web->Navigate (CComBSTR(url) , &v, &v, &v, &v );
		}
	}


	BOOL didSetDocUIHandler = FALSE;
	VARIANT_BOOL busy = VARIANT_FALSE;
	do
	{
		web->get_Busy(&busy);
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
			
		if(!didSetDocUIHandler)
		{
			CComPtr<IDispatch> doc;
			web->get_Document(&doc);
			if(doc)
			{
				CComQIPtr<ICustomDoc> customDoc(doc);
				customDoc->SetUIHandler(this);
				didSetDocUIHandler = TRUE;
			}
		}

	}while(busy);


	web->Refresh();

	busy = VARIANT_FALSE;
	do
	{
		web->get_Busy(&busy);
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}while(busy);

	CComPtr<IDispatch> disp;
	web->get_Document(&disp);
	CComQIPtr<IHTMLDocument2> doc (disp);
	if(NULL == doc)
	{
		win.DestroyWindow();
		return;
	}

	DWORD tc = GetTickCount();
	CComBSTR rs;
	do
	{
		MSG msg = {0};
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		rs.Empty();
		doc->get_readyState(&rs);
		if(GetTickCount() - tc > waitTimeOut)
			break;
	}while(rs != L"complete");

	if(!didSetDocUIHandler)
	{
		CComQIPtr<ICustomDoc> customDoc(doc);
		customDoc->SetUIHandler(this);
	}

	long cx = 0;
	long cy = 0;

	CComPtr<IHTMLElement> elem;
	doc->get_body(&elem);
	CComQIPtr<IHTMLBodyElement> body(elem);
	if(elem)
	{
		wndIE.MoveWindow(0,0, 1024, 768);

		elem->get_offsetWidth(&cx);
		elem->get_offsetHeight(&cy);

		cx = min(cx, 1024);
		cy = min(cy, 768);
	}

	dc.CreateCompatibleDC();
	bmp.CreateCompatibleBitmap(CWindowDC(NULL), cx, cy);
	dc.SelectBitmap(bmp);
	//dc.FillSolidRect(0,0, 1024, 768, RGB(255,0,0));

	HRESULT hr = OleDraw(web, DVASPECT_CONTENT, dc, CRect(0,0, cx, cy)); 

	GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Bitmap gbmp(bmp.m_hBitmap, NULL);
	Bitmap gbmp2(cx/2, cy/2);
	Graphics g(&gbmp2);

	g.SetSmoothingMode(/*SmoothingModeAntiAlias8x8*/SmoothingModeAntiAlias);
	g.SetInterpolationMode(InterpolationModeHighQualityBicubic);

	g.DrawImage(&gbmp, Rect(0,0, cx/2, cy/2), 0,0, cx, cy, UnitPixel, 0, 0, 0);
	//CLSID clsid = {0};
	//GetEncoderClsid(L"image/png", &clsid);
	//gbmp2.Save(L"c:\\users\\ave\\desktop\\s.png", &clsid);

	bmp.DeleteObject();
	gbmp2.GetHBITMAP(NULL, &bmp.m_hBitmap);

	dc.SelectBitmap(bmp);

	win.DestroyWindow();

	return;
}