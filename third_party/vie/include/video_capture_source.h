#ifndef __MULTIMEDIA_VIDEO_CAPTURE_SOURCE_H__
#define __MULTIMEDIA_VIDEO_CAPTURE_SOURCE_H__

#include "video_capture_source_type.h"
#include "multimedia_log.h"
#include "video_frame_delivery.h"
namespace multimedia
{
	class _MULTIMEDIA_API_EXPORT_ IVideoCameraDeviceAccess
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
	class IVideoCaptureSource;
	class _MULTIMEDIA_API_EXPORT_ IVideoCaptureSourceEventSink
	{
	public:
		virtual void OnCaptureFailed(IVideoCaptureSource* capture_source, 
			VideoCaptureSourceType capture_type) = 0;
		virtual void OnCaptureResume(IVideoCaptureSource* capture_source,
			VideoCaptureSourceType capture_type) = 0;
	protected:
		virtual ~IVideoCaptureSourceEventSink(){}
	};

	class _MULTIMEDIA_API_EXPORT_ IVideoCaptureSource :public VideoFrameProvider
	{
	public:
		static int CreateInstance(IVideoCaptureSource*& ptr);
		static int DestroyInstance(IVideoCaptureSource*& ptr);
	public:
		virtual int Start(const VideoCaptureSourceInfo& info,
			IVideoCaptureSourceEventSink* event_sink = nullptr) = 0;
		virtual int Stop() = 0;
		virtual int UpdateCapturedImageOrientation(int orient) = 0;
	protected:
		virtual ~IVideoCaptureSource(){}
	};
}
#endif/*!__MULTIMEDIA_VIDEO_CAPTURE_SOURCE_H__*/