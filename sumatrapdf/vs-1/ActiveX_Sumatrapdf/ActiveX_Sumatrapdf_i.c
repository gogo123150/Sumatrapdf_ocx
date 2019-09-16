

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sun Sep 08 19:14:22 2019
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_ActiveX_SumatrapdfLib,0xF57E33F0,0xBC15,0x4EDA,0x8C,0xAE,0x88,0x78,0x09,0x92,0xD0,0x33);


MIDL_DEFINE_GUID(IID, DIID__DActiveX_Sumatrapdf,0xAA407211,0x5BA5,0x441A,0xBE,0x0E,0x82,0x6F,0xA6,0xB4,0x8D,0xF9);


MIDL_DEFINE_GUID(IID, DIID__DActiveX_SumatrapdfEvents,0x526A5B43,0xBEBC,0x43B9,0xA2,0x3D,0xAF,0x1A,0x2D,0xEF,0xF5,0xBD);


MIDL_DEFINE_GUID(CLSID, CLSID_ActiveX_Sumatrapdf,0x1FFDCBF1,0x7BC9,0x4EDA,0x88,0x34,0x8A,0xD1,0xFD,0x72,0x22,0x27);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



