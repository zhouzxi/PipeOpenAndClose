/**********************************************************************
* 版权所有 (C)2015, Zhou Zhaoxiong。
*
* 文件名称：PipeOpenAndClose.c
* 文件标识：无
* 内容摘要：测试popen和pclose的用法
* 其它说明：利用popen和pclose处理远端的文件
* 当前版本：V1.0
* 作    者：Zhou Zhaoxiong
* 完成日期：20151202
*
**********************************************************************/
#include <stdio.h>
#include <string.h>

// 重定义数据类型
typedef unsigned char  UINT8;
typedef signed   int   INT32;

// 函数声明
void DealRemoteFile(void);


/**********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号      修改人              修改内容
* ---------------------------------------------------------------
* 20151202        V1.0     Zhou Zhaoxiong          创建
***********************************************************************/
INT32 main()
{
    DealRemoteFile();
    
    return 0; 
}


/**********************************************************************
* 功能描述：处理远端的文件
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号      修改人              修改内容
* ---------------------------------------------------------------
* 20151202        V1.0     Zhou Zhaoxiong          创建
***********************************************************************/
void DealRemoteFile(void)
{
    UINT8  szCmdBuf[1024]    = {0};
    UINT8  szResultBuf[1024] = {0};
    FILE  *fpPipe            = NULL;
	
    snprintf(szCmdBuf, sizeof(szCmdBuf)-1, "(sleep 0.5; echo zhou; sleep 1; echo zhou; sleep 5; echo \"cd /home/zhou/zhouzx/Test;rm -rf TestFile.txt;\"; sleep 2) | telnet 10.10.10.10");
	
    printf("DealRemoteFile: Cmd is %s\n", szCmdBuf);
	
    fpPipe = popen(szCmdBuf, "r"); 
    if (NULL == fpPipe)
    {
        printf("DealRemoteFile: fpPipe is NULL!\n");
	return;
    }
	
    while (fgets(szResultBuf, sizeof(szResultBuf), fpPipe) != NULL)
    {
        if ('\n' == szResultBuf[strlen(szResultBuf)-1])    // 将换行符去掉
    	{  
    	    szResultBuf[strlen(szResultBuf)-1] = '\0';  
	}  
    }  
    
    pclose(fpPipe);    // 关闭管道
    fpPipe = NULL;
} 

