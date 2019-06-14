#ifndef __VIDEO_ENGINE_EVENT_H__
#define __VIDEO_ENGINE_EVENT_H__

namespace multimedia
{
	//******************************************************************************
	// Discription:
	//   event call back function pointer, issued internal video engine 
	// Parameters:  
	//   event_id:         which is defined as VieEventIdType
	//   stream_type:      video stream type defined as VideoEventReportStreamType
	//   stream_id:        stream ID that result in the event, for the event that  
	//                     unrelated with the stream, please ignore this parameter 
	//   event_data_size:  the length of data buffer related to the event
	//   event_data_ptr:   the data buffer pointer related to the event
	// Remarks:
	//   this call back function would be issued in the engine working thread
	//******************************************************************************
	typedef void(*VideoEventCallBack)(int event_id,
		int stream_type,
		int stream_id,
		int event_data_size,
		const void* event_data_ptr);

	// type of the stream that generates the report
	typedef enum enuVideoEventReportStreamType
	{
		VEST_RESERVED = 1,
		VEST_VIDEO = 2,
		VEST_DATA = 3,
		VEST_RP = 4
	} VideoEventReportStreamType;

	// event ID
	typedef enum tagEventId
	{
		EI_NONE,

		// as multimedia data has not been received for 
		// 20 or above seconds, or recovered from the 
		// dead status, notify application this event
		// event data type: 
		// unsigned long(0: camera video; 1: data sharing video)
		EI_VIDEO_DEAD,
		EI_VIDEO_ALIVE,

		// if the received video date size changed, notify this event
		// to application.
		// event data type: structure VideoSizeChangeInfo
		EI_VIDEO_RECEIVE_SIZE_CHANGED,

		// notify application for the send video size changed
		// event data type: structure VideoSizeChangeInfo
		EI_VIDEO_SEND_SIZE_CHANGED,

		// not used, just for compatibility.
		VI_FECC_CMD,
		// not used, just for compatibility.
		VI_VIDEO_PAUSED,
		// not used, just for compatibility.
		VI_VIDEO_RECOVERED,

		// key frame request to sender by external signal 
		// event data type: unsigned long, referred by define of 
		// VCS_VIDEO_STREAM_PATTERN 0, camera video; 1 data sharing video
		EI_VIDEO_KEYFRAME_REQUEST_TO_SENDER,

		// for receiving side flow control feature
		// event data type, VideoFlowControlInfo
		EI_VIDEO_FLOW_CONTROL_BY_RECEIVER,

		// slave core working status is abnormal in the embedded system,
		// event data type: unsigned long, the error code feedback by embedded 
		// system
		EI_SLAVE_CORE_ABNORMAL,

	    ////////////////////////////////////////////////////////////////
	    // event Id from 50000 are Device Events for Software VCS
	    // for camera, notify when device state is changed
	    EI_CAMERA_DEVICE_LOST = 50000,
	    EI_CAMERA_DEVICE_RESUME,

		// SVC session join result
		EI_SVC_JOINSESSION_SUCCESSED = 60000,
		EI_SVC_JOINSESSION_FAILED,

		// subscribe result
		// event data type: unsigned int(ccid number)
		EI_SVC_SUBSCRIBE_SUCCESSED,
		EI_SVC_SUBSCRIBE_FAILED,

		// if the received video date  size changed, notify this event
		// to application.
		// event data type: structure SVCVideoSizeChangeInfo
		EI_SVC_VIDEO_RECEIVE_SIZE_CHANGED

	} VieEventIdType;


	// 视频分辨率变化信息
	typedef struct tagVideoSizeChangeInfo
	{
		unsigned short old_width;
		unsigned short old_height;
		unsigned short new_width;
		unsigned short new_height;
	} VideoSizeChangeInfo;

	// 视频接收端带宽反馈
	typedef struct tagVideoFlowControlInfo
	{
		unsigned long stream_type; // 0, camera video; 1 data sharing video
		unsigned long recommend_max_send_rate;
	} VideoFlowControlInfo;
}

#endif //__VIDEO_ENGINE_EVENT_H__