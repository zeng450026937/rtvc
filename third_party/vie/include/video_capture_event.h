#ifndef _MULTIMEDIA_VIDEO_CAPTURE_EVENT_H_
#define _MULTIMEDIA_VIDEO_CAPTURE_EVENT_H_

#include "video_capture_source_type.h"

namespace multimedia
{
	typedef enum enuVideoCaptureEventType
	{
		CAMERA_DEVICE_LOST = 50000,
		CAMERA_DEVICE_RESUME
	}VideoCaptureEventType;

	class IVideoCaptureEventSink
	{
	public:
		virtual void OnDeviceEvent(const VideoCaptureEventType &event_type, const VideoCaptureSourceType &capture_type) = 0;
	protected:
		virtual ~IVideoCaptureEventSink(){}
	};
}
#endif // !_MULTIMEDIA_VIDEO_CAPTURE_EVENT_H_
