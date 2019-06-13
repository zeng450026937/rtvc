#ifndef __MULTIMEDIA_LOG_H__
#define __MULTIMEDIA_LOG_H__

#include "multimedia_types.h"

namespace multimedia
{
	enum VideoLogLevelType
	{
		VIDEO_LOG_LEVEL_NONE = 0,
		VIDEO_LOG_LEVEL_ERR,
		VIDEO_LOG_LEVEL_WARN,
		VIDEO_LOG_LEVEL_INFO,
		VIDEO_LOG_LEVEL_DEBUG
	};

	typedef void(*VideoLogCallback) (VideoLogLevelType level, const char *data, int len);
	class _MULTIMEDIA_API_EXPORT_ MultimediaLogApi
	{
	public:
		static int SetLogCallback(VideoLogCallback log_callback);
	};	
}
#endif/*!__MULTIMEDIA_LOG_H__*/