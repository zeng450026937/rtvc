#ifndef __MULTIMEDIA_VIDEO_AVC_SESSION_TYPE_H__
#define __MULTIMEDIA_VIDEO_AVC_SESSION_TYPE_H__

#include "multimedia_types.h"
#include "video_session_common.h"
#include "video_external_transport.h"

namespace multimedia
{
	struct _MULTIMEDIA_API_EXPORT_ VideoStreamMultiplex
	{
		VideoStreamMultiplex();

		bool enable_rtp_multiplex;
		unsigned int rtp_multiplex_id;

		bool enable_rtcp_multiplex;
		unsigned int rtcp_multiplex_id;
	};

	enum VideoQualityPolicyType
	{
		OnlyFullyFrameRate,
		HighFrameRatePrefered,
		GoodStillImageQualityPrefered,
		OnlyStillImageQuality
	};

	enum VideoKeyFrameRequestMethod
	{
		KEYREQU_FIR_RTP,
		KEYREQU_PLI_RTCP,
		KEYREQU_FIR_RTCP,
		KEYREQU_EXTERNAL_SIGNAL
	};

	enum VideoFlowControlMethod
	{
		FLOWCTL_NONE,
		FLOWCTL_EXTERNAL_SIGNAL
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoSessionParams
	{
		VideoSessionParams();

		bool enable_net_adpter;
		bool enable_incomplete_decoding;
		bool enable_net_address_adpter;

		VideoStreamMultiplex multiplex;

		unsigned long qos_value;
		VideoQualityPolicyType quality_policy;
	};

	enum VideoCodecType
	{
		VIDEO_CODEC_UNDEF = -1,
		VIDEO_CODEC_H263,
		VIDEO_CODEC_H264
	};

	enum VideoCodecProfileType
	{
		VIDEO_CODEC_PROFILE_UNDEF = -1,
		VIDEO_CODEC_PROFILE_BASE,
		VIDEO_CODEC_PROFILE_MAIN,
		VIDEO_CODEC_PROFILE_HIGH,
		VIDEO_CODEC_PROFILE_MAX
	};

	enum VideoCodecSliceMode
	{
		VIDEO_CODEC_SLICE_UNDEF = -1,
		VIDEO_CODEC_SLICE_SINGLE,
		VIDEO_CODEC_SLICE_MULTI
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCodecInfo
	{
		VideoCodecInfo();

		VideoCodecType codec_type;

		unsigned char payload_type;
		unsigned int target_bitrate;
		unsigned int target_framerate;

		unsigned int width;
		unsigned int height;

		unsigned int key_frame_interval;
		unsigned int packet_mtu_size;

		VideoCodecSliceMode slice_mode;
		VideoCodecProfileType profile;
	};

	static const int kMediaVideoMaxCodecNumber = 32;
	struct _MULTIMEDIA_API_EXPORT_ MediaVideoCodecArray
	{
		MediaVideoCodecArray();

		VideoCodecInfo determined_send_codec;
		VideoCodecInfo available_send_codecs[kMediaVideoMaxCodecNumber];
		unsigned int available_send_codecs_num;

		VideoCodecInfo determined_recv_codec;
		VideoCodecInfo available_recv_codecs[kMediaVideoMaxCodecNumber];
		unsigned int available_recv_codecs_num;
	};

	struct _MULTIMEDIA_API_EXPORT_ MediaVideoPrivateCapacity
	{
		MediaVideoPrivateCapacity();

		unsigned char payload_type;
		char  codec_name[128];
		unsigned int clock_rate;
		char private_capacity[1024];
	};

	enum MediaTransportType
	{
		MEDIA_TRANSPORT_TYPE_UNDEF = -1,
		MEDIA_TRANSPORT_TYPE_NORMAL,
		MEDIA_TRANSPORT_TYPE_EXTERNAL
	};

	struct _MULTIMEDIA_API_EXPORT_ MediaTransportAddrInfo
	{
		MediaTransportAddrInfo();
		MediaTransportAddrInfo(const char* local_ip,
			unsigned short local_rtp_port, unsigned short local_rtcp_port,
			const char* remt_ip,
			unsigned short remt_rtp_port, unsigned short remt_rtcp_port);
		const char*    local_ip = nullptr;
		unsigned short local_rtpport = 0;
		unsigned short local_rtcpport = 0;

		const char*    remote_ip = nullptr;
		unsigned short remote_rtp_port = 0;
		unsigned short remote_rtcp_port = 0;
	};

	struct _MULTIMEDIA_API_EXPORT_ MediaTransportConfig
	{
		MediaTransportConfig();
		MediaTransportType transport_type;
		/*For MEDIA_TRANSPORT_TYPE_TRPT_HANDLE*/
		VideoTransportHandle rtp_handle;
		VideoTransportHandle rtcp_handle;
		/*For MEDIA_TRANSPORT_TYPE_NORMAL*/
		MediaTransportAddrInfo network_addr;
	};


	struct _MULTIMEDIA_API_EXPORT_ MediaRtcpKeepAliveConfig
	{
		MediaRtcpKeepAliveConfig();

		bool enable;
		unsigned char payload_type;
		unsigned int  send_interval_mills;
	};

	struct _MULTIMEDIA_API_EXPORT_ MediaVideoRtcpParams
	{
		MediaVideoRtcpParams();

		int no_data_report_secs;
		VideoKeyFrameRequestMethod keyframe_request_method;
		VideoFlowControlMethod flow_control_method;
		MediaRtcpKeepAliveConfig keep_alive_config;
	};

	enum MediaEncryptKeyPattern
	{
		MEK_MASTER_KEY = 0,  // used by SIP
		MEK_SESSION_KEY = 1  // used by H323
	};

	enum MediaEncryptType
	{
		MET_NONE,
		MET_AES_CM_128,
		MET_AEC_CBC_128,
		MET_AES_CM_128_HMAC_SHA1_80,
		MET_AES_CM_128_HMAC_SHA1_32,
		MET_AES_CM_256_HMAC_SHA1_80,
		MET_AES_CM_256_HMAC_SHA1_32
	};

	struct _MULTIMEDIA_API_EXPORT_ MediaEncryptKeyInfo
	{
		MediaEncryptKeyInfo();

		MediaEncryptType type;
		const char* key_ptr;
		unsigned int key_len;
	};

	struct _MULTIMEDIA_API_EXPORT_ MediaEncryptParams
	{
		MediaEncryptParams();

		MediaEncryptKeyPattern encrypt_key_pattern;
		MediaEncryptKeyInfo send_encrypt_key;
		MediaEncryptKeyInfo recv_encrypt_key;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoStatistics
	{
		VideoStatistics();

		VideoCodecType codec_type;
		VideoCodecProfileType profile;

		unsigned int width;
		unsigned int height;
		unsigned int frame_rate;
		unsigned int bit_rate;

		unsigned int loss_rate;
		unsigned int accumulated_loss_packets;
		unsigned int jitter;
		unsigned int rtt;
	};

	struct _MULTIMEDIA_API_EXPORT_ AvcConfig
	{
		AvcConfig();

		VideoStreamIDType stream_id;
		VideoSessionParams sess_pars;
		MediaVideoCodecArray codecs;
		MediaVideoPrivateCapacity remote_private_capset;
		MediaTransportConfig transport_config;
		MediaVideoRtcpParams rtcp_pars;
		MediaEncryptParams encrypt_pars;
	};
}
#endif/*!__MULTIMEDIA_VIDEO_AVC_SESSION_TYPE_H__*/