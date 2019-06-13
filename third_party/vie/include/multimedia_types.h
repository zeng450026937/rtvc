#ifndef __MULTIMEDIA_TYPES_H__
#define __MULTIMEDIA_TYPES_H__

#ifdef _WIN32
#ifdef _MULTIMEDIA_MEDIA_SDK_DLL_COMPILE_
#define _MULTIMEDIA_API_EXPORT_ __declspec (dllexport)
#else
#define _MULTIMEDIA_API_EXPORT_ __declspec (dllimport)
#endif
#else
#define _MULTIMEDIA_API_EXPORT_
#endif

namespace multimedia
{
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
}

#endif  // __MULTIMEDIA_TYPES_H__

