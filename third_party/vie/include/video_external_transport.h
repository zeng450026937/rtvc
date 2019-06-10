#ifndef __VIDEO_EXTERNAL_TRANSPORT_H__
#define __VIDEO_EXTERNAL_TRANSPORT_H__

namespace multimedia
{
	typedef int VideoTransportHandle;
	static const VideoTransportHandle kVideoTransportHandleInvalidValue = -1;

	struct VideoTransportHandleSet
	{
		static const int kVideoTransportHandleSize = 64;
		int handle_num = 0;
		VideoTransportHandle handle_array[kVideoTransportHandleSize];
	};

	struct VideoTransportTimeValue
	{
		long secs = 0;
		long micro_secs = 0;
	};

	struct VideoTransportBufferVector
	{
		static const int kVideoTransportBufferVectorSize = 64;
		int buffer_number = 0;
		char* buffers[kVideoTransportBufferVectorSize];
		int buf_lens[kVideoTransportBufferVectorSize];
	};

	class VideoExternalTransportSink
	{
	public:
		virtual int GetHandle(VideoTransportHandle handle) = 0;
		virtual int ReleaseHandle(VideoTransportHandle handle) = 0;

		virtual int Select(const VideoTransportHandleSet &check_set, VideoTransportHandleSet &recv_set, const VideoTransportTimeValue &timeout) = 0;
		virtual int Recv(VideoTransportHandle handle, char* &buffer, int &buf_len) = 0;
		virtual int ReleaseRecvBuffer(VideoTransportHandle handle, char* buffer) = 0;

		virtual int Send(VideoTransportHandle handle, const char* buffer, int buf_len) = 0;
		virtual int SendVector(VideoTransportHandle handle, const VideoTransportBufferVector &buffers) = 0;
	protected:
		virtual ~VideoExternalTransportSink(){}
	};
}
#endif/*!__VIDEO_EXTERNAL_TRANSPORT_H__*/