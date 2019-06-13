#ifndef __MULTIMEDIA_VIDEO_DELIVERY_FRAME_H__
#define __MULTIMEDIA_VIDEO_DELIVERY_FRAME_H__

#include "multimedia_types.h"
#include "video_frame.h"

namespace multimedia
{
	class _MULTIMEDIA_API_EXPORT_ VideoFrameDeliverySink
	{
	public:
		virtual void OnFrameIncoming(const VideoDeliveryFrame &frame) = 0;
	protected:
		virtual ~VideoFrameDeliverySink(){}
	};

	class _MULTIMEDIA_API_EXPORT_ VideoFrameProvider
	{
	public:
		virtual int ConnectToDeliverySink(VideoFrameDeliverySink* sink) = 0;
		virtual int DisconnectToDeliverySink(VideoFrameDeliverySink* sink) = 0;
	protected:
		virtual ~VideoFrameProvider(){}
	};

	class _MULTIMEDIA_API_EXPORT_ VideoFrameDelivery
	{
	public:
		virtual int ConnectToFrameProvider(VideoFrameProvider* provider) = 0;
		virtual int DisconncetToFrameProvider(VideoFrameProvider* provider) = 0;
	protected:
		virtual ~VideoFrameDelivery(){}
	};
}
#endif/*!__MULTIMEDIA_VIDEO_DELIVERY_FRAME_H__*/