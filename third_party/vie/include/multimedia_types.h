#ifndef __MULTIMEDIA_TYPES_H__
#define __MULTIMEDIA_TYPES_H__

#ifdef _WIN32
#ifdef _VCS_MEDIA_SDK_DLL_COMPILE_
#define _VCS_SDKAPI_EXPORT_ __declspec (dllexport)
#else
#define _VCS_SDKAPI_EXPORT_ __declspec (dllimport)
#endif
#else
#define _VCS_SDKAPI_EXPORT_
#endif

#include "video_engine_event.h"
#include "video_external_transport.h"

/************************************************************************/
/* Param For Render And OSD Function                                     */
/************************************************************************/
namespace multimedia
{
	struct _VCS_SDKAPI_EXPORT_ RenderCoordinate
	{
		RenderCoordinate();
		explicit RenderCoordinate(float left, float top, float right, float bottom, int z_order);

		float left;
		float top;
		float right;
		float bottom;
		int z_order;
	};

	struct _VCS_SDKAPI_EXPORT_ RenderConfig
	{
		RenderConfig();
		RenderConfig(void* win_handle, const RenderCoordinate &coor);
		void* win_handle;
		RenderCoordinate coor;
	};

	struct _VCS_SDKAPI_EXPORT_ OnScreenDisplayBitmap
	{
		OnScreenDisplayBitmap();

		long        bmType; // unused for now
		long        bmWidth;
		long        bmHeight;
		long        bmStrideBytes; // bytes per row
		void*       bmBits; // data point
		unsigned short bmBitsPixel; // bits per pixel
	};

	/************************************************************************/
	/* Param For Capture Function                                                   */
	/************************************************************************/
	struct _VCS_SDKAPI_EXPORT_ VideoCaptureString
	{
		VideoCaptureString();
		VideoCaptureString(const VideoCaptureString &src);
		VideoCaptureString(const char* str, int str_len);

		bool CheckValid() const;

		static const int kVideoCaptureStringSize = 2048;
		char str[kVideoCaptureStringSize];
		int str_len;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoCameraDeviceDescriptor
	{
		VideoCameraDeviceDescriptor();
		VideoCameraDeviceDescriptor(const VideoCaptureString &unique_id,
			const VideoCaptureString &device_name);
		VideoCameraDeviceDescriptor(const char* id_str, int id_len, const char* name_str, int name_len);

		VideoCaptureString unique_id;
		VideoCaptureString device_name;
	};

	enum VideoRawDataType
	{
		VIDEO_RAW_DATA_I420 = 0,
		VIDEO_RAW_DATA_YV12 = 1,
		VIDEO_RAW_DATA_YUY2 = 2,
		VIDEO_RAW_DATA_UYVY = 3,
		VIDEO_RAW_DATA_IYUV = 4,
		VIDEO_RAW_DATA_ARGB = 5,
		VIDEO_RAW_DATA_RGB24 = 6,
		VIDEO_RAW_DATA_RGB565 = 7,
		VIDEO_RAW_DATA_ARGB4444 = 8,
		VIDEO_RAW_DATA_ARGB1555 = 9,
		VIDEO_RAW_DATA_MJPEG = 10,
		VIDEO_RAW_DATA_NV12 = 11,
		VIDEO_RAW_DATA_NV21 = 12,
		VIDEO_RAW_DATA_BGRA = 13,
		VIDEO_RAW_DATA_UNKNOWN = 99
	};
	const char* VideoRawDataTypeToString(VideoRawDataType raw_type);

	struct _VCS_SDKAPI_EXPORT_ VideoCaptureFormat
	{
		VideoCaptureFormat();
		VideoCaptureFormat(int width, int height, int frame_rate, VideoRawDataType raw_type);

		void Set(int width, int height, int frame_rate, VideoRawDataType raw_type);
		void Get(int &width, int &height, int &frame_rate, VideoRawDataType &raw_type);

		int width;
		int height;
		int frame_rate;
		VideoRawDataType raw_type;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoCameraCaptureFormat
	{
		VideoCameraCaptureFormat();

		int orientation;
		int capture_delay;
		bool interlaced_flag;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoCameraDeviceCapability
	{
		VideoCameraDeviceCapability();
		VideoCameraDeviceCapability(const VideoCaptureFormat &format,
			const VideoCameraCaptureFormat &param);

		VideoCaptureFormat format;
		VideoCameraCaptureFormat camera_format;
	};

	enum VideoCaptureSourceType
	{
		VIDEO_CAPTURE_SOURCE_UNDEF = -1,
		VIDEO_CAPTURE_SOURCE_CAMERA,
		VIDEO_CAPTURE_SOURCE_SCREEN,
		VIDEO_CAPTURE_SOURCE_PICTURE
	};

	struct _VCS_SDKAPI_EXPORT_ VideoCameraDeviceParam
	{
		VideoCameraDeviceParam();

		VideoCaptureString unique_id;
		VideoCameraCaptureFormat camera_format;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoScreenCaptureParam
	{
		VideoScreenCaptureParam();
		VideoScreenCaptureParam(void* target_handle,
			const VideoCaptureString &cover_picture_path);

		void* target_handle;
		VideoCaptureString cover_picture_path;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoPictureCaptureParam
	{
		VideoPictureCaptureParam();
		VideoPictureCaptureParam(const VideoCaptureString &file_path);

		VideoCaptureString picture_path;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoCaptureSourceInfo
	{
		VideoCaptureSourceInfo();

		VideoCaptureSourceType capture_type;
		VideoCaptureFormat format;

		VideoCameraDeviceParam camera_param;
		VideoScreenCaptureParam screen_param;
		VideoPictureCaptureParam file_param;
	};
	/************************************************************************/
	/* Param For Video Codec                                                         */
	/************************************************************************/
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

	struct _VCS_SDKAPI_EXPORT_ VideoCodecInfo
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

	struct _VCS_SDKAPI_EXPORT_ VideoStreamMultiplex
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

	enum VideoSessionType
	{
		VIDEO_SESSION_UNDEF = -1,
		VIDEO_SESSION_CAMERA,
		VIDEO_SESSION_DATA_SHARE
	};

	typedef unsigned int VideoCCIDType;
	typedef unsigned int VideoStreamIDType;
	static const VideoStreamIDType kVideoStreamIDInvalidValue = (unsigned int)(~0);

	enum VideoSessionOrient
	{
		VIDEO_SESSION_ORIENT_UNDEF = 0,
		VIDEO_SESSION_ORIENT_SEND = 1,
		VIDEO_SESSION_ORIENT_RECV = 2,
		VIDEO_SESSION_ORIENT_BOTH = 3
	};

	struct _VCS_SDKAPI_EXPORT_ VideoSessionParams
	{
		VideoSessionParams();

		bool enable_net_adpter;
		bool enable_incomplete_decoding;
		bool enable_net_address_adpter;

		VideoStreamMultiplex multiplex;

		unsigned long qos_value;
		VideoQualityPolicyType quality_policy;
	};

	static const int kMediaVideoMaxCodecNumber = 32;
	struct _VCS_SDKAPI_EXPORT_ MediaVideoCodecArray
	{
		MediaVideoCodecArray();

		VideoCodecInfo determined_send_codec;
		VideoCodecInfo available_send_codecs[kMediaVideoMaxCodecNumber];
		unsigned int available_send_codecs_num;

		VideoCodecInfo determined_recv_codec;
		VideoCodecInfo available_recv_codecs[kMediaVideoMaxCodecNumber];
		unsigned int available_recv_codecs_num;
	};

	struct _VCS_SDKAPI_EXPORT_ MediaVideoPrivateCapacity
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

	struct _VCS_SDKAPI_EXPORT_ MediaTransportAddrInfo
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

	struct _VCS_SDKAPI_EXPORT_ MediaTransportConfig
	{
		MediaTransportConfig();
		MediaTransportType transport_type;
		/*For MEDIA_TRANSPORT_TYPE_TRPT_HANDLE*/
		VideoTransportHandle rtp_handle;
		VideoTransportHandle rtcp_handle;
		/*For MEDIA_TRANSPORT_TYPE_NORMAL*/
		MediaTransportAddrInfo network_addr;
	};


	struct _VCS_SDKAPI_EXPORT_ MediaRtcpKeepAliveConfig
	{
		MediaRtcpKeepAliveConfig();

		bool enable;
		unsigned char payload_type;
		unsigned int  send_interval_mills;
	};

	struct _VCS_SDKAPI_EXPORT_ MediaVideoRtcpParams
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

	struct _VCS_SDKAPI_EXPORT_ MediaEncryptKeyInfo
	{
		MediaEncryptKeyInfo();

		MediaEncryptType type;
		const char* key_ptr;
		unsigned int key_len;
	};

	struct _VCS_SDKAPI_EXPORT_ MediaEncryptParams
	{
		MediaEncryptParams();

		MediaEncryptKeyPattern encrypt_key_pattern;
		MediaEncryptKeyInfo send_encrypt_key;
		MediaEncryptKeyInfo recv_encrypt_key;
	};

	struct _VCS_SDKAPI_EXPORT_ AvcConfig
	{
		AvcConfig();

		VideoStreamIDType stream_id;
		VideoSessionParams sess_pars;
		MediaVideoCodecArray codecs;
		MediaVideoPrivateCapacity remote_private_capset;
		MediaTransportConfig transport_config;
		MediaVideoRtcpParams rtcp_pars;
		MediaEncryptParams encrypt_pars;
		VideoSessionOrient sess_orient;
	};

	struct _VCS_SDKAPI_EXPORT_ UserConfig
	{
		UserConfig();

		unsigned int user_ccid;
	};

	struct _VCS_SDKAPI_EXPORT_ SessionConfig
	{
		SessionConfig();

		UserConfig user_info;
		const char* confid;
		VideoSessionOrient orient;
	};

	struct _VCS_SDKAPI_EXPORT_ SvcConfig
	{
		SvcConfig();

		SessionConfig session_info;
		MediaTransportAddrInfo addr;
	};

	struct _VCS_SDKAPI_EXPORT_ SubscribeConfig
	{
		SubscribeConfig();

		VideoCCIDType ccid;
		int width;
		int height;
		RenderConfig render_info;
	};

	struct _VCS_SDKAPI_EXPORT_ VideoStatistics
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

	struct _VCS_SDKAPI_EXPORT_ SvcStatistics
	{
		SvcStatistics();

		unsigned int width;
		unsigned int height;
		unsigned int frame_rate;
		unsigned int bit_rate;

		unsigned int loss_rate;
		unsigned int accumulated_loss_packets;
		unsigned int jitter;
		unsigned int rtt;
	};

	/*Log callback function.*/
	enum VideoLogLevelType
	{
		VIDEO_LOG_LEVEL_NONE = 0,
		VIDEO_LOG_LEVEL_ERR,
		VIDEO_LOG_LEVEL_WARN,
		VIDEO_LOG_LEVEL_INFO,
		VIDEO_LOG_LEVEL_DEBUG
	};
	typedef void(*VideoLogCallback) (VideoLogLevelType level, const char *data, int len);
}

#endif  // __MULTIMEDIA_TYPES_H__

