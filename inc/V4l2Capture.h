/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** V4l2Capture.h
** 
** V4L2 wrapper 
**
** -------------------------------------------------------------------------*/


#ifndef V4L2_CAPTURE
#define V4L2_CAPTURE

#include <string>
#include <list> 
#include <iostream>

// ---------------------------------
// V4L2 Capture parameters
// ---------------------------------
struct V4L2DeviceParameters 
{
	V4L2DeviceParameters(const char* devname, unsigned int format, unsigned int width, unsigned int height, int fps, int verbose) : 
		m_devName(devname), m_format(format), m_width(width), m_height(height), m_fps(fps), m_verbose(verbose) {};
		
	std::string m_devName;
	unsigned int m_format;
	unsigned int m_width;
	unsigned int m_height;
	int m_fps;			
	int m_verbose;
};

// ---------------------------------
// V4L2 Capture
// ---------------------------------
class V4l2Capture
{		
	protected:
		V4l2Capture(const V4L2DeviceParameters&  params);
	
	public:
		virtual ~V4l2Capture();
	
	public:
		int getFd() { return m_fd; };		
		int getBufferSize() { return m_bufferSize; };
		int getFormat() { return m_format; } ;
		int getWidth() { return m_width; };
		int getHeight() { return m_height; };
		void queryFormat();

	protected:
		bool init(unsigned int mandatoryCapabilities);
		void close();
	
		int initdevice(const char *dev_name, unsigned int mandatoryCapabilities);
		int checkCapabilities(int fd, unsigned int mandatoryCapabilities);
		int configureFormat(int fd);
		int configureParam(int fd);		
		int xioctl(int fd, int request, void *arg);
				
	public:
		virtual bool captureStart() = 0;
		virtual size_t read(char* buffer, size_t bufferSize) = 0;
		virtual bool captureStop() = 0;
		virtual bool isReady() = 0;
		
	protected:
		V4L2DeviceParameters m_params;
		int m_fd;
		int m_bufferSize;
		int m_format;
		int m_width;
		int m_height;
};

// ---------------------------------
// V4L2 Output
// ---------------------------------
class V4l2Output
{		
	public:
		V4l2Output(const V4L2DeviceParameters&  params);
		virtual ~V4l2Output();
	
	public:
		int getFd() { return m_fd; };		
		
	protected:
		int m_fd;
};

#endif
