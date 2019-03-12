//--------------------------------------------------------------------
// 上海增容数据科技有限公司
// 2017年4月7日
// 编制：刘文
// 审核：
// 修改记录：2017年4月7日
// 1)
//--------------------------------------------------------------------
// BUG 记录:
//
//--------------------------------------------------------------------

//
// TODO: 1) 完成命名，函数以及结构体的修改  解决
//      
//

#ifndef __VIDEO_MERGE_ALG_H__
#define __VIDEO_MERGE_ALG_H__

#ifdef WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif



#include "StitchAndSeam.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IN
#define OUT

#define Video_Merge_Handler void*

typedef struct zbit_vm_cfg
{
	int m_iInputVideoWidth;
	int m_iInputVideoHeight;
	int m_iVideoType;
	int m_iVideoFrameRate;
}ZBIT_VM_CONFIG, *PZBIT_VM_CONFIG;


typedef struct zbit_vm_frameinfo
{
	void *ptrY;
	void *ptrU;
	void *ptrV;
	int  m_iWidth;
	int  m_iHeight;
	int  m_iFrameRate;
	int  m_iFrameType;
	int  m_iSeq;
	int  m_iRes[64];
}ZBIT_VM_FRAMEINFO, *PZBIT_VM_FRAMEINFO;


class ZbitVideoMerge
{
public:
	ZbitVideoMerge(int ichannleID);
	virtual ~ZbitVideoMerge();

	int  init();

	int SetConfig(PZBIT_VM_CONFIG inputCfg);

	int VideoProcess(
		PZBIT_VM_FRAMEINFO IN frameA,
		PZBIT_VM_FRAMEINFO IN frameB,
		PZBIT_VM_FRAMEINFO IN frameC,
		PZBIT_VM_FRAMEINFO IN frameD,
		int IN inframeSize,
		PZBIT_VM_FRAMEINFO OUT framOUT);

public:
	int m_IchannleID;
	PZBIT_VM_CONFIG m_InputCfg;

	int iFirstTime;

	unsigned char *strinBufferA;
	unsigned char *strinBufferB;
	unsigned char *strinBufferC;
	unsigned char *strinBufferD;
	unsigned char *strOutBuffer;

	int iMergeWidth;/*第一次融合分析出来的图像宽*/
	int iMergeHight;/*第一次融合分析出来的图像高*/

};


//opencv 2.4.8   远景  近景两种场景模式

/*====================================================================
    函数名      :ZBIT_VM_init
    功能        :算法初始化
    输入参数说明:
    返回值说明  ：0 = 成功，其他= 失败
******************************************************************************/
int ZBIT_VM_init();

/*====================================================================
    函数名      :ZBIT_VM_create
    功能        :创建处理通道
    输入参数说明:
    返回值说明  ：NULL == 失败
******************************************************************************/
Video_Merge_Handler ZBIT_VM_create();


/*====================================================================
    函数名      :ZBIT_VM_setConfig
    功能        :处理通道的配置
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
******************************************************************************/
int ZBIT_VM_setConfig(Video_Merge_Handler handid, PZBIT_VM_CONFIG inputCfg);

/*====================================================================
    函数名      :ZBIT_VM_algProcess
    功能        :处理主函数
    输入参数说明:
    handid = 创建的句柄
    frameA  frameB  frameC frameD 对应的输入的不同点位的YUV帧
    inframeSize = 目前输入源的点位数目
    framOUT = 融合之后的一帧YUV
    返回值说明  ：0 = 表示成功，0 >  表示失败
******************************************************************************/
int ZBIT_VM_algProcess(Video_Merge_Handler handid, 
		PZBIT_VM_FRAMEINFO IN frameA, 
		PZBIT_VM_FRAMEINFO IN frameB, 
		PZBIT_VM_FRAMEINFO IN frameC, 
		PZBIT_VM_FRAMEINFO IN frameD, 
		int IN inframeSize,
		PZBIT_VM_FRAMEINFO OUT framOUT );

/*====================================================================
    函数名      :ZBIT_VM_delete
    功能        :删除处理通道
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
******************************************************************************/
int ZBIT_VM_delete(Video_Merge_Handler handid);

/*====================================================================
    函数名      :ZBIT_VM_uninit
    功能        :算法模块的资源释放
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
******************************************************************************/
int ZBIT_VM_uninit();

/*====================================================================
    函数名      :ZBIT_VM_getAlgVersion
    功能        : 获取算法模块的版本
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
******************************************************************************/
char * ZBIT_VM_getAlgVersion(char * verString, int len);
#ifdef __cplusplus
}
#endif // extern "C"

#endif
