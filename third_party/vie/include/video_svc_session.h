#ifndef __MULTI_MEDIA_VIDEO_SVC_SESSION_H__
#define __MULTI_MEDIA_VIDEO_SVC_SESSION_H__

#include "video_svc_session_type.h"
#include "video_frame_delivery.h"

namespace multimedia
{
	class _MULTIMEDIA_API_EXPORT_ ISvcSessionApi :
		public VideoFrameDelivery/*Recv data to encode*/
	{
	public:
		static int CreateInstance(ISvcSessionApi*& inst, VideoCCIDType cid,
			VideoSessionType video_sess_type);
		static int DestroyInstance(ISvcSessionApi*& inst);

		virtual int InitConfig(const SvcConfig& config) = 0;

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
}
#endif/*!__MULTI_MEDIA_VIDEO_SVC_SESSION_H__*/