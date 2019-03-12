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
#include "ZbitVideoMergeAlg.h"


using namespace std;
using namespace cv;
using namespace cv::gpu;

#ifndef MEMORY_DELETE(x)
#define MEMORY_DELETE(x)  if(x) {delete x; x=NULL;}
#endif

#ifndef MEMORY_DELETE_EX(x)
#define MEMORY_DELETE_EX(x)  if(x){ delete[] x; x=NULL;}
#endif

#ifndef MEMORY_DELETE_FREE(x)
#define MEMORY_DELETE_FREE(x)  if(x){ free(x) ; x=NULL;}         //delete 内存数组
#endif

#ifndef     NULL
#define	    NULL    0
#endif

#define maxResolutionWith     4500
#define maxResolutionHigh     3000

#define ALG_VERSION "zbit & Dr-guo Team. Fuc[videomerge]  Ver[V1.0] "

#define BIG 1000000

FILE* pFileOut = fopen("stitch.yuv", "w+");



/*====================================================================
    函数名      :ZBIT_VM_init
    功能        :算法初始化
    输入参数说明:
    返回值说明  ：0 = 成功，其他= 失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
int ZBIT_VM_init()
{
	return 1;
}

/*====================================================================
    函数名      :ZBIT_VM_create
    功能        :创建处理通道
    输入参数说明:
    返回值说明  ：NULL == 失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
Video_Merge_Handler ZBIT_VM_create()
{
    ZbitVideoMerge *prtVideoMerge = new ZbitVideoMerge(1);
    if(prtVideoMerge == NULL)
    {
        return NULL;
    }
	
    return (Video_Merge_Handler)prtVideoMerge;
}


/*====================================================================
    函数名      :ZBIT_VM_setConfig
    功能        :处理通道的配置
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
int ZBIT_VM_setConfig(Video_Merge_Handler handid, PZBIT_VM_CONFIG inputCfg)
{
	int iRet = 0;
	
	if (NULL == handid)
	{
		return -1;
	}

	ZbitVideoMerge *prtVideoMerge = (ZbitVideoMerge *)handid;

	iRet = prtVideoMerge->SetConfig(inputCfg);
	if (0 <= iRet)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


/*====================================================================
    函数名      :ZBIT_VM_algProcess
    功能        :处理主函数
    输入参数说明:
    handid = 创建的句柄
    frameA  frameB  frameC frameD 对应的输入的不同点位的YUV帧
    inframeSize = 目前输入源的点位数目
    framOUT = 融合之后的一帧YUV
    返回值说明  ：0 = 表示成功，0 >  表示失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
int ZBIT_VM_algProcess(Video_Merge_Handler handid, 
		PZBIT_VM_FRAMEINFO IN frameA, 
		PZBIT_VM_FRAMEINFO IN frameB, 
		PZBIT_VM_FRAMEINFO IN frameC, 
		PZBIT_VM_FRAMEINFO IN frameD, 
		int IN inframeSize,
		PZBIT_VM_FRAMEINFO OUT framOUT )
{
	int iRet = 0;
	
	if (NULL == handid)
	{
		return -1;
	}

	ZbitVideoMerge *prtVideoMerge = (ZbitVideoMerge*)handid;

	iRet = prtVideoMerge->VideoProcess(
		frameA,
		frameB,
		frameC,
		frameD,
		inframeSize,
		framOUT);
	
	if (0 <= iRet)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


/*====================================================================
    函数名      :ZBIT_VM_delete
    功能        :删除处理通道
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
int ZBIT_VM_delete(Video_Merge_Handler handid)
{
	int iRet = 0;
	
	if (NULL == handid)
	{
		return -1;
	}
	else
	{
		MEMORY_DELETE(handid);
		return iRet;
	}
}


/*====================================================================
    函数名      :ZBIT_VM_uninit
    功能        :算法模块的资源释放
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
int ZBIT_VM_uninit()
{
	int iRet = 0;
	return iRet;
}

/*====================================================================
    函数名      :ZBIT_VM_uninit
    功能        :算法模块的资源释放
    输入参数说明:
    返回值说明  ：0 = 表示成功，0 >  表示失败
-------------------------------------------------------------------------------
修改记录:
日  期           版本        修改人      修改内容
9/8/2017           1.0              刘文         创建
******************************************************************************/
char * ZBIT_VM_getAlgVersion(char * verString, int len)
{
	int ifd = 0;
	char szVerBuild[128] = {0};
	char startTime[128] = {0};
	sprintf(szVerBuild, "%s Time[%s %s] ", ALG_VERSION, __TIME__, __DATE__);

	memcpy(verString, szVerBuild, strlen(szVerBuild));

	return verString;
}


ZbitVideoMerge::ZbitVideoMerge(int ichannleID)
{
	m_IchannleID = ichannleID;
	strinBufferA = NULL;
	strinBufferB = NULL;
	strinBufferC = NULL;
	strinBufferD = NULL;
	
	iFirstTime = 0;
	iMergeWidth = 0;
	iMergeHight = 0;
}


ZbitVideoMerge::~ZbitVideoMerge()
{

}

int ZbitVideoMerge::init()
{
	return 1;
}

int ZbitVideoMerge::SetConfig(PZBIT_VM_CONFIG inputCfg)
{
	m_InputCfg = inputCfg;
	return 0;
}



int ZbitVideoMerge::VideoProcess(
	PZBIT_VM_FRAMEINFO IN frameA,
	PZBIT_VM_FRAMEINFO IN frameB,
	PZBIT_VM_FRAMEINFO IN frameC,
	PZBIT_VM_FRAMEINFO IN frameD,
	int IN inframeSize,
	PZBIT_VM_FRAMEINFO OUT framOUT)
{
	if (2 == inframeSize)
	{
		if ((NULL == frameA) \
			|| (NULL == frameB))
		{
			printf("func[%s] Line[%d] input arge error \r\n", __FUNCTIONW__, __LINE__);
			return -1;
		}
	}

	if (3 == inframeSize)
	{
		if ((NULL == frameA) \
			|| (NULL == frameB) \
			|| (NULL == frameC))
		{
			printf("func[%s] Line[%d] input arge error \r\n", __FUNCTIONW__, __LINE__);
			return -1;
		}
	}

	if (4 == inframeSize)
	{
		if ((NULL == frameA) \
			|| (NULL == frameB) \
			|| (NULL == frameC) \
			|| (NULL == frameD))
		{
			printf("func[%s] Line[%d] input arge error \r\n", __FUNCTIONW__, __LINE__);
			return -1;
		}
	}

	int iWidth = m_InputCfg->m_iInputVideoWidth;
	int iHeigh = m_InputCfg->m_iInputVideoHeight;
	int iFrameSize = iWidth * iHeigh * 3 / 2;

	int Ysize = iWidth*iHeigh;
	int UVsize = (iWidth / 2) * (iHeigh / 2);

	cv::Mat yuvImg1;
	cv::Mat rgbImg1;
	if (NULL != frameA)
	{
		yuvImg1.create(iHeigh * 3 / 2, iWidth, CV_8UC1);
		memcpy(yuvImg1.data, frameA->ptrY, Ysize);
		memcpy(yuvImg1.data + Ysize, frameA->ptrU, UVsize);
		memcpy(yuvImg1.data + Ysize + UVsize, frameA->ptrV, UVsize);

		cv::cvtColor(yuvImg1, rgbImg1, CV_YUV2BGR_I420);
	}


	cv::Mat yuvImg2;
	cv::Mat rgbImg2;
	if (NULL != frameB)
	{
		yuvImg2.create(iHeigh * 3 / 2, iWidth, CV_8UC1);
		memcpy(yuvImg2.data, frameB->ptrY, Ysize);
		memcpy(yuvImg2.data + Ysize, frameB->ptrU, UVsize);
		memcpy(yuvImg2.data + Ysize + UVsize, frameB->ptrV, UVsize);

		cv::cvtColor(yuvImg2, rgbImg2, CV_YUV2BGR_I420);
	}

	if (NULL != frameC)
	{

	}

	if (NULL != frameD)
	{

	}

	//printf("file[%s] func:%s line:%d \r\n", __FILE__, __func__, __LINE__);

	/*如果判断第一次融合没有做，则继续做*/
	if (0 == iFirstTime)
	{
		printf("file[%s] func:%s line:%d \r\n", __FILE__, __FUNCTIONW__, __LINE__);
		/*因为发现第一次融合，只是获取到融合之后一帧的 宽 和 高， 那Later 融合函数，应该也能获取到宽和高*/
		Mat MergeRes = imageStitchForVideo(rgbImg1, rgbImg2);

		printf("file[%s] func:%s line:%d \r\n", __FILE__, __FUNCTIONW__, __LINE__);
		/*融合之后的第一帧图像 */
		iMergeHight = MergeRes.rows;//获取帧高度
		iMergeWidth = MergeRes.cols; //获取帧宽度 
		printf("func[%s] Line[%d] MergeResolution[%d * %d ] \r\n", __FUNCTIONW__, __LINE__, iMergeWidth, iMergeHight);
		framOUT->m_iWidth = iMergeWidth;
		framOUT->m_iHeight = iMergeHight;
		/*第一次融合之后，后续就不需要再判断了*/
		iFirstTime = 1;

		return 0;
	}

	//printf("file[%s] func:%s line:%d \r\n", __FILE__, __func__, __LINE__);

	/*因为发现第一次融合，只是获取到融合之后一帧的 宽 和 高， 那Later 融合函数，应该也能获取到宽和高*/
	Mat MergeRes = imageStitchForVideoLater(rgbImg1, rgbImg2);

	

	//printf("file[%s] func:%s line:%d \r\n", __FILE__, __func__, __LINE__);
	/*融合之后的第一帧图像 */
	int MergeframeH = iMergeHight;//获取帧高度
	int MergeframeW = iMergeWidth; //获取帧宽度 
	int MergeFrameSize = MergeframeH * MergeframeW;

	cv::Mat yuvImg;
	if (0 == (MergeframeW % 2))
	{
		cv::cvtColor(MergeRes, yuvImg, CV_BGR2YUV_I420);
	}
	else
	{
		cv::Mat yuvtemp;
		resize(MergeRes, yuvtemp, Size(MergeframeW + 1, MergeframeH), 0, 0, CV_INTER_LINEAR);
		framOUT->m_iWidth = MergeframeW + 1;
		MergeFrameSize = MergeframeH * (MergeframeW + 1);
		//printf("func[%s] Line[%d] MergeResolution[%d * %d ] \r\n", __func__, __LINE__, framOUT->m_iWidth, framOUT->m_iHeight);
		cv::cvtColor(yuvtemp, yuvImg, CV_BGR2YUV_I420);
	}

	if (NULL != framOUT)
	{
		/*把mat 融合之后的YUV 分别拷贝到输出framOUT 的 参数中*/
		//framOUT->m_iWidth = MergeframeW;
		//framOUT->m_iHeight = MergeframeH;

		

		memcpy(framOUT->ptrY, yuvImg.data, MergeFrameSize);
		memcpy(framOUT->ptrU, yuvImg.data + MergeFrameSize, MergeFrameSize / 4);
		memcpy(framOUT->ptrV, yuvImg.data + MergeFrameSize + MergeFrameSize / 4, MergeFrameSize / 4);


		//memcpy(pYuvBufs, yuvImg.data, bufLens*sizeof(unsigned char));
		//fwrite(pYuvBufs, bufLens*sizeof(unsigned char), 1, pFileOut);

		//memcpy(pYuvBufs, framOUT->ptrY, bufLens*sizeof(unsigned char));
		//fwrite(pYuvBufs, bufLens*sizeof(unsigned char), 1, pFileOut);

		//memcpy(pYuvBufsUV, framOUT->ptrU, bufLensUV*sizeof(unsigned char));
		//fwrite(pYuvBufsUV, bufLensUV*sizeof(unsigned char), 1, pFileOut);

		//memcpy(pYuvBufsUV, framOUT->ptrV, bufLensUV*sizeof(unsigned char));
		//fwrite(pYuvBufsUV, bufLensUV*sizeof(unsigned char), 1, pFileOut);
		fwrite(framOUT->ptrY, framOUT->m_iWidth * framOUT->m_iHeight, 1, pFileOut);
		fwrite(framOUT->ptrU, framOUT->m_iWidth * framOUT->m_iHeight / 4, 1, pFileOut);
		fwrite(framOUT->ptrV, framOUT->m_iWidth * framOUT->m_iHeight / 4, 1, pFileOut); 


	}

	return 0;
}



