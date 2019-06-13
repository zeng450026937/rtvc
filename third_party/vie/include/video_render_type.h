#ifndef __MULTIMEDIA_VIDEO_RENDER_TYPE_H__
#define __MULTIMEDIA_VIDEO_RENDER_TYPE_H__

namespace multimedia
{
	struct _MULTIMEDIA_API_EXPORT_ RenderCoordinate
	{
		RenderCoordinate();
		explicit RenderCoordinate(float left, float top, float right, float bottom, int z_order);

		float left;
		float top;
		float right;
		float bottom;
		int z_order;
	};

	struct _MULTIMEDIA_API_EXPORT_ RenderConfig
	{
		RenderConfig();
		RenderConfig(void* win_handle, const RenderCoordinate &coor);
		void* win_handle;
		RenderCoordinate coor;
	};

	struct _MULTIMEDIA_API_EXPORT_ OnScreenDisplayBitmap
	{
		OnScreenDisplayBitmap();

		long        bmType; // unused for now
		long        bmWidth;
		long        bmHeight;
		long        bmStrideBytes; // bytes per row
		void*       bmBits; // data point
		unsigned short bmBitsPixel; // bits per pixel
	};
}
#endif/*!__MULTIMEDIA_VIDEO_RENDER_TYPE_H__*/