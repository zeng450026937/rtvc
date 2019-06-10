#ifndef __MULTIMEDIA_INTERFACE_H__
#define __MULTIMEDIA_INTERFACE_H__

#include "multimedia_types.h"
#include "video_frame_delivery.h"
namespace multimedia
{
	class _VCS_SDKAPI_EXPORT_ MediaEngineGlobal
	{
	public:
		static int Startup(VideoEventCallBack event_cb,
			VideoLogCallback log_cb,
			VideoExternalTransportSink *trpt_cb);
		static int Shutdown();
	};

	//For access physical video camera devices
	class _VCS_SDKAPI_EXPORT_ IVideoCameraDeviceAccess
	{
	public:
		static const int kVideoCameraDeviceMaxNum = 5;
		static int EnumCameraDevices(VideoCameraDeviceDescriptor devs[], int arr_num, int& out_num);

		static int GetCameraCapability(const VideoCaptureString &unique_id,
			VideoCameraDeviceCapability dev_cap[], int caps_num, int& out_nums);

		static int GetMatchedCapability(const VideoCaptureString &unique_id,
			const VideoCameraDeviceCapability &target_cap,
			VideoCameraDeviceCapability &matched_cap);
	};

	class _VCS_SDKAPI_EXPORT_ IVideoCaptureSource
	{
	public:
		static int CreateInstance(IVideoCaptureSource*& ptr);
		static int DestroyInstance(IVideoCaptureSource*& ptr);
	public:
		virtual int Start(const VideoCaptureSourceInfo& info) = 0;
		virtual int Stop() = 0;
		virtual int UpdateCapturedImageOrientation(int orient) = 0;

		/*Set delivery sink. If set nullptr, it will stop delivery frame.*/
		virtual int SetDeliverySink(VideoFrameDeliverySink* sink = nullptr) = 0;
	protected:
		virtual ~IVideoCaptureSource(){}
	};

	// For SVC Session manager
	class _VCS_SDKAPI_EXPORT_ ISvcSessionApi
	{
	public:
		static int CreateInstance(ISvcSessionApi*& inst, VideoCCIDType cid,
			VideoSessionType video_sess_type);
		static int DestroyInstance(ISvcSessionApi*& inst);

		virtual int InitConfig(const SvcConfig& config) = 0;
		virtual int BindCaptureSource(IVideoCaptureSource* cap_src) = 0;
		virtual int UnBindCaptureSource() = 0;

		virtual int JoinSession() = 0;
		virtual int LeaveSession() = 0;

		virtual int GetStreamSendStatis(SvcStatistics& stat) const = 0;
		virtual int GetStreamReceiveStatis(SvcStatistics& stat) const = 0;
		virtual int GetNetWorkReceiveStatis(SvcStatistics& stat) const = 0;

		virtual int AddSubscriber(const SubscribeConfig& subcfg) = 0;
		virtual int UpdateSubscriberRenderInfo(unsigned int ccid, RenderConfig render_config) = 0;
		virtual int RemoveSubscriber(unsigned int ccid) = 0;

	protected:
		virtual ~ISvcSessionApi(){}
	};
	//For AVC Session Manager
	class _VCS_SDKAPI_EXPORT_ IAVCSessionApi
	{
	public:
		static int CreateInstance(IAVCSessionApi*& inst, VideoSessionType video_sess_type);
		static int DestroyInstance(IAVCSessionApi*& inst);

		virtual int InitConfig(const AvcConfig& config) = 0;
		virtual int BindCaptureSource(IVideoCaptureSource* cap_src) = 0;
		virtual int UnBindCaptureSource() = 0;

		virtual int StartSession() = 0;
		virtual int StopSession() = 0;

		/*Set delivery sink. If set nullptr, it will stop delivery frame.
			If VideoSessionOrient passed by InitConfig is VIDEO_SESSION_ORIENT_SEND, 
			there is no frame delivered either.*/
		virtual int SetDeliverySink(VideoFrameDeliverySink* sink = nullptr) = 0;

		virtual int GetMediaSendStatis(VideoStatistics& stat) const = 0;
		virtual int GetMediaReceiveStatis(VideoStatistics& stat) const = 0;

		virtual int GetPrivateCapabilitySetting(MediaVideoPrivateCapacity& self_priv_capset) = 0;
		virtual int FlowControl(int bps) = 0;
		virtual int RequestKeyFrame() = 0;

		virtual int UpdateEncodeTargetParas(int bit_rate, int frame_rate, int video_width, int video_height) = 0;
	protected:
		virtual ~IAVCSessionApi(){}
	};
}
#endif  // __MULTIMEDIA_INTERFACE_H__