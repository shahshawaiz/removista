//video writing specific
#include "opencv\highgui.h"
#include "opencv\cv.h"

//image segmentation (bg subtraction) specific
#include "opencv2\opencv.hpp"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\video\background_segm.hpp"

//c++ specific
#include "iostream"
#include "stdio.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{

	//-------------------------------------------------------------------image enhacment tests
	//Mat orignal, contrast, histogram, grey;

	//orignal = imread("C:\\Users\\user212\\Documents\\Visual Studio 2015\\Projects\\projectTestOpenCV\\projectTestOpenCV\\test\\test_image_enhacement_opreationsimg.jpg", CV_LOAD_IMAGE_COLOR);

	//if (orignal.empty())
	//{
	//	std::cout << "!!! Failed imread(): image not found" << std::endl;
	//	// don't let the execution continue, else imshow() will crash.
	//}

	//

	////contrast adjustment
	//	orignal.convertTo(contrast,-1,2.2,50);

	//	if (contrast.empty())
	//	{
	//		std::cout << "!!! Failed to convertto(): image not found" << std::endl;
	//		// don't let the execution continue, else imshow() will crash.
	//	}


	////histogram adjustment

	//	/// Convert to grayscale
	//	cvtColor(orignal, grey, CV_BGR2GRAY);

	//	/// Apply Histogram Equalization
	//	equalizeHist(grey, histogram);



	//namedWindow("Original Image", 0);
	//namedWindow("Contrast adjustments", 0);
	//namedWindow("Histogram adjustments", 0);

	//while (1) {
	//	
	//	imshow("Original Image", orignal);
	//	imshow("Contrast adjustments", contrast);
	//	imshow("Histogram adjustments", histogram);

	//	switch (waitKey(10))
	//	{
	//		case 32:
	//			//capture image at space bar
	//			//imwrite("test\\/orignal1.jpg", orignal);
	//			//imwrite("test\\/contrast1.jpg", contrast);
	//			imwrite("test\\/histogram1.jpg", histogram);

	//			break;

	//		case 27:
	//				//exit at escape
	//				return 0;
	//	}
	//}


	//------------------------------------------------------------------- image segmentation + init camera

//
//	//global variables  
//	Mat frame /*camera feed*/, res /*processed image*/, mask /*mask*/;
//
//	Ptr<BackgroundSubtractor> pMOG; //MOG Background subtractor  
//	Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor  
//	Ptr<BackgroundSubtractorGMG> pGMG; //MOG2 Background subtractor  
//
//	//pMOG = new BackgroundSubtractorMOG(100,5,0,1);
//	pMOG2 = new BackgroundSubtractorMOG2(1000,0,1);
//	//pGMG = new BackgroundSubtractorGMG();
//	
//	//for reading saved file
//	//char fileName[100] = "C:\\opencv\\/myVideo.avi"; //Gate1_175_p1.avi"; //mm2.avi"; //";//_p1.avi";
//	//VideoCapture stream1(fileName);
//
//	//camera initializer
//	VideoCapture cap;
//	cap.open(0);
//
//	//unconditional loop     
//	while (true) {
//
//		cap >> frame;
//		//contrast adjustment+brightness
//		//frame.convertTo(frame, -1, 0.5,0);
//
//
//
//		res = frame;
//
//		/////////////////////////////////////////using MOG -> constructor(set_input_frame, get_output_mask_here, learning_rate)
//		//pMOG->operator()(frame, mask, 0.8);
//		////enhancment of mask
//		//Mat histogram, grey;
//		///// Convert to grayscale
//		////cvtColor(frame, grey, CV_BGR2GRAY);
//
//		///// Apply Histogram Equalization
//		//equalizeHist(mask, histogram);
//
//		////test for channels in image matrix
//		////std::cout << mask.channels() << endl;
//		////std::cout << histogram.channels() << endl;
//
//		/////////////////////////////////////////using MOG2 -> constructor(set_input_frame, get_output_mask_here, learning_rate)
//		pMOG2->operator()(frame,mask,0.6);
//		
//			//enhancment of mask
//			Mat mask_histogram,grey,mask_salt,res_histogram, res_salt;
//			//Convert to grayscale
//			//cvtColor(frame, grey, CV_BGR2GRAY);
//
//			//Apply Histogram Equalization
//			equalizeHist(mask, mask_histogram);
//			
//			//salt pepper removal using median blurring
//			medianBlur(mask, mask_salt, 5);
//
//			//test for channels in image matrix
//			//std::cout << mask.channels() << endl;
//			//std::cout << histogram.channels() << endl;
//
//		/////////////////////////////////////////using GMG/////////////////////////////////////////
//		//pGMG->operator()(frame, mask);
//
//		//imshow("frame", frame);
//		//imshow("mask", mask);
//		//imshow("histogram enhanced mask", mask_histogram);
//
//		imshow("salt", mask_salt);
//
//		//????????????????? here frame from previous 10th last frame needs to be copied using max to current frame??????????????????
//		frame.copyTo(res, mask);
//		
//		frame.copyTo(res_histogram, mask_histogram);
//		frame.copyTo(res_salt, mask_salt);
//
//		/*imshow("No image enhancment", res);
//		imshow("Histogram Equalized", res_histogram);
//		imshow("Salt fixed", res_salt);
//*/
//		//listen for 10ms for a key to be pressed
//		switch (waitKey(10))
//		{
//			case 32:
//
//				//capture image at space bar
//				imwrite("captured_image\\/unprocessed.jpg", frame);
//				imwrite("captured_image\\/mask with histogram enhanced.jpg", mask_histogram);
//				imwrite("captured_image\\/mask with salt removed.jpg", mask_salt);
//				imwrite("captured_image\\/processed.jpg", res);
//
//				imshow("captured", res);
//				imshow("captured", mask_salt);
//
//				break;
//
//			case 27:
//				//exit at esc
//				return 0;
//		}
//
//	}
//


/////////////////////////////////////////////////////////////////background model calculation


//global variables  
	Mat frame /* camera feed */, 
		processed_image /* processed image */,
		initial_mask /* initial mask returned by MOG backgroud subtractor */,
		histogram_mask /* mask after histogram equalziation */,
		noise_free_mask /* mask after noise removal of salt and peper */,
		history[100],
		res
	;

	int counter_history = 0; /*sliding window history counter*/

//MOG Background subtractor initialziation
//constructor paramters : history size, number of gaussain mixtures, background ratio, noise strength)
	/*Ptr<BackgroundSubtractor> pMOG; 
	pMOG = new BackgroundSubtractorMOG(100,5,0,1);*/

//MOG2 Background subtractor initialziation
//constructor paramters : history size, threshold value, shadow detection 
	Ptr<BackgroundSubtractor> pMOG2; 
	pMOG2 = new BackgroundSubtractorMOG2(300,0, 0);

//camera initializer
	VideoCapture cap;
	cap.open(0);

	//sliding window history logic
	while (1) {
		
		//transfer feed to pre-intialized matrix
		cap >> frame;
		
		//image enhancement of gain (contrast) and bias (brightness) adustments
		//constructor : resulting (enhanced) image, ??, alpha/gain, beta/bias
		//frame.convertTo(frame, -1, 0.5, 0);

		//make a copy of frame for later comparision
		frame.copyTo(res);
		
		//exit if buffer exceeds 100
		if (counter_history == 100) {
			std::cout << "Applciation timed out. buffer exceeded 100 frames." << counter_history << endl;
			return 0;
		}
		
		//make a copy of frame for sliding window history
		waitKey(1); //buffer for not crashing system
		frame.copyTo(history[counter_history]);
		
		//wait untill 10th frame is obtained. to initialize history array
		if (counter_history > 10) {
			
			//output frame number for debugging purposes
			std::cout << "Frame feed No. " << counter_history << endl;
		
			////MOG implenetation
			////constructor : input image, resulting mask, learning_rate
			//	pMOG->operator()(frame, initial_mask, 0.8);
			//
			//	//enhancment of mask using histogram equlzation - constructor : input image (1 channel), output image (1 channel) 
			//	//Apply Histogram Equalization
			//	equalizeHist(initial_mask, histogram_mask);

			//	//noise reduction of salt and pepper using median blurring
			//	//constructor - input image (1 channel), output image (1 channel), k size (?)
			//		medianBlur(initial_mask, noise_free_mask, 5); //using input without histogram initialization
			//		//medianBlur(histogram_mask, noise_free_mask, 5); //using input with histogram initialization

			//	//test for checking channels in image matrix
			//	////std::cout << initial_mask.channels() << endl;
			//	////std::cout << histogram_mask.channels() << endl;

			//MOG2 implementation (image segmentation)
			//constructor : input image, resulting mask, learning_rate
			pMOG2->operator()(frame, initial_mask, 0.2);

			//enhancment of mask using histogram equlzation  
			//constructor : input image (1 channel), output image (1 channel)
			equalizeHist(initial_mask, histogram_mask);

			//noise reduction of salt and pepper using median blurring
			//constructor - input image (1 channel), output image (1 channel), k size (?)
			medianBlur(initial_mask, noise_free_mask, 5); //using input without histogram initialization
														  //medianBlur(histogram_mask, noise_free_mask, 5); //using input with histogram initialization

														  //test for channels in image matrix
														  //std::cout << mask.channels() << endl;
														  //std::cout << histogram.channels() << endl;
		
			//Morphological opreations
				//dilation
				//constructor : input image (1 channel), dilated image (1 image)
				dilate(noise_free_mask, noise_free_mask, MORPH_CROSS);
			
				//erosion
				//constructor : input image (1 channel), dilated image (1 image)
				erode(noise_free_mask, noise_free_mask, MORPH_CROSS);

			//Alpha Channel usage for traspareny addition of mask. smoothening
				//alpha is the transperny value. value of stimulated alpha channel
				//reconsider this?????
				/*double alpha=0.05, beta;
				beta = (0.5 - alpha);
				addWeighted(frame, alpha, history[counter_history - 10], beta, 0.0, history[counter_history - 10]);*/

			//Overwrite last frame from sliding window using generated mask of segmentation
			history[counter_history - 10].copyTo(frame ,noise_free_mask);
			
			//output results
			imshow("Orignal Image", res);
			imshow("Final processed image", frame);
			imshow("Final mask", noise_free_mask);
		}

		//event handling on preview
		switch (waitKey(10))
		{
			//capture image at space bar
			case 32:

				//freeze output window from feed
				imshow("Orignal Image", res);
				imshow("Final processed image", frame);
				imshow("Final mask", noise_free_mask);
				std::cout << "Image written from feed. frame no. " << counter_history << endl;

				imwrite("test\\captured_image\\/orignal iamge.jpg", res);
				imwrite("test\\captured_image\\/final processed image.jpg", frame);
				imwrite("test\\captured_image\\/final mask.jpg", noise_free_mask);

				break;

			//exit at esc
			case 27:
				return 0;
		}

		//increment frame count
		counter_history++;
	}


//unconditional loop for uninterupted webcam feed
	while (false) {

		cap >> frame;

		//image enhancement of gain (contrast) and bias (brightness) adustments
		//constructor : resulting (enhanced) image, ??, alpha/gain, beta/bias
		frame.convertTo(frame, -1, 0.5,0);

		////MOG implenetation
		////constructor : input image, resulting mask, learning_rate
		//	pMOG->operator()(frame, initial_mask, 0.8);
		//
		//	//enhancment of mask using histogram equlzation - constructor : input image (1 channel), output image (1 channel) 
		//	//Apply Histogram Equalization
		//	equalizeHist(initial_mask, histogram_mask);

		//	//noise reduction of salt and pepper using median blurring
		//	//constructor - input image (1 channel), output image (1 channel), k size (?)
		//		medianBlur(initial_mask, noise_free_mask, 5); //using input without histogram initialization
		//		//medianBlur(histogram_mask, noise_free_mask, 5); //using input with histogram initialization

		//	//test for checking channels in image matrix
		//	////std::cout << initial_mask.channels() << endl;
		//	////std::cout << histogram_mask.channels() << endl;

		//MOG2 implementation
		//constructor : input image, resulting mask, learning_rate
			pMOG2->operator()(frame, initial_mask,0.6);
		
			//enhancment of mask using histogram equlzation 
			//constructor : input image (1 channel), output image (1 channel)
				equalizeHist(initial_mask, histogram_mask);

			//noise reduction of salt and pepper using median blurring
			//constructor - input image (1 channel), output image (1 channel), k size (?)
				medianBlur(initial_mask, noise_free_mask, 5); //using input without histogram initialization
				//medianBlur(histogram_mask, noise_free_mask, 5); //using input with histogram initialization

			//test for channels in image matrix
			//std::cout << mask.channels() << endl;
			//std::cout << histogram.channels() << endl;

		//preview tempororary results
		//imshow("salt", noise_free_mask);

		//????????????????? here frame from previous 10th last frame needs to be copied using max to current frame??????????????????
		//frame.copyTo(processed_image, noise_free_mask);
		
		
		//imshow("captured", noise_free_mask);

		//event handling on preview
		switch (waitKey(10))
		{
			//capture image at space bar
			case 32:
				//imwrite("test\\captured_image\\/processed_image.jpg", noise_free_mask); //save image as jepg
				imshow("captured", processed_image); // show image in seprate windo

				break;

			//exit at esc
			case 27:
				return 0;
		}

	}
}