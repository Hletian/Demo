#ifndef _KEYBOARDEX_H_
#define _KEYBOARDEX_H_

/*******************************************************************************************/
#ifdef  _KEYBOARDEX_
#define  _KEYBOARDEX_DEF_
#else
#define  _KEYBOARDEX_DEF_		extern 
#endif

	/*typedef		unsigned int 	uint;
	typedef		short 		int16;
	typedef		unsigned short  uint16;
	typedef		long		int32;
	typedef		unsigned long  	uint32;*/

/*******************************************************************************************/
/*˽�б���*/

#ifdef  _KEYBOARDEX_
#endif

/*******************************************************************************************/

/*�������*/
	
	/*Para��ʾ����*/	
	typedef struct{
		uint ignore:1;		//=0�ɼ� =1���ɼ�
		uint modify:1;		//=0���ɸ�д =1�ɸ�д
		uint scal:3;		//Сshu��λ��   =0��  =1 =2 =3/1,2,3λ
		uint unit:3;		//��λ H=1 A=2 V=3 R=4 M=5
		uint sign:1;		//=1 ��
		uint flicker:1;		//=1 ��˸
		uint bhex:1;		//=1 16����
		uint rsv:5;		//����
		uint32 value;		//������ֵ
	}DataDisplayBits;


	_KEYBOARDEX_DEF_	DataDisplayBits *SDfirstip;		//ͣ��data��ʼָ��
	_KEYBOARDEX_DEF_	DataDisplayBits *SDfuncip;		//ͣ��data��ǰָ��
	_KEYBOARDEX_DEF_	DataDisplayBits *RDfirstip;		//����data��ʼָ��
	_KEYBOARDEX_DEF_	DataDisplayBits *RDfuncip;		//����data��ǰָ��
	_KEYBOARDEX_DEF_	DataDisplayBits *RSfuncip;		//��ʱָ��

	typedef struct	{
		DataDisplayBits SDFreqRef;		//SD00
		DataDisplayBits SDOutSpd;		//SD01
		DataDisplayBits SDSpdRef;		//SD02
		DataDisplayBits SDDCVolt;		//SD03
		DataDisplayBits SDOutLSpd;		//SD04
		DataDisplayBits SDLSpdRef;		//SD05
		DataDisplayBits SDPIDFB;		//SD06
		DataDisplayBits SDPIDRef;		//SD07
		DataDisplayBits SDAI1Volt;		//SD08
		DataDisplayBits SDAI2Volt;		//SD09
		DataDisplayBits SDAI3Volt;		//SD10
		DataDisplayBits SDDITermSts;		//SD11
	}sStopData;
	_KEYBOARDEX_DEF_	sStopData StopData;

	typedef struct	{
		DataDisplayBits RDOutFreq;		//RD00
		DataDisplayBits RDFreqRef;              //RD01
		DataDisplayBits RDOutCurr;              //RD02
		DataDisplayBits RDOutSpd;               //RD03
		DataDisplayBits RDSpdRef;               //RD04
		DataDisplayBits RDOutLSpd;              //RD05
		DataDisplayBits RDLSpdRef;              //RD06
		DataDisplayBits RDOutPower;             //RD07
		DataDisplayBits RDOutTorq;              //RD08
		DataDisplayBits RDOutVolt;              //RD09
		DataDisplayBits RDAI1Volt;              //RD10
		DataDisplayBits RDAI2Volt;              //RD11
		DataDisplayBits RDAI3Volt;		//RD12
		DataDisplayBits RDPIDFB;                //RD13
		DataDisplayBits RDPIDRef;               //RD14
		DataDisplayBits RDDITermSts;            //RD15
		DataDisplayBits RDDCVolt;               //RD16
	}sRunData;
	_KEYBOARDEX_DEF_	sRunData RunData;
/*******************************************************************************************/

	_KEYBOARDEX_DEF_	uint16 KeyValue;	//�����·���ֵ
							//Bit0	ENTER
							//Bit1	PANEL
							//Bit2	SHIFT
							//Bit3	UP
							//Bit4	JOG
							//Bit5	RUN
							//Bit6	DOWN
							//Bit7	STOP
							//Bit8	MENU/ESC
							
	_KEYBOARDEX_DEF_	uint16 curRunData;	//��ǰ��ʾ����Para
	_KEYBOARDEX_DEF_	uint16 curStopData;	//��ǰ��ʾͣ��Para
	_KEYBOARDEX_DEF_	uint16 LEDSeg[5];	//LED�ʶ���
	_KEYBOARDEX_DEF_	uint16 LCDSeg[4][21];
	_KEYBOARDEX_DEF_ 	uint16 M1Polars,M2Polars;
	/* ����Para*/
	typedef struct
	{
		uint bUserLock:1;			//=1 �趨���û�����
		uint bFactoryLock:1;			//=1 ��������������Ч
		uint bKeyLock:1;			//=1 ����������
		uint bErr:1;				//=1 �й���
		uint bErrFlag:1;			//=1 �����Ѵ��� 
		uint bParaInit:1;			//=1 �ָ�����para
		uint bLongTimeUp:1;			//=1 ��ʱ��Up
		uint bLongTimeDn:1;			//=1 ��ʱ��Down
		uint bParaUpload:1;			//=1 Para������
		uint bParaDnload:1;			//=1 Para������
		uint bPartDnload:1;			//=1 Para ���أ�except���para
		uint bParaDnOK:1;			//=1 Para ���ؽ���
		uint bParaCopyEnd:1;		//=1 Para ��������
		uint bTestMode:1;			//=1 in test mode 
		uint bAlarm:1;
		uint bMotorSwitch:1;			//=1 term func 88 select  2007.4.5 add
	}sKeyBoardPara;
	_KEYBOARDEX_DEF_	sKeyBoardPara uKeyPara;
	
	typedef struct
	{
		uint bFuncDebugLock:1;//���Թ����������־
		uint resv:15;
	}sKeyBoardPara1;
	_KEYBOARDEX_DEF_	sKeyBoardPara1 uKeyPara1;
	/* LED��*/
	typedef struct
	{
		uint bUnitH:1;			
		uint bUnitA:1;
		uint bUnitV:1;
		uint bUnitR:1;
		uint bUnitM:1;
		uint Rsv0507:3;
		uint bDirFWD:1;
		uint bDirREV:1;
		uint bMenuQuick:1;
		uint bMenuBasic:1;
		uint bAlarm:1;
		uint bRun:1;
		uint bPanel:1;
		uint btest:1;
	}sLEDLight;				//0��1��
	
	typedef union  
	{
		uint16     all;
		sLEDLight bit;
	}LEDLight;
	_KEYBOARDEX_DEF_	LEDLight unnLEDLight;
/*******************************************************************************************/
/*Function����*/
	_KEYBOARDEX_DEF_	void KBMange_step(void);
/*******************************************************************************************/
#endif	                         
