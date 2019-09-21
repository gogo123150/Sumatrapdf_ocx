

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Sep 21 23:03:23 2019
 */
/* Compiler settings for ActiveX_Sumatrapdf.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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


#ifndef __ActiveX_Sumatrapdfidl_h__
#define __ActiveX_Sumatrapdfidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DActiveX_Sumatrapdf_FWD_DEFINED__
#define ___DActiveX_Sumatrapdf_FWD_DEFINED__
typedef interface _DActiveX_Sumatrapdf _DActiveX_Sumatrapdf;
#endif 	/* ___DActiveX_Sumatrapdf_FWD_DEFINED__ */


#ifndef ___DActiveX_SumatrapdfEvents_FWD_DEFINED__
#define ___DActiveX_SumatrapdfEvents_FWD_DEFINED__
typedef interface _DActiveX_SumatrapdfEvents _DActiveX_SumatrapdfEvents;
#endif 	/* ___DActiveX_SumatrapdfEvents_FWD_DEFINED__ */


#ifndef __ActiveX_Sumatrapdf_FWD_DEFINED__
#define __ActiveX_Sumatrapdf_FWD_DEFINED__

#ifdef __cplusplus
typedef class ActiveX_Sumatrapdf ActiveX_Sumatrapdf;
#else
typedef struct ActiveX_Sumatrapdf ActiveX_Sumatrapdf;
#endif /* __cplusplus */

#endif 	/* __ActiveX_Sumatrapdf_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ActiveX_SumatrapdfLib_LIBRARY_DEFINED__
#define __ActiveX_SumatrapdfLib_LIBRARY_DEFINED__

/* library ActiveX_SumatrapdfLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_ActiveX_SumatrapdfLib;

#ifndef ___DActiveX_Sumatrapdf_DISPINTERFACE_DEFINED__
#define ___DActiveX_Sumatrapdf_DISPINTERFACE_DEFINED__

/* dispinterface _DActiveX_Sumatrapdf */
/* [uuid] */ 


EXTERN_C const IID DIID__DActiveX_Sumatrapdf;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AA407211-5BA5-441A-BE0E-826FA6B48DF9")
    _DActiveX_Sumatrapdf : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DActiveX_SumatrapdfVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DActiveX_Sumatrapdf * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DActiveX_Sumatrapdf * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DActiveX_Sumatrapdf * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DActiveX_Sumatrapdf * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DActiveX_Sumatrapdf * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DActiveX_Sumatrapdf * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DActiveX_Sumatrapdf * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DActiveX_SumatrapdfVtbl;

    interface _DActiveX_Sumatrapdf
    {
        CONST_VTBL struct _DActiveX_SumatrapdfVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DActiveX_Sumatrapdf_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DActiveX_Sumatrapdf_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DActiveX_Sumatrapdf_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DActiveX_Sumatrapdf_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DActiveX_Sumatrapdf_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DActiveX_Sumatrapdf_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DActiveX_Sumatrapdf_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DActiveX_Sumatrapdf_DISPINTERFACE_DEFINED__ */


#ifndef ___DActiveX_SumatrapdfEvents_DISPINTERFACE_DEFINED__
#define ___DActiveX_SumatrapdfEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DActiveX_SumatrapdfEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DActiveX_SumatrapdfEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("526A5B43-BEBC-43B9-A23D-AF1A2DEFF5BD")
    _DActiveX_SumatrapdfEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DActiveX_SumatrapdfEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DActiveX_SumatrapdfEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DActiveX_SumatrapdfEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DActiveX_SumatrapdfEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DActiveX_SumatrapdfEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DActiveX_SumatrapdfEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DActiveX_SumatrapdfEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DActiveX_SumatrapdfEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DActiveX_SumatrapdfEventsVtbl;

    interface _DActiveX_SumatrapdfEvents
    {
        CONST_VTBL struct _DActiveX_SumatrapdfEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DActiveX_SumatrapdfEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DActiveX_SumatrapdfEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DActiveX_SumatrapdfEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DActiveX_SumatrapdfEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DActiveX_SumatrapdfEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DActiveX_SumatrapdfEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DActiveX_SumatrapdfEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DActiveX_SumatrapdfEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ActiveX_Sumatrapdf;

#ifdef __cplusplus

class DECLSPEC_UUID("1FFDCBF1-7BC9-4EDA-8834-8AD1FD722227")
ActiveX_Sumatrapdf;
#endif
#endif /* __ActiveX_SumatrapdfLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


