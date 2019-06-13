#ifndef __MULTI_MEDIA_VIDEO_SVC_SESSION_TYPE_H__
#define __MULTI_MEDIA_VIDEO_SVC_SESSION_TYPE_H__

#include "multimedia_types.h"
#include "video_session_common.h"
#include "video_render_type.h"
#include "video_avc_session_type.h"

namespace multimedia
{
	struct _MULTIMEDIA_API_EXPORT_ UserConfig
	{
		UserConfig();

		unsigned int user_ccid;
	};

	struct _MULTIMEDIA_API_EXPORT_ SessionConfig
	{
		SessionConfig();

		UserConfig user_info;
		const char* confid;
		VideoSessionOrient orient;
	};

	struct _MULTIMEDIA_API_EXPORT_ SvcConfig
	{
		SvcConfig();
		SessionConfig session_info;
		MediaTransportAddrInfo addr;
	};

	struct _MULTIMEDIA_API_EXPORT_ SubscribeConfig
	{
		SubscribeConfig();

		VideoCCIDType ccid;
		int width;
		int height;
		RenderConfig render_info;
	};

	struct _MULTIMEDIA_API_EXPORT_ SvcStatistics
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
}
#endif/*!__MULTI_MEDIA_VIDEO_SVC_SESSION_TYPE_H__*/