#ifndef __MULTIMEDIA_VIDEO_SESSION_COMMON_TYPE_H__
#define __MULTIMEDIA_VIDEO_SESSION_COMMON_TYPE_H__

#include "multimedia_types.h"
#include "multimedia_log.h"

#include "video_engine_event.h"

namespace multimedia
{
	enum VideoSessionType
	{
		VIDEO_SESSION_UNDEF = -1,
		VIDEO_SESSION_CAMERA,
		VIDEO_SESSION_DATA_SHARE
	};

	enum VideoSessionOrient
	{
		VIDEO_SESSION_ORIENT_UNDEF = 0,
		VIDEO_SESSION_ORIENT_SEND = 1,
		VIDEO_SESSION_ORIENT_RECV = 2,
		VIDEO_SESSION_ORIENT_BOTH = 3
	};

	typedef unsigned int VideoCCIDType;
	typedef unsigned int VideoStreamIDType;
	static const VideoStreamIDType kVideoStreamIDInvalidValue = (unsigned int)(~0);

	/*To Do : (2019-6-10 duanxc)
		Remove these functions.Use Event Sink Interface for avc session and svc session separately. */
	class _MULTIMEDIA_API_EXPORT_ VideoSessionGlobalApi
	{
	public:
		static int StartUp(VideoEventCallBack event_cb);
		static void ShutDown();
	};
}
#endif/*!__MULTIMEDIA_VIDEO_SESSION_COMMON_TYPE_H__*/