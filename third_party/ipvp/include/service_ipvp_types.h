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
* for export IPVP APIs types header file
*
*/

#ifndef __SERVICE_IPVP_TYPES_H__
#define __SERVICE_IPVP_TYPES_H__



/************************************************************************/
/* common&limit define                                                  */
/************************************************************************/

/*
*----------------------------------------------------------------------
* limits
*----------------------------------------------------------------------
*/
#define  IPVP_MAX_CODECNAME     16
#define  IPVP_MAX_ADDR_LEN      48
#define  IPVP_MAX_SRTPKEY       128
#define  IPVP_MAX_ALERT_LEN     12
#define  IPVP_MAX_SPEECH        28       /*max speech session is 8,other system ,such MCU should be using other value!*/
#define  IPVP_MAX_CODEC         8       /*use for video codec only!*/
#define  IPVP_MAX_CODEC_ATTR    128     /*FIXME:size need to be decide*/
#define  IPVP_MAX_PATH          256
#define  IPVP_MAX_DEV_NAME      16
#define  IPVP_MAX_CNAME_LEN     256
/*
*----------------------------------------------------------------------
* speech mode
*----------------------------------------------------------------------
*/
#define  IPVP_POWER_INVAL       -1
#define  IPVP_POWER_FULL        0
#define  IPVP_POWER_SAVING      1
#define  IPVP_POWER_DEEP        2
#define  IPVP_POWER_SLEEP       3


#define  IPVP_MUTE              1
#define  IPVP_UNMUTE            0

#define  IPVP_SYNC_POST         0       /*just post the message to the IPC*/
#define  IPVP_SYNC_SEND         1       /*send the message, ensure it can be recv&deal*/
#define  IPVP_SYNC_CALL         2       /*call the function, wait till it is done*/

/* loop mode , as type of 'unsigned short'*/
#define  IPVP_LOOP_NONE         0
#define  IPVP_LOOP_ONCE         1
#define  IPVP_LOOP_FOREVER      0xFFFF

/*type of role*/
#define  IPVP_ROLE_MASTER        0
#define  IPVP_ROLE_SLAVE         1
#define  IPVP_ROLE_SLAVE_ID(subdev_id)   ((IPVP_ROLE_SLAVE<<8)|((subdev_id)&0xFF)<<0)

/*speech mode:exclusive(MIC and SPK are fixed paired)*/
#define  IPVP_MODE_IDLE          0      /*none*/
#define  IPVP_MODE_HF            1      /*handsfree*/
#define  IPVP_MODE_HS            2      /*handset*/
#define  IPVP_MODE_ES            3      /*headset*/
#define  IPVP_MODE_HG            4      /*handset group*/
#define  IPVP_MODE_EG            5      /*headset group*/
#define  IPVP_MODE_DU            6      /*double headset group*/
#define  IPVP_MODE_BTES          7      /*Bluetooth headset*/
#define  IPVP_MODE_VCP           8      /*CP phone speaker&microphone VCP40,etc*/
#define  IPVP_MODE_LINE          9      /*External microphone&loudspeaker pair*/
#define  IPVP_MODE_DECT          10     /*DECT Handset/Headset ,etc*/
#define  IPVP_MODE_USB           11     /*USB Handset*/
#define  IPVP_MODE_NA12          12     /*NA*/
#define  IPVP_MODE_NA13          13     /*NA*/
#define  IPVP_MODE_NA14          14     /*NA*/
#define  IPVP_MODE_NA15          15     /*NA*/

/*speech mode:extension(MIC is fixed by mode,SPK is flexible[HDMI/Speaker,etc])*/
#define  IPVP_MODE_INTERNAL_1MIC 16     /*internal 1-wired-microphone with HDMI speaker*/
#define  IPVP_MODE_INTERNAL_3MIC 17     /*internal 3-wired-microphone with HDMI speaker*/
#define  IPVP_MODE_EXTERNAL_1MIC 18     /*external 1-wired-microphone with HDMI speaker*/
#define  IPVP_MODE_EXTERNAL_3MIC 19     /*external 3-wired-microphone with HDMI speaker*/
#define  IPVP_MODE_DECT_WMIC     20     /*external dect wireless-microphone with HDMI speaker*/
#define  IPVP_MODE_WIRELESS_3MIC 21     /*external wireless 3-microphone with HDMI speaker*/
#define  IPVP_MODE_BT_WMIC       22     /*external bt wireless-microphone with HDMI speaker*/
#define  IPVP_MODE_WIFI_WMIC     23     /*external bt wifi-microphone with HDMI speaker*/
#define  IPVP_MODE_HS_HDMI       24     /*handset hdmi group*/
#define  IPVP_MODE_ES_HDMI       25     /*headset hdmi group*/
#define  IPVP_MODE_HS_USB        26     /*handset usb group*/
#define  IPVP_MODE_ES_USB        27     /*headset usb group*/
#define  IPVP_MODE_NA28          28     /*NA*/
#define  IPVP_MODE_NA29          29     /*NA*/
#define  IPVP_MODE_NA30          30     /*NA*/
#define  IPVP_MODE_HDMI          31     /*HDMI TV Speaker*/


#define  IPVP_MODE_MIN           0
#define  IPVP_MODE_MID           16
#define  IPVP_MODE_MAX           32     /*mode max*/
#define  IPVP_MODE_INV           -1     /*invalid*/

/*mode usage */
#define  IPVP_MODE_USAGE_GUI     0
#define  IPVP_MODE_USAGE_DEV     1


/* band width */
#define  IPVP_BW_NB             0   /*narrow band, 8000Hz samples*/
#define  IPVP_BW_WB             1   /*wide band, 16000Hz samples*/
#define  IPVP_BW_SB             2   /*super wide band, 24000Hz or 32000Hz samples*/
#define  IPVP_BW_FB             3   /*full band, 44100Hz or 48000Hz samples*/

#define  IPVP_BW_GEN_MAX        2   /*general band width support*/
#define  IPVP_BW_ENH_MAX        3   /*enhancing band width support*/
#define  IPVP_BW_CMP_MAX        4   /*complete band width support*/
#define  IPVP_BW_UTR_MAX        5   /*ultra band width support*/

#define  IPVP_BW_INVAL          -1  /*invalid band define*/
#define  IPVP_BW_MIN            0
#define  IPVP_BW_MAX            IPVP_BW_GEN_MAX

/* speak volume */
#define  IPVP_VOLUME_MIN        0   /*the minimum volume, can be set to IPVP_VOLUME_MIN */
#define  IPVP_VOLUME_MAX        32  /*the maximum volume, cannot be set to IPVP_VOLUME_MAX*/
#define  IPVP_GAIN_MIN          0   /*the minimum gain percentage 0%*/
#define  IPVP_GAIN_MAX          400 /*the maximum gain percentage*400%*/

/* slave direction */
#define  IPVP_SLAVE_CLOSE       (0)        /*close slave mode*/
#define  IPVP_SLAVE_DIR_OUT     (1<<0)     /*slave as input*/
#define  IPVP_SLAVE_DIR_IN      (1<<1)     /*slave as output*/
#define  IPVP_SLAVE_DIR_INOUT   (3<<0)     /*slave as input&output*/
#define  IPVP_SLAVE_DIR_MASK    (3<<0)     /*slave direction mask*/

/* slave mode */
#define  IPVP_SLAVE_NONE        0   /*none*/
#define  IPVP_SLAVE_BTHF        1   /*bluetooth handsfree profile*/
#define  IPVP_SLAVE_LINE        2   /*DC line*/
#define  IPVP_SLAVE_USB         3   /*USB audio device*/
#define  IPVP_SLAVE_SYS         4   /*system audio*/
#define  IPVP_SLAVE_HDMIIN      5   /*HDMI IN/DP*/
#define  IPVP_SLAVE_BTA2DP      6   /*bluetooth a2dp sink profile*/
#define  IPVP_SLAVE_DECT        7   /*dect audio*/
#define  IPVP_SLAVE_LINEOUT     8   /*mix audio line out*/
#define  IPVP_SLAVE_MAX         9   /*max usage*/
/*
* type of echo test
*/
#define  IPVP_ECHO_STOP         0   /*stop echo test*/
#define  IPVP_ECHO_LOOP         1   /*echo test loop, mic in then speaker out 1 sec later*/
#define  IPVP_ECHO_RECORD       2   /*echo test record, only mic in, MUST be called match with IPVP_ECHO_PLAY*/
#define  IPVP_ECHO_PLAY         3   /*echo test play, only speaker out, MUST be called match with IPVP_ECHO_RECORD*/
#define  IPVP_ECHO_FASTLOOP     4   /*echo test loop, fast version,mic in and fast out to spk*/

/*
* type of audio loop test
*/ 
#define  IPVP_LOOP_STOP         0   /*stop audio loop test*/
#define  IPVP_LOOP_ESHF         1   /*audio loop, headset-handsfree cross type (effect on SIP series)*/
#define  IPVP_LOOP_HSHS         2   /*audio loop, handset-handset loop type (effect on SIP series)*/
#define  IPVP_LOOP_ESES         3   /*audio loop, headset-headset loop type (effect on SIP series)*/
#define  IPVP_LOOP_HFLINE1      4   /*audio loop, mic1-lineout cross type (effect on VCS)*/
#define  IPVP_LOOP_HFLINE2      5   /*audio loop, mic2-lineout cross type (effect on VCS)*/
#define  IPVP_LOOP_VCP          6   /*audio loop, mic-spk cross type (effect on CP)*/
#define  IPVP_LOOP_WMIC         7   /*audio loop, wmic-spk cross type (effect on WMIC)*/

/*
* type of tone&DTMF
*/
/*DTMF tone*/
#define  IPVP_DTMF_0            '0'
#define  IPVP_DTMF_1            '1'
#define  IPVP_DTMF_2            '2'
#define  IPVP_DTMF_3            '3'
#define  IPVP_DTMF_4            '4'
#define  IPVP_DTMF_5            '5'
#define  IPVP_DTMF_6            '6'
#define  IPVP_DTMF_7            '7'
#define  IPVP_DTMF_8            '8'
#define  IPVP_DTMF_9            '9'
#define  IPVP_DTMF_A            'A'
#define  IPVP_DTMF_B            'B'
#define  IPVP_DTMF_C            'C'
#define  IPVP_DTMF_D            'D'
#define  IPVP_DTMF_STAR         '*'
#define  IPVP_DTMF_POUND        '#'
#define  IPVP_DTMF_FLASH        '+'

/*country tone*/
#define  IPVP_TONE_KEY          0   /* common key tone */
#define  IPVP_TONE_DIAL         1   /*dial tone(standard-dial-tone)*/
#define  IPVP_TONE_RING         2   /*ring back*/
#define  IPVP_TONE_BUSY         3   /*busy tone*/
#define  IPVP_TONE_RECORD       4   /*record*/
#define  IPVP_TONE_AA           5   /*auto answer*/
#define  IPVP_TONE_CONGESTON    6   /*congestion*/
#define  IPVP_TONE_DIALRECALL   7   /*dial recall*/
#define  IPVP_TONE_INFO         8   /*info*/
#define  IPVP_TONE_STUTTER      9   /*stutter*/
#define  IPVP_TONE_MESSAGE      10  /*message*/
#define  IPVP_TONE_CALLWAITING  11  /*call waiting*/
#define  IPVP_TONE_CALLERWAIT   12  /*caller wait*/

/*extension tone*/
#define  IPVP_TONE_EXT_CW1      13  /*BSFT CallWaitingTone1*/
#define  IPVP_TONE_EXT_CW2      14  /*BSFT CallWaitingTone2*/
#define  IPVP_TONE_EXT_CW3      15  /*BSFT CallWaitingTone3*/
#define  IPVP_TONE_EXT_CW4      16  /*BSFT CallWaitingTone4*/
#define  IPVP_TONE_EXT_DIAL     17  /*dial_tone(special-condition-tone)*/
#define  IPVP_TONE_EXT_DIAL2    18  /*dial_tone(message-waiting-tone)*/

#define IPVP_TONE_CONF          19  /*enter conference*/
#define IPVP_TONE_STUTTER_DIAL  20  /*stutter dial tone*/

#define  IPVP_TONE_MAX          21  /*MUST be change due to the country tone*/

#define  IPVP_FL_UNHOLD         0x00000000 /*unhold: send & recv */
#define  IPVP_FL_HOLD_ACTIVE    0x00000001 /*hold: talk inactive */
#define  IPVP_FL_HOLD_PASSIVE   0x00000002 /*held: only recv */
#define  IPVP_FL_HOLD_MOH       0x00000003 /*hold: music on hold, send music */

/*roaming control*/
#define  IPVP_ROAMING_STOP       0x00000000  /*roaming control:stop*/
#define  IPVP_ROAMING_START      0x00000001  /*roaming control:start*/
#define  IPVP_ROAMING_READY      0x00000002  /*roaming control:ready*/
#define  IPVP_ROAMING_UPDATE     0x00000004  /*roaming control:ready*/

#define  IPVP_GROUP_MOH         31
/*----------------------------------------------------------------------
* type of video
*----------------------------------------------------------------------
*/
/*video-src:source of video:from 0 to 7*/
#define  IPVP_VIDEO_SRC_CAM      0   /*source from camera*/
#define  IPVP_VIDEO_SRC_VGA      1   /*source from VGA/PC*/
#define  IPVP_VIDEO_SRC_HDMI     2   /*source from primary HDMI*/
#define  IPVP_VIDEO_SRC_HDMI2    3   /*source from secondary HDMI*/
#define  IPVP_VIDEO_SRC_CAMMIX   4   /*source from mix camera*/
#define  IPVP_VIDEO_SRC_SHAMIX   5   /*source from mix share*/
#define  IPVP_VIDEO_SRC_PRIMARY  6   /*source from primary*/
#define  IPVP_VIDEO_SRC_SECONDLY 7   /*source from secondly*/

/*video-dst:display of video:from 8 to 15*/
#define  IPVP_VIDEO_DST_LCD      8   /*display to LCD*/
#define  IPVP_VIDEO_DST_VGA      9   /*display to VGA/HDCOMP*/
#define  IPVP_VIDEO_DST_HDMI     10  /*display to primary HDMI with audio playback*/
#define  IPVP_VIDEO_DST_HDMI2    11  /*display to secondary HDMI display only*/
#define  IPVP_VIDEO_DST_CAMMIX   12  /*display to mix camera*/
#define  IPVP_VIDEO_DST_SHAMIX   13  /*display to mix share*/
#define  IPVP_VIDEO_DST_ENC      14  /*display to encodec*/
#define  IPVP_VIDEO_DST_REC      15  /*display to record*/
#define  IPVP_VIDEO_DST_PRIMARY  16  /*display to primary*/
#define  IPVP_VIDEO_DST_SECONDLY 17  /*display to secondary*/
#define  IPVP_VIDEO_DST_CONTROL_USER  18  /*display to control PAD*/

/*video-ID:FIXME:how to define this??*/
#define  IPVP_VIDEO_ID_SPEECH    0   /*layout of remote video speech*/
#define  IPVP_VIDEO_ID_SHARED    1   /*layout of remote video shared*/
#define  IPVP_VIDEO_ID_CAMERA    2   /*layout of local camera*/
#define  IPVP_VIDEO_ID_PC        3   /*layout of local PC(VGA input)*/
#define  IPVP_VIDEO_ID_FILE      4   /*layout of media file*/
#define  IPVP_VIDEO_ID_MIXER     5   /*layout of conference*/
#define  IPVP_VIDEO_ID_CAMMIX    6   /*layout of mix camera*/
#define  IPVP_VIDEO_ID_SHAMIX    7   /*layout of mix share*/
#define  IPVP_VIDEO_ID_PRIMARY   8   /*layout of main*/
#define  IPVP_VIDEO_ID_SENCOND   9   /*layout of sencond*/

/*video-qp:video quality policy*/
#define  IPVP_VIDEO_QP_DEFAULT          0   /*default,depends on global config*/
#define  IPVP_VIDEO_QP_SMOOTH_ONLY      1   /*smooth video only*/
#define  IPVP_VIDEO_QP_SMOOTH_PREFERED  2   /*smooth video prior*/
#define  IPVP_VIDEO_QP_STATIC_ONLY      3   /*static picture video only*/
#define  IPVP_VIDEO_QP_STATIC_PREFERED  4   /*static picture video prior*/

/*video-sst:video snap stream type*/
#define  IPVP_VIDEO_SST_MIN       0
#define  IPVP_VIDEO_SST_CAMERA    0   /*snap stream of camera*/
#define  IPVP_VIDEO_SST_PCBOX     1   /*snap stream of pcbox*/
#define  IPVP_VIDEO_SST_MAINSCR   2   /*snap stream of main screen*/
#define  IPVP_VIDEO_SST_SECSCR    3   /*snap stream of secondary screen*/
#define  IPVP_VIDEO_SST_CHN       4   /*snap stream of multi-camera*/
#define  IPVP_VIDEO_SST_MAX       4

/*type of video stream priority:FIXME:how to define this??*/
#define  IPVP_VIDEO_SP_DEFAULT   0   /*default,depends on global config*/
#define  IPVP_VIDEO_SP_HIGH      1   /*high*/
#define  IPVP_VIDEO_SP_MEDIAL    2   /*medial*/
#define  IPVP_VIDEO_SP_LOW       3   /*low*/

/*type of video codec profile:FIXME:how to define this??*/
#define  IPVP_VIDEO_PF_BASE      0   /*default,depends on global config*/
#define  IPVP_VIDEO_PF_MAIN      0   /*main profile*/
#define  IPVP_VIDEO_PF_EXTEND    0   /*extend profile*/
#define  IPVP_VIDEO_PF_HIGH      0   /*high profile*/

/*type of video codec mode:FIXME:how to define this??*/
#define  IPVP_VIDEO_PM_SSLICES   0   /*single-slices*/
#define  IPVP_VIDEO_PM_MSLICES   1   /*multi-slices*/

/*type of HDMI display mode:FIXME:how to define this??*/
#define  IPVP_DHMI_DM_NONE       0   /*no display*/
#define  IPVP_DHMI_DM_COPY       1   /*copy display*/
#define  IPVP_DHMI_DM_EXTEND     2   /*extend display*/

/***********************************************************************/
/* notification  define  id from 0 to 256                              */
/***********************************************************************/
#define IPVP_MSG_MIN                  MKSRV_MSG(MKSRV_ID_IPVP,0)
#define IPVP_MSG_MAX                  MKSRV_MSG(MKSRV_ID_IPVP,255)
/*
*---------------------------------------------------------------------
* notification [0 to 63] for common
*---------------------------------------------------------------------
*/
#define IPVP_MSG_COMMON_MIN           IPVP_MSG_MIN
#define IPVP_MSG_COMMON_MAX           MKSRV_MSG(MKSRV_ID_IPVP,63)

/*
* usage   :to notify that phone speech mode has changed!
*          
* id      :0
* target  :ipvp server
* wparam  :LOWORD==usage,  HIWORD=reserved
* lparam  :LOWORD==mode  HIWORD=reserved
*
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_MODECHANGED          MKSRV_MSG(MKSRV_ID_IPVP,0)

/*FIXME:port hot-plug event
* usage   :to notify hw port hot-plug event
*          
* id      :1
* target  :ipvp server
* wparam  :LOWORD==event type,  HIWORD=reserved
* lparam  :LOWORD==status code  HIWORD=reserved
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_HPEVENT             MKSRV_MSG(MKSRV_ID_IPVP,1)

/*event type*/
#define IPVP_HPEV_INVALID             0x0000  /*invalid*/
#define IPVP_HPEV_LINEIN              0x0001  /*audio line-in*/
#define IPVP_HPEV_LINEOUT             0x0002  /*audio line-out*/
#define IPVP_HPEV_VGA                 0x0003  /*video VGA*/
#define IPVP_HPEV_DVI                 0x0004  /*video DVI*/
#define IPVP_HPEV_HDMI                0x0005  /*master HDMI*/
#define IPVP_HPEV_HDMI2               0x0006  /*slave HDMI*/
#define IPVP_HPEV_CAMERA              0x0007  /*hot-plug camera*/
#define IPVP_HPEV_VCP40               0x0008  /*net port sub device VCP40*/
#define IPVP_HPEV_3MIC                0x0009  /*net port sub device 3MICPod*/
#define IPVP_HPEV_WMIC                0x000A  /*wireless (DECT) MICPod*/
#define IPVP_HPEV_VCP41               0x000B  /*net port sub device VCP41*/
#define IPVP_HPEV_BOX                 0x000C  /*net port sub device BOX*/
#define IPVP_HPEV_USB                 0x000D  /*audio USB card*/

#define IPVP_HPEV_SUB_MASK            0x1000
#define IPVP_HPEV_SUB(id)             (IPVP_HPEV_SUB_MASK|id)
#define IPVP_HPEV_CP960               IPVP_HPEV_SUB(1)       /*net port sub device CP960*/
#define IPVP_HPEV_CP920               IPVP_HPEV_SUB(2)       /*net port sub device CP920*/

/*status code*/
#define IPVP_HPST_REMOVED             0x0000  /*status code: device removed*/
#define IPVP_HPST_PLUGIN              0x0001  /*status code: device physically plug-in*/
#define IPVP_HPST_READY               0x0002  /*status code: device ready to go*/
#define IPVP_HPST_SUSPEND             0x0003  /*status code: device suspend*/
#define IPVP_HPST_RESUME              0x0004  /*status code: device resume*/
#define IPVP_HPST_FAILED              0x1000  /*status error:failed on I/O*/


/*
* usage   :to notify audio tuning status
*          
* id      :0x00050002/0x00050003
* target  :ipvp server
* wparam  :LOWORD==audio mode type,HIWORD=reserved
* lparam  :LOWORD==status code    ,HIWORD=reserved
*           status code:
*               0==started 
*               1==ended and successful
*               2==ended and failed
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_ATRAIN               MKSRV_MSG(MKSRV_ID_IPVP,2)
#define IPVP_MSG_ATUNING              MKSRV_MSG(MKSRV_ID_IPVP,3)

/*
* usage   :to notify video tuning status
*          
* id      :0x00050004/0x00050005
* target  :ipvp server
* wparam  :reserved
* lparam  :reserved
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_VTRAIN               MKSRV_MSG(MKSRV_ID_IPVP,4)
#define IPVP_MSG_VTUNING              MKSRV_MSG(MKSRV_ID_IPVP,5)

/*
* usage   :to notify sub server register
*          
* id      :0x00050006
* target  :ipvp server
* wparam  :server ID
* lparam  :server index
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_REGSUB               MKSRV_MSG(MKSRV_ID_IPVP,6)

/*
*---------------------------------------------------------------------
* notification [64 to 127] for audio
*---------------------------------------------------------------------
*/
#define IPVP_MSG_AUDIO_MIN            MKSRV_MSG(MKSRV_ID_IPVP,64)
#define IPVP_MSG_AUDIO_MAX            MKSRV_MSG(MKSRV_ID_IPVP,127)

/*
* usage   :to notify that DTMF detected on receive path
*          
* id      :0x00050040
* target  :ipvp server
* wparam  :call ID
* lparam  :
*           HIWORD():DTMF id
*           LOWORD():none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_RECVDTMF       MKSRV_MSG(MKSRV_ID_IPVP,64+0)

/*
* usage   :to notify that receive rtp do not match
*          
* id      :0x00050041
* target  :ipvp server
* wparam  :call ID
* lparam  :
*           HIWORD():rtpmap in use
*           LOWORD():rtpmap recv indeed
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_RTPVIOLATE     MKSRV_MSG(MKSRV_ID_IPVP,64+1)

/*
* usage   :to notify that receive addr changed start or during a talk
*          
* id      :0x00050042
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:union of {struct sockaddr_in & struct sockaddr_in6}
* data_len:AF_INET6?sizeof(struct sockaddr_in6):sizeof(struct sockaddr_in)
*/
#define IPVP_MSG_AUDIO_ADDRCHANGED    MKSRV_MSG(MKSRV_ID_IPVP,64+2)

/*
* usage   :to notify that receive ssrc changed during a talk
*          
* id      :0x00050043
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_SSRCCHANGED    MKSRV_MSG(MKSRV_ID_IPVP,64+3)

/*
* usage   :to notify that receive an rtcp goodbye
*          
* id      :0x00050044
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_RTCPBYE        MKSRV_MSG(MKSRV_ID_IPVP,64+4)

/*
* usage   :to notify the voice quality report
*          
* id      :0x00050045
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_VQREPORT       MKSRV_MSG(MKSRV_ID_IPVP,64+5)

/*
* usage   :to notify that security call failed, may be the handle do not match
*          
* id      :0x00050046
* target  :ipvp server
* wparam  :call ID
* lparam  :HIWORD: 0x01 - encrypt rtp fail; 0x02 decrypt rtp fail; 
0x04 - encrypt rtcp fail;0x08 decrypt rtcp fail
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_SRTPFAIL       MKSRV_MSG(MKSRV_ID_IPVP,64+6)

/*
* usage   :to notify the jitter buffer overflow and then discard packet
*          
* id      :0x00050047
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_PKTDISCARD     MKSRV_MSG(MKSRV_ID_IPVP,64+7)

/*
* usage   :to notify the audio lost packet
*          
* id      :0x00050048
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_PKTLOST        MKSRV_MSG(MKSRV_ID_IPVP,64+8)


/*FIXME:new event!
* usage   :to notify we can NOT recv any packet for long time
*          
* id      :0x00050049
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_NETLOST        MKSRV_MSG(MKSRV_ID_IPVP,64+9)


/*
* usage   :to notify train/tuning status
*          
* id      :0x0005004a/0x0005004b
* target  :ipvp server
* wparam  :status code,0==ok and finished,else==error-no
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_TRAIN         MKSRV_MSG(MKSRV_ID_IPVP,64+10)
#define IPVP_MSG_AUDIO_TUNING        MKSRV_MSG(MKSRV_ID_IPVP,64+11)


/*
* usage   :to notify diagnose event
*          
* id      :0x0005004c
* target  :ipvp server
* wparam  :event : 1==AUDIO LATENCY,2==ONE-WAY AUDIO,3==AUDIO QUALITY,4==MEETING AUDIO QUALITY
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_DIAGNOSE       MKSRV_MSG(MKSRV_ID_IPVP,64+12)

/*
* usage   :to notify whether audio rtp&rtcp packets received
*
* id      :0x0005004d/0x0005004e
* target  :ipvp server
* wparam  :callid
* lparam  :reserved
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_DEAD          MKSRV_MSG(MKSRV_ID_IPVP,64+13)
#define IPVP_MSG_AUDIO_ALIVE         MKSRV_MSG(MKSRV_ID_IPVP,64+14)

/*
* usage   :to report the rms data
*          
* id      :0x0005004f
* target  :ipvp server
* wparam  :call count in group
* lparam  :gid
* data_ptr:{callid,rms}
* data_len: count*size
*/
#define IPVP_MSG_AUDIO_RMSREPORT      MKSRV_MSG(MKSRV_ID_IPVP,64+15)

/*
* usage   :to report the voice distortion
*          
* id      :0x00050050
* target  :ipvp server
* wparam  :percent of adjust volume
* lparam  :adjust dB
* data_ptr:none
* data_len: none
*/
#define IPVP_MSG_AUDIO_GAIN_CTRL    MKSRV_MSG(MKSRV_ID_IPVP,64+16)

/*
* usage   :to notify SRTP lifetime event
*          
* id      :0x00050052
* target  :ipvp server
* wparam  :callid
* lparam  :event : 1==SRTP REINVITE
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_SRTP_REINVITE  MKSRV_MSG(MKSRV_ID_IPVP,64+18)

/*
* usage   :to report talk start failed
*          
* id      :0x00050053
* target  :ipvp server
* wparam  :call ID
* lparam  :error no
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_TALK_FAILED   MKSRV_MSG(MKSRV_ID_IPVP,64+19)
/*
* usage   :to notify first rtp event
*          
* id      :0x00050054
* target  :ipvp server
* wparam  :callid
* lparam  :event : 1==receive first rtp
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_FIRST_RTP    MKSRV_MSG(MKSRV_ID_IPVP,64+20)

/*
* usage   :to report adaptive speaker compensate
*
* id      :0x00050055
* target  :ipvp server
* wparam  :call ID
* lparam  :error no
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_ASC_ADAPTED   MKSRV_MSG(MKSRV_ID_IPVP,64+21)

/*
* usage   :to notify QOE param
*          
* id      :0x00050056
* target  :ipvp server
* wparam  :callid
* lparam  :none
* data_ptr:QOE
* data_len:sizeof(ipvp_qoestats_t)
*/
#define IPVP_MSG_AUDIO_QOEREPORT     MKSRV_MSG(MKSRV_ID_IPVP,64+22)

/*
* usage   :to notify media play or record failed
*          
* id      :0x00050057
* target  :ipvp server
* wparam  :0 play 1 record
* lparam  :error id
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_MEDIA_FAILED  MKSRV_MSG(MKSRV_ID_IPVP,64+23)

/*
* usage   :to notify echo cancellation failed
*
* id      :0x00050058
* target  :ipvp server
* wparam  :mic mode
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_AUDIO_ECHOCANC_FAILED  MKSRV_MSG(MKSRV_ID_IPVP,64+24)

/*
*---------------------------------------------------------------------
* notification [128 to 192] for video
*---------------------------------------------------------------------
*/
#define IPVP_MSG_VIDEO_MIN           MKSRV_MSG(MKSRV_ID_IPVP,128)
#define IPVP_MSG_VIDEO_MAX           MKSRV_MSG(MKSRV_ID_IPVP,192)

/*FIXME:new event!
* usage   :to notify 
*          
* id      :0x00050080/0x00050081
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_VIDEO_DEAD          MKSRV_MSG(MKSRV_ID_IPVP,128+0)
#define IPVP_MSG_VIDEO_ALIVE         MKSRV_MSG(MKSRV_ID_IPVP,128+1)

/*FIXME:new event!
* usage   :to notify that video window has [been] resized
*          
* id      :0x00050082/0x00050083
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:ptrof (ipvp_resize_t)
* data_len:sizeof(ipvp_resize_t)
*/
#define IPVP_MSG_VIDEO_RECV_RESIZED  MKSRV_MSG(MKSRV_ID_IPVP,128+2)
#define IPVP_MSG_VIDEO_SEND_RESIZED  MKSRV_MSG(MKSRV_ID_IPVP,128+3)

/*FIXME:new event!
* usage   :to notify that video window has [been] resized
*          
* id      :0x00050084/0x00050085
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_VIDEO_CAM_PAUSED    MKSRV_MSG(MKSRV_ID_IPVP,128+4)
#define IPVP_MSG_VIDEO_CAM_RESTORE   MKSRV_MSG(MKSRV_ID_IPVP,128+5)


/*FIXME:new event!
* usage   :to notify that remote-request-control
*          
* id      :0x00050086/0x00050087
* target  :ipvp server
* wparam  :call ID
* lparam  :video ID
* data_ptr:(int*)recommend_max_rate
* data_len:sizeof(int)
*/
#define IPVP_MSG_VIDEO_RREQ_KFRAME   MKSRV_MSG(MKSRV_ID_IPVP,128+6)
#define IPVP_MSG_VIDEO_RREQ_FCTRL    MKSRV_MSG(MKSRV_ID_IPVP,128+7)

/*FIXME:new event!
* usage   :to notify that  core working status is abnormal
*          
* id      :0x00050088
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_VIDEO_CORE_ABNORMAL MKSRV_MSG(MKSRV_ID_IPVP,128+8)

/*FIXME:new event!
* usage   :to notify that snapshot is done
*
* id      :0x00050089
* target  :ipvp server
* wparam  :return value
* lparam  :video ID
* data_ptr:file path
* data_len:sizeof(path)
*/
#define IPVP_MSG_VIDEO_SNAPSHOT_DONE  MKSRV_MSG(MKSRV_ID_IPVP,128+9)

/*FIXME:new event!
* usage   :to notify the video switch update 
*
* id      :0x0005008a
* target  :ipvp server
* wparam  :none
* lparam  :none
* data_ptr: private cmd
* data_len: sizeof(cmd)
*/
#define IPVP_MSG_VIDEO_PRIVATE_CMD   MKSRV_MSG(MKSRV_ID_IPVP,128+10)

/*
* usage   :to notify the video lost packet
*          
* id      :0x0005008b
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_VIDEO_PKTLOST        MKSRV_MSG(MKSRV_ID_IPVP,128+11)

/*
* usage   :to notify the video quality report
*          
* id      :0x0005008c
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:ipvp_vstats_t
* data_len:sizeof(ipvp_vstats_t)
*/
#define IPVP_MSG_VIDEO_VQREPORT       MKSRV_MSG(MKSRV_ID_IPVP,128+12)
/*
* usage   :to notify the video bandwidth quality
*          
* id      :0x0005008d/0x0005008e
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_VIDEO_BANDWIDTH_BAD        MKSRV_MSG(MKSRV_ID_IPVP,128+13)
#define IPVP_MSG_VIDEO_BANDWIDTH_GOOD       MKSRV_MSG(MKSRV_ID_IPVP,128+14)

/*
*---------------------------------------------------------------------
* notification [192 to 255] for media
*---------------------------------------------------------------------
*/
#define IPVP_MSG_MEDIA_MIN           MKSRV_MSG(MKSRV_ID_IPVP,192)
#define IPVP_MSG_MEDIA_MAX           IPVP_MSG_MAX

/*
* usage   :to notify that something happen while recording call
*          
* id      :0x000500c0/0x000500c1/0x000500c2/0x000500c3
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_RECORD_FAIL         MKSRV_MSG(MKSRV_ID_IPVP,192+0)
#define IPVP_MSG_RECORD_DONE         MKSRV_MSG(MKSRV_ID_IPVP,192+1)
#define IPVP_MSG_RECORD_STEP         MKSRV_MSG(MKSRV_ID_IPVP,192+2)
#define IPVP_MSG_RECORD_ABORT        MKSRV_MSG(MKSRV_ID_IPVP,192+3)

/*
* usage   :to notify that something happen while playing media
*          
* id      :0x000500c8-0x000500cc
* target  :ipvp server
* wparam  :call ID
* lparam  :none
* data_ptr:none
* data_len:none
*/
#define IPVP_MSG_MEDIA_FAIL          MKSRV_MSG(MKSRV_ID_IPVP,192+8)
#define IPVP_MSG_MEDIA_DONE          MKSRV_MSG(MKSRV_ID_IPVP,192+9)
#define IPVP_MSG_MEDIA_STEP          MKSRV_MSG(MKSRV_ID_IPVP,192+10)
#define IPVP_MSG_MEDIA_ABORT         MKSRV_MSG(MKSRV_ID_IPVP,192+11)
#define IPVP_MSG_MEDIA_REPEAT        MKSRV_MSG(MKSRV_ID_IPVP,192+12)

/************************************************************************/
/* type define                                                          */
/************************************************************************/

/*
* common control flags
*/
#define  IPVP_FL_NONE               0x00000000
#define  IPVP_FL_ALL                0xFFFFFFFF

#define  IPVP_FL_DIR_NONE           IPVP_FL_NONE                          /*direction:none*/
#define  IPVP_FL_DIR_LOCAL          0x00000001                            /*direction:to local*/
#define  IPVP_FL_DIR_NET            0x00000002                            /*direction:to network*/
#define  IPVP_FL_DIR_MIX            0x00000004                            /*direction:to mix local and network*/
#define  IPVP_FL_DIR_ALL            (IPVP_FL_DIR_LOCAL|IPVP_FL_DIR_NET)   /*direction:to local and network*/
#define  IPVP_FL_DIR_MASK           0x0000000F                            /*direction:mask*/

#define  IPVP_FL_NET_NONE           IPVP_FL_NONE                          /*net:none*/
#define  IPVP_FL_NET_RTP            0x00000010                            /*net:has RTP media stream*/
#define  IPVP_FL_NET_RTCP           0x00000020                            /*net:has RTCP media stream*/
#define  IPVP_FL_NET_ALL            (IPVP_FL_NET_RTP|IPVP_FL_NET_RTCP)    /*net:mask*/

#define  IPVP_FL_MOD_NONE           IPVP_FL_NONE                          /*mode:none*/
#define  IPVP_FL_MOD_SILENCE        0x00000100                            /*mode:as silence*/
#define  IPVP_FL_MOD_SYNC           0x00000200                            /*mode:as  synchronous*/
#define  IPVP_FL_MOD_ASYNC          0x00000400                            /*mode:as  asynchronous*/
#define  IPVP_FL_MOD_MASK           0x00000F00                            /*mode:mask*/

#define  IPVP_FL_VAM_NONE           IPVP_FL_NONE                          /*va mode:none*/
#define  IPVP_FL_VAM_AUDIO          0x00001000                            /*va mode:audio is valid*/
#define  IPVP_FL_VAM_VIDEO          0x00002000                            /*va mode:video is valid*/
#define  IPVP_FL_VAM_AUDIO_EXT      0x00004000                            /*va mode:audio extern is valid*/
#define  IPVP_FL_VAM_MASK           0x0000F000                            /*va mode:mask*/

#define  IPVP_FL_REC_NONE           IPVP_FL_NONE                          /*record mode:none*/
#define  IPVP_FL_REC_MIC            0x00010000                            /*record mode:microphone*/
#define  IPVP_FL_REC_SPK            0x00020000                            /*record mode:speaker*/
#define  IPVP_FL_REC_MIX            0x00040000                            /*record mode:mix all*/
#define  IPVP_FL_REC_LOOP           0x00080000                            /*record mode:write loop back*/
#define  IPVP_FL_REC_MASK           0x000F0000                            /*record mode:mask*/

#define  IPVP_FL_VQR_NONE           IPVP_FL_NONE                          /*voice quality:report none*/
#define  IPVP_FL_VQR_SESSN          0x00100000                            /*voice quality:session report*/
#define  IPVP_FL_VQR_INTVL          0x00200000                            /*voice quality:interval report*/
#define  IPVP_FL_VQR_ALERT          0x00400000                            /*voice quality:alert report*/
#define  IPVP_FL_VQR_PRIV           0x00800000                            /*voice quality:private report*/
#define  IPVP_FL_VQR_MASK           0x00F00000                            /*voice quality:mask*/

#define  IPVP_FL_GROUP_MCU          IPVP_FL_NONE                          /*talk group:mcu*/
#define  IPVP_FL_GROUP_VMR          0x01000000                            /*talk group:vmr*/
#define  IPVP_FL_GROUP_MASK         0xFF000000                            /*talk group:mask*/

#define  IPVP_FL_GAIN_NONE          IPVP_FL_NONE                          /*direction:none*/
#define  IPVP_FL_GAIN_RECV          0x00000001                            /*direction:recv gain*/
#define  IPVP_FL_GAIN_SEND          0x00000002                            /*direction:send gain*/

#define  IPVP_FL_SURF_NONE          IPVP_FL_NONE                          /*surface:none*/
#define  IPVP_FL_SURF_DISPLAY       0x00000001                            /*surface: display mask*/
#define  IPVP_FL_SURF_NOCAMERA      0x00000002                            /*surface: nocamera mask*/
#define  IPVP_FL_SURF_RESOLUTION    0x000000f0                            /*surface:resolution mask*/
#define  IPVP_FL_SURF_RESOL_720P    0x00000010                            /*surface:resolution 720p*/
#define  IPVP_FL_SURF_RESOL_1080P   0x00000020                            /*surface:resolution 1080p*/
#define  IPVP_FL_SURF_RESOL_4K      0x00000030                            /*surface:resolution 4k*/
#define  IPVP_FL_SURF_RESOL_1088P   0x00000040                            /*surface:resolution 1088p for test*/
#define  IPVP_FL_SURF_CAPTURE       0x00000f00                            /*surface:capture mask*/
#define  IPVP_FL_SURF_CAPT_720P     0x00000100                            /*surface:capture resolution 720p*/
#define  IPVP_FL_SURF_CAPT_1080P    0x00000200                            /*surface:capture resolution 1080p*/
#define  IPVP_FL_SURF_CAPT_4K       0x00000300                            /*surface:capture resolution 4k*/

#define  IPVP_FL_SW_DIRECTLY        IPVP_FL_NONE                          /*stream switch: directly  */
#define  IPVP_FL_SW_TRANSCODE       0x00000001                            /*stream switch: transcode*/
#define  IPVP_FL_SW_PROXY           0x00000002                            /*stream switch: PROXY*/

#define  IPVP_FL_CONF_USER          IPVP_FL_NONE                          /*stream role: conf user  */
#define  IPVP_FL_REMOTE_CAMERA      0x00000001                            /*stream role: remote camera*/
#define  IPVP_FL_WILESS_DATA        0x00000002                            /*stream role: wiless share*/
#define  IPVP_FL_CONTROL_USER       0x00000004                            /*stream role: control user*/

#define  IPVP_FL_VIDEO_UNHOLD       0x00000000                            /*video unhold: send & recv */
#define  IPVP_FL_VIDEO_HOLD_ACTIVE  0x00000001                            /*video hold: inactive*/
#define  IPVP_FL_VIDEO_HOLD_PASSIVE 0x00000002                            /*video held: only recv*/
#define  IPVP_FL_VIDEO_HOLD_MASK    0x0000000F                            /*voice hold: mask*/

#define  IPVP_FL_VIDEO_LOCAL_CAMERA          0                            /*camera mute: local camera*/
#define  IPVP_FL_VIDEO_REMOTE_CAMERA         1                            /*camera mute: remote camera*/

#define  IPVP_FL_NETCAP_NONE        0x00000000
#define  IPVP_FL_NETCAP_MIC         0x00000001
#define  IPVP_FL_NETCAP_SPK         0x00000002
#define  IPVP_FL_NETCAP_BOTH        (IPVP_FL_NETCAP_MIC|IPVP_FL_NETCAP_SPK)

#define  IPVP_FL_DATAFORMAT_MIX     0x00000100                    /*dual-channel format:mix*/
#define  IPVP_FL_DATAFORMAT_INTLD   0x00000200                    /*dual-channel format:sampler interleaved*/
#define  IPVP_FL_DATAFORMAT_BLOCK   0x00000400                    /*dual-channel format:block splice*/
#define  IPVP_FL_DATAFORMAT_APART   0x00000800                    /*dual-channel format:double stream of apart*/

/*
* common error types
*/
#define  IPVP_ERR_MEDIA_OK                   0
#define  IPVP_ERR_MEDIA_PARAM               -1                            /* input param error */
#define  IPVP_ERR_MEDIA_FILENAME            -2                            /* a fault file name or address */
#define  IPVP_ERR_MEDIA_CODEC_NOT_SUPPORT   -3                            /* codec not support */
#define  IPVP_ERR_MEDIA_STREAM              -4                            /* media stream error */
#define  IPVP_ERR_MEDIA_NULLP               -5                            /* null pointer error */
#define  IPVP_ERR_MEDIA_FILE                -6                            /* media file has damaged, cannot parse */
#define  IPVP_ERR_MEDIA_SEEKEND             -7                            /* seek to the file end */
#define  IPVP_ERR_MEDIA_SEEKHEADER          -8                            /* seek to the file header */
#define  IPVP_ERR_MEDIA_FILE_EOF            -9                            /* read the file EOF flag */
#define  IPVP_ERR_MEDIA_NO_SPACE            -10                           /* no space to record file */
#define  IPVP_ERR_MEDIA_BAD_FRAME           -11                           /* decode a bad frame*/

/*
* common tuning adapted types
*/
#define  IPVP_ERR_TUNING_ADAPTED_OK          0                            /* tuning eq adapt success*/
#define  IPVP_ERR_TUNING_ADAPTED_FAIL        1                            /* tuning eq adapt fail*/

/*
* talk error types
*/
#define  IPVP_ERR_TALK_MEDIA                -1                             /* talk media error*/
#define  IPVP_ERR_TALK_LIMIT                -2                             /* talk performance limit*/

/*
*----------------------------------------------------------------------
*   type of windows softphone
*----------------------------------------------------------------------
*/
typedef struct
{
    int format;         /* audio data format */
#define IPVP_AUDIO_FORMAT_INTER_PCM     1
#define IPVP_AUDIO_FORMAT_MOTOROLA_PCM  2
#define IPVP_AUDIO_FORMAT_DEFAULT       IPVP_AUDIO_FORMAT_INTER_PCM

    int samplerate;     /* audio samplerate  */
#define IPVP_AUDIO_SAMPLERATE_6000      6000
#define IPVP_AUDIO_SAMPLERATE_8000      8000
#define IPVP_AUDIO_SAMPLERATE_11025     11025
#define IPVP_AUDIO_SAMPLERATE_16000     16000
#define IPVP_AUDIO_SAMPLERATE_22050     22050
#define IPVP_AUDIO_SAMPLERATE_32000     32000
#define IPVP_AUDIO_SAMPLERATE_44100     44100
#define IPVP_AUDIO_SAMPLERATE_48000     48000
#define IPVP_AUDIO_SAMPLERATE_64000     64000
#define IPVP_AUDIO_SAMPLERATE_88200     88200
#define IPVP_AUDIO_SAMPLERATE_96000     96000
#define IPVP_AUDIO_SAMPLERATE_192000    192000
#define IPVP_AUDIO_SAMPLERATE_DEFAULT   IPVP_AUDIO_SAMPLERATE_32000

    int resolution;     /* bits per sample   */
#define IPVP_AUDIO_BPS_8                8
#define IPVP_AUDIO_BPS_16               16
#define IPVP_AUDIO_BPS_32               32
#define IPVP_AUDIO_BPS_DEFAULT          IPVP_AUDIO_BPS_16

    int channels;       /* channels          */
#define IPVP_AUDIO_CHAN_MONO            1
#define IPVP_AUDIO_CHAN_STEREO          2
#define IPVP_AUDIO_CHAN_DEFAULT         IPVP_AUDIO_CHAN_MONO
}ipvp_frame_t;

typedef struct {
    int  sharing;       /*voice channel control, -1:no change; 0:disable; 1:enable*/
    int  mix_spk;       /*VCD output use default audio card,
                          -1:no change; 0:no defult card; 1:default car*/
    int  volume;        /*voice audio volume, 0~100*/

    int reserve[8];     /*reserve*/
}ipvp_ext_voice_t;

/*
*----------------------------------------------------------------------
*   type of callback for library
*----------------------------------------------------------------------
*/
typedef struct
{
    int         argc;
    const char**argv;
    void       *jvm;
    /*use for logging*/
    int       (*cb_log)(void *priv,int module,int log_level,const char* fmt,...);
    void       *cb_log_priv;
    /*use for configuration*/
    int       (*cb_cfg)(void *priv,const char* name,void *value,size_t vallen);
    void       *cb_cfg_priv;
    /*use for event callback*/
    int       (*cb_evt)(void *priv,int event,unsigned int wparam,unsigned long lparam,const void*data,size_t data_len);
    void       *cb_evt_priv;

}ipvp_init_t;

/*
*----------------------------------------------------------------------
*   type of capacity informations
*----------------------------------------------------------------------
*/
typedef struct
{
    unsigned int     size;                  /*self size*/
    unsigned int     flags;                 /*flags of capacity*/
#define  IPVP_CAP_FL_NONE           0           /*should be invalid*/
#define  IPVP_CAP_FL_AUDIO          (1<<0)      /*support audio,basic capacity*/
#define  IPVP_CAP_FL_AUDIO_SECURE   (1<<1)      /*support audio SRTP,basic capacity*/
#define  IPVP_CAP_FL_VIDEO          (1<<2)      /*support video*/
#define  IPVP_CAP_FL_VIDEO_SECURE   (1<<3)      /*support video SRTP*/

    /*audio capacity*/
    unsigned int    audio_codec;             /*support audio codec*/
#define  IPVP_CAP_ACODEC_CNG        (1<<0)      /*Comfort Noise in rfc3389*/
#define  IPVP_CAP_ACODEC_PCMU       (1<<1)      /*ITU-T G.711 PCM ¦Ì-Law */
#define  IPVP_CAP_ACODEC_PCMA       (1<<2)      /*ITU-T G.711 PCM A-Law */
#define  IPVP_CAP_ACODEC_G722       (1<<3)      /*ITU-T G.722 Audio*/
#define  IPVP_CAP_ACODEC_G729       (1<<4)      /*ITU-T G.729 and G.729a*/
#define  IPVP_CAP_ACODEC_iLBC       (1<<5)      /*Internet low Bitrate Codec 13.33 or 15.2 kbps in rfc3952*/
#define  IPVP_CAP_ACODEC_G726_32    (1<<6)      /*ITU-T G.726 audio with 32 kbps*/
#define  IPVP_CAP_ACODEC_G726_16    (1<<7)      /*ITU-T G.726 audio with 16 kbps*/
#define  IPVP_CAP_ACODEC_G726_24    (1<<8)      /*ITU-T G.726 audio with 24 kbps*/
#define  IPVP_CAP_ACODEC_G726_40    (1<<9)      /*ITU-T G.726 audio with 40 kbps*/
#define  IPVP_CAP_ACODEC_G723       (1<<10)     /*ITU-T G.723.1 , with 5.3 or 6.3 kbps */
#define  IPVP_CAP_ACODEC_L16PCM     (1<<11)     /*Linear PCM 16-bit audio*/
#define  IPVP_CAP_ACODEC_GSM_FR     (1<<12)     /*GSM 06.10, European GSM Full Rate Audio 13 kbps */
#define  IPVP_CAP_ACODEC_GSM_EFR    (1<<13)     /*GSM 06.60, ITU-T GSM-EFR */
#define  IPVP_CAP_ACODEC_AMR        (1<<14)     /*GSM-AMR, Adaptive Multi-Rate audio in rfc4867*/
#define  IPVP_CAP_ACODEC_AMR_WB     (1<<15)     /*ITU-T G.722.2, Adaptive Multi-Rate Wideband audio in rfc4867*/
#define  IPVP_CAP_ACODEC_SPEEX      (1<<16)     /*the Speex Codec in rfc5574*/
#define  IPVP_CAP_ACODEC_OPUS       (1<<17)     /*Opus Speech Audio Codec*/
#define  IPVP_CAP_ACODEC_PCMU_WB    (1<<18)     /*ITU-T G.711.1 PCM ¦Ì-Law in rfc5391*/
#define  IPVP_CAP_ACODEC_PCMA_WB    (1<<19)     /*ITU-T G.711.1 PCM A-Law in rfc5391*/

    unsigned int    audio_mode;             /*support mode of audio*/
#define  IPVP_CAP_AMODE_HF          (1<<0)      /*support handsfree mode*/
#define  IPVP_CAP_AMODE_HS          (1<<1)      /*support handset mode*/
#define  IPVP_CAP_AMODE_ES          (1<<2)      /*support headset mode*/
#define  IPVP_CAP_AMODE_HG          (1<<3)      /*support handset-handsfree group mode*/
#define  IPVP_CAP_AMODE_EG          (1<<4)      /*support headset-handsfree group mode*/
#define  IPVP_CAP_AMODE_DU          (1<<5)      /*support double headset group mode*/
#define  IPVP_CAP_AMODE_BTES        (1<<6)      /*support Bluetooth headset mode*/
#define  IPVP_CAP_AMODE_BTHF        (1<<7)      /*support Bluetooth handfree mode*/

    unsigned int    audio_record;           /*support record audio data*/

    unsigned int    audio_process;          /*support processing algorithm */
#define  IPVP_CAP_APROC_AEC         (1<<0)      /*acoustics echo canceller*/
#define  IPVP_CAP_APROC_PLC         (1<<1)      /*packet loss concealment*/
#define  IPVP_CAP_APROC_JIB         (1<<2)      /*jitter buffer*/
#define  IPVP_CAP_APROC_VAD         (1<<3)      /*voice activity detection*/
#define  IPVP_CAP_APROC_CNG         (1<<4)      /*comfort noise generation*/
#define  IPVP_CAP_APROC_AGC_TX      (1<<5)      /*automatic gain control in transmit path*/
#define  IPVP_CAP_APROC_AGC_RX      (1<<6)      /*automatic gain control in receive path*/
#define  IPVP_CAP_APROC_ANS         (1<<7)      /*acoustics noise suppression*/

    unsigned short  audio_aec_taillen;      /*support the max tail length of aec */
    unsigned short  audio_plc;              /*support conceal type in lost packets*/
#define  IPVP_CAP_APLC_UNSPECIFIED  0x00        /*no information is available concerning the use of PLC*/
#define  IPVP_CAP_APLC_DISABLED     0x01        /*silence is being inserted in place of lost packets*/
#define  IPVP_CAP_APLC_ENHANCED     0x10        /*an enhanced interpolation algorithm is being used*/
#define  IPVP_CAP_APLC_STANDARD     0x11        /*a simple replay or interpolation algorithm is being used*/

    unsigned short  audio_jib_min;          /*support minimum delay of jitter buffer in milliseconds*/
    unsigned short  audio_jib_max;          /*support maximum delay of jitter buffer in milliseconds*/

    unsigned short  audio_channel;          /*support number of audio channel*/
    unsigned short  audio_conference;       /*support number of audio conference way*/

    unsigned short  audio_rtcpxr;           /*support RTP Control Protocol Extended Reports of rfc3611*/
#define  IPVP_CAP_ARTCPXR_BT1       (1<<0)      /*Loss RLE Report Block, BT=1*/
#define  IPVP_CAP_ARTCPXR_BT2       (1<<1)      /*Duplicate RLE Report Block, BT=2*/
#define  IPVP_CAP_ARTCPXR_BT3       (1<<2)      /*Packet Receipt Times Report Block, BT=3*/
#define  IPVP_CAP_ARTCPXR_BT4       (1<<3)      /*Receiver Reference Time Report Block, BT=4*/
#define  IPVP_CAP_ARTCPXR_BT5       (1<<4)      /*DLRR Report Block, BT=5*/
#define  IPVP_CAP_ARTCPXR_BT6       (1<<5)      /*Statistics Summary Report Block, BT=6*/
#define  IPVP_CAP_ARTCPXR_BT7       (1<<6)      /*VoIP Metrics Report Block, BT=7*/

    unsigned short  audio_dtmf;             /*support dtmf event */
#define  IPVP_CAP_ADTMF_RX_RELAY    (1<<0)      /*play dtmf tone on receive 2833 event*/
#define  IPVP_CAP_ADTMF_TX_RELAY    (1<<1)      /*transmit dtmf tone as 2833 event if directly call*/
#define  IPVP_CAP_ADTMF_RX_DETECT   (1<<2)      /*detect dtmf tone, translate it to event*/
#define  IPVP_CAP_ADTMF_TX_DETECT   (1<<3)      /*detect dtmf tone, translate it to 2833 packets*/

    /*video capacity*/
    unsigned int    video_codec;            /*support video codec*/
#define  IPVP_CAP_VCODEC_H263        (1<<0)
#define  IPVP_CAP_VCODEC_H263_1998   (1<<1)
#define  IPVP_CAP_VCODEC_H264        (1<<2)
#define  IPVP_CAP_VCODEC_H265        (1<<3)
#define  IPVP_CAP_VCODEC_MPEG2       (1<<4)
#define  IPVP_CAP_VCODEC_MPEG4       (1<<5)
#define  IPVP_CAP_VCODEC_MJPEG       (1<<6)

    unsigned short  video_channel;          /*support number of video channel*/
    unsigned short  video_conference;       /*support number of video conference way*/

    /*other capacity*/

    /*reserved*/
    unsigned int    reserved[8];
}ipvp_capacity_t;


/*
*----------------------------------------------------------------------
*   type of private capset
*----------------------------------------------------------------------
*/
typedef struct
{
    unsigned char   payload_type;           /* private codec payload(117)*/
    char            codec_name[128];        /* must end with '\0'*/
    unsigned int    clock_rate;             /* 90000*/
    char            capacity_string[1024];
}ipvp_capset_t;

/*
*----------------------------------------------------------------------
*  type of voice quality report
*----------------------------------------------------------------------
*/
typedef struct
{
    /*
    * Mandatory part
    */
    unsigned char       sd_pt;          /* SessionDescription - PayloadType */
    unsigned char       sd_plc;         /* SessionDescription - PacketLossConcealment */
    unsigned char       sd_ssup;        /* SessionDescription - SilenceSuppressionState */
    unsigned char       jb_jba;         /* JitterBuffer       - JitterBufferAdaptive */

    unsigned char       jb_jbr;         /* JitterBuffer       - JitterBufferRate */
    unsigned char       pl_nlr;         /* PacketLoss         - NetworkPacketLossRate 
                                        the result of the division by 256, MUST transform when display */
    unsigned char       pl_jdr;         /* PacketLoss         - JitterBufferDiscardRate 
                                        the result of the division by 256, MUST transform when display */
    unsigned char       bgl_bld;        /* BurstGapLoss       - BurstLossDensity 
                                        the result of the division by 256, MUST transform when display */

    unsigned char       bgl_gld;        /* BurstGapLoss       - GapLossDensity 
                                        the result of the division by 256, MUST transform when display */
    unsigned char       bgl_gmin;       /* BurstGapLoss       - MinimumGapThreshold */
    signed   char       sign_sl;        /* Signal             - SignalLevel */
    signed   char       sign_nl;        /* Signal             - NoiseLevel */

    signed   char       sign_rerl;      /* Signal             - ResidualEchoReturnLoss */
    char                reserved8_1[3];

    unsigned char       qe_rcq;         /* QualityEstimates   - ConversationalQualityR*/
    unsigned char       qe_extri;       /* QualityEstimates   - ExternalR-In*/
    unsigned char       qe_moslq;       /* QualityEstimates   - MOS-LQ 
                                        it is expressed as an integer in the range 10 to 50,corresponding to MOS x 10, and a value of 127 stands for unavailable */
    unsigned char       qe_moscq;       /* QualityEstimates   - MOS-CQ 
                                        it is expressed as an integer in the range 10 to 50,corresponding to MOS x 10, and a value of 127 stands for unavailable */

    unsigned short      sd_pps;         /* SessionDescription - PacketsPerSecond */
    unsigned short      jb_jbn;         /* JitterBuffer       - JitterBufferNominal */
    unsigned short      jb_jbm;         /* JitterBuffer       - JitterBufferMax */
    unsigned short      jb_jbx;         /* JitterBuffer       - JitterBufferAbsMax */

    unsigned short      bgl_bd;         /* BurstGapLoss       - BurstDuration */
    unsigned short      bgl_gd;         /* BurstGapLoss       - GapDuration */

    unsigned short      delay_rtd;      /* Delay              - RoundTripDelay */
    unsigned short      delay_esd;      /* Delay              - EndSystemDelay */
    unsigned short      delay_sowd;     /* Delay              - SymmOneWayDelay*/
    unsigned short      delay_iaj;      /* Delay              - InterarrivalJitter */

    /*
    * Optional part
    */
    unsigned char       qe_rlq;         /* QualityEstimates   - ListeningQualityR */
    unsigned char       qe_extro;       /* QualityEstimates   - ExternalR_Out*/
    char                reserved8_2[2];

    unsigned short      sd_fpp;         /* SessionDescription - FramesPerPacket */
    unsigned short      sd_sr;          /* SessionDescription - SampleRate */
    unsigned short      sd_fd;          /* SessionDescription - FrameDuration*/
    unsigned short      sd_fo;          /* SessionDescription - FrameOctets*/
    unsigned short      delay_owd;      /* Delay              - OneWayDelay */
    unsigned short      delay_maj;      /* Delay              - MeanAbsoluteJitter */

    /*
    * to be complete
    */
    /*
    Timestamps          -   StartTime       UTC
    Timestamps          -   StopTime        UTC
    SessionDescription  -   PayloadDesc     text  such as "PCMU","G722", "iLBC" ect.
    SessionDescription  -   FmtpOptions     text  such as "18 annexb=off" ,"101 0-15" ect.
    QualityEstimates    -   RLQEstAlg       text  such as "P.564","G.107" ect
    QualityEstimates    -   RCQEstAlg       text  such as "P.564","G.107" ect
    QualityEstimates    -   ExtRInEstAlg    text  such as "P.564","G.107" ect
    QualityEstimates    -   ExtROutEstAlg   text  such as "P.564","G.107" ect
    QualityEstimates    -   MOSLQEstAlg     text  such as "P.564","G.107" ect
    QualityEstimates    -   MOSCQEstAlg     text  such as "P.564","G.107" ect
    QualityEstimates    -   QoEEstAlg       text  such as "P.564","G.107" ect  
    */

}ipvp_vq_metrics_t;

typedef struct
{
    /*
    * Mandatory part
    */
    unsigned int        pkt_cnt;        /* Sender Packet count*/
    unsigned int        oct_cnt;        /* Sender Octet count */
    unsigned int        pkt_lost;       /* Received Packets lost*/

    unsigned short      frac_lost;      /* Received Fraction Lost 
                                        the result of the division by 256, MUST transform when display */
    unsigned short      jitter;         /* Interarrival jitter in RTP timestamp units*/

    /*
    * Optional part
    */
    unsigned int        lsr_ts;         /* Receiver Report last SR timestamp */
    unsigned int        dlsr;           /* Receiver Report delay since last SR  */

    unsigned int        rtp_ts;         /* RTP timestamp of the statistics reported*/
    unsigned short      xhi_seqnum;     /* Received Extended Highest Sequence Number*/
    unsigned short      reserved16_1;

}ipvp_vq_statics_t;

typedef struct
{
    /*
    * header
    */
    unsigned short      length;     /*size of THIS struct*/
    unsigned char       version;
#define  IPVP_VQR_VER1          1
#define  IPVP_VQR_VER2          2
    unsigned char       direct;
#define  IPVP_VQR_DIR_NONE      0
#define  IPVP_VQR_DIR_LOCAL     1
#define  IPVP_VQR_DIR_REMOTE    2

    /*
    * body
    */
    unsigned int        local_ssrc;
    unsigned int        remote_ssrc;

    time_t              start_time;
    time_t              current_time;

    unsigned int        pkts_from_net;
    unsigned int        bytes_from_net;

    char                codec_name[IPVP_MAX_CODECNAME];
    char                remote_ip_addr[IPVP_MAX_ADDR_LEN];
    unsigned short      local_port;
    unsigned short      remote_port;

    char                alert_section_name[IPVP_MAX_ALERT_LEN];
    unsigned int        severity;
#define  IPVP_VQR_SEV_CLEAR    0
#define  IPVP_VQR_SEV_WARNIN   1
#define  IPVP_VQR_SEV_CRITIC   2

    ipvp_vq_statics_t   statics;
    ipvp_vq_metrics_t   metrics;

}ipvp_vq_report_t;


/*
*----------------------------------------------------------------------
* type of basic
*----------------------------------------------------------------------
*/

/*
*   type of network address
*   including src/dst address
*/
typedef struct
{
    unsigned char           disable;    /*default to be 0 unless you want to disable rtp/rtcp*/

    unsigned char           af_type;    /*AF_INET or AF_INET6*/
    unsigned char           sa_len;     /*real len of 'src' or 'dst'*/
    unsigned char           sock_type;  /*sock type such as SOCK_STREAM SOCK_DGRAM*/
    union
    {
        struct sockaddr_in  sa4;
        struct sockaddr_in6 sa6;
    }src;
    union
    {
        struct sockaddr_in  sa4;
        struct sockaddr_in6 sa6;
    }dst;
}ipvp_addr_t;

/*
*   type of window rect
*   --just for video
*/
typedef struct
{
    unsigned short  left;
    unsigned short  top;
    unsigned short  right;
    unsigned short  bottom;
}ipvp_rect_t;

/*
*----------------------------------------------------------------------
* type of config
*----------------------------------------------------------------------
*/

/*
*   type of rtp config
*/
typedef struct
{
    /*header*/
    unsigned short  flags;                      /*control flags of ??*/
    unsigned short  size;                       /*size of self*/

    /*rtp config*/
    int             detect;                     /*rtp detect codec which use static payload*/
    int             keep_alive;                 /*rtp keep alive on hold*/
    int             symmetrical;                /*rtp mirror symmetry return back to the address come from*/
    int             detect_srtp;                /*detect and filter srtp when recv rtp*/
    int             adapt_ipv6;                 /*ipv4 recv ipv6 packet*/
    int             nopkt_timeout;              /*timeout for no packet detect*/

    int             reserved[8];
}ipvp_rtpcfg_t;

/*
*   type of DTMF config
*/
typedef struct
{
    /*header*/
    unsigned short  flags;                      /*control flags of ??*/
    unsigned short  size;                       /*size of self*/

    /*DTMF config*/
    int             duration;                   /*DTMF duration*/
    int             repetition;                 /*DMTF end packet repetition*/
    int             volume;                     /*DTMF packet volume*/                   
    int             relay;                      /*play remote RFC2833 packet*/
    int             dtmf_flash;                 /*DTMF_D be used to DTMF_E*/

    int             reserved[8];
}ipvp_dtmfcfg_t;

/*
*   type of speech control info
*   including audio+SRTP+vido+SRTP
*/

/*
*----------------------------------------------------------------------
* type of audio speech
*----------------------------------------------------------------------
*/

/*
*   type of audio stats
*   --FIXME:to be finished
*/
    typedef struct
    {
        /*header*/
        unsigned short  flags;                          /*control flags of ??*/
        unsigned short  size;                           /*size of self*/

        /*codec info*/
        char            tx_codec[IPVP_MAX_CODECNAME];    /*transmit codec name*/
        char            rx_codec[IPVP_MAX_CODECNAME];    /*receive  codec name*/
        unsigned int    tx_bitrate;                     /*transmit bit rate*/
        unsigned int    rx_bitrate;                     /*receive  bit rate*/
        unsigned int    tx_samplerate;                  /*transmit sample rate*/
        unsigned int    rx_samplerate;                  /*receive  sample rate*/

        /*packet info*/
        unsigned int    tx_rtp;                         /*transmit rtp packets count*/
        unsigned int    rx_rtp;                         /*receive  rtp packets count*/
        unsigned int    tx_rtp_bytes;                   /*transmit rtp bytes count*/
        unsigned int    rx_rtp_bytes;                   /*receive  rtp bytes count*/
        unsigned int    tx_rtcp;                        /*transmit rtcp packets count*/
        unsigned int    rx_rtcp;                        /*receive  rtcp packets count*/
        unsigned short  tx_lost_frac;                   /*transmit packets lost rate, depend on remote feedback via RTCP*/
        unsigned short  rx_lost_frac;                   /*receive  packets lost rate*/
        unsigned int    tx_lost_total;                  /*transmit packets lost count, depend on remote feedback via RTCP*/
        unsigned int    rx_lost_total;                  /*receive  packets lost count*/

        /*jitter info*/
        unsigned short  tx_jit_cur;                     /*transmit interarrival jitter, depend on remote feedback via RTCP*/
        unsigned short  rx_jit_cur;                     /*receive  interarrival jitter*/
        unsigned short  tx_jit_avg;                     /*transmit average jitter, calculate by the history of RTCP*/
        unsigned short  rx_jit_avg;                     /*receive  average jitter*/
        unsigned short  tx_jit_max;                     /*transmit maximum jitter, calculate by the history of RTCP*/
        unsigned short  rx_jit_max;                     /*receive  maximum jitter*/
        unsigned short  tx_jit_min;                     /*transmit minimum jitter, calculate by the history of RTCP*/
        unsigned short  rx_jit_min;                     /*receive  minimum jitter*/
        unsigned short  tx_delay_rt;                    /*transmit round trip delay, may be the same as Rx path*/
        unsigned short  rx_delay_rt;                    /*receive round trip delay*/
        unsigned short  tx_jb_avg;                      /*transmit network  average jitter*/
        unsigned short  tx_jb_max;                      /*transmit network  maximum jitter*/
        unsigned short  tx_jb_min;                      /*transmit network  minimum jitter*/
        unsigned short  rx_jb_avg;                      /*receive network  average jitter*/
        unsigned short  rx_jb_max;                      /*receive network  maximum jitter*/
        unsigned short  rx_jb_min;                      /*receive network  minimum jitter*/

        /*diagnose info*/
        unsigned int    tx_codec_ptype;                 /*transmit codec  ptype*/
        unsigned int    rx_codec_ptype;                 /*receive codec  ptype*/
        unsigned char   tx_mos_conver;                  /*transmit conversational mos*/
        unsigned char   rx_mos_conver;                  /*receive conversational mos*/
        unsigned char   tx_mos_listen;                  /*transmit listinening mos*/
        unsigned char   rx_mos_listen;                  /*receive listinening mos*/
        unsigned char   mos_sending;                    /*sending mos*/
        unsigned char   mos_network;                    /*network mos*/

        unsigned char   reserved[24];                   /*reserved*/
    }ipvp_astats_t;

    /*
    *   type of QoE stats
    */
    typedef struct
    {
        /*header*/
        unsigned short  flags;                          /*control flags of ??*/
        unsigned short  size;                           /*size of self, now 440 bytes*/

        /*codec info*/
        char            tx_codec[IPVP_MAX_CODECNAME];   /*transmit codec name*/
        char            rx_codec[IPVP_MAX_CODECNAME];   /*receive  codec name*/
        unsigned int    tx_codec_ptype;                 /*transmit codec  ptype*/
        unsigned int    rx_codec_ptype;                 /*receive codec  ptype*/
        unsigned short  tx_ptime;                       /*transmit packetization period*/
        unsigned short  rx_ptime;                       /*receive packetization period*/
        unsigned int    tx_bitrate;                     /*transmit bit rate*/
        unsigned int    rx_bitrate;                     /*receive  bit rate*/
        unsigned int    tx_samplerate;                  /*transmit sample rate*/
        unsigned int    rx_samplerate;                  /*receive  sample rate*/
        unsigned int    tx_ssrc;                        /*transmit ssrc*/
        unsigned int    rx_ssrc;                        /*receive  ssrc*/

        /*packet info*/
        unsigned int    tx_rtp;                         /*transmit rtp packets count*/
        unsigned int    rx_rtp;                         /*receive  rtp packets count*/
        unsigned int    tx_rtp_bytes;                   /*transmit rtp bytes count*/
        unsigned int    rx_rtp_bytes;                   /*receive  rtp bytes count*/
        unsigned int    tx_rtcp;                        /*transmit rtcp packets count*/
        unsigned int    rx_rtcp;                        /*receive  rtcp packets count*/
        unsigned int    tx_lost_total;                  /*transmit packets lost count, depend on remote feedback via RTCP*/
        unsigned int    rx_lost_total;                  /*receive  packets lost count*/
        
        float           tx_lost_rate_cur;               /*Current transmit packets lost rate, depend on remote feedback via RTCP*/
        float           tx_lost_rate_avg;               /*Average transmit packets lost rate*/
        float           tx_lost_rate_max;               /*Maximum transmit packets lost rate*/
        float           rx_lost_rate_cur;               /*Current receive  packets lost rate*/
        float           rx_lost_rate_avg;               /*Average receive  packets lost rate*/
        float           rx_lost_rate_max;               /*Maximum receive  packets lost rate*/

        /*jitter info*/
        unsigned short  tx_jit_cur;                     /*Current transmit interarrival jitter, depend on remote feedback via RTCP*/
        unsigned short  tx_jit_avg;                     /*Average transmit interarrival jitter */
        unsigned short  tx_jit_max;                     /*Maximum transmit interarrival jitter */
        unsigned short  tx_jit_min;                     /*Minimum transmit interarrival jitter */
        float           tx_jit_sd;                      /*Standard deviation of transmit interarrival jitter */
        unsigned short  rx_jit_cur;                     /*Current transmit receive interarrival jitter */
        unsigned short  rx_jit_avg;                     /*Average transmit receive interarrival jitter average */
        unsigned short  rx_jit_max;                     /*Maximum transmit receive interarrival jitter maximum */
        unsigned short  rx_jit_min;                     /*Minimum transmit receive interarrival jitter minimum */
        float           rx_jit_sd;                      /*Standard deviation of receive interarrival jitter standard deviation*/

        float           tx_netjit_avg;                  /*Average transmit network jitter*/
        float           tx_netjit_max;                  /*Maximum transmit network jitter*/
        float           tx_netjit_min;                  /*Minimum transmit network jitter*/
        float           tx_netjit_sd;                   /*Standard deviation of transmit network  minimum jitter*/
        float           rx_netjit_avg;                  /*Average receive network jitter*/
        float           rx_netjit_max;                  /*Maximum receive network jitter*/
        float           rx_netjit_min;                  /*Minimum receive Minimum network jitter*/
        float           rx_netjit_sd;                   /*Standard deviation of receive network  minimum jitter*/

        unsigned short  delay_rtd_cur;                  /*transmit round trip delay, may be the same as Rx path*/
        unsigned short  delay_rtd_avg;                  /*Average transmit round trip delay*/
        unsigned short  delay_rtd_max;                  /*Maximum transmit round trip delay*/
        unsigned short  delay_rtd_min;                  /*Minimum transmit round trip delay*/


        float           delay_owd_cur;                  /*The computed relative one way delay of the peer, only inbound*/
        float           delay_owd_avg;                  /*Average one way delay*/
        float           delay_owd_max;                  /*Maximum one way delay*/
        float           delay_owd_min;                  /*Minimum one way delay*/

        unsigned int    gap_occur;                      /*Number of instances of Gap.*/
        float           gap_density;                    /*Average density of Gap.*/
        unsigned int    gap_duration;                   /*Average duration of Gap.*/
        unsigned int    burst_occur;                    /*Number of instances of Burst*/
        float           burst_density;                  /*Average density of Burst.*/
        unsigned int    burst_duration;                 /*Average duration of Burst.*/

        unsigned short  rx_jb_avg;                      /*receive  average jitter buffer*/
        unsigned short  rx_jb_max;                      /*receive  maximum jitter buffer*/
        unsigned short  rx_jb_min;                      /*receive  minimum jitter buffer*/
        unsigned short  rx_jb_sd;                       /*receive jitter buffer underrun count*/
        unsigned short  rx_jb_over;                     /*receive jitter buffer overrun count*/
        unsigned short  rx_jb_under;                    /*receive jitter buffer underrun count*/

        /*diagnose info*/
        float           tx_mos_conver;                  /*transmit conversational mos(MOS-CQ)*/
        float           tx_mos_cq_min;                  /*Minimum of transmit conversational mos(MOS-CQ)*/
        float           tx_mos_cq_max;                  /*Absolute Maximum of transmit conversational mos(MOS-CQ)*/

        float           rx_mos_conver;                  /*receive conversational mos(MOS-CQ)*/
        float           rx_mos_cq_min;                  /*Minimum of receive conversational mos(MOS-CQ)*/
        float           rx_mos_cq_max;                  /*Absolute Maximum of receive conversational mos(MOS-CQ)*/

        float           tx_mos_listen;                  /*transmit listinening mos(MOS-LQ),SendListenMOS*/
        float           tx_mos_lq_min;                  /*Minimum of transmit listinening mos(MOS-LQ)*/
        float           tx_mos_lq_max;                  /*Absolute Maximum of transmit listinening mos(MOS-LQ)*/
        char            tx_mos_alg[8];                  /*transmit listen MOS alg*/

        float           rx_mos_listen;                  /*receive  listinening mos(MOS-LQ),RecvListenMOS*/
        float           rx_mos_lq_min;                  /*Minimum of receive listinening mos(MOS-LQ)*/
        float           rx_mos_lq_max;                  /*Absolute Maximum of receive listinening mos(MOS-LQ)*/
        char            rx_mos_alg[8];                  /*receive listen MOS alg*/

        float           rx_degra_avg;                   /*DegradationAvg,is  difference between the mos_cq_avg and the maximum
                                                          possible MOS-LQO for the audio codec */
        float           rx_degra_max;                   /*Maximum MOS degradation,is  difference between the mos_cq_min and the maximum
                                                          possible MOS-LQO for the audio codec */

        signed char     tx_sig_sl;                      /*The average energy level of sent audio classified as speech*/
        signed char     tx_sig_nl;                      /*The average energy level of sent audio classified as noise*/

        signed char     rx_sig_sl;                      /*The average energy level of received audio classified as speech*/
        signed char     rx_sig_nl;                      /*The average energy level of received audio classified as noise*/

        float           init_sl_rms;                    /*The root-mean-square of the received signal for the first 30 seconds of the call.*/
        float           render_sl;                      /*Average render speech level after dynamic range compression or
                                                          analog gain control is applied*/
        float           render_nl;                      /*Average render noise level after dynamic range compression or
                                                          analog gain control is applied*/
        float           render_loop_sl;                 /*Average level of speaker loopback signal (after any device offload
                                                          effects have been applied)*/

        float           micin_echo_per;                 /*Percentage prior echo cancellation.*/
        float           tx_echo_per;                    /*Percentage after echo cancellation.*/

        float           tx_tsdif_rate;                  /*Microphone or capture device clock drift rate*/
        float           tx_tserr_time;                  /*Noise in timestamp information from microphone or capture device*/
        float           rx_tsdif_rate;                  /*Speaker or render device clock drift rate*/
        float           rx_tserr_time;                  /*Noise in timestamp information from speaker or render device*/

        signed char     rx_agc_gain;                    /*the post AGC gain*/

        unsigned char   aec_inuse;                      /*echo cancellation in use*/
        unsigned short  aec_tail;                       /*echo cancellation tail*/

        /* speaker or microphone glitch rate*/
        unsigned char   tx_mic_gt_rate;                 /*Average glitches per 5 minutes for the microphone capture*/
        unsigned char   rx_spk_gt_rate;                 /*Average glitches per 5 minutes for the loudspeaker rendering*/

        unsigned char   vsentry_causes;                 /*The bit flag indicating the reason(s) the AEC entered halfduplex mode*/
        unsigned char   echoevent_causes;               /*The bit flag indicating the reasons the DeviceEchoEvent was detected*/

        /*tr104 info*/
        unsigned char   tx_sil_sup;                     /*transmit silence suppression*/
        unsigned char   rx_sil_sup;                     /*receive silence suppression*/

        char            LastRTPSendTime[32];            /*the last rtp send time*/
        char            LastRTCPSendTime[32];           /*the last rtcp send time*/
        char            LastRTPReceiveTime[32];         /*the last rtp receive time*/
        char            LastRTCPReceiveTime[32];        /*the last rtcp receive time*/  
        float           rx_RatioConcealedSamplesAvg;    /*average of concealed samples ratio*/
        float           tx_RatioConcealedSamplesAvg;    
        float           rx_RatioStretchedSamplesAvg;    /*average of stretched samples ratio*/
        float           tx_RatioStretchedSamplesAvg;
        float           rx_RatioCompressedSamplesAvg;   /*average of compressed samples ratio*/
        float           tx_RatioCompressedSamplesAvg;
        float           ConcealRatioMax;                /*max of concealed samples ratio in 10 seconds*/
        float           ConcealRatioSd;                 /*standard deviation of concealed samples ratio in 10 seconds*/
        float           HealerPacketDropRatio;          /*Ratio of audio packets dropped by healer over total number of audio packets received by healer*/
        float           HealerFECPacketUsedRatio;       /*Ratio of used FEC packets over total number of received FEC packets*/
        unsigned int    MaxCompressedSamples;           /*Maximum number of contiguous audio packets compressed by the healer*/
        signed char     SpeakerFeedbackMicIn;           /*Signal level of the leakage of Loudspeaker output into the microphone input,unit is dBoV*/
        signed char     SpeechLevelMicIn;               /*The speech level into the microphone at a given endpoint,unit is dBoV*/
        signed char     SpeechLevelPostProcess;         /*Overall average speech level sent from an endpoint after all processing,unit is dBoV*/
        signed char     SignalLevelLoudSpeaker;         /*Input level to the loudspeaker or headphone input*/
        unsigned int    SpeakerClipRate;                /*Average clips per 5 minutes during the call for the loudspeaker rendering*/
        signed char     RxAGCSignalLevel;               /*Signal level received at the automatic gain control for the inbound audio stream*/        
        signed char     RxAGCNoiseLevel;                /*Noise level received at the automatic gain control for the inbound audio stream*/
        float           InitialSignalLevelRMS;          /*The root-meansquare of the received signal for the first 30 seconds of the call*/
        float           AudioTimestampDriftRateSpk;     /*Speaker or render device clock drift rate,percent*/
        float           AudioTimestampErrorSpkMs;       /*Noise in timestamp information from speaker or render device, unit is ms*/
        char            rx_AudioFECUsed;                /*true=used FEC, false=not used*/
        char            tx_AudioFECUsed;
        float           DecodeStereoPercent;            /*Percentage of audio decoded as stereo*/          
        float           AecRenderStereoPercent;         /*Percentage of call processed by AEC as stereo render*/
        float           AudioPostFECPLR;                /*Reports packet loss rate after FEC has been applied for audio. Value between 0.00 and 1.00.*/
        float           PacketReorderRatio;             /*Ratio of packets received that were out of sequence during the session*/          
        unsigned int    PacketReorderDepthAvg;          /*Average of reorder depth*/
        unsigned int    PacketReorderDepthMax;          /*Maximum of reorder depth*/
        float           BurstLossLength1;               /*Ratio of lost single lost packet over the total number packets for the session*/
        float           BurstLossLength2;               /*Ratio of 2 consecutive lost packets over the total number packets for the session*/
        float           BurstLossLength3;               /*Ratio of 3 consecutive lost packets*/
        float           BurstLossLength4;               /*Ratio of 4 consecutive lost packets*/
        float           BurstLossLength5;               /*Ratio of 5 consecutive lost packets*/
        float           BurstLossLength6;               /*Ratio of 6 consecutive lost packets*/
        float           BurstLossLength7;               /*Ratio of 7 consecutive lost packets*/    
        float           BurstLossLength8OrHigher;       /*Ratio of 8 or more consecutive lost packets*/
        float           FECRecvOnPercent;               /*Percentage of session where FEC was enabled for packets received*/
        float           FECRecvDistance1;               /*Percentage of session where packets with FEC distance of 1 was received*/        
        float           FECRecvDistance2;               /*Percentage of session where packets with FEC distance of 2 was received*/
        float           FECRecvDistance3;               /*Percentage of session where packets with FEC distance of 3 was received*/
        float           FECRecvDistance4;               /*Percentage of session where packets with FEC distance of 4 was received*/
        float           FECRecvDistance5;               /*Percentage of session where packets with FEC distance of 5 was received*/
        float           FECRecvDistance6;               /*Percentage of session where packets with FEC distance of 6 was received*/
        float           FECRecvDistance7;               /*Percentage of session where packets with FEC distance of 7 was received*/
        float           FECRecvDistance8OrHigher;       /*Percentage of session where packets with FEC distance of 8 or larger was received*/
        float           FECRecvScheme;                  /*FEC scheme,0 ¨C codec level FEC (in-band),1 ¨Cexternal FEC (RFC 2198)*/                
        float           FECRecvRedundancy;              /*Average FEC redundancy for packets received*/
        unsigned int    HealerPushCount;                /*Number of packets pushed into the audio healer/jitter buffer from network*/
        unsigned int    HealerPullCount;                /*Number of packets pulled from the audio healer/jitter buffer to be rendered or mixed*/
        char            CountGoodNWState;
        unsigned short  TimeInGoodNWState;
        char            CountPoorNWState;
        unsigned short  TimeInPoorNWState;
        char            CountBadNWState;
        unsigned short  TimeInBadNWState;
        char            CountCatastrophicNWState;
        unsigned short  TimeInCatastrophicNWState;
        float           DegradationJitterAvg;           /*The average fraction of the DegradationAvg that was caused by inter-arrival packet jitter*/
        float           DegradationPacketLossAvg;       /*The average fraction of the DegradationAvg that was caused by packet loss*/
        float           LossCongestionPercent;          /*Percentage of the call that congestion is detected due to high loss rate*/
        float           DelayCongestionPercent;         /*Percentage of the call that congestion is detected due to high one way delay*/
        float           ContentionDetectedPercent;      /*Percentage of the call that contention is detected*/
        signed char     BackGroundNoiseMicIn;           /*Background noise input to the microphone,unit is dBoV*/
        signed char     BackGroundNoiseSent;            /*Background noise left over after all processing,unit is dBoV*/
        signed char     LocalSpeechToEcho;              /*speech level to echo level,unit is dB*/
        unsigned int    MicClipRate;                    /*Average clips per 5 minutes during the call for the microphone capture*/
        float           AudioTimestampDriftRateMic;     /*Microphone or capture device clock drift rate*/
        float           AudioTimestampErrorMicMs;       /*Noise in timestamp information from microphone or capture device*/
        float           EncodeStereoPercent;            /*Percentage of audio encoded as stereo*/
        float           AecCaptureStereoPercent;        /*Percentage of call processed by AEC as stereo capture*/
        float           SendMutePercent;                /*Percentage of session duration where the client was muted*/
        unsigned int    CaptureOffloadedEffectsAudio;   /*Bitmask representing which audio capture DSP effects were used in hardware*/
        float           LocalConversationalMOS;         /*Conversational clarity index for remote party, as described in [ITUP.562] section 6.3*/

        float           NetworkSendQualityEventRatio;   /*Fraction of call that the network was causing poor quality of the audio sent*/
        float           NetworkReceiveQualityEventRatio;/*Fraction of call that the network was causing poor quality of the audio received*/
        float           NetworkDelayEventRatio;         /*Fraction of the call that the reporting endpoint detected the network delay was significant enough to impact the ability to have real-time two-way communication*/
        float           NetworkBandwidthLowEventRatio;  /*Fraction of the call that the reporting endpoint detected the available bandwidth or bandwidth policy was low enough to cause poor quality of the audio sent*/
        float           DeviceHalfDuplexAECEventRatio;  /*Fraction of the call that the AEC in half duplex mode,*/
        float           DeviceRenderNotFunctioningEventRatio;   /*Fraction of the call that the reporting endpoint detected the render device was not working properly*/
        float           DeviceCaptureNotFunctioningEventRatio;  /*Fraction of the call that the reporting endpoint detected the capture device was not working properly*/
        float           DeviceGlitchesEventRatio;               /*Fraction of the call that the reporting endpoint detected glitches or gaps in the audio played or captured that caused poor quality of the audio being sent or received.*/
        float           DeviceLowSNREventRatio;                 /*Fraction of the call that the low SNR caused poor quality of the audio being sent*/
        float           DeviceLowSpeechLevelEventRatio;         /*Fraction of the call that the low speech level that caused poor quality of the audio being sent*/
        float           DeviceClippingEventRatio;               /*Fraction of the call that the clipping caused poor quality of the audio being sent*/
        float           DeviceEchoEventRatio;                   /*Fraction of the call that the echo caused poor quality of the audio being sent*/
        float           DeviceNearEndToEchoRatioEventRatio;     /*Fraction of the call that the ratio of the near end signal level to the echo level caused poor quality of the audio being sent*/
        float           DeviceMultipleEndpointsEventCount;      /*Number of times during the call that the reporting endpoint detected multiple endpoints in the same room or acoustic environmen*/
        float           DeviceHowlingEventCount;                /*Number of times during the call that two or more endpoints in the same room caused howling*/
        float           DeviceRenderZeroVolumeEventRatio;       /*Fraction of the call that device render volume is set to 0*/
        float           DeviceRenderMuteEventRatio;             /*Fraction of the call that device render is muted*/

        unsigned short  reserved[33];                   /*reserved*/
    }ipvp_qoestats_t;


/*
*   type of audio codec
*   --NOT used so far!but should be replace in ${ipvp_audio_t}
*/
typedef struct
{
    /*
    * Mandatory part
    */
    char            codec_name[IPVP_MAX_CODECNAME]; /*codec name*/
    unsigned short  codec_ptype;                    /*codec ptype*/
    unsigned short  codec_bitrate;                  /*codec bit rate*/
    unsigned short  codec_ptime;                    /*codec packet time in ms*/
    unsigned short  codec_clock;                    /*codec clock rate*/

    /*
    * Optional part
    */
    unsigned short  ext_octet_align;                /*octet align for amrwb*/
    unsigned short  ext_toc_mode;                   /*toc mode for amrwb*/
    unsigned short  ext_annexa;                     /*annexa:cng mode */

    unsigned short  local_maxplaybackrate;          /*local,maximum decode sampling rate*/
    unsigned short  local_maxcapturerate;           /*local,maximum encode sampling rate*/
    unsigned short  remote_maxplaybackrate;         /*remote,maximum decode sampling rate*/
    unsigned short  remote_maxcapturerate;          /*remote,maximum encode sampling rate*/
    unsigned short  remote_minplaybackrate;         /*remote,minimum decode sampling rate*/
    unsigned short  remote_mincapturerate;          /*remote,minimum encode sampling rate*/

    unsigned short  remote_maxbitrate;              /*remote,maximum decode bit rate*/
    unsigned short  remote_minbitrate;              /*remote,minimum decode bit rate*/

    unsigned char   evs_cmr;
    unsigned char   version;                        /*codec version*/

    unsigned short  codec_opts;
#define IPVP_CODEC_BIT_AMRWBIO       (1<<0)         /*AMR-WB IO mode*/
#define IPVP_CODEC_BIT_HFONLY        (1<<1)         /*full head payload*/
#define IPVP_CODEC_BIT_DTXSEND       (1<<2)         /*send DTX*/
#define IPVP_CODEC_BIT_DTXRECV       (1<<3)         /*receive DTX*/
#define IPVP_CODEC_BIT_STEREO        (1<<4)         /*stereo*/
#define IPVP_CODEC_BIT_INBANDFEC     (1<<5)         /*use inband fec*/
#define IPVP_CODEC_BIT_USEYLRTX      (1<<6)         /*useylrtx*/

    unsigned short  reserved[5];                    /*for reserved */
}ipvp_acodec_t;

/*
*   type of rtp & rtcp multiplex params
*   Reference: ITU-T Rec. H.460.19
*/
typedef struct
{
    unsigned int    rtp_multiplex_enable;           /*0: disable; 1 enable*/
    unsigned int    rtp_multiplex_id;
    unsigned int    rtcp_multiplex_enable;          /*0: disable; 1 enable*/
    unsigned int    rtcp_multiplex_id;
}ipvp_multiplex_t;

typedef struct
{
    /*header:FIXME:could i split ${32:flag} into ${16:flag} and ${16:size}*/
    unsigned short  flag;                           /*control flags of IPVP_FL_xxx*/
#define  IPVP_ADDR_FL_INACTIVE  0x0000                  /*inactive*/
#define  IPVP_ADDR_FL_RECVONLY  0x0001                  /*recv*/
#define  IPVP_ADDR_FL_SENDONLY  0x0002                  /*send*/
#define  IPVP_ADDR_FL_SENDRECV  (IPVP_ADDR_FL_SENDONLY|IPVP_ADDR_FL_RECVONLY)
#define  IPVP_ADDR_FL_SENDEVNT  0x0004                  /*send dtmf event*/
#define  IPVP_ADDR_FL_PAGING    0X0008                  /*recv paging*/
#define  IPVP_ADDR_FL_MAX       (IPP_ADDR_RECVONLY|IPP_ADDR_SENDONLY|IPP_ADDR_SENDEVNT|IPP_ADDR_PAGING)

    unsigned short  size;                           /*size of self*/

    /*address*/
    ipvp_addr_t     addr_rtp;                       /*RTP address*/
    ipvp_addr_t     addr_rtcp;                      /*RTCP address*/

    /*codec:should be replace by ${ipvp_acodec_t}*/
    char            codec_name[IPVP_MAX_CODECNAME]; /*codec name*/
    unsigned short  codec_ptype;                    /*codec ptype*/
    unsigned short  codec_clock;                    /*codec clock rate*/
    unsigned short  codec_rate;                     /*codec bit rate,MUST divide 10 because superHD codec will over range*/
    unsigned short  event_ptype;                    /*event ptype*/
    unsigned short  event_clock;                    /*event clock rate*/
    unsigned short  ptime;                          /*packetize time*/

    /*SRTP*/
    unsigned char   enc_key[IPVP_MAX_SRTPKEY];      /*srtp encrypt key*/
    unsigned char   dec_key[IPVP_MAX_SRTPKEY];      /*srtp decrypt key*/

    /*SRTCP*/
    unsigned char   rtcp_enc_key[IPVP_MAX_SRTPKEY]; /*srtp encrypt key*/
    unsigned char   rtcp_dec_key[IPVP_MAX_SRTPKEY]; /*srtp decrypt key*/

    /*extra MUST be below:*/
    /*...*/
    unsigned short  ext_octet_align;                /*octet align for amrwb*/
    unsigned short  ext_toc_mode;                   /*toc mode for amrwb*/
    unsigned short  ext_annexa;                     /*annexa:cng mode */

    ipvp_acodec_t   codec_list[IPVP_MAX_CODEC];     /*codec list support*/
    int             codec_list_cnt;                 /*valid codec*/

    /*loop back*/
    signed char     loopback_type;                  /*0 ;invalid;1-media;2-pkt */
#define  IPVP_LOOPBACK_TYPE_MEIDA    1
#define  IPVP_LOOPBACK_TYPE_PKT      2
    signed char     loopback_pkt_mode;              /*0;invalid; 1-encap;2-direct*/
#define  IPVP_LOOPBACK_PKT_ENCAP     1
#define  IPVP_LOOPBACK_PKT_DIRECT    2
    signed char     loopback_role;                  /*0 invalid; 1-source; 2-mirror*/
#define  IPVP_LOOPBACK_ROLE_MIRROR   2
    signed char     loopback_pkt_dynamic_pl;        /*0 invaliad; other-*/

    /*multiplexed media(ITU-T Rec. H.460.19)*/
    ipvp_multiplex_t multiplex;                     /*rtp & rtcp multiplex params*/

    unsigned short  local_maxplaybackrate;          /*local,maximum decode sampling rate*/
    unsigned short  local_maxcapturerate;           /*local,maximum encode sampling rate*/
    unsigned short  remote_maxplaybackrate;         /*remote,maximum decode sampling rate*/
    unsigned short  remote_maxcapturerate;          /*remote,maximum decode sampling rate*/

    unsigned short   rtp_ka_ptype;                  /*rtp keep alive ptype*/
    unsigned short   rtp_ka_interval;               /*rtp keep alive interval in ms,0 for disable*/

    unsigned short  srtp_ext_param;                 /*srtp crypto extern parameter*/
#define IPVP_SRTP_UNENCRY_RTP    (1<<0)
#define IPVP_SRTP_UNENCRY_RTCP   (1<<1)
#define IPVP_SRTP_UNAUTH_RTP     (1<<2)


    unsigned short  remote_minplaybackrate;         /*remote,minimum decode sampling rate*/
    unsigned short  remote_mincapturerate;          /*remote,minimum encode sampling rate*/

    unsigned short  remote_maxbitrate;              /*remote,maximum decode bit rate*/
    unsigned short  remote_minbitrate;              /*remote,maximum decode bit rate*/

    unsigned char   evs_cmr;   
    unsigned char   version;                        /*codec version*/   

    unsigned short  codec_opts;
#define IPVP_CODEC_BIT_AMRWBIO       (1<<0)         /*AMR-WB IO mode*/
#define IPVP_CODEC_BIT_HFONLY        (1<<1)         /*full head payload*/
#define IPVP_CODEC_BIT_DTXSEND       (1<<2)         /*send DTX*/
#define IPVP_CODEC_BIT_DTXRECV       (1<<3)         /*receive DTX*/
#define IPVP_CODEC_BIT_STEREO        (1<<4)         /*stereo*/
#define IPVP_CODEC_BIT_INBANDFEC     (1<<5)         /*use inband fec*/
#define IPVP_CODEC_BIT_USEYLRTX      (1<<6)         /*useylrtx*/

    unsigned short  reserved[8];                    /*for reserved */
}ipvp_audio_t;

/*
*   type of audio extern
*   --
*/
typedef struct
{
    /*header*/
    unsigned short  size;                        /*size of self*/

    /*
    * FEC
    */
    unsigned char    fec_ptype;                 /*fecptype*/
    unsigned char    fec_format;                /*fec format,0 URL 1 FLEX*/
    unsigned short   fec_local_port;
    unsigned short   fec_remote_port;

    unsigned int     ssrc;            
    char             cname_text[256];  /*SDES CNAME*/

    unsigned short   reserved[512];            /*for reserved */
}ipvp_audio_ext;


typedef struct
{
    /* the same as ipp_talk_t*/
    unsigned short  flag;                           /*this flag will effect rtp only*/
    unsigned short  size;                           /*size of "ipp_talk_t"*/
                                                    /*address*/
    ipvp_addr_t     addr_rtp;                       /*RTP address*/
    ipvp_addr_t     addr_rtcp;                      /*RTP address*/

    /*codec*/
    char            codec_name[IPVP_MAX_CODECNAME]; /*codec name*/
    unsigned short  codec_ptype;                    /*codec ptype*/
    unsigned short  codec_clock;                    /*codec clock rate*/
    unsigned short  codec_rate;                     /*codec bit rate,MUST divide 10 because superHD codec will over range*/
    unsigned short  event_ptype;                    /*event ptype*/
    unsigned short  event_clock;                    /*event clock rate*/
    unsigned short  ptime;                          /*packetize time*/

    char            enc_key[IPVP_MAX_SRTPKEY];      /*srtp encrypt key*/
    char            dec_key[IPVP_MAX_SRTPKEY];      /*srtp decrypt key*/

    char            rtcp_enc_key[IPVP_MAX_SRTPKEY]; /*srtcp encrypt key*/
    char            rtcp_dec_key[IPVP_MAX_SRTPKEY]; /*srtcp decrypt key*/

    unsigned short  ext_octet_align;                /*octet align for amrwb*/
    unsigned short  ext_toc_mode;                   /*toc mode for amrwb*/
    unsigned short  ext_annexa;                     /*annexa:cng mode */

    ipvp_acodec_t   codec_list[IPVP_MAX_CODEC];     /*codec list support*/
    int             codec_list_cnt;                 /*valid codec*/

    /*loop back*/
    signed char     loopback_type;                  /*0 ;invalid;1-media;2-pkt */
    signed char     loopback_pkt_mode;              /*0;invalid; 1-encap;2-direct*/
    signed char     loopback_role;                  /*0 invalid; 1-source; 2-mirror*/
    signed char     loopback_pkt_dynamic_pl;        /*0 invaliad; other-*/

    /*multiplexed media(ITU-T Rec. H.460.19)*/
    ipvp_multiplex_t multiplex;                     /*rtp & rtcp multiplex params*/

    unsigned short  local_maxplaybackrate;          /*local,opus maximum decode sampling rate*/
    unsigned short  local_maxcapturerate;           /*local,opus maximum encode sampling rate*/
    unsigned short  remote_maxplaybackrate;         /*remote,opus maximum decode sampling rate*/
    unsigned short  remote_maxcapturerate;          /*remote,opus maximum decode sampling rate*/

    unsigned short  rtp_ka_ptype;                   /*rtp keep alive ptype*/
    unsigned short  rtp_ka_interval;                /*rtp keep alive interval in ms,0 for disable*/

    unsigned short  srtp_ext_param;                 /*srtp crypto extern parameter*/

    unsigned short  remote_minplaybackrate;         /*remote,minimum decode sampling rate*/
    unsigned short  remote_mincapturerate;          /*remote,minimum encode sampling rate*/

    unsigned short  remote_maxbitrate;              /*remote,maximum decode bit rate*/
    unsigned short  remote_minbitrate;              /*remote,maximum decode bit rate*/

    unsigned char   evs_cmr;
    unsigned char   version;                        /*codec version*/

    unsigned short  codec_opts;

    /*
    * FEC
    */
    unsigned char   fec_ptype;                     /*fecptype*/
    unsigned char   fec_format;                    /*fec format,0 URL 1 FLEX*/
    unsigned short  fec_local_port;
    unsigned short  fec_remote_port;

    unsigned int    ssrc;
    unsigned int    sequence;
    unsigned int    timestamp;
    char            cname_text[256];               /*SDES CNAME*/

    unsigned short  reserved[14];                   /*for reserved */
    /*ipp_talk_t end*/

    /*srtp context*/
    unsigned int    srtp_ctx_flags;
    unsigned char   srtp_context[1024];
    unsigned char   srtcp_context[1024];

    /*other data*/
    unsigned short  call_is_hold;
    unsigned short  resverd[21];
}ipvp_audio_ctx;

typedef struct
{
    /*header*/
    unsigned short  size;                   /*size of self,now is 256*2B=0.5kB*/
    unsigned short  mode;                   /*mode for reserved*/

    /*address*/
    ipvp_addr_t     addr_rtp_wide;          /*RTP wide address,user for connect remote*/
    ipvp_addr_t     addr_rtcp_wide;         /*RTCP wide address,user for connect remote*/
    ipvp_addr_t     addr_rtp_bridg;         /*RTP bridg address,user for connect other base*/
    ipvp_addr_t     addr_rtcp_bridg;        /*RTCP bridg address,user for connect other base*/

    unsigned short  reserved2[64];          /*for reserved */
}ipvp_roaming_t;

/*
*----------------------------------------------------------------------
* type of video speech
*----------------------------------------------------------------------
*/

/*
*   type of video stats
*   --FIXME:to be finished
*/
typedef struct
{
    /*header*/
    unsigned short  flags;                          /*control flags of ??*/
    unsigned short  size;                           /*size of self*/

    /*codec info*/
    char            tx_codec[IPVP_MAX_CODECNAME];   /*transmit codec name*/
    char            rx_codec[IPVP_MAX_CODECNAME];   /*receive  codec name*/
    unsigned int    tx_bitrate;                     /*transmit bit rate*/
    unsigned int    rx_bitrate;                     /*receive  bit rate*/
    unsigned short  tx_profile;                     /*transmit H.264 profile*/
    unsigned short  rx_profile;                     /*receive  H.264 profile*/
    unsigned short  tx_framerate;                   /*transmit frame rate*/
    unsigned short  rx_framerate;                   /*receive  frame rate*/

    /*packet info*/
    unsigned int    tx_rtp;                         /*transmit rtp packets count*/
    unsigned int    rx_rtp;                         /*receive  rtp packets count*/
    unsigned int    tx_rtp_bytes;                   /*transmit rtp bytes count*/
    unsigned int    rx_rtp_bytes;                   /*receive  rtp bytes count*/
    unsigned int    tx_rtcp;                        /*transmit rtcp packets count*/
    unsigned int    rx_rtcp;                        /*receive  rtcp packets count*/
    unsigned short  tx_lost_frac;                   /*transmit packets lost rate, depend on remote feedback via RTCP*/
    unsigned short  rx_lost_frac;                   /*receive  packets lost rate*/
    unsigned int    tx_lost_total;                  /*transmit packets lost count, depend on remote feedback via RTCP*/
    unsigned int    rx_lost_total;                  /*receive  packets lost count*/

    /*jitter info*/
    unsigned short  tx_jit_cur;                     /*transmit interarrival jitter, depend on remote feedback via RTCP*/
    unsigned short  rx_jit_cur;                     /*receive  interarrival jitter*/
    unsigned short  tx_jit_avg;                     /*transmit average jitter, calculate by the history of RTCP*/
    unsigned short  rx_jit_avg;                     /*receive  average jitter*/
    unsigned short  tx_jit_max;                     /*transmit maximum jitter, calculate by the history of RTCP*/
    unsigned short  rx_jit_max;                     /*receive  maximum jitter*/
    unsigned short  tx_delay_rt;                    /*transmit round trip delay, may be the same as Rx path*/
    unsigned short  rx_delay_rt;                    /*receive round trip delay*/

    /*
    * video size
    */
    unsigned short  tx_width;                       /*transmit video width*/
    unsigned short  rx_width;                       /*receive  video width*/
    unsigned short  tx_height;                      /*transmit video height*/
    unsigned short  rx_height;                      /*receive  video height*/
    
    unsigned short  tx_lost_frac_avg;               /*transmit video average lost rate*/        
    unsigned short  tx_lost_frac_max;               /*transmit video maximum lost rate*/
    unsigned short  rx_lost_frac_avg;               /*receive video average lost rate*/
    unsigned short  rx_lost_frac_max;               /*receive video maximum lost rate*/

    unsigned short  tx_delay_avg;                   /*transmit video average delay*/
    unsigned short  tx_delay_max;                   /*transmit video maximum delay*/
    unsigned short  rx_delay_avg;                   /*receive video average delay*/
    unsigned short  rx_delay_max;                   /*receive video maximum delay*/

    unsigned int    reserved[10];                   /*reserved*/
}ipvp_vstats_t;

/*
*   type of video codec
*   --
*/
typedef struct
{
    char            codec_name[IPVP_MAX_CODECNAME]; /*codec name*/
    unsigned short  codec_ptype;                    /*codec ptype*/
    unsigned short  codec_fec;                      /*codec ptype for fec*/
    unsigned int    codec_bitrate;                  /*codec bit rate*/
    unsigned short  codec_frmrate;                  /*codec frame rate,for video only*/
    unsigned short  codec_profile;                  /*codec profile ID for H.26x,IPVP_VIDEO_PF_xxx*/
    unsigned short  codec_pmode;                    /*codec packet mode ,IPVP_VIDEO_PM_xxx*/
    unsigned short  codec_clock;                    /*codec clock rate*/
    unsigned short  event_ptype;                    /*event(RTCP) ptype*/
    unsigned short  event_clock;                    /*event(RTCP) clock rate*/
    unsigned short  win_width;                      /*width  of video window for startup*/
    unsigned short  win_height;                     /*height of video window for startup*/
    unsigned short  key_frame_interval;             /*interval of sending key frame*/
    unsigned short  quality_policy;                 /*policy for video smooth and quality,IPVP_VIDEO_QP_xxx*/
    unsigned short  packet_mtu_size;

    unsigned short  reserved[3];                    /*reserved*/
}ipvp_vcodec_t;

/*
*   type of video speech
*   --
*/
typedef struct
{
    /*header*/
    unsigned short  flags;                          /*control flags of IPVP_FL_xxx*/
#define IPVP_VIDEO_DIR_MASK            0x000F
#define IPVP_VIDEO_SHA_MASK            0x00F0
#define IPVP_VIDEO_SHA_INCLUDE_CREATE  0x0000       /*share start inclued create*/
#define IPVP_VIDEO_SHA_WITHOUT_CREATE  0x0010       /*share start without create*/

    unsigned short  size;                           /*size of self*/

    /*address*/
    ipvp_addr_t     addr_rtp;                       /*RTP address*/
    ipvp_addr_t     addr_rtcp;                      /*RTCP address*/

    /*codec list*/
    unsigned short  enc_max;                        /*number of available encoder,[1,IPVP_MAX_CODEC]*/
    unsigned short  dec_max;                        /*number of available encoder,[1,IPVP_MAX_CODEC]*/
    ipvp_vcodec_t   enc_list[IPVP_MAX_CODEC];       /*available encoder*/
    ipvp_vcodec_t   dec_list[IPVP_MAX_CODEC];       /*available decoder*/

    /*SRTP*/
    char            enc_key[IPVP_MAX_SRTPKEY];       /*srtp encrypt key*/
    char            dec_key[IPVP_MAX_SRTPKEY];       /*srtp decrypt key*/

    /*SRTCP*/
    char            rtcp_enc_key[IPVP_MAX_SRTPKEY];  /*srtcp encrypt key*/
    char            rtcp_dec_key[IPVP_MAX_SRTPKEY];  /*srtcp decrypt key*/

    /*extra MUST be below:*/
    /*codec:extra param:FIXME:how to define this kind??*/
    char            RTCP_params[IPVP_MAX_CODEC_ATTR];/*RTCP string,FIXME:what is this for??*/
    char            H460_params[IPVP_MAX_CODEC_ATTR];/*text like xxx:xxx payload:timeout,FIXME:what is this for??*/
    char            priv_capset[IPVP_MAX_CODEC_ATTR];/*text like yl-capset=7;yl-ver=1;yl-ext=19,FIXME:what is this for??*/

    unsigned short  switch_mode;                     /*stream switch mode*/
    unsigned short  conf_role;                       /*stream conference role*/

    /*multiplexed media(ITU-T Rec. H.460.19)*/
    ipvp_multiplex_t multiplex;                      /*rtp & rtcp multiplex params*/

    /*rtp header extensions*/
    unsigned int     rtp_ext_CVO_id;                  /*Coordination of Video Orientation identifier,general range 1~14,0 for disable*/

    char             dev_name[IPVP_MAX_DEV_NAME];
    
    /*
    * webrtc param
    */
    unsigned int     encode_media_ssrc;            
    char             encode_cname_text[IPVP_MAX_CNAME_LEN];     /*SDES CNAME*/

    unsigned int     decode_media_ssrc;            
    char             decode_cname_text[IPVP_MAX_CNAME_LEN];     /*SDES CNAME*/

    /*softenc in rk ms*/
    unsigned int     softenc_flag;

    char             priv_capset_local[IPVP_MAX_CODEC_ATTR];/*text like yl-capset=7;yl-ver=1;yl-ext=19,FIXME:what is this for??*/

    unsigned int     reserved[223];
}ipvp_video_t;
#define IPVP_VIDEO_SIZE_V1 0x0780               /*ipvp_video_t size no webrtc*/
#define IPVP_VIDEO_SIZE_V2 0x0D70               /*ipvp_video_t size add webrtc*/

/*
*   type of video shared
*   --
*/
typedef struct
{
    /*header*/
    unsigned short  flags;                       /*control flags of IPVP_FL_xxx*/
    unsigned short  size;                        /*size of self*/

    /*session*/
    int             callID;                      /*call id related*/
    int             videoID;

    /*window*/
    ipvp_rect_t     window;                      /*rect of layout position*/
}ipvp_layout_t;

/*
*----------------------------------------------------------------------
* type of speech
*----------------------------------------------------------------------
*/
typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*speech mode of IPVP_FL_VAM_xxx*/
    ipvp_audio_t    audio;                      /*audio param*/
    ipvp_video_t    video;                      /*video param*/
    ipvp_audio_ext  audio_ext;                  /*audio extern param*/
}ipvp_speech_t;

#define IPVP_SPEECH_SIZE_V1 0x0C4C              /*ipvp_speech_t size no ipvp_audio_ext*/
#define IPVP_SPEECH_SIZE_V2 0x1748              /*ipvp_speech_t size add ipvp_audio_ext*/

/*
* type of conference
*/
typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*conference mode of ...*/
    unsigned int    count;                      /*number of valid speech call ID*/
    unsigned int    callID[IPVP_MAX_SPEECH];    /*conference mode of ...*/
}ipvp_confer_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*reserved*/
    ipvp_astats_t   audio;                      /*audio stats*/
    ipvp_vstats_t   video;                      /*video stats*/
    ipvp_vstats_t   share;                      /*share video stats, only one of tx&rx can be effect*/
}ipvp_stats_t;

/*
*----------------------------------------------------------------------
* type of audio/video media(file,etc)
*----------------------------------------------------------------------
*/
typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*media mode of IPVP_FL_VAM_xxx*/

    /*file&path:should be at tail*/
    char            file[IPVP_MAX_PATH];

    /*audio info*/
    unsigned int    audio_dst;                  /*audio direction mask,could be IPVP_FL_DIR_xx*/
    unsigned int    audio_reserved;

    /*video info*/
    unsigned int    video_dst;                  /*video display id,could be IPVP_VIDEO_DST_xx*/
    unsigned int    video_reserved;             /*reserved*/
    ipvp_rect_t     video_win;                  /*video display rect*/

}ipvp_playback_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*media mode of IPVP_FL_VAM_xxx*/
#define  IPVP_FILE_AUDIO           0            /*audio type*/
#define  IPVP_FILE_VIDEO           1            /*video type*/

    /*FIXME:extra file info need to be add!!*/
    unsigned int    sec_total;                  /*total seconds of file*/
    unsigned int    sec_current;                /*current seconds of playing*/

    /*...*/

}ipvp_pinfo_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*media mode of IPVP_FL_VAM_xxx*/

    /*file&path:should be at tail,could be unicode/utf-8*/
    char            file[IPVP_MAX_PATH];
    unsigned int    file_maxMB;

    /*audio info*/
    ipvp_acodec_t   audio;                      /*audio codec info*/
    unsigned int    audio_source;               /*audio source id,could be IPVP_FL_REC_xx*/

    /*video info*/
    ipvp_vcodec_t   video;                      /*video codec info*/
    unsigned int    video_source;               /*video source id,could be IPVP_VIDEO_SRC_xx or IPVP_VIDEO_DST_xx*/

    /*FIXME:extra file info need to be add!!*/
    /*...*/

}ipvp_record_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    mode;                       /*media mode of IPVP_FL_VAM_xxx*/

    /*FIXME:extra file info need to be add!!*/
    /*...*/

}ipvp_rinfo_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    flag;                       /*control flags*/
#define IPVP_QUALITY_BITRATE       (1<<0)
#define IPVP_QUALITY_FRAMERATE     (1<<1)
#define IPVP_QUALITY_WIDTH         (1<<2)       /*SHOULD be set with IPVP_QUAL_VID_HEIGHT at the same time*/
#define IPVP_QUALITY_HEIGHT        (1<<3)       /*SHOULD be set with IPVP_QUAL_VID_WIDTH  at the same time*/
#define IPVP_QUALITY_ALL           0xFFFFFFFF

    /*
     * Video Quality, (video specificality struction)
     */
    unsigned int    bitrate;
    unsigned int    framerate;
    unsigned int    width;
    unsigned int    height;
    unsigned int    reserved[12];

}ipvp_quality_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    flag;                       /*control flags*/

    /*
     * Video OSD parameter
     */

    /*osd file path*/
    char            file[IPVP_MAX_PATH];

    /*osd postion*/
    unsigned int    x;                          /*must be multiple of 2*/
    unsigned int    y;                          /*must be multiple of 2*/
    unsigned int    width;                      /*must be multiple of 8*/
    unsigned int    height;                     /*must be multiple of 4*/

#define IPVP_OSD_MODE_MIN          1
#define IPVP_OSD_MODE_FIXED        1            /*use fixed size specified by width & height*/
#define IPVP_OSD_MODE_FILE         2            /*use size that read from osd file*/
#define IPVP_OSD_MODE_MAX          2
    unsigned int    display_mode;               /*osd display mode of IPVP_OSD_MODE_xxx*/

#define IPVP_OSD_ALPHA_MIN         0x00         /*not transparent*/
#define IPVP_OSD_ALPHA_MAX         0x80         /*totally transparent*/
    unsigned int    alpha;                      /*alpha channel:IPVP_OSD_ALPHA_MIN~IPVP_OSD_ALPHA_MAX*/

    unsigned int    reserved[12];

}ipvp_osd_t;

typedef struct
{
    unsigned int    size;                       /*self size*/
    unsigned int    flag;                       /*control flags*/

    /*
    * Video size change info
    */
    unsigned short  old_width;
    unsigned short  old_height;
    unsigned short  new_width;
    unsigned short  new_height;

    unsigned int    reserved[8];

}ipvp_resize_t;

/*
* rms report
*/
typedef struct 
{
    int             callid;                    /*callID, =-1:local rms*/
    int             rms;                       /*rms data (dB,<0)*/
}ipvp_rmsinfo_t;

typedef struct 
{
    unsigned int    tx_audio_bw;               /*audio send bandwidth */
    unsigned int    rx_audio_bw;               /*audio recv bandwidth */
    unsigned int    tx_video_bw;               /*video send bandwidth */
    unsigned int    rx_video_bw;               /*video recv bandwidth */
    unsigned int    tx_share_bw;               /*share send bandwidth */
    unsigned int    rx_share_bw;               /*share recv bandwidth */
}ipvp_bandwidth_t;

typedef struct 
{
    unsigned int    videoDST;
    unsigned int    width;
    unsigned int    height;
    unsigned int    fps;
    unsigned int    force;
    unsigned int    reserved[8];
}ipvp_display_t;

typedef struct
{
    unsigned short      size;                           /*self size*/
    unsigned short      flag;                           /*control flags*/

    unsigned char       af_type;                        /*AF_INET or AF_INET6*/
    unsigned char       sock_type;                      /*sock type such as SOCK_STREAM SOCK_DGRAM*/
    char                remote_addr[IPVP_MAX_ADDR_LEN]; /*remote server addr*/
    unsigned short      remote_port;                    /*remote server port*/

    unsigned short      source_mode;                    /*data source format,MIC/SPK/MIC+SPK */
    char                channel[IPVP_MAX_CODECNAME];    /*capture channel name*/
    unsigned short      data_format;                    /*output data format*/
    char                codec_name[IPVP_MAX_CODECNAME]; /*output data codec name, same as talk*/

    unsigned short      resverd[18];
}ipvp_netcap_t;

typedef struct
{
	int x;
	int y;
	int z;
} ipvp_image_pos;

/**
* @brief  :soceket_cb api is same to socket api
*
* @param  :
* @warning:
* @return :
*
*/
typedef int(*socket_cb)(int af, int type, int protocol);
typedef int(*setsockopt_cb)(int sockfd, int level, int optname, const char * optval, int optlen);
typedef int(*bind_cb)(int sockfd, const struct sockaddr *addr, int addrlen);
typedef int(*listen_cb)(int sockfd, int backlog);
typedef int(*accept_cb)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
typedef int(*connect_cb)(int sockfd, const struct sockaddr *addr, int addrlen);
typedef int(*close_cb)(int sockfd);
typedef int(*select_cb)(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
typedef int(*sendto_cb)(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, int addrlen);
typedef int(*send_cb)(int sockfd, const void *buf, size_t len, int flags);
typedef int(*recvfrom_cb)(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, int *addrlen);
typedef int(*recv_cb)(int sockfd, void *buf, size_t len, int flags);

typedef struct
{
    socket_cb       cb_socket;
    setsockopt_cb   cb_setsockopt;
    bind_cb         cb_bind;
    listen_cb       cb_listen;
    accept_cb       cb_accept;
    connect_cb      cb_connect;
    close_cb        cb_close;
    select_cb       cb_select;
    sendto_cb       cb_sendto;
    send_cb         cb_send;
    recvfrom_cb     cb_recvfrom;
    recv_cb         cb_recv;
}ipvp_socket_t;
/************************************************************************/
/*                                                                      */
/************************************************************************/
#endif /* __SERVICE_IPVP_TYPES_H__ */
