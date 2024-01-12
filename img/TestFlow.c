#include "SKF_Conf.h"
//extern u32 ThreadCout;
//extern u32 bMultipleApp;
//extern u8 szPin[6];
typedef struct TESTINFO
{
	DEVHANDLE hDev;
	HAPPLICATION hApp;
	HCONTAINER hCtn;
	char Pwd[6];
	u32 TestID;
	BOOL TestResult;
	DWORD ThreadId;
}TESTINFO;

volatile int TestResult;

u32 TestFlow()
{
	DEVHANDLE hDev = 0;
	u32 ret,TCout = 0,i;
	TESTINFO *TestItemInfo = NULL;

#ifdef _WIN32
	HAPPLICATION hApp = 0;
	HANDLE hThread[MAX_PATH];
#endif
	LOG("********************** TEST First ***********************\n");
	//支持多应用操作
	ret = OpenDev(&hDev,0);
	if (ret) goto End;

	if (TestItemList.b_Atuh)
	{
		ret = DevAuth_Test(hDev,TCout);
		if (ret) goto End;
	}

	if (bMultipleApp)
	{
		ret = APPControl(hDev,ThreadCout);
		if (ret) goto End;
	}

#ifdef _WIN32
	//若支持多应用，需在多线程测试各项前测试多应用的删减
	TestItemInfo = (TESTINFO *)malloc(sizeof(TESTINFO)*ThreadCout);		
	for (i=0;i<ThreadCout;i++)
	{
		TestItemInfo[i].hDev = hDev;
		TestItemInfo[i].TestID = i;
		//memset(TestItemInfo[i].Pwd,i,6);
		hThread[i] = CreateThread(NULL,0,TestThread,&TestItemInfo[i],0,NULL);
		Sleep(1000);
	}
	for (i=0;i<ThreadCout;i++)
	{
		DWORD m;
		while(1)
		{
			GetExitCodeThread(hThread[i],&m);
			if (m!=STILL_ACTIVE)
			{	
				TerminateThread(hThread[i],m);
				break;
			}
		}
	}
	for (i = 0;i<ThreadCout;i++)
	{
		if (TestItemInfo[i].TestResult)
			printf("Thread%d:****************** TEST OK ******************\n",TestItemInfo[i].ThreadId);
		else
			printf("Thread%d:****************** TEST Fail ******************\n",TestItemInfo[i].ThreadId);
	}
#else
		TestThread(hDev);
#endif

#if 0
		ret = OpenDev(&hDev,0);
		if (ret) goto End;	

		ret = DevAuth_Test(hDev,0);
		if (ret) goto End;
		////应用的测试
		ret = AppliCation_Test(hDev,"",szPin,0);
		//if(ret) goto err;
		
		ret = OpenApp(hDev,"",&hApp,szPin,0);

		FileInfo.hDev = CtnInfo.hDev = AlgInfo.hDev = hDev;
		FileInfo.hApp =  CtnInfo.hApp = AlgInfo.hApp = hApp;
		FileInfo.TestID = 0;
		CtnInfo.TestID = 1;
		AlgInfo.TestID = 2;
		//ret = File_Test(hDev,hApp,pwd,1);

		//ret = Contanier_Test(hDev,hApp,&)

		for (i=0;i<3;i++)
		{
			hThread[i] = CreateThread(NULL,0,TestFun_ID,(LPVOID),0,NULL);
		}
		hThread[0] = CreateThread(NULL,0,TestFun_ID,&FileInfo,0,NULL);
		//hThread[1] = CreateThread(NULL,0,TestFun_ID,&CtnInfo,0,NULL);
		//hThread[2] = CreateThread(NULL,0,TestFun_ID,&AlgInfo,0,NULL);
		for (i=0;i<1;i++)
		{
			DWORD m;
			while(1)
			{
				GetExitCodeThread(hThread[i],&m);
				if (m!=STILL_ACTIVE)
				{	
					break;
				}
			}
		}
#endif
End:
	if (hDev!= NULL)
	{	
		FunctionList->SKF_DisconnectDev(hDev);
	}
#ifdef _WIN32
	FreeLibrary(H_DLL);
#endif
	return ret;
}

#ifdef _WIN32
DWORD WINAPI TestThread(LPVOID param)
#else
DWORD TestThread(DEVHANDLE gDev)
#endif

{
	DEVHANDLE hDev;
	u32 ret,TCout;
	DWORD m = 0;
#ifdef _WIN32
	TESTINFO *testiteminfo = NULL;
	testiteminfo = (TESTINFO*)param;
	TCout = testiteminfo->TestID;
	hDev = testiteminfo->hDev;
	testiteminfo->ThreadId = GetCurrentThreadId();
#else
	hDev = gDev;
	TCout = 0;
#endif
	//搜索存在的设备并打开
	//ret = OpenDev(&hDev,TCout);
	//if (ret) goto err;

	//设备认证测试
	//if (TestItemList.b_Atuh)
	//{
		//ret = DevAuth_Test(hDev,TCout);
		//if (ret) goto err;
	//}
	
	//关于应用、文件、容器的测试
	if (TestItemList.b_App)
	{
		ret = App_File_Ctn_Test(hDev,TCout);
		if (ret) goto err;
	}

	if (TestItemList.b_Alg)
	{
		ret = Algorithm_Test(hDev,TCout);
		if (ret) goto err;
	}

#ifdef _WIN32
		testiteminfo->TestResult = TRUE;
#else
		LOG("****************** TEST OK ******************\n");
#endif
	return ret;

err:
#ifdef _WIN32
		testiteminfo->TestResult = FALSE;
#else
		LOG("****************** TEST Fail ******************\n");
#endif
	return ret;
}

#if 0
#ifdef _WIN32
DWORD WINAPI TestFun_ID(LPVOID param)
#else
DWORD TestFun_ID(int param)
#endif
{
	
	DEVHANDLE hDev;
	HAPPLICATION hApp;
	HCONTAINER hCtn;
	TESTINFO *TestInfo = (TESTINFO*)param;
	hDev = TestInfo->hDev;
	hApp = TestInfo->hApp;
	/*TESTINFO *TestInfomation = (TESTINFO*)param;
	hDev = TestInfomation->hDev;
	hApp = TestInfomation->hApp;
	hCtn = TestInfomation->hCtn;
	TestID = TestInfomation->TestID;*/
	//memcpy(pin,"111111",6);
	
	//OpenDev1(&hDev,TestID);
	/*FunctionList->SKF_LockDev(hDev,-1);
	OpenApp(hDev,"",&hApp,szPin,TestInfo->TestID);
	FunctionList->SKF_UnlockDev(hDev);*/
	switch (TestInfo->TestID)
	{
	case 0:
		File_Test(hDev,hApp,szPin,TestInfo->TestID);
		break;
	case 1:
		Contanier_Test(hDev,hApp,&hCtn,TestInfo->TestID);
		break;
	case 2:
		Algorithm_Test(hDev,TestInfo->TestID);
		break;
	}
	//free(TestInfomation);
	return 0;
}

#endif

u32 App_File_Ctn_Test(DEVHANDLE hDev,u32 TCout)
{
	HCONTAINER		hCtn = 0;
	HAPPLICATION	hApp = 0;
	u32 ret;
	char appname[260];
	char pin[6];
	memset(appname,0,sizeof(appname));
	if (bMultipleApp !=0)
	{
		sprintf(pin,"111111");
		//sprintf(pin,"%d%d%d%d%d%d",TCout,TCout,TCout,TCout,TCout,TCout);
		sprintf(appname,"TestApp%d",TCout);
	}
	else
	{
		memset(pin,'1',6);
		sprintf(appname,"");
	}
	
	//应用的测试
	ret = AppliCation_Test(hDev,appname,&hApp,pin,TCout);
	if(ret) goto End;

	//获取用于操作的应用
	if (TestItemList.b_Pin)
	{
		ret = Pin_Test(hDev,hApp,pin,TCout);
		if(ret) goto End;
	}

	//容器测试
	if (TestItemList.b_Ctn)
	{
		ret = Contanier_Test(hDev,hApp,&hCtn,TCout);
		if (ret) goto End;
	}
	//文件的测试
	if (TestItemList.b_File)
	{
		ret = File_Test(hDev,hApp,pin,TCout);
		if(ret) goto End;
	}
End:
	//ret = FunctionList->SKF_DeleteApplication(hDev, appname);
	if (hCtn!=NULL)
	{
		FunctionList->SKF_CloseContainer(hCtn);
	}
	if (hApp!=NULL)
	{
		FunctionList->SKF_CloseApplication(hApp);
	}
	return ret;
}
u32 Algorithm_Test(DEVHANDLE hDev,u32 TCout)
{
	u32 ret;
	if (TestItemList.b_Hash)
	{
		if (TestItemList.b_Sha1)
		{
			ret = Digest_Test(hDev,SGD_SHA1,TCout);
			if(ret) return ret;
		}
		if (TestItemList.b_Sha256)
		{
			ret = Digest_Test(hDev,SGD_SHA256,TCout);
			if(ret) return ret;
		}
		if (TestItemList.b_Sha512)
		{
			//ret = Digest_Test(hDev,SGD_SHA512,TCout);
			//if(ret) return ret;
		}
		if (TestItemList.b_SM3)
		{
			ret = Digest_Test(hDev,SGD_SM3,TCout);
			if(ret) return ret;
		}
	}

	if (TestItemList.b_SM1)
	{
		ret = Encrtpy_Test(hDev,SGD_SM1_ECB,TCout);
		if(ret) return ret;
		ret = Encrtpy_Test(hDev,SGD_SM1_CBC,TCout);
		if(ret) return ret;

		ret = Cipher_Test(hDev,SGD_SM1_ECB,TCout);
		if(ret) return ret;
		ret = Cipher_Test(hDev,SGD_SM1_CBC,TCout);
		if(ret) return ret;

		ret = Mac_Test(hDev,SGD_SM1_MAC,TCout);
		if(ret) return ret;
	}
	
	if (TestItemList.b_SMS4)
	{
		//ret = Encrtpy_Test(hDev,SGD_SMS4_ECB,TCout);
		//if(ret) return ret;
		//ret = Encrtpy_Test(hDev,SGD_SMS4_CBC,TCout);
		if(ret) return ret;

		ret = Cipher_Test(hDev,SGD_SMS4_ECB,TCout);
		if(ret) return ret;
		ret = Cipher_Test(hDev,SGD_SMS4_CBC,TCout);
		if(ret) return ret;

		ret = Mac_Test(hDev,SGD_SMS4_MAC,TCout);
		if(ret) return ret;
	}

	if (TestItemList.b_SSF33)
	{
		ret = Encrtpy_Test(hDev,SGD_SSF33_ECB,TCout);
		if(ret) return ret;
		//not support
		//ret = Encrtpy_Test(hDev,SGD_SSF33_CBC,TCout);
		//if(ret) return ret;

		ret = Cipher_Test(hDev,SGD_SSF33_ECB,TCout);
		if(ret) return ret;
		//ret = Cipher_Test(hDev,SGD_SSF33_CBC,TCout);
		//if(ret) return ret;

		ret = Mac_Test(hDev,SGD_SSF33_MAC,TCout);
		if(ret) return ret;
	}

	if(TestItemList.b_SM6)
	{
		//ret = Encrtpy_Test(hDev,SGD_SM6_ECB,TCout);
		//if(ret) return ret;
		//not support
		//ret = Encrtpy_Test(hDev,SGD_SM6_CBC,TCout);
		//if(ret) return ret;

		//ret = Cipher_Test(hDev,SGD_SM6_ECB,TCout);
		//if(ret) return ret;
		//ret = Cipher_Test(hDev,SGD_SM6_CBC,TCout);
		//if(ret) return ret;

		//ret = Mac_Test(hDev,SGD_SM6_MAC,TCout);
		//if(ret) return ret;
	}

	if (TestItemList.b_DES)
	{
		ret = Encrtpy_Test(hDev,SGD_DES_ECB,TCout);
		if(ret) return ret;
		ret = Encrtpy_Test(hDev,SGD_DES_CBC,TCout);
		if(ret) return ret;

		ret = Cipher_Test(hDev,SGD_DES_ECB,TCout);
		if(ret) return ret;
		ret = Cipher_Test(hDev,SGD_DES_CBC,TCout);
		if(ret) return ret;

		ret = Mac_Test(hDev,SGD_DES_MAC,TCout);
		if(ret) return ret;
	}


	if (TestItemList.b_AES)
	{
		ret = Encrtpy_Test(hDev,SGD_AES_ECB,TCout);
		if(ret) return ret;
		//not support
		//ret = Encrtpy_Test(hDev,SGD_AES_CBC,TCout);
		//if(ret) return ret;
		
		ret = Cipher_Test(hDev,SGD_AES_ECB,TCout);
		if(ret) return ret;
		//ret = Cipher_Test(hDev,SGD_AES_CBC,TCout);
		//if(ret) return ret;

		//not support
		//ret = Mac_Test(hDev,SGD_AES_MAC,TCout);
		//if(ret) return ret;
	}
	return ret;
}


