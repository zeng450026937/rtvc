#ifndef __MULTIMEDIA_VIDEO_FRAME_H__
#define __MULTIMEDIA_VIDEO_FRAME_H__

#include "multimedia_types.h"

namespace multimedia
{
	typedef unsigned char Byte;
	class _MULTIMEDIA_API_EXPORT_ VideoDeliveryFrame
	{
	public:
		typedef int PlaneType;
		struct PlaneValueType
		{
			static const PlaneType kYPlane = 0;
			static const PlaneType kUPlane = 1;
			static const PlaneType kVPlane = 2;
		};
		virtual VideoRawDataType RawDataType() const = 0;
		virtual int Width() const = 0;
		virtual int Height() const = 0;

		virtual int PlaneNumber() const = 0;
		virtual const Byte* PlaneBuffer(PlaneType type) const = 0;
		virtual int PlaneSize(PlaneType type) const = 0;
		virtual int PlaneStride(PlaneType type) const = 0;
		virtual void * GetHandle() const { return nullptr; }
	protected:
		virtual ~VideoDeliveryFrame(){}
	};

	class _MULTIMEDIA_API_EXPORT_ VideoFrameProcess
	{
	public:
		struct _MULTIMEDIA_API_EXPORT_  I420VideoFrameInfo
		{
			I420VideoFrameInfo();
			I420VideoFrameInfo(int src_w, int src_h,
				Byte* plane_y, int stride_y,
				Byte* plane_u, int stride_u,
				Byte* plane_v, int stride_v);
			I420VideoFrameInfo(const VideoDeliveryFrame &delivery_frame);

			int width;
			int height;

			Byte* plane_y;
			int stride_y;
			Byte* plane_u;
			int stride_u;
			Byte* plane_v;
			int stride_v;
		};

		static int ScaleI420Frame(const I420VideoFrameInfo &src_frame,
			I420VideoFrameInfo &dst_frame);
		static int ConvertI420ToARGB(const I420VideoFrameInfo &src_frame,
			Byte* rgb_buf, int buf_len, int &data_len);
	};
}
#endif/*!__MULTIMEDIA_VIDEO_FRAME_H__*/