/*************************************************************
 *				福建省数字安全证书管理有限公司				 * 
 *					 数字证书接口函数说明					 * 
 *				   适用操作系统:Windows环境					 *
 *************************************************************/
#ifndef _LCardCERT_H_
#define _LCardCERT_H_

#define IN
#define OUT

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <middleware/gm_api/skfapi.h>


#ifndef FJCA_COMMON_DEFINE
#define FJCA_COMMON_DEFINE

//#define calg_md2	1
//#define calg_md4	2
#define calg_md5	3
#define calg_sha1	4
#define calg_sm3	5
#define calg_sha256	6

//typedef HANDLE		DEVHANDLE;

/*
*临界值定义
*/
//#define MAX_IV_LEN			32		//初始化向量的最大长度
//#define	MAX_FILE_NAME_LEN	32		//文件名最大长度
//#define MAX_CONTAINER_NAME_LEN	128	//容器名最大长度

/*
 *算法标识符
 */
// #define SGD_SM1_ECB		0x00000101	//SM1算法ECB加密模式
// #define SGD_SM1_CBC		0x00000102	//SM1算法CBC加密模式
// #define SGD_SM1_CFB		0x00000104	//SM1算法CFB加密模式
// #define SGD_SM1_OFB		0x00000108	//SM1算法OFB加密模式
// #define SGD_SM1_MAC		0x00000110	//SM1算法MAC运算
// #define SGD_SSF33_ECB	0x00000201	//SSF33算法ECB加密模式
// #define SGD_SSF33_CBC	0x00000202	//SSF33算法CBC加密模式
// #define SGD_SSF33_CFB	0x00000204	//SSF33算法CFB加密模式
// #define SGD_SSF33_OFB	0x00000208	//SSF33算法OFB加密模式
// #define SGD_SSF33_MAC	0x00000210	//SSF33算法MAC运算
// #define SGD_SMS4_ECB	0x00000401	//SMS4算法ECB加密模式
// #define SGD_SMS4_CBC	0x00000402	//SMS4算法CBC加密模式
// #define SGD_SMS4_CFB	0x00000404	//SMS4算法CFB加密模式
// #define SGD_SMS4_OFB	0x00000408	//SMS4算法OFB加密模式
// #define SGD_SMS4_MAC	0x00000410	//SMS4算法MAC运算
/*	0x00000400-0x800000xx	为其它分组密码算法预留	*/

// #define SGD_RSA			0x00010000	//RSA算法
// #define SGD_SM2_1		0x00020100	//椭圆曲线签名算法
// #define SGD_SM2_2		0x00020200	//椭圆曲线密钥交换协议
// #define SGD_SM2_3		0x00020400	//椭圆曲线加密算法
/*	0x00000400～0x800000xx	为其它非对称密码算法预留	*/

// #define SGD_SM3			0x00000001	//SM3杂凑算法
// #define SGD_SHA1		0x00000002	//SHA1杂凑算法
// #define SGD_SHA256		0x00000004	//SHA256杂凑算法
/*	0x00000010～0x000000FF	为其它密码杂凑算法预留	*/

/*
 *权限类型
 */
// #define SECURE_NEVER_ACCOUNT	0x00000000		//不允许
// #define SECURE_ADM_ACCOUNT		0x00000001		//管理员权限
// #define SECURE_USER_ACCOUNT		0x00000010		//用户权限
// #define SECURE_EVERYONE_ACCOUNT	0x000000FF		//任何人

#pragma pack(1)

/*
 *分组密码参数
 */
// typedef struct Struct_BLOCKCIPHERPARAM{
// 	BYTE	IV[MAX_IV_LEN];			//初始向量，MAX_IV_LEN为初始向量的最大长度
// 	ULONG	IVLen;					//初始向量实际长度，按字节计算
// 	ULONG	PaddingType;			//填充方式，0表示不填充，1表示按照PKCS#5方式进行填充
// 	ULONG	FeedBitLen;				//反馈值的位长度，按字节计算，只针对OFB、CFB模式
// } BLOCKCIPHERPARAM, *PBLOCKCIPHERPARAM;

/*
 *文件属性
 */
// typedef struct Struct_FILEATTRIBUTE{
// 	CHAR	FileName[32];			//文件名
// 	ULONG	FileSize;				//文件大小
// 	ULONG	ReadRights;				//读权限
// 	ULONG	WriteRights;			//写权限
// } FILEATTRIBUTE, *PFILEATTRIBUTE;

#pragma pack()

#endif

#ifdef __cplusplus
extern "C"{
#endif

/************************************************************************/
/*	1. 设备管理 														*/
/*	LCardGetDevState													*/
/*	InitLCard															*/
/*	ExitLCard															*/
/*	LCardGetDeviceInfo													*/
/*	LCardGetRandom														*/
/************************************************************************/

/*
 *	返回设备状态值。
 *	dwStateLen	设备状态值的长度
 *	pbState 	设备状态值
 *	备注:
		插入的Key序号（索引号）从0开始依次增加。
		若有Key被拔出，其序号空闲。
		新插入的Key使用空闲序号。若没有空闲序号，则使用新的序号。
		若Key未拔出，其序号始终保持不变。
 		举例如下：
 		若dwStateLen ＝ 8，
 		插入三个Key，序号依次为0、1、2，该函数返回时：
 			pbState[0] = 0x31;
 			pbState[1] = 0x31;
 			pbState[2] = 0x31;
 			pbState[3] = 0x0;
 			pbState[4] = 0x0;
 			pbState[5] = 0x0;
 			pbState[6] = 0x0;
 			pbState[7] = 0x0;
		新插入一个Key，则其序号为3，该函数返回时：
  			pbState[0] = 0x31;
 			pbState[1] = 0x31;
 			pbState[2] = 0x31;
 			pbState[3] = 0x31;
 			pbState[4] = 0x0;
 			pbState[5] = 0x0;
 			pbState[6] = 0x0;
 			pbState[7] = 0x0;
		拔出第二、三个Key（序号为1、2），该函数返回时：
 			pbState[0] = 0x31;
 			pbState[1] = 0x0;
 			pbState[2] = 0x0;
 			pbState[3] = 0x31;
 			pbState[4] = 0x0;
 			pbState[5] = 0x0;
 			pbState[6] = 0x0;
 			pbState[7] = 0x0;
		新插入一个Key，则其序号为1，该函数返回时：
 			pbState[0] = 0x31;
 			pbState[1] = 0x31;
 			pbState[2] = 0x0;
 			pbState[3] = 0x31;
 			pbState[4] = 0x0;
 			pbState[5] = 0x0;
 			pbState[6] = 0x0;
 			pbState[7] = 0x0;
 */
BOOL LCardGetDevState(
	IN DWORD	dwStateLen,
	OUT BYTE	*pbState
	);

/*
 *	连接设备，返回设备的句柄。
 *	szDevName		对于USB读写器和Key可指定要打开的智能卡读写设备
 					szDevName为USB1、USB2 ...
 					USBX，X为Key序号加1，先插入的设备为USB1，后插入的为USB2
 *	phDev			返回设备操作句柄
 */
BOOL InitLCard(
	IN char			*szDevName = "USB1",
	OUT DEVHANDLE	*phDev = NULL
	);

/*
 *	断开一个已经连接的设备，并释放句柄。
 *	hDev			连接设备时返回的设备句柄
 */
BOOL ExitLCard(
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	取设备信息。
 *	szDeviceInfo	设备的详细信息。若无，可返回空串
 *	szVID			Vender ID，即厂商编号，长度4字节。如："D6A3"
 *	szPID			Product ID，即产品编号，长度4字节。如："2599"
 *	szSN			Serial Number，即产品唯一序列号。如："03081612130000001895"
 *	szPD			Produce Date，即生产日期，长度8字节。如："20061213"
 *	szPI			附加信息。若无，可返回空串
 *	szAF			预留。若无，可返回空串
 *	szLabel 		标签
 *	pdwTotalSpace	设备存储空间
 *	pdwFreeSpace	设备剩余空间
 *	hDev			连接设备时返回的设备句柄
 *	备注：			返回的各个字符串参数必须只包含可打印字符。
 					厂家应保证，对每个Key，pszVID、pszPID、pszSN这3个串相连的结果是唯一的。
 */
BOOL LCardGetDeviceInfo(
	OUT char		*szDeviceInfo,
	OUT char		*szVID,
	OUT char		*szPID,
	OUT char		*szSN,
	OUT char		*szPD,
	OUT char		*szPI,
	OUT char		*szAF,
	OUT char		*szLabel,
	OUT DWORD		*pdwTotalSpace,
	OUT DWORD		*pdwFreeSpace,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	产生随机数。
 *	dwRandomDataLen		随机数的长度
 *	pbRandomData		随机数
 *	hDev				连接设备时返回的设备句柄
 */
BOOL LCardGetRandom(
	IN DWORD		dwRandomDataLen,
	OUT BYTE		*pbRandomData,
	IN DEVHANDLE	hDev = NULL
	);

/************************************************************************/
/*	2. 访问控制 														*/
/*	LCardInitKey														*/
/*	LCardVerifyUserPin													*/
/*	LCardVerifyAdminPin 												*/
/*	LCardChangeUserPin													*/
/*	LCardChangeAdminPin 												*/
/*	LCardUnlockPin														*/
/************************************************************************/

/*
 *	初始化Key。
 *	pbUserPin				用户口令
 *	byUserPinLen			用户口令的长度
 *	dwUserPinMaxRetryCount	用户口令最大重试次数
 *	pbAdminPin				管理员口令
 *	byAdminPinLen			管理员口令的长度
 *	dwAdminPinMaxRetryCount 管理员口令最大重试次数
 *	hDev					连接设备时返回的设备句柄
 */
BOOL LCardInitKey(
	IN BYTE					*pbUserPin,
	IN BYTE					byUserPinLen,
	IN DWORD				dwUserPinMaxRetryCount,
	IN BYTE					*pbAdminPin,
	IN BYTE					byAdminPinLen,
	IN DWORD				dwAdminPinMaxRetryCount,
	IN DEVHANDLE			hDev = NULL
	);

/*
 *	核对用户口令。
 *	pbUserPin		用户口令
 *	byUserPinLen	用户口令的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			若校验口令失败，请在函数返回前调用SetLastError设置错误码：
 						0x6983		Key已被锁定
 						0x63CX		X为Key口令还可尝试次数
 */
BOOL LCardVerifyUserPin(
	IN BYTE			*pbUserPin,
	IN BYTE			byUserPinLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	核对管理员口令。
 *	pbAdminPin		管理员口令
 *	byAdminPinLen	管理员口令的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			若校验口令失败，请在函数返回前调用SetLastError设置错误码：
 						0x6983		Key已被锁定
 						0x63CX		X为Key口令还可尝试次数
 */
BOOL LCardVerifyAdminPin(
	IN BYTE			*pbAdminPin,
	IN BYTE			byAdminPinLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	核对并修改用户口令。
 *	pbOldUserPin	旧用户口令
 *	byOldUserPinLen 旧用户口令的长度
 *	pbNewUserPin	新用户口令
 *	byNewUserPinLen 新用户口令的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			若校验口令失败，请在函数返回前调用SetLastError设置错误码：
 						0x6983		Key已被锁定
 						0x63CX		X为Key口令还可尝试次数
 */
BOOL LCardChangeUserPin(
	IN BYTE			*pbOldUserPin,
	IN BYTE			byOldUserPinLen,
	IN BYTE			*pbNewUserPin,
	IN BYTE			byNewUserPinLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	核对并修改管理员口令。
 *	pbOldAdminPin		旧管理员口令
 *	byOldAdminPinLen	旧管理员口令的长度
 *	pbNewAdminPin		新管理员口令
 *	byNewAdminPinLen	新管理员口令的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				若校验口令失败，请在函数返回前调用SetLastError设置错误码：
 							0x6983		Key已被锁定
 							0x63CX		X为Key口令还可尝试次数
 */
BOOL LCardChangeAdminPin(
	IN BYTE				*pbOldAdminPin,
	IN BYTE				byOldAdminPinLen,
	IN BYTE				*pbNewAdminPin,
	IN BYTE				byNewAdminPinLen,
	IN DEVHANDLE		hDev = NULL
	);

/*
 *	当用户口令锁死后，通过调用该函数来解锁用户口令。
 	解锁后，用户口令被设置成新值，用户口令的重试次数也恢复到原值。
 *	pbAdminPin		管理员口令
 *	byAdminPinLen	管理员口令的长度
 *	pbNewUserPin	新用户口令
 *	byNewUserPinLen 新用户口令的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			若校验口令失败，请在函数返回前调用SetLastError设置错误码：
 						0x6983		Key已被锁定
 						0x63CX		X为Key口令还可尝试次数
 */
BOOL LCardUnlockPin(
	IN BYTE			*pbAdminPin,
	IN BYTE			byAdminPinLen,
	IN BYTE			*pbNewUserPin,
	IN BYTE			byNewUserPinLen,
	IN DEVHANDLE	hDev = NULL
	);

/************************************************************************/
/*	4. 证书操作 														*/
/*	LCardGetCertNo														*/
/*	LCardSetCertNo														*/
/*	LCardReadCert 														*/
/*	LCardWriteCert														*/
/*	LCardGetContainerName												*/
/*	LCardSetupIECert													*/
/************************************************************************/

/*
 *	返回卡内存放的证书状态:
 		0			卡内无证书
 		1			卡内存在第一张证书 
 		2			卡内存在第二张证书	 
 		3			卡内存在二张证书
 *	pbCertNo		证书状态
 *	hDev			连接设备时返回的设备句柄
 */
BOOL LCardGetCertNo(
	OUT BYTE		*pbCertNo,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	选择当前操作的证书，隐含为第一张证书。
 *	byCertNo		证书号（1-2）
 					当Key内存放双证书时，第一张证书为签名证书，第二张证书为加密证书。
 *	hDev			连接设备时返回的设备句柄
 */
BOOL LCardSetCertNo(
	IN BYTE			byCertNo,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	从智能卡或Key中读取当前证书（DER编码）。
 *	pbCert			证书数据
 *	pdwCertLen		输入为证书数据缓冲区的长度，输出为实际证书数据的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardReadCert(
	OUT BYTE		*pbCert,
	IN OUT DWORD	*pdwCertLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	把DER编码的证书写入智能卡或Key中。
 *	pbCert			证书数据
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardWriteCert(
	IN BYTE			*pbCert,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	取当前证书所在容器的名称。
 *	szContainerName	证书容器名称
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardGetContainerName(
	OUT char		*szContainerName,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	当有Key插入时，弹出口令框提示用户输入口令。若口令校验成功，Key内证书自动注册到IE。
 *	当有Key拔出时，Key内证书从IE中删除。
 *	pnKeyStatus		Key的状态
 *	pnKeyIndex		Key的序号，从0开始
 *	pbOperation		是否有证书操作
 *	pszPin			用户输入的口令
 *	备注：
 *		调用者在WM_DEVICECHANGE消息处理函数中调用LCardSetupIECert。
 *		如果插拔的不是本厂家Key，*pnKeyStatus = 0
 *		如果有本厂家Key插入，*pnKeyStatus = 1，*pnKeyIndex存放Key的序号。
 *			如果用户证书被导入IE，*pbOperation = TRUE, pszPin存放用户输入的口令。
 *		如果有本厂家Key拔出，*pnKeyStatus = 2，*pnKeyIndex存放Key的序号。
 *			如果用户证书从IE中删除，*pbOperation = TRUE。
 */
BOOL LCardSetupIECert(
	OUT int			*pnKeyStatus,
	OUT int			*pnKeyIndex,
	OUT BOOL		*pbOperation,
	OUT char		*pszPin
	);

/************************************************************************/
/*	5. RSA运算	 														*/
/*	LCardGenRSAKey														*/
/*	LCardGetPubKey														*/
/*	LCardImportRSAKey													*/
/*	LCardSign 															*/
/*	LCardSignDigest														*/
/*	LCardVerifyDigest													*/
/*	LCardRSAEncrypt														*/
/*	LCardRSADecrypt 													*/
/************************************************************************/

/*
 *	生成RSA密钥对，并输出公钥（DER编码）。
 *	pbPubKey		公钥数据
 *	pdwPubKeyLen	输入为公钥数据缓冲区的长度，输出为实际公钥数据的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardSetCertNo选择当前操作的证书。
 */
//BOOL LCardGenRSAKey(
//	OUT BYTE		*pbPubKey,
//	IN OUT DWORD	*pdwPubKeyLen,
//	IN DEVHANDLE	hDev = NULL
//	);

/*
 *	读RSA公钥数据（DER编码）。
 *	pbPubKey		公钥数据
 *	pdwPubKeyLen	输入为公钥数据缓冲区的长度，输出为实际公钥数据的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardGetPubKey(
	OUT BYTE		*pbPubKey,
	IN OUT DWORD	*pdwPubKeyLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	导入RSA解密私钥。
 *	pbPriKey		使用对称密钥保护的RSA解密私钥
 *	dwPriKeyLen		使用对称密钥保护的RSA解密私钥的长度
 *	pbSymmKey		使用签名公钥保护的对称密钥
 *	dwSymmKeyLen	使用签名公钥保护的对称密钥的长度
 *	dwSymmAlgID		对称算法
 *	hDev			连接设备时返回的设备句柄
 */
//BOOL LCardImportRSAKey(
//	IN BYTE			*pbPriKey,
//	IN DWORD		dwPriKeyLen,
//	IN BYTE			*pbSymmKey,
//	IN DWORD		dwSymmKeyLen,
//	IN DWORD		dwSymmAlgID,
//	IN DEVHANDLE	hDev = NULL
//	);

/*
 *	用RSA私钥对数据进行加密。
 *	pbData				待加密数据
 *	dwDataLen			待加密数据的长度
 *	pbSignedData		加密数据
 *	pdwSignedDataLen	输入为加密数据缓冲区的长度，输出为实际加密数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardSign(
	IN BYTE				*pbData,
	IN DWORD			dwDataLen,
	OUT BYTE			*pbSignedData,
	IN OUT DWORD		*pdwSignedDataLen,
	IN DEVHANDLE		hDev = NULL
	);

/*
 *	用RSA私钥对数据进行签名。
 *	pbData				待签名数据
 *	dwDataLen			待签名数据的长度
 *	byHashAlgID			摘要算法
 *	pbSignedData		签名数据
 *	pdwSignedDataLen	输入为签名数据缓冲区的长度，输出为实际签名数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardSignDigest(
	IN BYTE				*pbData,
	IN DWORD			dwDataLen,
	IN BYTE				byHashAlgID,
	OUT BYTE			*pbSignedData,
	IN OUT DWORD		*pdwSignedDataLen,
	IN DEVHANDLE		hDev = NULL
	);

/*
 *	验证RSA数据签名。
 *	pbSignedData	签名数据
 *	dwSignedDataLen	签名数据的长度
 *	byHashAlgID		摘要算法
 *	pbData			待签名数据
 *	dwDataLen		待签名数据的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardVerifyDigest(
	IN BYTE			*pbSignedData,
	IN DWORD		dwSignedDataLen,
	IN BYTE			byHashAlgID,
	IN BYTE			*pbData,
	IN DWORD		dwDataLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	RSA数据加密。
 *	pbData				待加密数据
 *	dwDataLen			待加密数据的长度
 *	pbEncryptedData		加密数据
 *	pdwEncryptedDataLen	输入为加密数据缓冲区的长度，输出为实际加密数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardRSAEncrypt(
	IN BYTE				*pbData,
	IN DWORD			dwDataLen,
	OUT BYTE			*pbEncryptedData,
	IN OUT DWORD		*pdwEncryptedDataLen,
	IN DEVHANDLE		hDev = NULL
	);

/*
 *	用RSA私钥对数据进行解密。
 *	pbEncryptedData		已加密数据
 *	dwEncryptedDataLen	已加密数据的长度
 *	pbDecryptedData		解密数据
 *	pdwDecryptedDataLen	输入为解密数据缓冲区的长度，输出为实际解密数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardSetCertNo选择当前操作的证书。
 */
BOOL LCardRSADecrypt(
	IN BYTE				*pbEncryptedData,
	IN DWORD			dwEncryptedDataLen,
	OUT BYTE			*pbDecryptedData,
	IN OUT DWORD		*pdwDecryptedDataLen,
	IN DEVHANDLE		hDev = NULL
	);



/************************************************************************/
/*	8. ECC证书操作 														*/
/*	LCardECCGetCertNo													*/
/*	LCardECCSetCertNo													*/
/*	LCardECCReadCert 													*/
/*	LCardECCWriteCert													*/
/*	LCardECCGetContainerName											*/
/*	LCardECCSetupIECert		//这先不用实现								*/
/************************************************************************/

/*
 *	返回卡内存放的证书状态:
 		0			卡内无证书
 		1			卡内存在第一张证书 
 		2			卡内存在第二张证书	 
 		3			卡内存在二张证书
 *	pbCertNo		证书状态
 *	hDev			连接设备时返回的设备句柄
 */
BOOL LCardECCGetCertNo(
	OUT BYTE		*pbCertNo,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	选择当前操作的证书，隐含为第一张证书。
 *	byCertNo		证书号（1-2）
 					当Key内存放双证书时，第一张证书为签名证书，第二张证书为加密证书。
 *	hDev			连接设备时返回的设备句柄
 */
BOOL LCardECCSetCertNo(
	IN BYTE			byCertNo,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	从智能卡或Key中读取当前证书（DER编码）。
 *	pbCert			证书数据
 *	pdwCertLen		输入为证书数据缓冲区的长度，输出为实际证书数据的长度
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCReadCert(
	OUT BYTE		*pbCert,
	IN OUT DWORD	*pdwCertLen,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	把DER编码的证书写入智能卡或Key中。
 *	pbCert			证书数据
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCWriteCert(
	IN BYTE			*pbCert,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	取当前证书所在容器的名称。
 *	szContainerName	证书容器名称
 *	hDev			连接设备时返回的设备句柄
 *	备注：			请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCGetContainerName(
	OUT char		*szContainerName,
	IN DEVHANDLE	hDev = NULL
	);

/*
 *	当有Key插入时，弹出口令框提示用户输入口令。若口令校验成功，Key内证书自动注册到IE。
 *	当有Key拔出时，Key内证书从IE中删除。
 *	pnKeyStatus		Key的状态
 *	pnKeyIndex		Key的序号，从0开始
 *	pbOperation		是否有证书操作
 *	pszPin			用户输入的口令
 *	备注：
 *		调用者在WM_DEVICECHANGE消息处理函数中调用LCardECCSetupIECert。
 *		如果插拔的不是本厂家Key，*pnKeyStatus = 0
 *		如果有本厂家Key插入，*pnKeyStatus = 1，*pnKeyIndex存放Key的序号。
 *			如果用户证书被导入IE，*pbOperation = TRUE, pszPin存放用户输入的口令。
 *		如果有本厂家Key拔出，*pnKeyStatus = 2，*pnKeyIndex存放Key的序号。
 *			如果用户证书从IE中删除，*pbOperation = TRUE。
 */
BOOL LCardECCSetupIECert(
	OUT int			*pnKeyStatus,
	OUT int			*pnKeyIndex,
	OUT BOOL		*pbOperation,
	OUT char		*pszPin
	);

/************************************************************************/
/*	9. ECC运算															*/
/*	LCardECCGenKey														*/
/*	LCardECCGetPubKey													*/
/*	LCardECCImportKey													*/
/*	LCardECCSign														*/
/*	LCardExtECCVerify	//外部不重要											*/
/*	LCardECCSignDigest													*/
/*	LCardExtECCVerifyDigest	//外部不重要											*/
/*	LCardExtECCEncrypt 	//外部不重要                                                                             */
/*	LCardECCDecrypt 													*/
/*	LCardECCGetTempPubKey												*/
/*	LCardECCKeyExchange 	//不需要											*/
/************************************************************************/
//	备注：
//	x||y：x与y的拼接

/*
 *	产生ECC密钥对，并输出公钥。
 *	pbECCPubKey 		公钥数据，格式：x||y
 *	pdwECCPubKeyLen 	输入为公钥数据缓冲区的长度，输出为实际公钥数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardECCSetCertNo选择当前操作的证书。
 */
//BOOL LCardECCGenKey(
//	OUT BYTE			*pbECCPubKey,
//	IN OUT DWORD		*pdwECCPubKeyLen,
//	IN DEVHANDLE		hDev = NULL
//	);

/*
 *	读ECC公钥数据。
 *	pbECCPubKey 		公钥数据，格式：x||y
 *	pdwECCPubKeyLen 	输入为公钥数据缓冲区的长度，输出为实际公钥数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCGetPubKey(
	OUT BYTE			*pbECCPubKey,
	IN OUT DWORD		*pdwECCPubKeyLen,
	IN DEVHANDLE		hDev = NULL
	);


/*
 *	用ECC密钥对数据签名。
 *	pbData				待签名数据，必须为32字节
 *	dwDataLen			待签名数据的长度
 *	pbSignedData		签名数据，格式：r||s
 *	pdwSignedDataLen	输入为签名数据缓冲区的长度，输出为实际签名数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCSign(
	IN BYTE 			*pbData,
	IN DWORD			dwDataLen,
	OUT BYTE			*pbSignedData,
	IN OUT DWORD		*pdwSignedDataLen,
	IN DEVHANDLE		hDev = NULL
	);



/*
 *	用ECC密钥对数据签名。
 *	pbData				待签名数据
 *	dwDataLen			待签名数据的长度
 *	byHashAlgID 		摘要算法
						当byHashAlgID为SM3且dwUserIDLen不为0的情况下pbUserID有效
						此时执行SM2算法签名预处理1、预处理2操作
 *	pbUserID			用户ID
 *	dwUserIDLen 		用户ID的长度
 *	pbSignedData		签名数据，格式：r||s
 *	pdwSignedDataLen	输入为签名数据缓冲区的长度，输出为实际签名数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCSignDigest(
	IN BYTE 			*pbData,
	IN DWORD			dwDataLen,
	IN BYTE 			byHashAlgID,
	IN BYTE 			*pbUserID,
	IN DWORD			dwUserIDLen,
	OUT BYTE			*pbSignedData,
	IN OUT DWORD		*pdwSignedDataLen,
	IN DEVHANDLE		hDev = NULL
	);



/*
 *	ECC数据解密。
 *	pbEncryptedData		已加密数据，格式：C1长度(DWORD)||C1||C2长度(DWORD)||C2||C3长度(DWORD)||C3
 *	dwEncryptedDataLen	已加密数据的长度
 *	pbDecryptedData		解密数据
 *	pdwDecryptedDataLen	输入为解密数据缓冲区的长度，输出为实际解密数据的长度
 *	hDev				连接设备时返回的设备句柄
 *	备注：				请先调用LCardECCSetCertNo选择当前操作的证书。
 */
BOOL LCardECCDecrypt(
	IN BYTE				*pbEncryptedData,
	IN DWORD			dwEncryptedDataLen,
	OUT BYTE			*pbDecryptedData,
	IN OUT DWORD		*pdwDecryptedDataLen,
	IN DEVHANDLE		hDev = NULL
	);



#ifdef __cplusplus
}
#endif

#endif
