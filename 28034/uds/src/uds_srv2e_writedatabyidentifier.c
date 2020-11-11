/****************************************************************************
 	@Module       
 	@Filename      uds_srv2e_writedatabyidentifier.c
 	@Project       BQApp
----------------------------------------------------------------------------
 	@Controller    TI 28034

 	@Compiler      V5.211

 	@Codegenerator CCS 3.3

 	@Description   

----------------------------------------------------------------------------
	 @Date          12/19/2014

******Copyright Auto Group , Shenzhen Megmeet Drive Technology Co.,LTD*****

****************************************************************************/



#include "main.h"
#include "uds_target.h"
#include "uds_confpriv.h"
#include "uds_confdefs.h"
#include "uds_priv.h"
#include "uds_inf.h"
//#include "eed_data.h"
#include "FblMgr.h"
#include "Error.h"
#include "EepromManage.h"



#ifdef UDS_ENABLE_WRITEDATABYIDENTIFIER


extern uint8_t rub_ReqDnUpldDataBuf[UDS_C_REQ_DN_OR_UP_LD_BUF_SIZE];


static uint8_t rub_2eWtDatByDid_PendingFlg ; //= (uint8_t)FALSE;
uint8_t rub_2eWtDatByDid_CurrUsingTblIndex ; //= 0x00u;
static Uds_APduData_t* pSavedAPduResp;

uint16 WriteStep;

static Std_UdsReturnType UDS_FN_TYPE UdsApp_2eWtDatByDid_WriteDataProc(Uds_APduData_t* pAPduInd, 
                                                                       Uds_APduData_t* pAPduResp ); 




/* no Sun-Function parameter for this service */

/* NRC for ReadDataByIdentifier
 * 	0x13	UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT
 * 	0x22	UDS_NRC_CONDITIONSNOTCORRECT
 * 	0x31	UDS_NRC_REQUESTOUTOFRANGE
 *	0x33	UDS_NRC_SECUTITYACCESSDENIED
 */

Std_UdsReturnType UDS_FN_TYPE UdsApp_WriteDataByIdentifier(Uds_APduData_t* pAPduInd, 
                                                        Uds_APduData_t* pAPduResp )
{
   uint8_t lub_error = UDS_POSITIVE_RESPONSE;

   if (TARGETADDR_FUNCTIONAL == UDS_APP_ITF_IMP_GET_TP_CHNL())
   {
       lub_error = UDS_NRC_SERVICENOTSUPPORTED;
   }
   else if (UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION() == UDS_DEFAULT_SESSION)
   {
       lub_error = UDS_NRC_SERVICENOTSUPPORTEDINACTIVESESSION;
   }
   else
   {
       lub_error = UdsApp_2eWtDatByDid_WriteDataProc(pAPduInd, 
                                                  pAPduResp );

   }

   return lub_error;

}  /* end of Uds_WriteDataByIdentifier()  */


static Std_UdsReturnType UDS_FN_TYPE UdsApp_2eWtDatByDid_WriteDataProc(Uds_APduData_t* pAPduInd, 
                                                                    Uds_APduData_t* pAPduResp ) 
{
   uint8_t  lub_index             = 0x00u;
   //uint8_t  lub_E2DrvReturnCode = FALSE;
   uint8_t  lub_response          = UDS_POSITIVE_RESPONSE;
   uint16_t luw_InDid2WrtE2       = 0x0000u;
   uint8_t  lub_CurrActiveSession = UDS_APP_ITF_IMP_GET_CURR_ACTIVE_SESSION();
   /*
   uint32_t lul_RcvdSwProgVldFlg = 0x00000000u; 
   uint32_t lul_SwProgVldFlgChkSum = 0x00000000u; 
   uint8_t   i = 0x00u; 
   uint8_t   j = 0x00u; 
    */
   pSavedAPduResp = pAPduResp; /* just to remove the compiliation warning */

   if (pAPduInd->msgLength < 0x03u)
   {
	   lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT ;
	   return lub_response ;
   }
   else
   {
   }

   luw_InDid2WrtE2  = (uint16_t)((pAPduInd->pduData[0x01u]) << 0x08u);
   luw_InDid2WrtE2 |= (uint16_t)( pAPduInd->pduData[0x02u]);

	 lub_index = Uds_Generic_DatMgr_SearchTblByKey(luw_InDid2WrtE2,
	                                               KeyTypeIsUINT16, 
	                                               (uint8_t *)&(Uds_g_DidEepromDataTable[0x00u].dataIdentifier),
	 								                               sizeof(Uds_g_DidEepromDataTable[0x00u]));
	                                 
   if (lub_index == UDS_C_IDX_NOT_IN_TBL)
	 {
	     lub_response = UDS_NRC_REQUESTOUTOFRANGE ;
       return lub_response ;
	 }
	 else
	 {

   }


	 if (pAPduInd->msgLength != (0x03u + Uds_g_DidEepromDataTable[lub_index].DataSize ))
	 {
	     lub_response = UDS_NRC_INCORRECTMESSAGELENGTHORINVALIDFORMAT ;
       return lub_response ;
	 }
   else
   {
   }


   if ( ( (Uds_g_DidEepromDataTable[lub_index].AccessAttribute) & 
          (UDS_C_DID_ATR_ENA_WT )
        ) != UDS_C_DID_ATR_ENA_WT
      )
	 {
			 lub_response =  UDS_NRC_REQUESTOUTOFRANGE;
       return lub_response ;
	 }
   else
   {
   }

   if ( ( ( (Uds_g_DidEepromDataTable[lub_index].AccessAttribute) & 
             UDS_C_DID_ATR_WT_SESN_EXTD
          ) == UDS_C_DID_ATR_WT_SESN_EXTD
        ) &&
        (lub_CurrActiveSession !=  UDS_PROGRAMMING_SESSION) &&        
        (lub_CurrActiveSession !=  UDS_EXTENDED_DIAGNOSTIC_SESSION) &&
        (lub_CurrActiveSession !=  UDS_SAFTEY_SYSTEM_DIAGNOSTIC_SESSION)
      )
   {
       lub_response = UDS_NRC_REQUESTOUTOFRANGE;
       return lub_response;
   }
   else
   {
   }

   if ( ( ( (Uds_g_DidEepromDataTable[lub_index].AccessAttribute) & 
             UDS_C_DID_ATR_WT_SESN_SSS
          ) == UDS_C_DID_ATR_WT_SESN_SSS 
        ) &&
        (lub_CurrActiveSession !=  UDS_PROGRAMMING_SESSION) &&                
        (lub_CurrActiveSession !=  UDS_SAFTEY_SYSTEM_DIAGNOSTIC_SESSION)
      )
   {
       lub_response = UDS_NRC_REQUESTOUTOFRANGE;
       return lub_response;
   }
   else
   {

   }   

   if (((((Uds_g_DidEepromDataTable[lub_index].AccessAttribute) & UDS_C_DID_ATR_WT_SAL11) == UDS_C_DID_ATR_WT_SAL11) 
             && (!UdsApp_27SecuAcc_IsSpecifiedSALHasUnlocked(UDS_C_SECU_ACC_SECU_LEVEL11))))                        
   {
       lub_response = UDS_NRC_SECUTITYACCESSDENIED;
	   return lub_response ;
   }
   else
   {

   }

   
   if (Uds_g_DidEepromDataTable[lub_index].pFuncPtrCheckData != NULL)
   {
       lub_response = (Uds_g_DidEepromDataTable[lub_index].pFuncPtrCheckData)( &(pAPduInd->pduData[0x04u])) ;
   }
   else
   {
   }


	   if (UDS_POSITIVE_RESPONSE == lub_response )
	   {
		   //
           Uds_MemCopy(Uds_g_DidEepromDataTable[lub_index].pDataBuf,
	                   &(pAPduInd->pduData[0x03u]), // pDatSrc,
	                   Uds_g_DidEepromDataTable[lub_index].DataSize);
		   rub_2eWtDatByDid_CurrUsingTblIndex = lub_index;
		   WriteStep = 1;

	   	   lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
	       rub_2eWtDatByDid_PendingFlg = TRUE;     		
	   } /* end of if (UDS_POSITIVE_RESPONSE == lub_response ) */
       else
       {
       
       }


	 return lub_response ;
    
}   /* end of Uds_2eWtDatByDid_WriteDataProc () */

/******************************************************************************
* Name: Uds_2eWtDatByDid_PendingStProc
* Description: Checks the status of "Write Memory Block" request.
*              Will send a success response when the write is finished.
* Parameter: none
* Return: the error code
* Critical: Yes.
* Explanation: Called periodically
******************************************************************************/
uint8_t UDS_FN_TYPE UdsApp_2eWtDatByDid_Pending(void)
{
	uint8_t lub_response  = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING  ;

	if (rub_2eWtDatByDid_PendingFlg == TRUE)
	{
          /* check if EEPROM driver has already finished updating the block
           */
          if (WriteStep == 0)		    
		  {
			rub_2eWtDatByDid_PendingFlg    = FALSE ;
			lub_response                   = UDS_POSITIVE_RESPONSE ;
            (pSavedAPduResp->msgLength)    = 0x03u; 
            pSavedAPduResp->pduData[0x00u] = 0x2Eu; /*SID should be response now */
            pSavedAPduResp->pduData[0x01u] = (uint8_t)(((0xFF00u) & (Uds_g_DidEepromDataTable[rub_2eWtDatByDid_CurrUsingTblIndex].dataIdentifier)) >> 0x08u);
            pSavedAPduResp->pduData[0x02u] =  (uint8_t)(((0x00FFu) & (Uds_g_DidEepromDataTable[rub_2eWtDatByDid_CurrUsingTblIndex].dataIdentifier)));

		  }
		  else	
		  {
			lub_response = UDS_NRC_REQUESTCORRECTLYRECEIVED_RESPPENDING;
		  }        
	}
	else
	{
	}

	return lub_response;
}  /* end of Uds_2eWtDatByDid_Pending() */


void UDS_FN_TYPE UdsApp_2eWtDatByDid_Pend_Overtime(void)
{
   uint8_t lub_response = UDS_NRC_NORESPONSEFROMSUBNETCOMPONENT; 

      pSavedAPduResp->pduData[0x00u] = 0x2Eu; /*SID should be response now */ 
   
   rub_2eWtDatByDid_PendingFlg = (uint8_t)FALSE;
   rub_2eWtDatByDid_CurrUsingTblIndex = (uint8_t)0x00u;
    	Uds_generic_SendResp(pSavedAPduResp, lub_response);    
} /* end of Uds_2eWtDatByDid_Pend_Overtime() */


void UDS_FN_TYPE UdsApp_2eWtDatByDid_Init(void) 
{
   rub_2eWtDatByDid_PendingFlg = (uint8_t)FALSE;
   rub_2eWtDatByDid_CurrUsingTblIndex = (uint8_t)0x00u;
	WriteStep = 0;
}


#endif /* UDS_ENABLE_WRITEDATABYIDENTIFIER */
/******************************************************************************
*                               end of file                                   *
******************************************************************************/
