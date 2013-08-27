
/*
 * This file was generated by the SOM Compiler.
 * FileName: MNIcon.c.
 * Generated using:
 *     SOM Precompiler spc: 1.22
 *     SOM Emitter emitc: 1.24
 */

/*
 * MNIcon class release 2.0 (02/06/96) by Makoto Nagata
 */

#define MNIcon_Class_Source
#include "MNIcon.ih"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <wpshadow.h>

/*******************************************************************************

    Class Data

*******************************************************************************/

char szClassName[] = "MNIcon";

/*******************************************************************************

    Get Original Object

    - if pObject is a shadow, returns the original

*******************************************************************************/

WPObject* GetOriginalObject(WPObject* pObject)
{
    if (pObject)
    {
        if (_somIsA(pObject, _WPShadow))
        {
            return _wpQueryShadowedObject(pObject, FALSE);
        }
    }

    return pObject;
}

/*******************************************************************************

    _wpDragOver

    - objects are droppable only if it is an object other than MNIcon

*******************************************************************************/

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

SOM_Scope MRESULT   SOMLINK mnicon_wpDragOver(MNIcon *somSelf,
		HWND hwndCnr,
		PDRAGINFO pdrgInfo)
{
    PDRAGITEM pdrgItem;
    ULONG ulIndex;
    WPObject* object;

    /* MNIconData *somThis = MNIconGetData(somSelf); */
    MNIconMethodDebug("MNIcon","mnicon_wpDragOver");

    for (ulIndex = 0; ulIndex < DrgQueryDragitemCount(pdrgInfo); ulIndex ++)
    {
        pdrgItem = DrgQueryDragitemPtr(pdrgInfo, ulIndex);

        if (!DrgVerifyRMF(pdrgItem, "DRM_OBJECT", "DRF_OBJECT"))
        {
            return MRFROM2SHORT(DOR_NEVERDROP, DO_UNKNOWN);
        }
        else
        {
            object = GetOriginalObject((WPObject *)OBJECT_FROM_PREC(pdrgItem->ulItemID));

            if ((!object) || (_somIsA(object, _MNIcon)))
            {
                return MRFROM2SHORT(DOR_NEVERDROP, DO_UNKNOWN);
            }
        }
    }

    return MRFROM2SHORT(DOR_DROP, DO_UNKNOWN);
}

/*******************************************************************************

    _wpDrop

    - sets the icon of the dropped objects using _wpSetIconData
    - uses fixed size buffer because _wpQueryIconData doesn't give me the size!
    - works only if the IconData type is ICON_DATA (which is the case for *.ICO)

*******************************************************************************/

#define MAXICONINFO 8192

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMInstance

SOM_Scope MRESULT   SOMLINK mnicon_wpDrop(MNIcon *somSelf,
		HWND hwndCnr,
		PDRAGINFO pdrgInfo,
		PDRAGITEM pdrgItem)
{
    WPObject* object;
    PICONINFO pIconInfo;
    ULONG ulSize;

    /* MNIconData *somThis = MNIconGetData(somSelf); */
    MNIconMethodDebug("MNIcon","mnicon_wpDrop");

    if (DrgVerifyRMF(pdrgItem, "DRM_OBJECT", "DRF_OBJECT"))
    {
        object = GetOriginalObject((WPObject *)OBJECT_FROM_PREC(pdrgItem->ulItemID));

        if ((object) && (!_somIsA(object, _MNIcon)))
        {
            ulSize = MAXICONINFO;

            if (pIconInfo = (PICONINFO)_wpAllocMem(somSelf, ulSize, NULL))
            {
                if (_wpQueryIconData(somSelf, pIconInfo))
                {
                    if (pIconInfo->fFormat == ICON_DATA)
                    {
                        pIconInfo->cb = sizeof(ICONINFO) + pIconInfo->cbIconData;
                        pIconInfo->pIconData = ((PBYTE)pIconInfo) + sizeof(ICONINFO);

                        _wpSetIconData(object, pIconInfo);
                    }
                }
                _wpFreeMem(somSelf, (PBYTE)pIconInfo);
            }
        }
    }

    return (parent_wpDrop(somSelf,hwndCnr,pdrgInfo,pdrgItem));
}

/*******************************************************************************

    _wpclsQueryTitle

*******************************************************************************/

#undef SOM_CurrentClass
#define SOM_CurrentClass SOMMeta

SOM_Scope PSZ   SOMLINK mniconM_wpclsQueryTitle(M_MNIcon *somSelf)
{
    /* M_MNIconData *somThis = M_MNIconGetData(somSelf); */
    
    M_MNIconMethodDebug("M_MNIcon","mniconM_wpclsQueryTitle");

    return szClassName;
}

