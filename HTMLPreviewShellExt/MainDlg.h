// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainDlg : public CAxDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler,
		public IDocHostUIHandler, 
		public IOleCommandTarget,
		public IMoniker
{
public:
	enum { IDD = IDD_MAINDLG };

	CString url;
	CDC dc;
	CBitmap bmp;

	CAxWindow wndIE;
	CComPtr<IWebBrowser2> web;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_HANDLER(ID_APP_ABOUT, BN_CLICKED, OnBnClickedAppAbout)
	END_MSG_MAP()

	void visitSite(const WCHAR* url);

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);
	LRESULT OnBnClickedAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);


	  virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE QueryStatus( 
            /* [unique][in] */ __RPC__in_opt const GUID *pguidCmdGroup,
            /* [in] */ ULONG cCmds,
            /* [out][in][size_is] */ __RPC__inout_ecount_full(cCmds) OLECMD prgCmds[  ],
            /* [unique][out][in] */ __RPC__inout_opt OLECMDTEXT *pCmdText) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE Exec( 
            /* [unique][in] */ __RPC__in_opt const GUID *pguidCmdGroup,
            /* [in] */ DWORD nCmdID,
            /* [in] */ DWORD nCmdexecopt,
            /* [unique][in] */ __RPC__in_opt VARIANT *pvaIn,
            /* [unique][out][in] */ __RPC__inout_opt VARIANT *pvaOut) { return E_NOTIMPL; }


	          virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
                /* [in] */ REFIID riid,
				/* [iid_is][out] */ __RPC__deref_out void __RPC_FAR *__RPC_FAR *ppvObject) 
				{
					if(NULL == ppvObject)
						return E_POINTER;

					*ppvObject = NULL;

					if(IsEqualIID(riid, IID_IUnknown))
						*ppvObject = static_cast<IUnknown*>((IDocHostUIHandler*)this);
					else	if(IsEqualIID(riid, IID_IDocHostUIHandler))
						*ppvObject = static_cast<IDocHostUIHandler*>(this);
					else	if(IsEqualIID(riid, IID_IOleCommandTarget))
						*ppvObject = static_cast<IOleCommandTarget*>(this);
					else	if(IsEqualIID(riid, IID_IMoniker))
						*ppvObject = static_cast<IMoniker*>(this);
					else	if(IsEqualIID(riid, IID_IPersistStream))
						*ppvObject = static_cast<IPersistStream*>(this);

					return *ppvObject != NULL ? S_OK : E_NOINTERFACE;
				}

			  virtual ULONG STDMETHODCALLTYPE AddRef( void) { return 1;}

			  virtual ULONG STDMETHODCALLTYPE Release( void) {return 1;};


	    virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( 
            /* [in] */ DWORD dwID,
            /* [in] */ POINT *ppt,
            /* [in] */ IUnknown *pcmdtReserved,
			/* [in] */ IDispatch *pdispReserved) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetHostInfo( 
            /* [out][in] */ DOCHOSTUIINFO *pInfo) 
		{ 
			if(NULL == pInfo)
				return E_POINTER;

			pInfo->dwFlags = DOCHOSTUIFLAG_NO3DBORDER | DOCHOSTUIFLAG_SCROLL_NO | DOCHOSTUIFLAG_THEME | DOCHOSTUIFLAG_NO3DOUTERBORDER | DOCHOSTUIFLAG_USE_WINDOWLESS_SELECTCONTROL;
			return S_OK; 
		}
        
        virtual HRESULT STDMETHODCALLTYPE ShowUI( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject *pActiveObject,
            /* [in] */ IOleCommandTarget *pCommandTarget,
            /* [in] */ IOleInPlaceFrame *pFrame,
            /* [in] */ IOleInPlaceUIWindow *pDoc)
		{ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE HideUI( void) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE UpdateUI( void) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate( 
            /* [in] */ BOOL fActivate)
		{ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate)
		{ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fRameWindow) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID *pguidCmdGroup,
            /* [in] */ DWORD nCmdID) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( 
            /* [out] */ 
            __out  LPOLESTR *pchKey,
            /* [in] */ DWORD dw){ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetDropTarget( 
            /* [in] */ IDropTarget *pDropTarget,
            /* [out] */ IDropTarget **ppDropTarget) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetExternal( 
            /* [out] */ IDispatch **ppDispatch) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ 
            __in __nullterminated  OLECHAR *pchURLIn,
            /* [out] */ 
            __out  OLECHAR **ppchURLOut){ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE FilterDataObject( 
            /* [in] */ IDataObject *pDO,
            /* [out] */ IDataObject **ppDORet) { return E_NOTIMPL; }





	
		 virtual HRESULT STDMETHODCALLTYPE GetClassID( 
            /* [out] */ __RPC__out CLSID *pClassID) { return E_NOTIMPL; }

		virtual HRESULT STDMETHODCALLTYPE IsDirty( void) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [unique][in] */ __RPC__in_opt IStream *pStm) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE Save( 
            /* [unique][in] */ __RPC__in_opt IStream *pStm,
            /* [in] */ BOOL fClearDirty) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetSizeMax( 
            /* [out] */ __RPC__out ULARGE_INTEGER *pcbSize) { return E_NOTIMPL; }


		virtual /* [local] */ HRESULT STDMETHODCALLTYPE BindToObject( 
            /* [unique][in] */ IBindCtx *pbc,
            /* [unique][in] */ IMoniker *pmkToLeft,
            /* [in] */ REFIID riidResult,
            /* [iid_is][out] */ void **ppvResult)
		{ return E_NOTIMPL; }
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE BindToStorage( 
            /* [unique][in] */ IBindCtx *pbc,
            /* [unique][in] */ IMoniker *pmkToLeft,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObj)
		{ 
			if(!IsEqualIID(riid, IID_IStream))
				return E_FAIL;

			WCHAR base[MAX_PATH] = {0};
			wcscpy_s(base, MAX_PATH, url);
			PathRemoveFileSpec(base);

			const WCHAR* ext = PathFindExtension(url);
			BOOL appendBase = TRUE;

			if(ext != NULL && (_wcsicmp(ext, L".mht") == 0  || _wcsicmp(ext, L".mhtml") == 0))
			{
				appendBase = FALSE;
			}

			CComBSTR baseTag;
			if(appendBase)
			{
				baseTag.Append(L"<base href=\"");
				baseTag.Append(base);
				baseTag.Append(L"\\\"/>");
			}


			//CComPtr<IStream> stream;
			//SHCreateStreamOnFileEx(url, STGM_READ | STGM_SHARE_DENY_NONE, 0, FALSE, NULL, &stream);

			//stream->QueryInterface(riid, ppvObj);

			//stream->

			HANDLE hFile = CreateFile(url,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			DWORD dwSize = GetFileSize(hFile, NULL);
		

			CComPtr<IStream> stream2;


			// allocate global memory to copy the HTML content to 
			DWORD len = baseTag.Length() * sizeof(WCHAR) + dwSize;
			HGLOBAL hHTMLContent = ::GlobalAlloc( GPTR, len);
			if (!hHTMLContent) 
				return E_FAIL; 

			WCHAR* wstr = (WCHAR*)GlobalLock(hHTMLContent);
			memcpy(wstr, baseTag.m_str, baseTag.Length() * sizeof(WCHAR));
			BYTE* ptr = (BYTE*)wstr;
			ptr += baseTag.Length() * sizeof(WCHAR);

			DWORD numRead = 0;
			ReadFile(hFile, (LPVOID)ptr, dwSize, &numRead, NULL);
			CloseHandle(hFile);

			GlobalUnlock(hHTMLContent);


			::CreateStreamOnHGlobal(hHTMLContent,  TRUE, &stream2.p ); 

			stream2->QueryInterface(riid, ppvObj);

			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE Reduce( 
            /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
            /* [in] */ DWORD dwReduceHowFar,
            /* [unique][out][in] */ __RPC__deref_opt_inout_opt IMoniker **ppmkToLeft,
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmkReduced) { return E_NOTIMPL; };
        
        virtual HRESULT STDMETHODCALLTYPE ComposeWith( 
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkRight,
            /* [in] */ BOOL fOnlyIfNotGeneric,
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmkComposite) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE Enum( 
            /* [in] */ BOOL fForward,
            /* [out] */ __RPC__deref_out_opt IEnumMoniker **ppenumMoniker) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE IsEqual( 
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkOtherMoniker) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE Hash( 
            /* [out] */ __RPC__out DWORD *pdwHash) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE IsRunning( 
            /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkToLeft,
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkNewlyRunning){ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetTimeOfLastChange( 
            /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkToLeft,
            /* [out] */ __RPC__out FILETIME *pFileTime) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE Inverse( 
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmk) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE CommonPrefixWith( 
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkOther,
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmkPrefix){ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE RelativePathTo( 
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkOther,
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmkRelPath) 
		{ return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE GetDisplayName( 
            /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkToLeft,
			/* [out] */ __RPC__deref_out_opt LPOLESTR *ppszDisplayName) 
		{
			WCHAR base[MAX_PATH] = {0};
			wcscpy_s(base, MAX_PATH, url);
			PathRemoveFileSpec(base);
			wcscat_s(base, MAX_PATH, L"\\");
			//PathAppend(base, L"______unknown.html");

			*ppszDisplayName = NULL;
			CComPtr<IMalloc> malloc;
			CoGetMalloc(1, &malloc);
			DWORD len = (DWORD)wcslen(base) + 1;
			WCHAR* str = (WCHAR*) malloc->Alloc(len * sizeof(WCHAR));
			if(str != NULL)
			{
				wcscpy_s(str, size_t(len), base);
				*ppszDisplayName = str;
			}
			return S_OK;
		}
        
        virtual HRESULT STDMETHODCALLTYPE ParseDisplayName( 
            /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
            /* [unique][in] */ __RPC__in_opt IMoniker *pmkToLeft,
            /* [in] */ __RPC__in LPOLESTR pszDisplayName,
            /* [out] */ __RPC__out ULONG *pchEaten,
            /* [out] */ __RPC__deref_out_opt IMoniker **ppmkOut) { return E_NOTIMPL; }
        
        virtual HRESULT STDMETHODCALLTYPE IsSystemMoniker( 
            /* [out] */ __RPC__out DWORD *pdwMksys) { return E_NOTIMPL; }
};
