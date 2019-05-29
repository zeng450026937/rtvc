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
* for export IPVP APIs header file
*
*/

#ifndef __SERVICE_IPVP_API_H__
#define __SERVICE_IPVP_API_H__

/************************************************************************/
/* APIs for c                                                           */
/* [NNS] : not necessary                                                */
/*         if you are not sure, please set to -1 for default            */
/************************************************************************/
/*
*-----------------------------------------------------------
*   version APIs
*-----------------------------------------------------------
*/
/*for version*/
IPVP_API const char* ipvp_version(void);
IPVP_API const char* ipvp_build(void);


/**
* @brief  : audio device APIs
*
* @param  :
*           samplerate[in] :  audio samplerate
*           chan[in]       :  audio channels
*           Hz[out]        :  period of dsp
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_init(int *samplerate,int *chan,int *Hz);

/**
* @brief  : audio device APIs
*
* @param  :
*           Hz[out]  :   period of dsp
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_init2(int *Hz);

/**
* @brief  : audio device APIs
*
* @param  :
*           none
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_exit(void);

/**
* @brief  : audio device API
*
* @param  :
*           spk[out] :  spk data
*           mic[in]  :  mic data
*           ref[in]  :  ref data, can be null
*           ch[in]   :  Number of channel, must be 1
*           fs[in]   :  Number of samples, not means bytes
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_framing(void *spk[],void *mic[],void *ref[],size_t ch,size_t fs);

/**
* @brief  : audio device API
*
* @param  :
*           spk[out]      : spk data
*           spk_size[in]  : spk data size
*           mic[in]      : mic data
*           mic_size[in]  : mic data size
*           ref[in]       : ref data, can be null
*           ref_size[in]  : ref data size
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_framing2(void *spk,size_t spk_size,void *mic,size_t mic_size,void *ref,size_t ref_size);

/**
* @brief  : audio device API
*
* @param  :
*           spk[in]      : parameter of spk
*           mic[in]      : parameter of mic
*           ref[in]      : parameter of ref,can be null
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_set_framing(ipvp_frame_t *spk,ipvp_frame_t *mic,ipvp_frame_t *ref);

/**
* @brief  : extern audio device API
*
* @param  :
*           voice       : ref data
*           voice_size  : ref data size
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_ext_voice(unsigned int voice_type, void* voice, size_t voice_size);

/**
* @brief  : extern audio device API
*
* @param  :
*           share_config   : config data
* @warning:
*
* @return :0 is success,otherwise failed.
*/
IPVP_API int ipvp_dev_set_ext(ipvp_ext_voice_t* voice_config);

/**
* @brief  :video device API
*
* @param  :
*         gid        :surface group ID
*         mode       :display & camera mask
*                     IPVP_FL_SURF_DISPLAY, 0 for normal, 1 for update
*                     IPVP_FL_SURF_NOCAMERA, 0 for normal, 1 for nocamera
*         surface    :surface handle
*         extra      :JNI environment
*         size       :size of extra
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_dev_surface(mkit_handle_t caller,int gid,int mode,void *surface,void*extra,int size);
static __inline int ipvp_dev_surface(int gid,int mode,void *surface,void*extra)
{
    return ipvp_mcu_dev_surface(0,gid,mode,surface,extra,0);
}

/*
*-----------------------------------------------------------
*   library APIs
*-----------------------------------------------------------
*/
IPVP_API int ipvp_lib_init(ipvp_init_t *init,size_t init_size);
IPVP_API int ipvp_lib_exit(void);

IPVP_API int ipvp_get_flow_info(int *iio_num, int *eio_num, int *nrt_num);

/*
*-----------------------------------------------------------
*   debug/init APIs
*-----------------------------------------------------------
*/
/**
* @brief  :initialize/terminate
*
* @param  :
*           reset   : == 0, only initialize service handle, have nothing to do with ipvpserver
*                      > 0, initialize service and reset ipvpserver, the value means time to wait in second
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_init(mkit_handle_t caller,int reset);
IPVP_API int ipvp_exit(mkit_handle_t caller);

/**
* @brief  :system power control
*
* @param  :
*         power_level:power level define in IPVP_POWER_xxx
*
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_power(mkit_handle_t caller,int power_level);
IPVP_API int ipvp_get_power(mkit_handle_t caller);
IPVP_API int ipvp_alive  (mkit_handle_t caller);

/**
* @brief  :set role
*
* @param  :
*         role: IPVP_ROLE_XX
*         addr: host addr when role
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_set_role  (mkit_handle_t caller, int role, const char *addr);

/*
*-----------------------------------------------------------
*   info APIs
*-----------------------------------------------------------
*/
/**
* @brief  :get capacity info
*
* @param  :
*           capacity : data of capacity
* @warning:
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_get_capacity(mkit_handle_t caller,ipvp_capacity_t* capacity);

/**
* @brief  :get private capset
*
* @param  :
*           capset : data of private capset
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_get_capset(mkit_handle_t caller,ipvp_capset_t* capset);

/*
*-----------------------------------------------------------
*   config APIs
*-----------------------------------------------------------
*/

/**
* @brief  :config update request, it depends on the config file
*
* @param  :
*           
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_update(mkit_handle_t caller);

/**
* @brief  :config jitter buffer
*
* @param  :
*           adaptive    :0 for static, 1 for adaptive
*           jibmin      :minimum JIB as ms
*           jibmax      :maximum JIB as ms
*           jibnor      :target JIB as ms
* @warning: 
*           1.all setting must be range from 20ms to 1000ms
*           2.jibmin<=jibnor<=jibmax
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_jib(mkit_handle_t caller,int adaptive,int jibmin,int jibnor,int jibmax);

/**
* @brief  :config cng/vad
*
* @param  :
*           vad_enable :vad enable
*           cng_enable :cng enable
*           cng_rx_gain:cng gain in receive path [NNS]
*           cng_tx_gain:cng gain in transmit path [NNS]
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_cng(mkit_handle_t caller,int vad_enable,int cng_enable ,int cng_rx_gain, int cng_tx_gain);

/**
* @brief  :config sidetone
*
* @param  :
*           handset_gain: side tone gain of handset [NNS]
*           headset_gain: side tone gain of headset [NNS]
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_sidetone(mkit_handle_t caller,int handset_gain,int headset_gain);

/**
* @brief  :config AEC (acoustic echo cancellation)
*
* @param  :
*           aec_enable :0==disable AEC,else enable AEC.
*           hec_enable :0==disable HEC,else enable HEC. [NNS]
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_aec(mkit_handle_t caller,int aec_enable, int lec_enable);
IPVP_API int ipvp_config_agc(mkit_handle_t caller,int rx_enable,  int tx_enable);

/**
* @brief  :config RTCP
*
* @param  :
*           rtcp_enable: enable RTCP
*           interval: RTCP interval as seconds,range from 5 to 60,set 0 to disable RTCP [NNS]
*           rtcpxr  : enable RTCP-XR [NNS]
*           xr_report : enable RTCP package with XR
*           cname   : CNAME information of RTCP-SDES used [NNS]
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_rtcp(mkit_handle_t caller,int rtcp_enable, int interval,int rtcpxr, const char* cname);

/**
* @brief  :config dtmf
*
* @param  :
*           dtmfcfg ipvp_dtmfcfg_t
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_dtmf(mkit_handle_t caller,ipvp_dtmfcfg_t *dtmfcfg);

/**
* @brief  :config tone
*
* @param  :
*           toneid      : the index of country tone
*           tone_string : tone config string
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_tone(mkit_handle_t caller,int toneid,const char* tone_string);

/**
* @brief  :config tx gain
*
* @param  :
*           handsfree_gain  : handsfree digital mic gain [NNS]
*           handset_gain    : handset digital mic gain [NNS]
*           headset_gain    : headset digital mic gain [NNS]
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_gain(mkit_handle_t caller,int handsfree_gain, int handset_gain, int headset_gain);

/**
* @brief  :config RTP
*
* @param  :
*           rtpcfg     : rtp configurations
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_rtp(mkit_handle_t caller,ipvp_rtpcfg_t* rtpcfg);

/**
* @brief  :config G726
*
* @param  :
*           bit_reverse  : bit reverse of g.726 data
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int  ipvp_config_g726(mkit_handle_t caller,int bit_reverse);

/**
* @brief  :config vqmon
*
* @param  :
*           warning      : the warning threshold of report item 
*           critical     : the critical threshold of report item
*           item         : the name of report item
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int  ipvp_config_vqmon(mkit_handle_t caller,int warning, int critical, const char* item);

/**
* @brief  :config QoS, IP type of service and preced
*
* @param  :
*           gid       : speech group ID
*           audiotos  : audio port config, cfg in "network.qos.audiotos"
*           videotos  : video port config, cfg in "network.qos.videotos"
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int  ipvp_mcu_config_QoS(mkit_handle_t caller,int gid, int audiotos, int videotos);
static __inline int ipvp_config_QoS(mkit_handle_t caller, int audiotos, int videotos)
{
    return ipvp_mcu_config_QoS(caller,0,audiotos,videotos);
}

/**
* @brief  :config NS (noise suppression)
*
* @param  :
*           tns_en    : 0==disable TNS,else enable TNS.
*           ans_en    : 0==disable ANS,else enable ANS.
*           ans_nb_en : 0==disable ANSNB,else enable ANSNB.
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_config_ns(mkit_handle_t caller,int tns_en,int ans_en,int ans_nb_en);


/**
* @brief  :config MNS (Multi-Microphone-Noise-Suppression)
*
* @param  :
*           enable       :-1 no change, 0==disable, else enable
*           level        :-1 no change, [1/2/3]
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_config_mns(mkit_handle_t caller,int enable,int level);

/**
* @brief  :config vtuner
*
* @param  :
*           enable       :0==disable, else enable
*           proxy        :0==disable, else enable
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_config_vtuner(mkit_handle_t caller, int enable, int proxy);

/**
* @brief  :config socket api
*
* @param  :
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_config_socket(ipvp_socket_t *socket_def);

/**
* @brief  :config bypass
*
* @param  :
*           enable       :0==disable, else enable
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_set_bypass(mkit_handle_t caller, int bypass);

/**
* @brief  :config bandwidth
*
* @param  :
*           bw_in/bw_out : FIXME:what is this unit?
* @warning: 
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int  ipvp_config_bandwidth(mkit_handle_t caller,int bw_in, int bw_out);

/*
*-----------------------------------------------------------
*   speech independent APIs
*-----------------------------------------------------------
*/
/**
* @brief  :request speech mode.
*
* @param  :
*          mode     : IPVP_MODE_xx,valid mode is depend on different device!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_mode(mkit_handle_t caller,int mode);

/**
* @brief  :request speech mode, by paired for your custom.
*
* @param  :
*          mic_mode : IPVP_MODE_xx, set IPVP_MODE_INV to skip this parameter!
*          spk_mode : IPVP_MODE_xx, set IPVP_MODE_INV to skip this parameter!
* @warning:
*          only the composition user manual declare may be successful
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_DEV(mkit_handle_t caller,int mic_mode, int spk_mode);

IPVP_API int ipvp_set_SPK(mkit_handle_t caller,int mode,int on);
IPVP_API int ipvp_set_MIC(mkit_handle_t caller,int mode,int on);

/**
* @brief  :get current hot-plug states
*
* @param  :
*          dev      : define in IPVP_HPEV_xxx 
* @warning:
*          
* @return : >=0 states define is IPP_HPST_xxx
*            <0 is failed.
*
*/
IPVP_API int ipvp_get_HPE(mkit_handle_t caller,int hpev);

/**
* @brief  :get current speech mode.
*
* @param  :
*
* @warning:
*          
* @return :>=0:valid current mode
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_mode(mkit_handle_t caller);

/**
* @brief  :request the device works as a slave one.
*
* @param  :
*           slave  : define in IPVP_SLAVE_xx
*           dir    : salve direction of IPVP_FL_DIR_xx, 0(IPVP_FL_DIR_NONE) for turn off
*           id     : 0                             ->master
*                    IPVP_ROLE_SLAVE_ID(subdev_id) ->slave
* @warning:
*          some salve will conflict with mode such as IPVP_MODE_BTES&IPVP_SLAVE_BTHF
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_set_slave(mkit_handle_t caller, int slave, int dir, int id);

/**
* @brief  :query the salve mode.
*
* @param  :
*           slave  : define in IPVP_SLAVE_xx
* @warning:
*          
* @return : 
*           1) slave direction of IPVP_FL_DIR_xx (include IPVP_FL_DIR_MIX).
*           2) total slaves count, when slave input is IPVP_SLAVE_NONE
*           3) -1 for call failed.
*/
IPVP_API int ipvp_get_slave(mkit_handle_t caller, int slave);

/**
* @brief  :query the salve mode.
*
* @param  :
*           slave  : define in IPVP_SLAVE_xx
*           id     : 0                             ->master
*                    IPVP_ROLE_SLAVE_ID(subdev_id) ->slave

* @warning:
*
* @return :
*           1) slave direction of IPVP_FL_DIR_xx (include IPVP_FL_DIR_MIX).
*           2) total slaves count, when slave input is IPVP_SLAVE_NONE
*           3) -1 for call failed.
*/
IPVP_API int ipvp_get_slave2(mkit_handle_t caller, int slave, int id);



/**
* @brief  :select mic(s)/spk(s) for specified mode
*
* @param  :
*          mic_mode: mic mode
*          spk_mode: spk mode
*          ctrl    : reserved
*          mask    : selected mic mask, 0x0 is not allowed
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_select_mic(mkit_handle_t caller, int mic_mode, unsigned short ctrl, unsigned short mask);
IPVP_API int ipvp_select_spk(mkit_handle_t caller, int spk_mode, unsigned short ctrl, unsigned short mask);

/**
* @brief  :request volume of current mode.
*
* @param  :
*          volume :volume step
*           #define  IPVP_VOLUME_MIN    0
*           #define  IPVP_VOLUME_MAX    32
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_volume(mkit_handle_t caller,int volume);

/**
* @brief  :get current speech volume.
*
* @param  :
*
* @warning:
*          
* @return :>=0:valid current mode
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_volume(mkit_handle_t caller);

/**
* @brief  :request gain of current mode.
*
* @param  :
*          gain :gain percentage [0%,400%]
*           #define  IPVP_GAIN_MIN    0
*           #define  IPVP_GAIN_MAX    400
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_gain(mkit_handle_t caller,int gain,int dir);

/**
* @brief  :get current speech gain.
*
* @param  :
*
* @warning:
*          
* @return :>=0:valid current mode
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_gain(mkit_handle_t caller,int dir);


/**
* @brief  :set gain for system input stream
*
* @param  :
*          gain :gain percentage [0%,400%]
*           #define  IPVP_GAIN_MIN    0
*           #define  IPVP_GAIN_MAX    400
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_osin_gain(mkit_handle_t caller,int gain);

/**
* @brief  :set gain for system output stream
*
* @param  :
*          gain :gain percentage [0%,400%]
*           #define  IPVP_GAIN_MIN    0
*           #define  IPVP_GAIN_MAX    400
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_osout_gain(mkit_handle_t caller,int gain);

/**
* @brief  :get gain of system input stream
*
* @param  :
*
* @warning:
*          
* @return :>=0:valid current mode
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_osin_gain(mkit_handle_t caller);


/**
* @brief  :get gain of system output stream
*
* @param  :
*
* @warning:
*          
* @return :>=0:valid current mode
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_osout_gain(mkit_handle_t caller);

/**
* @brief  :set/get gain of system input stream
*
* @param  :
*
* @warning:
*          
* @return :>=0:valid current mode
*          < 0:failed
* 
*/
IPVP_API int ipvp_set_osout_volume(mkit_handle_t caller, int volume);
IPVP_API int ipvp_get_osout_volume(mkit_handle_t caller);

/**
* @brief  :set mute
*
* @param  :
*           mute :IPVP_MUTE / IPVP_UNMUTE
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_mute(mkit_handle_t caller,int mute);

/**
* @brief  :set signal mic mute
*
* @param  :
*           mic_mode:IPVP_MODE_xx, set IPP_MODE_INV to skip this parameter!
*           mic_id  :selected mic id
*           mute    :IPVP_MUTE / IPVP_UNMUTE
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_mic_mute(mkit_handle_t caller, int mic_mode,unsigned short mic_id,  unsigned short mute);

/**
* @brief  :get mute status
*
* @param  :
* 
* @warning:
*          
* @return :>=0:valid current mute state
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_mute(mkit_handle_t caller);


/**
* @brief  :play DTMF on local
*
* @param  :
*           dtmf    :dtmf id , '0' to '9','A','B','C','D','*','#','+'
*           sync    :0==do not wait,1==to wait until play end!if not sure,then set 0!
* @warning:
*          '+':flash key
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_dtmf_play(mkit_handle_t caller,char dtmf,int sync);

/**
* @brief  :play DTMF on speech
*
* @param  :
*           callID  :speech call ID
*           dtmf    :dtmf id , '0' to '9','A','B','C','D','*','#','+'
*           dir     :play direction of IPVP_FL_DIR_xx
*           sync    :0==do not wait,1==to wait until play end!if not sure,then set 0!
* @warning:
*          '+':flash key
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_dtmf_send(mkit_handle_t caller,int callID,char dtmf,int dir,int sync);

/**
* @brief  :play tone on local
*
* @param  :
*           toneid:tone id ,any valid tone predefine here!
*           dir   :play direction of IPVP_FL_DIR_xx
*           sync  :0==do not wait,1==to wait until play end!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_tone_play (mkit_handle_t caller,int toneid,int dir, int sync);
/**
* @brief  :play tone on local
*
* @param  :
*           toneid:tone id ,any valid tone predefine here!
*           mix   :the tone will mix with speech while on call if "mix" set to 1
*           duration: tone play time(ms,max 65535ms),0 is forever
*           sync  :0==do not wait,1==to wait until play end!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_tone_play2(mkit_handle_t caller,int toneid,int dir, unsigned short duration, int sync);

/**
* @brief  :stop any tone that's playing now!
*
* @param  :
*           sync   :0==do not wait,1==to wait until play really stopped!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_tone_stop(mkit_handle_t caller,int sync);

/**
* @brief  : to play a audio file, for MCU
*
* @param  :
*           gid    : speech group ID,-1 as local
*           file   :audio file path to play
*           dir    :play direction of IPVP_FL_DIR_xx
*           loop   :play loop,must be greater than 0;-1 as forever!
*           sync   :0==do not wait,1==to wait until play really started!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_audio_play (mkit_handle_t caller,int gid,const char *file,int loop,int sync);
IPVP_API int ipvp_mcu_audio_play2(mkit_handle_t caller,int gid,const char *file,int dir,int loop,int sync);

/**
* @brief  :stop/pause/resume any audio file play that's playing now!
*
* @param  :
*           gid    : speech group ID,-1 as local
*           dir    :play direction of IPVP_FL_DIR_xx
*           sync   :0==do not wait,1==to wait until play really done!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_audio_stop  (mkit_handle_t caller,int gid,int sync);
IPVP_API int ipvp_mcu_audio_stop2 (mkit_handle_t caller,int gid,int dir,int sync);
IPVP_API int ipvp_mcu_audio_pause (mkit_handle_t caller,int gid,int sync);
IPVP_API int ipvp_mcu_audio_resume(mkit_handle_t caller,int gid,int sync);

/**
* @brief  :audio  play/stop/pause/resume
*
* @param  :
*              then same as ipvp_mcu_audio_xxx(...) 
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
static __inline int ipvp_audio_play (mkit_handle_t caller,const char *file,int loop,int sync)
{
    return ipvp_mcu_audio_play(caller,0,file,loop,sync);
}
static __inline int ipvp_audio_play2(mkit_handle_t caller,const char *file,int dir,int loop,int sync)
{
    return ipvp_mcu_audio_play2(caller,0,file,dir,loop,sync);
}
static __inline int ipvp_audio_stop  (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_audio_stop(caller,0,sync);
}
static __inline int ipvp_audio_stop2 (mkit_handle_t caller,int dir,int sync)
{
    return ipvp_mcu_audio_stop2(caller,0,dir,sync);
}
static __inline int ipvp_audio_pause (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_audio_pause(caller,0,sync);
}
static __inline int ipvp_audio_resume(mkit_handle_t caller,int sync)
{
    return ipvp_mcu_audio_resume(caller,0,sync);
}

/**
* @brief  :ring play/stop
*
* @param  :then same as ipvp_media_xxx(...) 
*
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
static __inline int ipvp_mcu_ring_play(mkit_handle_t caller,int gid,const char *file,int loop)
{
    return ipvp_mcu_audio_play(caller,gid,file,loop,0);
}
static __inline int ipvp_mcu_ring_stop(mkit_handle_t caller,int gid)
{
    return ipvp_mcu_audio_stop(caller,gid,0);
}
static __inline int ipvp_ring_play(mkit_handle_t caller,const char *file,int loop)
{
    return ipvp_mcu_audio_play(caller,0,file,loop,0);
}
static __inline int ipvp_ring_stop(mkit_handle_t caller)
{
    return ipvp_mcu_audio_stop(caller,0,0);
}

/**
* @brief  :sound play/stop
*
* @param  :then same as ipvp_media_xxx(...)
*
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
static __inline int ipvp_sound_play(mkit_handle_t caller,const char *file,int loop)
{
    return ipvp_mcu_audio_play(caller,-2,file,loop,0);
}

static __inline int ipvp_sound_stop(mkit_handle_t caller)
{
    return ipvp_mcu_audio_stop(caller,-2,0);
}

/**
* @brief  : to record current sound, for MCU
*
* @param  :
*           gid      : speech group ID,-1 as local
*           file     :file path to play
*           file_siz :file size limit as k-bytes,if no limit,then set -1!
*           sync     :0==do not wait,1==to wait until play really started!if not sure,then set 0!
* @warning:
*          the 'mode' define the record channel number,that's ,
*          IPVP_FL_REC_MIC or IPVP_FL_REC_SPK only,it will record as mono(single)
*          IPVP_FL_REC_MIX, it will record as mono(single),and mix the two channel to one!
*
*          in ipvp_record_start2, parameters of ipvp_record_t is fixed:
*          ipvp_record_t info;
*          info.file_maxMB          = 2 * 1024;
*          info.audio.codec_clock   = 32000;
*          info.audio_source        = IPVP_FL_REC_MIX;
*          info.video.win_width     = 1280;
*          info.video.win_height    = 720;
*          info.video.codec_frmrate = 30;
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_record_start (mkit_handle_t caller,int gid,ipvp_record_t *info,int sync);
IPVP_API int ipvp_mcu_record_start2(mkit_handle_t caller,int gid,const char *file,int sync);
IPVP_API int ipvp_mcu_record_stop  (mkit_handle_t caller,int gid,int sync);

/**
* @brief  :pause/resume any recording
*
* @param  :
*           gid    : speech group ID,-1 as local
*           sync   :0==do not wait,1==to wait until recording really done!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_record_pause  (mkit_handle_t caller,int gid,int sync);
IPVP_API int ipvp_mcu_record_resume (mkit_handle_t caller,int gid,int sync);

/**
* @brief  :audio record
*
* @param  :
*              then same as ipvp_mcu_record_xxx(...) 
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
static __inline int ipvp_record_start (mkit_handle_t caller,ipvp_record_t *info,int sync)
{
    return ipvp_mcu_record_start(caller,0,info,sync);
}
static __inline int ipvp_record_start2(mkit_handle_t caller,const char *file,int sync)
{
    return ipvp_mcu_record_start2(caller,0,file,sync);
}
static __inline int ipvp_record_stop  (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_record_stop(caller,0,sync);
}
static __inline int ipvp_record_pause  (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_record_pause(caller,0,sync);
}
static __inline int ipvp_record_resume (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_record_resume(caller,0,sync);
}

/**
* @brief  :echo test
*
* @param  :
*           control : echo test type, define in IPVP_ECHO_xx
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_echo_test(mkit_handle_t caller,int control);

/**
* @brief  :audio loop test
*
* @param  :
*           control : define in IPVP_LOOP_xxx 
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_loop_test(mkit_handle_t caller,int control);

/**
* @brief  :video test
*
* @param  :
*           control : 1 for start;  0 for stop
*           videoID : video ID
*           win     : display window
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_loop_video(mkit_handle_t caller,int control,int videoSRC,int videoDST);


/**
* @brief  :audio train/tun APIs
*
* @param  :
* @warning:
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_audio_train_start(mkit_handle_t caller,int mode,const char*file);
IPVP_API int ipvp_audio_train_term (mkit_handle_t caller);

IPVP_API int ipvp_audio_tuning_start(mkit_handle_t caller,int mode,int type);
/**
* @brief  :audio tun APIs
*
* @param  :
*           type: 0 for timeout,1 for web set disable
* @warning:
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_audio_tuning_term (mkit_handle_t caller, int type);

/**
* @brief  : notice the engine that something (mainly gear motor) in motion now
*           to adapt some anomalous noise or other usage
*
* @param  :
*           on_off  : 1 for on ; 0 for off
* @warning:
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_audio_motion (mkit_handle_t caller, int on_off);

/**
* @brief  :media play/stop, for MCU
*
* @param  :
*           gid  : speech group ID,-1 as local
*           
* @warning: in ipvp_media_play2, parameters of ipvp_playback_t is fixed:
*           ipvp_playback_t play;
*           play.audio_dst = IPVP_FL_DIR_LOCAL;
*           play.video_dst = IPP_VIDEO_DST_HDMI;
*           play.video_win.left   = 0;
*           play.video_win.right  = 1920;
*           play.video_win.top    = 0;
*           play.video_win.bottom = 1080;
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_media_play (mkit_handle_t caller,int gid,ipvp_playback_t *play,int sync);
IPVP_API int ipvp_mcu_media_play2(mkit_handle_t caller,int gid,const char *file,int sync);
IPVP_API int ipvp_mcu_media_stop (mkit_handle_t caller,int gid,int sync);

/**
* @brief  :media pause/resume, for MCU
*
* @param  :
*           gid  : speech group ID,-1 as local
*           
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_media_pause (mkit_handle_t caller,int gid,int sync);
IPVP_API int ipvp_mcu_media_resume(mkit_handle_t caller,int gid,int sync);

/**
* @brief  :media FF/FR/seek, for MCU
*
* @param  :
*           gid     : speech group ID,-1 as local
*           step    : the FF/FR step in seconds, >0 for FF , <0 for FR
*           locate  : the seek location of media in seconds
* @warning:
*           it can be call when pause, and will not chang the pause state
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_media_FFFR(mkit_handle_t caller,int gid,int step,int sync);
IPVP_API int ipvp_mcu_media_seek(mkit_handle_t caller,int gid,unsigned int locate, int sync);

/**
* @brief  :get the media file information, get the current states if empty name
*
* @param  :
*           gid     : speech group ID,-1 as local
*           info    : the strunction of media information
* @warning:
*           
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_media_getinfo(mkit_handle_t caller,int gid,ipvp_pinfo_t *info,const char* file);

/**
* @brief  :media play/stop/pause/resume/FF/FR/seek
*
* @param  :
*              then same as ipvp_mcu_media_xxx(...) 
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
static __inline int ipvp_media_play (mkit_handle_t caller,ipvp_playback_t *play,int sync)
{
    return ipvp_mcu_media_play(caller,0,play,sync);
}
static __inline int ipvp_media_play2(mkit_handle_t caller,const char *file,int sync)
{
    return ipvp_mcu_media_play2(caller,0,file,sync);
}
static __inline int ipvp_media_stop (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_media_stop(caller,0,sync);
}
static __inline int ipvp_media_pause (mkit_handle_t caller,int sync)
{
    return ipvp_mcu_media_pause(caller,0,sync);
}
static __inline int ipvp_media_resume(mkit_handle_t caller,int sync)
{
    return ipvp_mcu_media_resume(caller,0,sync);
}
static __inline int ipvp_media_FFFR(mkit_handle_t caller,int step,int sync)
{
    return ipvp_mcu_media_FFFR(caller,0,step,sync);
}
static __inline int ipvp_media_seek(mkit_handle_t caller,unsigned int locate, int sync)
{
    return ipvp_mcu_media_seek(caller,0,locate,sync);
}
static __inline int ipvp_media_getinfo(mkit_handle_t caller,ipvp_pinfo_t *info,const char* file)
{
    return ipvp_mcu_media_getinfo(caller,0,info,file);
}

/*
*-----------------------------------------------------------
*   speech dependent APIs
*-----------------------------------------------------------
*/
/**
* @brief  :start a speech talk for MCU, if has video it will start a primary stream
*
* @param  :
*           callID  :speech call ID
*           gid     : speech group ID
*           speech  :speech param,size might be dynamic!
*           sync    :0==do not wait,1==to wait until speech really ready!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_audio_start(mkit_handle_t caller,int callID,int gid, ipvp_speech_t *speech,int sync);

/**
* @brief  :stop a speech talk
*
* @param  :
*           callID  :speech call ID
*           sync    :0==do not wait,1==to wait until speech really stopped!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_speech_stop(mkit_handle_t caller,int callID,int sync);

/**
* @brief  :modify a speech talk 
*
* @param  :
*           callID  :speech call ID
*           speech  :speech param,size might be dynamic!
*           sync    :0==do not wait,1==to wait until speech really modified!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_speech_modify(mkit_handle_t caller,int callID, ipvp_speech_t *speech,int sync);

/**
* @brief  :hold/resume a speech talk
*
* @param  :
*           callID  :speech call ID
*           hold    :IPVP_FL_HOLD_XX.
*           sync    :0==do not wait,1==to wait until speech really holded/resumed!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_speech_hold(mkit_handle_t caller,int callID,int hold,int sync);

/**
* @brief  :farmute/unfarmute a speech talk
*
* @param  :
*           callID  :speech call ID
*           hold    :0==resume speech;1==hold speech.
*           sync    :0==do not wait,1==to wait until speech really farmute/unfarmute!if not sure,then set 0!
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_speech_farmute(mkit_handle_t caller,int callID,int farmute,int sync);

/**
* @brief  :farmute/unfarmute a group talk
*
* @param  :
*           callID  :speech group ID
*           farmute    :0==unfarmute;1==farmute
*           sync    :0==do not wait,1==to wait until speech really farmute/unfarmute!if not sure,then set 0!
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_mcu_farmute(mkit_handle_t caller,int gid,int farmute,int sync);

/**
* @brief  :merge a set speech talk to a conference talk
*
* @param  :
*           gid     : speech group ID
*           confer  :param of speech conference
*           sync    :0==do not wait,1==to wait until speech really connected!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_audio_merge(mkit_handle_t caller,int gid,const ipvp_confer_t *confer,int sync);

/**
* @brief  :split a set speech talk of a conference talk
*
* @param  :
*           gid     : speech group ID
*           confer  :param of speech conference
*           sync    :0==do not wait,1==to wait until speech really connected!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_audio_split(mkit_handle_t caller,int gid,const ipvp_confer_t *confer,int sync);

/**
* @brief  :speech talk   start/merge/split
*
* @param  :
*              then same as ipvp_mcu_speech_xxx(...) 
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_video_start (mkit_handle_t caller,int callID,int gid,ipvp_video_t *video,int sync);
static __inline int ipvp_speech_start(mkit_handle_t caller,int callID, ipvp_speech_t *speech,int sync)
{
    ipvp_speech_t speech_t;

    if (!speech)
        return -EINVAL;

    if (speech->size)
    {
        memcpy(&speech_t, speech, speech->size);
    }
    else
    {
        memcpy(&speech_t, speech,IPVP_SPEECH_SIZE_V1);
    }

    if(speech->mode & IPVP_FL_VAM_VIDEO)
        ipvp_mcu_video_start(caller,callID,0,&speech_t.video,sync);

    return ipvp_mcu_audio_start(caller,callID,0,speech,sync);
}
static __inline int ipvp_confer_merge(mkit_handle_t caller,const ipvp_confer_t *confer,int sync)
{
    return ipvp_mcu_audio_merge(caller,0,confer,sync);
}
static __inline int ipvp_confer_split(mkit_handle_t caller,const ipvp_confer_t *confer,int sync)
{
    return ipvp_mcu_audio_split(caller,0,confer,sync);
}


/**
* @brief  :talk roaming control
*
* @param  :
            callID  :speech call ID
*           control :IPVP_ROAMING_XXX
*           romaing :talk roaming param
* @warning:
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_speech_roaming_in (mkit_handle_t caller, int callID, int gid,     ipvp_audio_ctx *context);
IPVP_API int ipvp_speech_roaming_out(mkit_handle_t caller, int callID, int control, ipvp_roaming_t *romaing);

/**
* @brief  :get/set speech context
*
* @param  :
            callID  :speech call ID
*           control :reserved, MUST set 0
*           context :speech context
* @warning:
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_get_audio_context(mkit_handle_t caller,int callID,int reserved,ipvp_audio_ctx *context);
IPVP_API int ipvp_set_audio_context(mkit_handle_t caller,int callID,int control,ipvp_audio_ctx *context);

IPVP_API int ipvp_speech_roaming_rollback(mkit_handle_t caller, int callID);
IPVP_API int ipvp_speech_roaming_dump(mkit_handle_t caller, char* buff, int length);
IPVP_API int ipvp_speech_roaming_ready(mkit_handle_t caller, int callID, ipvp_roaming_t *romaing);
/**
* @brief  :get number of speech that running now!
*
* @param  :
* @warning:
* @return :==0 is no speech now;
*          > 0:number of active speech
*          < 0:failed.
* 
*/
IPVP_API int ipvp_get_speeches (mkit_handle_t caller);

/**
* @brief  :get number of conference that running now!
*
* @param  :
* @warning:
* @return :==0:conference is NOT active
*          ==1:conference is active
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_conferes(mkit_handle_t caller);


/**
* @brief  :get stats data of speech
*
* @param  :
* @warning:
* @return :=>0:OK
*          < 0:failed
* 
*/
IPVP_API int ipvp_get_audio_stats (mkit_handle_t caller,int callID,ipvp_astats_t *stats);
IPVP_API int ipvp_get_video_stats (mkit_handle_t caller,int callID,ipvp_vstats_t *stats);
IPVP_API int ipvp_get_share_stats (mkit_handle_t caller,int callID,ipvp_vstats_t *stats);
IPVP_API int ipvp_get_speech_stats(mkit_handle_t caller,int callID,ipvp_stats_t  *stats);
IPVP_API int ipvp_get_qoe_stats   (mkit_handle_t caller,int callID,ipvp_qoestats_t *qoe);

/**
* @brief  :get bandwidth of speech that running now!
*
* @param  :
*           gid             : speech group ID
*          bandwidth  : ltotal bandwidth of active speech
* @warning:
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_get_bandwidth(mkit_handle_t caller,int gid,ipvp_bandwidth_t *bandwidth);

/**
* @brief  :set gid and  interval for rms report.
*
* @param  :
*           gid     : speech group ID
*          interval :report interval
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_rms_report(mkit_handle_t caller,int gid,int interval);

/**
* @brief  :set lostrate and  lasttime for lostpkt report.
*
* @param  :
*          alostrate : audio lost rate
*          vlostrate : video lost rate
*          lasttime  : last time sec
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_set_lostpkt_report(mkit_handle_t caller,int alossrate,int vlossrate,int lasttime);

/*
*-----------------------------------------------------------
*   video dependent APIs
*-----------------------------------------------------------
*/
/**
* @brief  :get/set the device configure
*
* @param  :
*           videoSRC: IPVP_VIDEO_SRC_xx
*           videoDST: IPVP_VIDEO_DST_xx
*
* @warning:
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_get_display(mkit_handle_t caller,int videoDST, int* width, int* height, int* fps);
IPVP_API int ipvp_get_capture(mkit_handle_t caller,int videoSRC, int* width, int* height, int* fps);
IPVP_API int ipvp_set_capture(mkit_handle_t caller,int videoSRC, int width, int height);
IPVP_API int ipvp_set_display(mkit_handle_t caller,int videoDST, int width, int height, int fps);
IPVP_API int ipvp_set_display2(mkit_handle_t caller,int videoDST, int width, int height, int fps, int sync);
/**
* @brief  :merge a set speech talk to a conference talk
*
* @param  :
*           display :display param
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_set_display_force(mkit_handle_t caller, ipvp_display_t *display, int sync);
IPVP_API int ipvp_set_display_ratio(mkit_handle_t caller,int videoDST, int ratio);
IPVP_API int ipvp_set_hdmi_map(mkit_handle_t caller,int reverse);
IPVP_API int ipvp_camera_mute(mkit_handle_t caller,int camera_type,int mute, int color);

/**
* @brief  :set hdmi enable
*
* @param  :
*           hdmi_idx :hdmi serial number
* @warning:
*
* @return :0 is success,otherwise failed.
*
*/
int ipvp_set_hdmi_status(mkit_handle_t caller, int hdmi_idx, int enable, int sync);

/**
* @brief  :start/modify/stop a video call as a primary stream
*          (index by IPVP_VIDEO_ID_SPEECH) with stream!!
*
* @param  :
*           gid     : speech group ID
* @warning:
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_video_modify(mkit_handle_t caller,int callID,ipvp_video_t *video,int sync);
IPVP_API int ipvp_video_stop  (mkit_handle_t caller,int callID,int sync);

/**
* @brief  :create/destroy a video call as a secondary stream 
*          (index by IPVP_VIDEO_ID_SHARED) without stream!!
*
* @param  :
*           gid     : speech group ID
* @warning:
*           
* @return :=>0 OK
*          < 0:failed.
* 
*/
/*FIXME:do we need to create/destroy???*/
IPVP_API int ipvp_mcu_shared_create (mkit_handle_t caller,int callID,int gid,ipvp_video_t *video,int sync);
IPVP_API int ipvp_shared_destroy(mkit_handle_t caller,int callID,int sync);

/**
* @brief  :start/stop/modify a video call as a secondary stream
*          (index by IPVP_VIDEO_ID_SHARED) with stream!!
*
* @param  :
*           gid     : speech group ID
* @warning:
*           the share video callID MAY be different from primary call
*           
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_mcu_shared_start(mkit_handle_t caller,int callID,int gid,ipvp_video_t *video,int sync);
IPVP_API int ipvp_shared_stop (mkit_handle_t caller,int callID,int sync);
IPVP_API int ipvp_share_modify(mkit_handle_t caller,int callID,ipvp_video_t *video,int sync);

/**
* @brief  : hold a secondary stream, pause to send/recv a secondary stream
*
* @param  :
* @warning:
            this api only for share recv
* @return :=>0 OK
*          < 0:failed.
*
*/
IPVP_API int ipvp_shared_hold(mkit_handle_t caller,int callID,int hold,int sync);

/**
* @brief  : hold a video stream, pause to send/recv a video stream
*
* @param  : 
*          hold : IPVP_VIDEO_HOLD_ACTIVE - hold,
*                 IPVP_VIDEO_HOLD_PASSIVE - held,
*                 IPVP_VIDEO_UNHOLD  - unhold,
* @warning:
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_video_hold(mkit_handle_t caller,int callID,int hold,int sync);

/**
* @brief  : mute near-end video by cover a picture
*
* @param  :
*           videoSRC: IPVP_VIDEO_ID_xx
*           mute    : 1 - mute; 0 - unmute
*           file    : the cover picture, must be as the same size as videoSRC
* @warning:
*           can it mute distinctive by the callID??
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_video_mute(mkit_handle_t caller,int callID,int videoID, int mute, const char* file,int sync);

/**
* @brief  :merge a set video talk to a conference talk
*
* @param  :
*           gid     : speech group ID
*           confer  :param of video conference
*           sync    :0==do not wait,1==to wait until speech really connected!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_video_merge(mkit_handle_t caller,int gid,const ipvp_confer_t *confer,int sync);

/**
* @brief  :split a set video talk of a conference talk
*
* @param  :
*           gid     : speech group ID
*           confer  :param of video conference
*           sync    :0==do not wait,1==to wait until speech really connected!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_mcu_video_split(mkit_handle_t caller,int gid,const ipvp_confer_t *confer,int sync);

/**
* @brief  :control API for video session
*
* @param  :
* @warning:
* @return :=>0 OK
*          < 0:failed.
* 
*/
/*FIXME:${videoID} can be IPVP_VIDEO_ID_SPEECH/IPVP_VIDEO_ID_SHARED*/
IPVP_API int ipvp_video_req_keyframe (mkit_handle_t caller,int callID,int videoID,int sync);

/**
* @brief  :request a speech quality change
*
* @param  :
*           callID  :speech call ID
*           quality :param of speech quality
*           sync    :0==do not wait,1==to wait until speech really connected!if not sure,then set 0!
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_video_set_quality(mkit_handle_t caller,int callID,int videoID,ipvp_quality_t* quality,int sync);

/**
* @brief  :control API for layout
*
* @param  :
*           gid     : speech group ID
* @warning:
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_mcu_set_layout(mkit_handle_t caller,int gid,int devDST,ipvp_layout_t layout[],int layout_nr,int sync);

/**
* @brief  :combine video source to a video ID (NOT IMPLEMENTED YET)
*
* @param  :
* @warning:
*           there we bind IPVP_VIDEO_ID_SPEECH to IPVP_VIDEO_SRC_CAM,
*           and IPVP_VIDEO_ID_SHARED to IPVP_VIDEO_SRC_VGA statically
*
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_video_set_source(mkit_handle_t caller,int callID,int videoID,int videoSRC, int sync);

/**
* @brief  :misc API for layout/camera/display
*
* @param  :
*           gid     : speech group ID
* @warning:
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_mcu_snapshot(mkit_handle_t caller,int gid,int stream,const char*file,int sync);
IPVP_API int ipvp_mcu_snapshot2(mkit_handle_t caller,int callID,int gid,int stream,const char*file,int sync);

/**
* @brief  : API for set / clear (one) / reset (clear off) OSD layout
*
* @param  :
*           gid     : speech group ID
* @warning:
*           the same OSD file is seen as the same OSD layout
*
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_mcu_osd_setup(mkit_handle_t caller,int gid,int videoID,int osdID,ipvp_osd_t* osd,int sync);
IPVP_API int ipvp_mcu_osd_clear(mkit_handle_t caller,int gid,int videoID,int osdID,int sync);
IPVP_API int ipvp_mcu_osd_reset(mkit_handle_t caller,int gid,int sync);

/**
* @brief  : API for load OSD mute image
*
* @param  :
*           gid     : speech group ID
*           file_image : image file path
* @warning:        
*
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_mcu_osd_load_image(mkit_handle_t caller,int gid, const char* file_image,int sync);

/**
* @brief  : API for enable/disable mute OSD image
*
* @param  :
*           gid     : speech group ID
*           mute    : IPVP_MUTE / IPVP_UNMUTE
*           type    : 0:show video, 0xFF:show OSD image
* @warning:
*
* @return :=>0 OK
*          < 0:failed.
* 
*/
IPVP_API int ipvp_mcu_osd_mute_image(mkit_handle_t caller,int gid, int mute, unsigned short type, int sync);

/**
* @brief  :video  API
*
* @param  :
*              then same as ipvp_mcu_video_xxx(...) 
* @warning:
*          
* @return :0 is success,otherwise failed.
* 
*/
static __inline int ipvp_video_start(mkit_handle_t caller,int callID,ipvp_video_t *video,int sync)
{
    return ipvp_mcu_video_start(caller,callID,0,video,sync);
}
static __inline int ipvp_shared_create (mkit_handle_t caller,int callID,ipvp_video_t *video,int sync)
{
    return ipvp_mcu_shared_create(caller,callID,0,video,sync);
}
static __inline int ipvp_shared_start (mkit_handle_t caller,int callID,ipvp_video_t *video,int sync)
{
    return ipvp_mcu_shared_start(caller,callID,0,video,sync);
}
static __inline int ipvp_video_merge(mkit_handle_t caller,const ipvp_confer_t *confer,int sync)
{
    return ipvp_mcu_video_merge(caller,0,confer,sync);
}
static __inline int ipvp_video_split(mkit_handle_t caller,const ipvp_confer_t *confer,int sync)
{
    return ipvp_mcu_video_split(caller,0,confer,sync);
}
static __inline int ipvp_video_set_layout(mkit_handle_t caller,int devDST,ipvp_layout_t layout[],int layout_nr,int sync)
{
    return ipvp_mcu_set_layout(caller,0,devDST,layout,layout_nr,sync);
}
static __inline int ipvp_video_snapshot(mkit_handle_t caller,int videoID,const char*file,int sync)
{
    return ipvp_mcu_snapshot(caller,0,videoID,file,sync);
}
static __inline int ipvp_video_snapshot2(mkit_handle_t caller,int callID,int videoID,const char*file,int sync)
{
    return ipvp_mcu_snapshot2(caller,callID,0,videoID,file,sync);
}
static __inline int ipvp_OSD_setup(mkit_handle_t caller,int videoID,int osdID,ipvp_osd_t* osd,int sync)
{
    return ipvp_mcu_osd_setup(caller,0,videoID,osdID,osd,sync);
}
static __inline int ipvp_OSD_clear(mkit_handle_t caller,int videoID,int osdID,int sync)
{
    return ipvp_mcu_osd_clear(caller,0,videoID,osdID,sync);
}
static __inline int ipvp_OSD_reset(mkit_handle_t caller,int sync)
{
    return ipvp_mcu_osd_reset(caller,0,sync);
}

/**
* @brief  :video private message notify
*
* @param  :
*           callID  :speech call ID
*           videoID  :speech video ID
*           data :private message string
*           data :message len
*
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_video_private_notify(mkit_handle_t caller,int callID,int videoID,const char* data,int len);

/*
*-----------------------------------------------------------
*   notification APIs
*-----------------------------------------------------------
*/
/**
* @brief  :to request a notification
*
* @param  :
* @warning:
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_request_notify(mkit_handle_t caller,int event);

/**
* @brief  :to request a notification
*
* @param  :
* @warning:
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_cancel_notify(mkit_handle_t caller,int event);


/*
*-----------------------------------------------------------
*   help APIs
*-----------------------------------------------------------
*/
/**
* @brief  :dump current state, for debug function 
*
* @param  :
* @warning:
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_dump_stat(mkit_handle_t caller,char*buff,size_t buff_max);

IPVP_API int ipvp_memcheck (mkit_handle_t caller, char*buff, size_t buff_max);

/**
* @brief  :dump current audio
*
* @enable   :1 start dump,0 stop dump
* @file_path:audio dump file path  
* @return :0 is success,otherwise failed.
* 
*/
IPVP_API int ipvp_dump_audio(mkit_handle_t caller,int enable,char *file_path);

/**
* @brief  :dump current audio
*
* @buf   :data buf
* @buf_max :buf max,less than 65535
* @return :data length.
*
*/
IPVP_API int ipvp_get_audio_data(mkit_handle_t caller, char *buf, int buf_max);

/**
* @brief  :capture audio to network
*
* @enable   :1 start dump,0 stop dump
* @file_path:audio dump file path
* @return :0 is success,otherwise failed.
*
*/
IPVP_API int ipvp_network_capture_audio(mkit_handle_t caller, int inst, ipvp_netcap_t *capture);
IPVP_API int ipvp_network_capture_stop(mkit_handle_t caller, int inst);

/**
* @brief  :share PC mouse position
*
* @param  :
*           callID  :speech call ID
*           videoID  :speech video ID
*           file_image : image file path
*
* @return :0 is success,otherwise failed.
*
*/
int ipvp_video_load_mouse(mkit_handle_t caller, int callID, int gid, int videoID, const char* file_imagee, int sync);
int ipvp_video_update_mouse(mkit_handle_t caller, int callID, int gid, int videoID, ipvp_image_pos *imge_pos, int sync);
/************************************************************************/
/*                                                                      */
/************************************************************************/
#endif /* __SERVICE_IPVP_API_H__ */
