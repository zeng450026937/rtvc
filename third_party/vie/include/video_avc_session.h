#ifndef __MULTIMEDIA_AVC_SESSION_H__
#define __MULTIMEDIA_AVC_SESSION_H__

#include "video_avc_session_type.h"

#include "video_frame_delivery.h"
#include "video_external_transport.h"

namespace multimedia
{
	class _MULTIMEDIA_API_EXPORT_ IAVCSessionApi :
		public VideoFrameDelivery/*Recv data to encode*/
		, public VideoFrameProvider/*Provide decoding video data*/
	{
	public:
		static int CreateInstance(IAVCSessionApi*& inst, VideoSessionType video_sess_type);
		static int DestroyInstance(IAVCSessionApi*& inst);
		static int GetPrivateCapabilitySetting(MediaVideoPrivateCapacity& self_priv_capset);

		virtual int InitConfig(const AvcConfig& config) = 0;

		virtual int StartSession(const VideoSessionOrient& sess_orient) = 0;
		virtual int StopSession() = 0;

		virtual int GetMediaSendStatis(VideoStatistics& stat) const = 0;
		virtual int GetMediaReceiveStatis(VideoStatistics& stat) const = 0;

		virtual int FlowControl(int bps) = 0;
		virtual int RequestKeyFrame() = 0;

		virtual int UpdateEncodeTargetParas(int bit_rate, int frame_rate,
			int video_width, int video_height) = 0;		
	protected:
		virtual ~IAVCSessionApi(){}
	};
}
#endif/*!__MULTIMEDIA_AVC_SESSION_H__*/