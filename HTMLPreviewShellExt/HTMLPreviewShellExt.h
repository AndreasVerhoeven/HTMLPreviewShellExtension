

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0499 */
/* at Sat Apr 12 18:10:58 2008
 */
/* Compiler settings for .\HTMLPreviewShellExt.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __HTMLPreviewShellExt_h__
#define __HTMLPreviewShellExt_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHTMLExtractImage2_FWD_DEFINED__
#define __IHTMLExtractImage2_FWD_DEFINED__
typedef interface IHTMLExtractImage2 IHTMLExtractImage2;
#endif 	/* __IHTMLExtractImage2_FWD_DEFINED__ */


#ifndef __HTMLExtractImage2_FWD_DEFINED__
#define __HTMLExtractImage2_FWD_DEFINED__

#ifdef __cplusplus
typedef class HTMLExtractImage2 HTMLExtractImage2;
#else
typedef struct HTMLExtractImage2 HTMLExtractImage2;
#endif /* __cplusplus */

#endif 	/* __HTMLExtractImage2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IHTMLExtractImage2_INTERFACE_DEFINED__
#define __IHTMLExtractImage2_INTERFACE_DEFINED__

/* interface IHTMLExtractImage2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IHTMLExtractImage2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("691EFBA0-45A1-4389-8A50-2BEABB48DD40")
    IHTMLExtractImage2 : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IHTMLExtractImage2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHTMLExtractImage2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHTMLExtractImage2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHTMLExtractImage2 * This);
        
        END_INTERFACE
    } IHTMLExtractImage2Vtbl;

    interface IHTMLExtractImage2
    {
        CONST_VTBL struct IHTMLExtractImage2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHTMLExtractImage2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHTMLExtractImage2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHTMLExtractImage2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHTMLExtractImage2_INTERFACE_DEFINED__ */



#ifndef __HTMLPreviewShellExtLib_LIBRARY_DEFINED__
#define __HTMLPreviewShellExtLib_LIBRARY_DEFINED__

/* library HTMLPreviewShellExtLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_HTMLPreviewShellExtLib;

EXTERN_C const CLSID CLSID_HTMLExtractImage2;

#ifdef __cplusplus

class DECLSPEC_UUID("28AC834E-D791-4E37-BEEE-C1739AE9F5EE")
HTMLExtractImage2;
#endif
#endif /* __HTMLPreviewShellExtLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


