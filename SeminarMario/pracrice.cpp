#include "Animation.h"
#include <opencv2/opencv.hpp>

// before you start: open SeminarMario project properties, go to 
// Debugging -> Environment
// set the following value:
// PATH=$(PATH);../OpenCV_451/bin
// hit Ctrl + F5 and see a walking lady. that's our hero!
// press Esc to exit.
// read carefully the comments below - it contains explanations and instructions.
// and do the exercises.
cv::Point walkRight(cv::Point topLeft)
{
	topLeft.x += 10;
	return topLeft;
}


//int main()
//{
//
//	// Animation is a class we wrote for saving you the handling with the 
//	// details of image processing and focusing on code design. iyH we'll get 
//	// to it in the image processing course.
//	Animation animation(R"(../Animations/Hero/runRight)");
//
//	// OpenCV is a popular image processing and computer vision library.
//	// it is not part of the C++ language, but it's written in C++.
//	// in this project we integrated it for you.
//	// The class that represents an image in OpenCV is Mat (i.e. Matrix),
//	// and it's defined inside namespace cv. So the full name is cv::Mat.
//	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
//
//	// Draw
//	bool isToExit = false;
//	while (false == isToExit)
//	{
//		duck();
//		for (int i = 0; i < animation.numFrames(); i++)
//		{
//			Frame const& frame = animation.getFrame(i);
//			// create a copy of the original backgrount - not to "dirty" it.
//			cv::Mat canvas = background.clone();
//			// the point of the canvas where we would like to place the top left corner 
//			// of our frame. NOTE: the y axis on the screen goes from top to bottom.
//			cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 2 / 3);
//			topLeft = walkRight(topLeft);
//			drawFrame(frame, canvas, topLeft);
//			// show what we've got (use BOTH of the following two commands):
//			cv::imshow("test", canvas);
//			// wait 100 milliseconds for a key to be pressed. if not pressed, returns -1:
//			// (you MUST call it after cv::imshow. will discuss why in image processing).
//			int key = cv::waitKey(100);
//
//			if (key == 27) // if you pressed ESC key
//			{
//				isToExit = true;
//			}
//		}
//	}
//
//
//	return 0;
//}
// 1.
// draws an animation of our hero that ducks in place, and stays down till you 
// press the 'w' key. (if (key == 'w'))
void duck()
{
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);

	Animation animation(R"(../Animations/Hero/duckDown)");
	bool isKeyW = false;
	int key = cv::waitKey(100);
	for (int i = 0; i < animation.numFrames(); i++)
	{
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
		cv::Mat canvas = background.clone();
		Frame const& frame = animation.getFrame(i);
	
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 4.4/6);
		topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);


	}

	while (false == isKeyW)
	{
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
		cv::Mat canvas = background.clone();
		Animation animation(R"(../Animations/Hero/duckStay)");
		Frame const& frame = animation.getFrame(0);
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 4.4/6);
		topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		key = cv::waitKey(100);
		if (key == 'w')
		{
			isKeyW = true;

		}

	}

	Animation animation1("../Animations/Hero/standAfterDuck");
	for (int i = 0; i < animation.numFrames(); i++)
	{
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
		cv::Mat canvas = background.clone();
		Frame const& frame = animation1.getFrame(i);
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height *4.4/6);
		topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);
	}
}

// 2.
// draws an animation of our hero that walks to the right, and ACTUALLLY MOVES RIGHT
// with a constant speed, of (1/10)*(image width) per 100 milliseconds (=0.1 second).
void walksright()
{
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	Animation animation(R"(../Animations/Hero/runRight)");
	cv::Mat canvas = background.clone();

	int key = cv::waitKey(100);
	int X = canvas.size().width / 2;
	while (key != 'a')
	{
		
		for (int i = 0; i < animation.numFrames(); i++)
		{
			cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
			cv::Mat canvas = background.clone();
			Frame const& frame = animation.getFrame(i);
			X = X + canvas.size().width * 0.01;
			cv::Point topLeft(X, canvas.size().height * 4.4/6);
			
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			key = cv::waitKey(100);

		}
	}
	Animation animation1(R"(../Animations/Hero/idle)");
	for (int i = 0; i < animation1.numFrames(); i++)
	{
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
		cv::Mat canvas = background.clone();
		Frame const& frame = animation1.getFrame(i);
		cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 4.4 / 6);
		topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);


	}
}



// 3.
// draw our hero jumps up and right, and stays standing after jump finishes.
void jumpRight()
{

	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	Animation animation(R"(../Animations/Hero/jump)");
	int key = cv::waitKey(100);
	cv::Mat canvas = background.clone();
	int Y = canvas.size().height * 4.4/6;
	int X = canvas.size().width / 2;
	for (int i = 0; i < animation.numFrames()/2; i++)
	{
		if (X >= canvas.size().width)
		{
			X = 0;
		}
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
		cv::Mat canvas = background.clone();
		Frame const& frame = animation.getFrame(i);
		Y = Y - canvas.size().height*0.01;
		X = X +canvas.size().width*0.01;
		cv::Point topLeft(X, Y);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);
	}
	for (int i = animation.numFrames() / 2; i < animation.numFrames() ; i++)
	{
		if (X >= canvas.size().width)
		{
			X = 0;
		}
		cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
		cv::Mat canvas = background.clone();
		Frame const& frame = animation.getFrame(i);
		Y = Y + canvas.size().height * 0.01;
		X = X + canvas.size().width * 0.01;
		cv::Point topLeft(X, Y);
		
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);
	}
	

}

// 4.
// write a main() that:
// when user presses 'd' - hero walks right
// when user presses 's' - hero ducks
// when user presses 'w' - hero jumps
// when user presses 'a' - hero stops (if it was walking right before)
int main1() 
{
	int key = cv::waitKey(100);
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	Animation animation(R"(../Animations/Hero/idle)");
	bool isToExit = false;

	while (false == isToExit)
	{
		for (int i = 0; i < animation.numFrames(); i++)
		{
			cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
			Frame const& frame = animation.getFrame(i);
			cv::Mat canvas = background.clone();
			cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 4.4 / 6);
			topLeft = walkRight(topLeft);
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			int key = cv::waitKey(100);
			switch (key)
			{
			case 'd': {walksright();
				int key = cv::waitKey(100);
				break;
				
			}
			case 's': {duck();
				int key = cv::waitKey(100);
				break;
			}
			case 'w': {jumpRight();
				int key = cv::waitKey(100);
				break;
			}

			}
			if (key == 27)
			{
				isToExit = true;
			}

		}
		

			
		
		

	}
	return 0;
}

// 5.
// in walkRight - when hero reaches the canvas boundery - don't let it go outside of image.
// force the hero x coordinate to be such that we'll see her.
// hint: you can get hero image cv::Mat with frame.image

// 6.
// do the same with jumpRight