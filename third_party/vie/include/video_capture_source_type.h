#ifndef __MULTIMEDIA_VIDEO_CAPTURE_SOURCE_TYPE__
#define __MULTIMEDIA_VIDEO_CAPTURE_SOURCE_TYPE__

#include "multimedia_types.h"

namespace multimedia
{
	struct _MULTIMEDIA_API_EXPORT_ VideoCaptureString
	{
		VideoCaptureString();
		VideoCaptureString(const VideoCaptureString &src);
		VideoCaptureString(const char* str, int str_len);

		bool CheckValid() const;

		static const int kVideoCaptureStringSize = 2048;
		char str[kVideoCaptureStringSize];
		int str_len;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCameraDeviceDescriptor
	{
		VideoCameraDeviceDescriptor();
		VideoCameraDeviceDescriptor(const VideoCaptureString &unique_id,
			const VideoCaptureString &device_name);
		VideoCameraDeviceDescriptor(const char* id_str, int id_len, const char* name_str, int name_len);

		VideoCaptureString unique_id;
		VideoCaptureString device_name;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCaptureFormat
	{
		VideoCaptureFormat();
		VideoCaptureFormat(int width, int height, int frame_rate, VideoRawDataType raw_type);

		void Set(int width, int height, int frame_rate, VideoRawDataType raw_type);
		void Get(int &width, int &height, int &frame_rate, VideoRawDataType &raw_type);

		int width;
		int height;
		int frame_rate;
		VideoRawDataType raw_type;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCameraCaptureFormat
	{
		VideoCameraCaptureFormat();

		int orientation;
		int capture_delay;
		bool interlaced_flag;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCameraDeviceCapability
	{
		VideoCameraDeviceCapability();
		VideoCameraDeviceCapability(const VideoCaptureFormat &format,
			const VideoCameraCaptureFormat &param);

		VideoCaptureFormat format;
		VideoCameraCaptureFormat camera_format;
	};

	enum VideoCaptureSourceType
	{
		VIDEO_CAPTURE_SOURCE_UNDEF = -1,
		VIDEO_CAPTURE_SOURCE_CAMERA,
		VIDEO_CAPTURE_SOURCE_SCREEN,
		VIDEO_CAPTURE_SOURCE_PICTURE
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCameraDeviceParam
	{
		VideoCameraDeviceParam();

		VideoCaptureString unique_id;
		VideoCameraCaptureFormat camera_format;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoScreenCaptureParam
	{
		VideoScreenCaptureParam();
		VideoScreenCaptureParam(void* target_handle,
			const VideoCaptureString &cover_picture_path);

		void* target_handle;
		VideoCaptureString cover_picture_path;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoPictureCaptureParam
	{
		VideoPictureCaptureParam();
		VideoPictureCaptureParam(const VideoCaptureString &file_path);

		VideoCaptureString picture_path;
	};

	struct _MULTIMEDIA_API_EXPORT_ VideoCaptureSourceInfo
	{
		VideoCaptureSourceInfo();

		VideoCaptureSourceType capture_type;
		VideoCaptureFormat format;

		VideoCameraDeviceParam camera_param;
		VideoScreenCaptureParam screen_param;
		VideoPictureCaptureParam file_param;
	};
}
#endif/*!__MULTIMEDIA_VIDEO_CAPTURE_SOURCE_TYPE__*/