/**
 * FileName:	ccurl.h
 * Author:		chsMiao
 * Description: �򵥷�װLibcurl��easy interface,
 *				����ʵ��Ftp�ϴ������ؼ���Ӧ������ʾ����
 *
 * ps :	
 *   1. curl_global_init��curl_global_cleanup ֻ�ܱ�����һ��
 *		���ڴ�ԭ��, �����õ�������з�װ
 *
 *	 2. ����˽����Ƕ����е��������������
 *	    ��ԭ�������ڽ�����ʱ��
 *      ϵͳ���Զ��������е�ȫ�ֱ�����������ľ�̬��Ա����
 *
 *	 3.	����CLOG��־���������μ�outctrl.h
 */

#ifndef __CCURL_H__ 
#define __CCURL_H__ 

#include <curl/curl.h>
#include <string>
using std::string;

class CCurl
{
public:
	static CCurl * Instance();

	void setHostInfo(char *ip, int port = 21);			// ����ftp��������IP�Ͷ˿ں�
	void setUserPwd(char *name, char *pwd);				// ����ftp������û���������
	void setHostUserPwd(char *name, char *pwd,			// ��Ч setHostInfo + setUserPwd
						char *ip, int port = 21);

	bool upload(char *localFullName, 
				char *remoteFileName = nullptr);		// �ϴ��ļ�
	bool download(char *remoteFileName, 
				  char *localFullName = nullptr);		// �����ļ�

private:
	CCurl();
	static CCurl *m_pInstance;

	/*
	 * ����˽����Ƕ�༰�侲̬��Ա����,ʵ�ֵ�����CCurl����Դ�ͷ�
	 */
	class CGarbo
	{
	public:
		~CGarbo();
	};

	static CGarbo m_Garbo;

private:

	/*
	 * callback functions
	 */
	static size_t readCallback(char *buffer, size_t size, 
							   size_t nitems, void *instream);
	static size_t writeCallback(char *buffer, size_t size, 
								size_t nitems, void *outstream);
	static int uploadProgressCallback(void *clientp, 
									  curl_off_t dltotal, 
									  curl_off_t dlnow, 
									  curl_off_t ultotal, 
									  curl_off_t ulnow);
	static int downloadProgressCallback(void *clientp, 
										curl_off_t dltotal, 
										curl_off_t dlnow, 
										curl_off_t ultotal, 
										curl_off_t ulnow);


	void init();										 // curl��ʼ��
	static string speedConvert(double &speed);			 // ת���ϴ�/�����ٶȵĵ�λ
	int  get_file_size(FILE *file);						 // ��ȡ�ϴ��ļ���С
	void setUploadOpt(FILE *file, const char* url);		 // �ϴ�ʱcurl_easy_setopt�ĸ�������
	void setDownLoadOpt(FILE *file, const char* url);	 // ����ʱcurl_easy_setopt�ĸ�������
	string getUploadFullName(char *localFullName,		 // �����ϴ�ʱ������ftp�������ϵ��ļ�ȫ��
						char *remoteFileName);

	string m_strServerUrl;								 // ftp��Ŀ¼��ַ
	string m_strUserPwd;								 // �û���:����
	static CURL *curl;									 // CURL easy interface �ľ��
	static bool m_bGlobalInit;
	static curl_off_t m_nUploaded;
	static curl_off_t m_nDownloaded;
};

#endif