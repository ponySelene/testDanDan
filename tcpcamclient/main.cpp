
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencvcom/streamingreceiver.h"

using namespace std;
using namespace cv;
using namespace cvproc;
int main(int argc, char **argv)
{
	if (argc < 3)
	{
		cout << "commandline <ip> <port> <gray=1 or 0>" << endl;
		return 0;
	}

	const string ip = argv[1];
	const int port = atoi(argv[2]);
	int gray = 0;
	if (argc >= 4)
		gray = atoi(argv[3]);
	
	cout << "streaming client init... " << endl;
	cvproc::cStreamingReceiver receiver;
	if (!receiver.Init(ip, port, gray))
	{
		cout << "connect error!!" << endl;
		return 0;
	}

	cout << "success" << endl;
	cout << "start loop" << endl;

	const string windowName = "Camera Streaming Client";
	namedWindow(windowName);

	int count = 0;
	while (1)
	{
		cv::Mat frame = receiver.Update();

		if(!frame.empty())
		{	
			imshow(windowName, frame);
			waitKey(1);
			count++;
		}
	}

	return 0;
}
