/* ******************************************************************
*
*    DESCRIPTION:Copyright(c) 2010-2020 Xiamen Yealink Network Technology Co,.Ltd
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:2013-06-19
*
* for export APIs header file
*
*    history:
*------------------------------------------------------------------
* 0.0.0.0  ->  1.0.0.0 : ͳһ����ƽ̨�����汾
* 1.0.0.0  ->  1.0.0.1 : ����Ӳ��loop mode�Ĺ���
* 1.0.0.1  ->  1.0.0.2 : ������Ϣ����Log
* 1.0.0.2  ->  1.0.0.3 : ��API�ĺ�����ID�ֿ������ļ�����
* 1.0.0.3  ->  1.0.0.4 : �����Ȳ���¼��ϱ�����
* 1.0.0.4  ->  1.0.0.5 : �����������set_layout,video_creat,������˽ӿ�
* 1.0.0.5  ->  1.0.0.6 : ����֪ͨ���ת���Ľӿ�,sip������ipvp������ת����UIά��
* 1.0.0.6  ->  1.0.0.7 : �޸�ģʽmic��spk����ʹ�õķ�ʽ,���ӻ�ȡHot-plug ״̬
* 1.0.0.7  ->  1.0.0.8 : ��video request�����Ĳ����ϲ�,�޸ĳ�ʼ������
* 1.0.0.8  ->  1.0.0.9 : ipvp�ӿ��ڲ�����,���������¼�ID
* 1.0.0.9  ->  1.0.0.10: ��������handsfreeģʽ�ӿںͲ��߲���ģʽ�¼�ID
* 1.0.0.10  ->  1.0.0.11: ����ͬ������ipvp API�ķ�ʽ
* 1.0.0.11  ->  1.80.0.15: ͳһipvp API
* 1.80.0.15  ->  1.83.0.2: ipvp_qoestats_t������ȫ
* 1.32.0.7  ->  1.32.0.8: GROUP 31����MOH��,audio dump·������GUI����
* 1.0.0.57  ->  1.0.0.58: SIP-V84�ӿڷ���
* 1.0.0.58  ->  1.0.0.59: ipvp_dump_audio���Ӷ�file·�����
* 1.0.0.59  ->  1.0.0.60: ����ipvp_config_mns���ýӿ�
* 1.0.0.60  ->  1.0.0.61: ����IPVP_ADDR_FL_PAGING��
* 1.0.0.64  ->  1.0.0.65: ���ӵ��ӳٵ�echo_test����
*------------------------------------------------------------------
*
*/

#ifndef __SERVICE_IPVP_H__
#define __SERVICE_IPVP_H__

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
* for c
*/
#ifdef WIN32
/*Win32 platform*/
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <process.h>
#include <io.h>
#else
/*Linux platform*/
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#endif

/*
* for framework
*/
#if    defined(IPVP_HAVE_MSGKIT)
#include <mkmessage.h>
#include <mkservice.h>
#elif !defined(IPVP_BUILD)
typedef unsigned long mkit_handle_t;
#endif

/*
* API export
*/
#ifdef WIN32
#  ifdef IPVP_BUILD
#    define IPVP_API __declspec (dllexport)
#  else
#    define IPVP_API __declspec (dllimport)
#  endif
#else /*Linux*/
#  define IPVP_API
#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

    /*
    * include basic types
    */
#include "service_ipvp_types.h"

    /*
    * include basic APIs
    */
#include "service_ipvp_api.h"


#ifdef __cplusplus
}
#endif
/************************************************************************/
/*                                                                      */
/************************************************************************/
#endif /* __SERVICE_IPVP_H__ */
