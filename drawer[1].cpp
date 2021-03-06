﻿#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <fcntl.h> 
#include <io.h>  

using namespace std;
using namespace cv;

int cellsize = 1;															//eventually will be expanded to allow for larger cell sizes. the infrastructure is in place, just not made use of yet
float SENSITIVITY = 128.0;													//threshhold for how light a pixel must be to be set to a white pixel in the black/white image. default is 128.0

vector < vector<bool> > cellvec;
vector<bool> cellrowvec;
vector < vector<bool> > vec;
vector<bool> rowvec;
vector<bool> cellstringvec;
string inputstring;
ofstream wout;
ofstream out;
string nls("\x0A\x00", 2);													//required to print '\x00' as a literal, not as a null character. caused 2 days of frustration
string blank("\x00\x28", 2);


void drawCell()
{
	//algorithm to construct "cellstringvec," which becomes a number in binary with
	//0,0 at the start, 3,2 at the end, in y,x format

	cellstringvec.clear();

	for (int ch = 0; ch < cellvec.size(); ch++)
	{
		for (int cw = 0; cw < cellvec[0].size(); cw++)
		{
			cellstringvec.push_back(cellvec[ch][cw]);
		}
	}

	//converts the 8 bit binary number to an integer, logically 0 <= i <= 255

	ostringstream os;
	for (int i : cellstringvec)
	{
		os << i;
	}

	string str(os.str());

	int i = stoi(str, nullptr, 2);

	cout << i;

	//actually prints the braille characters
	switch (i)
	{
	case(0):wout << blank; break;
	case(255):wout << "\xFF\x28"; break;
	case(1):wout << "\x80\x28"; break;
	case(2):wout << "\x40\x28"; break;
	case(3):wout << "\xC0\x28"; break;
	case(4):wout << "\x20\x28"; break;
	case(5):wout << "\xA0\x28"; break;
	case(6):wout << "\x60\x28"; break;
	case(7):wout << "\xE0\x28"; break;
	case(8):wout << "\x04\x28"; break;
	case(9):wout << "\x84\x28"; break;
	case(10):wout << "\x44\x28"; break;
	case(11):wout << "\xC4\x28"; break;
	case(12):wout << "\x24\x28"; break;
	case(13):wout << "\xA4\x28"; break;
	case(14):wout << "\x64\x28"; break;
	case(15):wout << "\xE4\x28"; break;
	case(16):wout << "\x10\x28"; break;
	case(17):wout << "\x90\x28"; break;
	case(18):wout << "\x50\x28"; break;
	case(19):wout << "\xD0\x28"; break;
	case(20):wout << "\x30\x28"; break;
	case(21):wout << "\xB0\x28"; break;
	case(22):wout << "\x70\x28"; break;
	case(23):wout << "\xF0\x28"; break;
	case(24):wout << "\x14\x28"; break;
	case(25):wout << "\x94\x28"; break;
	case(26):wout << "\x54\x28"; break;
	case(27):wout << "\xD4\x28"; break;
	case(28):wout << "\x34\x28"; break;
	case(29):wout << "\xB4\x28"; break;
	case(30):wout << "\x74\x28"; break;
	case(31):wout << "\xF4\x28"; break;
	case(32):wout << "\x02\x28"; break;
	case(33):wout << "\x82\x28"; break;
	case(34):wout << "\x42\x28"; break;
	case(35):wout << "\xC2\x28"; break;
	case(36):wout << "\x22\x28"; break;
	case(37):wout << "\xA2\x28"; break;
	case(38):wout << "\x62\x28"; break;
	case(39):wout << "\xE2\x28"; break;
	case(40):wout << "\x06\x28"; break;
	case(41):wout << "\x86\x28"; break;
	case(42):wout << "\x46\x28"; break;
	case(43):wout << "\xC6\x28"; break;
	case(44):wout << "\x26\x28"; break;
	case(45):wout << "\xA6\x28"; break;
	case(46):wout << "\x66\x28"; break;
	case(47):wout << "\xE6\x28"; break;
	case(48):wout << "\x12\x28"; break;
	case(49):wout << "\x92\x28"; break;
	case(50):wout << "\x52\x28"; break;
	case(51):wout << "\xD2\x28"; break;
	case(52):wout << "\x32\x28"; break;
	case(53):wout << "\xB2\x28"; break;
	case(54):wout << "\x72\x28"; break;
	case(55):wout << "\xF2\x28"; break;
	case(56):wout << "\x16\x28"; break;
	case(57):wout << "\x96\x28"; break;
	case(58):wout << "\x56\x28"; break;
	case(59):wout << "\xD6\x28"; break;
	case(60):wout << "\x36\x28"; break;
	case(61):wout << "\xB6\x28"; break;
	case(62):wout << "\x76\x28"; break;
	case(63):wout << "\xF6\x28"; break;
	case(64):wout << "\x08\x28"; break;
	case(65):wout << "\x88\x28"; break;
	case(66):wout << "\x48\x28"; break;
	case(67):wout << "\xC8\x28"; break;
	case(68):wout << "\x28\x28"; break;
	case(69):wout << "\xA8\x28"; break;
	case(70):wout << "\x68\x28"; break;
	case(71):wout << "\xE8\x28"; break;
	case(72):wout << "\x0C\x28"; break;
	case(73):wout << "\x8C\x28"; break;
	case(74):wout << "\x4C\x28"; break;
	case(75):wout << "\xCC\x28"; break;
	case(76):wout << "\x2C\x28"; break;
	case(77):wout << "\xAC\x28"; break;
	case(78):wout << "\x6C\x28"; break;
	case(79):wout << "\xEC\x28"; break;
	case(80):wout << "\x18\x28"; break;
	case(81):wout << "\x98\x28"; break;
	case(82):wout << "\x58\x28"; break;
	case(83):wout << "\xD8\x28"; break;
	case(84):wout << "\x38\x28"; break;
	case(85):wout << "\xB8\x28"; break;
	case(86):wout << "\x78\x28"; break;
	case(87):wout << "\xF8\x28"; break;
	case(88):wout << "\x1C\x28"; break;
	case(89):wout << "\x9C\x28"; break;
	case(90):wout << "\x5C\x28"; break;
	case(91):wout << "\xDC\x28"; break;
	case(92):wout << "\x3C\x28"; break;
	case(93):wout << "\xBC\x28"; break;
	case(94):wout << "\x7C\x28"; break;
	case(95):wout << "\xFC\x28"; break;
	case(96):wout << "\x0A\x28"; break;
	case(97):wout << "\x8A\x28"; break;
	case(98):wout << "\x4A\x28"; break;
	case(99):wout << "\xCA\x28"; break;
	case(100):wout << "\x2A\x28"; break;
	case(101):wout << "\xAA\x28"; break;
	case(102):wout << "\x6A\x28"; break;
	case(103):wout << "\xEA\x28"; break;
	case(104):wout << "\x0E\x28"; break;
	case(105):wout << "\x8E\x28"; break;
	case(106):wout << "\x4E\x28"; break;
	case(107):wout << "\xCE\x28"; break;
	case(108):wout << "\x2E\x28"; break;
	case(109):wout << "\xAE\x28"; break;
	case(110):wout << "\x6E\x28"; break;
	case(111):wout << "\xEE\x28"; break;
	case(112):wout << "\x1A\x28"; break;
	case(113):wout << "\x9A\x28"; break;
	case(114):wout << "\x5A\x28"; break;
	case(115):wout << "\xDA\x28"; break;
	case(116):wout << "\x3A\x28"; break;
	case(117):wout << "\xBA\x28"; break;
	case(118):wout << "\x7A\x28"; break;
	case(119):wout << "\xFA\x28"; break;
	case(120):wout << "\x1E\x28"; break;
	case(121):wout << "\x9E\x28"; break;
	case(122):wout << "\x5E\x28"; break;
	case(123):wout << "\xDE\x28"; break;
	case(124):wout << "\x3E\x28"; break;
	case(125):wout << "\xBE\x28"; break;
	case(126):wout << "\x7E\x28"; break;
	case(127):wout << "\xFE\x28"; break;
	case(128):wout << "\x01\x28"; break;
	case(129):wout << "\x81\x28"; break;
	case(130):wout << "\x41\x28"; break;
	case(131):wout << "\xC1\x28"; break;
	case(132):wout << "\x21\x28"; break;
	case(133):wout << "\xA1\x28"; break;
	case(134):wout << "\x61\x28"; break;
	case(135):wout << "\xE1\x28"; break;
	case(136):wout << "\x05\x28"; break;
	case(137):wout << "\x85\x28"; break;
	case(138):wout << "\x45\x28"; break;
	case(139):wout << "\xC5\x28"; break;
	case(140):wout << "\x25\x28"; break;
	case(141):wout << "\xA5\x28"; break;
	case(142):wout << "\x65\x28"; break;
	case(143):wout << "\xE5\x28"; break;
	case(144):wout << "\x11\x28"; break;
	case(145):wout << "\x91\x28"; break;
	case(146):wout << "\x51\x28"; break;
	case(147):wout << "\xD1\x28"; break;
	case(148):wout << "\x31\x28"; break;
	case(149):wout << "\xB1\x28"; break;
	case(150):wout << "\x71\x28"; break;
	case(151):wout << "\xF1\x28"; break;
	case(152):wout << "\x15\x28"; break;
	case(153):wout << "\x95\x28"; break;
	case(154):wout << "\x55\x28"; break;
	case(155):wout << "\xD5\x28"; break;
	case(156):wout << "\x35\x28"; break;
	case(157):wout << "\xB5\x28"; break;
	case(158):wout << "\x75\x28"; break;
	case(159):wout << "\xF5\x28"; break;
	case(160):wout << "\x03\x28"; break;
	case(161):wout << "\xFD\x28"; break;
	case(162):wout << "\x83\x28"; break;
	case(163):wout << "\x43\x28"; break;
	case(164):wout << "\x23\x28"; break;
	case(165):wout << "\xC3\x28"; break;
	case(166):wout << "\xA3\x28"; break;
	case(167):wout << "\x63\x28"; break;
	case(168):wout << "\x07\x28"; break;
	case(169):wout << "\xE3\x28"; break;
	case(170):wout << "\x87\x28"; break;
	case(171):wout << "\x47\x28"; break;
	case(172):wout << "\x27\x28"; break;
	case(173):wout << "\xC7\x28"; break;
	case(174):wout << "\xA7\x28"; break;
	case(175):wout << "\x67\x28"; break;
	case(176):wout << "\x13\x28"; break;
	case(177):wout << "\xE7\x28"; break;
	case(178):wout << "\x93\x28"; break;
	case(179):wout << "\x53\x28"; break;
	case(180):wout << "\x33\x28"; break;
	case(181):wout << "\xD3\x28"; break;
	case(182):wout << "\xB3\x28"; break;
	case(183):wout << "\x73\x28"; break;
	case(184):wout << "\x17\x28"; break;
	case(185):wout << "\xF3\x28"; break;
	case(186):wout << "\x97\x28"; break;
	case(187):wout << "\x57\x28"; break;
	case(188):wout << "\x37\x28"; break;
	case(189):wout << "\xD7\x28"; break;
	case(190):wout << "\xB7\x28"; break;
	case(191):wout << "\x77\x28"; break;
	case(192):wout << "\x09\x28"; break;
	case(193):wout << "\xF7\x28"; break;
	case(194):wout << "\x89\x28"; break;
	case(195):wout << "\x49\x28"; break;
	case(196):wout << "\x29\x28"; break;
	case(197):wout << "\xC9\x28"; break;
	case(198):wout << "\xA9\x28"; break;
	case(199):wout << "\x69\x28"; break;
	case(200):wout << "\x0D\x28"; break;
	case(201):wout << "\xE9\x28"; break;
	case(202):wout << "\x8D\x28"; break;
	case(203):wout << "\x4D\x28"; break;
	case(204):wout << "\x2D\x28"; break;
	case(205):wout << "\xCD\x28"; break;
	case(206):wout << "\xAD\x28"; break;
	case(207):wout << "\x6D\x28"; break;
	case(208):wout << "\x19\x28"; break;
	case(209):wout << "\xED\x28"; break;
	case(210):wout << "\x99\x28"; break;
	case(211):wout << "\x59\x28"; break;
	case(212):wout << "\x39\x28"; break;
	case(213):wout << "\xD9\x28"; break;
	case(214):wout << "\xB9\x28"; break;
	case(215):wout << "\x79\x28"; break;
	case(216):wout << "\x1D\x28"; break;
	case(217):wout << "\xF9\x28"; break;
	case(218):wout << "\x9D\x28"; break;
	case(219):wout << "\x5D\x28"; break;
	case(220):wout << "\x3D\x28"; break;
	case(221):wout << "\xDD\x28"; break;
	case(222):wout << "\xBD\x28"; break;
	case(223):wout << "\x7D\x28"; break;
	case(224):wout << "\x0B\x28"; break;
	case(225):wout << "\x8B\x28"; break;
	case(226):wout << "\x4B\x28"; break;
	case(227):wout << "\xCB\x28"; break;
	case(228):wout << "\x2B\x28"; break;
	case(229):wout << "\xAB\x28"; break;
	case(230):wout << "\x6B\x28"; break;
	case(231):wout << "\xEB\x28"; break;
	case(232):wout << "\x0F\x28"; break;
	case(233):wout << "\x8F\x28"; break;
	case(234):wout << "\x4F\x28"; break;
	case(235):wout << "\xCF\x28"; break;
	case(236):wout << "\x2F\x28"; break;
	case(237):wout << "\xAF\x28"; break;
	case(238):wout << "\x6F\x28"; break;
	case(239):wout << "\xEF\x28"; break;
	case(240):wout << "\x1B\x28"; break;
	case(241):wout << "\x9B\x28"; break;
	case(242):wout << "\x5B\x28"; break;
	case(243):wout << "\xDB\x28"; break;
	case(244):wout << "\x3B\x28"; break;
	case(245):wout << "\xBB\x28"; break;
	case(246):wout << "\x7B\x28"; break;
	case(247):wout << "\xFB\x28"; break;
	case(248):wout << "\x1F\x28"; break;
	case(249):wout << "\x9F\x28"; break;
	case(250):wout << "\x5F\x28"; break;
	case(251):wout << "\xDF\x28"; break;
	case(252):wout << "\x3F\x28"; break;
	case(253):wout << "\xBF\x28"; break;
	case(254):wout << "\x7F\x28"; break;


	}

}


int main()
{
	int cellheight = cellsize * 4;
	int cellwidth = cellsize * 2;

	cout
		<< "Image to Braille Art Converter\n\n"
		<< "Suggested image file types: .jpg or .png\n"
		<< "Suggested image dimensions: around 100x100\n"
		<< "Suggested image coloring: as dichromatic as possible\n"
		<< "Suggested image transparency: none, exhibits strange behavior\n"
		<< "REQUIRED image location: same folder as the program.\n\n"
		<< "Enter image name, with filetype extension:\n\n";

	cin 
		>> inputstring;

	cout
		<< "\nEnter sensitivity, lower = more white, higher = more black. Default is 128.0, max is 254.9:\n\n";

	cin 
		>> SENSITIVITY;

	cout 
		<< "\n\n";

	Mat img = imread(inputstring);
	Mat im_gray;
	cvtColor(img, im_gray, CV_RGB2GRAY);
	Mat im_bw;
	threshold(im_gray, im_bw, SENSITIVITY, 255.0, THRESH_BINARY);
	imwrite("TEMP_IMG.jpg", im_bw);
	Mat im_cv = imread("TEMP_IMG.jpg");

	/*
	namedWindow("ORIGINALIMAGE", WINDOW_NORMAL);
	imshow("ORIGINALIMAGE", img);
	namedWindow("OUTPUTIMAGE", WINDOW_NORMAL);
	imshow("OUTPUTIMAGE", im_cv);
	*/

	int addwidth = cellwidth - (im_cv.cols % cellwidth);					
	int addheight = cellheight - (im_cv.rows % cellheight);

	for (int y = 0; y < im_cv.rows; y++)									//solves a problem with strange invisible imperfections created in the black and white image
	{
		rowvec.clear();
		for (int x = 0; x < im_cv.cols; x++)
		{
			if ((im_cv.at<Vec3b>(y, x)[0] >= 200) && (im_cv.at<Vec3b>(y, x)[1] >= 200) && (im_cv.at<Vec3b>(y, x)[2] >= 200))
			{
				rowvec.push_back(0);			//0 = white
			}
			else if ((im_cv.at<Vec3b>(y, x)[0] < 200) && (im_cv.at<Vec3b>(y, x)[1] < 200) && (im_cv.at<Vec3b>(y, x)[2] < 200))
			{
				rowvec.push_back(1);			//1 = black
			}
			else
			{
				cout << "PIXEL COLORING ERROR\n";
			}
		}

		for (int tempx = 0; tempx < addwidth; tempx++)					//makes sure that the width of the image in pixels is divisible by the cell's width in dots
		{
			cout << "+C";
			rowvec.push_back(0);
		}
		vec.push_back(rowvec);
	}
	for (int temp = 0; temp < addheight; temp++)						//makes sure that the height of the image in pixels is divisible by the cell's height in dots
	{
		cout << "+R";
		rowvec.clear();
		for (int tempx = 0; tempx < vec[0].size(); tempx++)				//handles endings automatically because the first horizontal vector within the main vector is already set to the correct size
		{
			rowvec.push_back(0);
		}
		vec.push_back(rowvec);
	}

	wout.open((inputstring + ".txt"), ofstream::binary | ofstream::trunc);			//creates a txt file for the braille drawing, opens it in binary mode, truncates (wipes) it
	wout << "\xFF\xFE";																//UTF-16 BOM, must be set once at the start for unicode utf 16 encoding. must use 16 bit characters from now on

	/*

	out.open((inputstring + "2.txt"), ofstream::out | ofstream::trunc);				//prints the large drawing in ascii, not braille. normally disabled

	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			if (vec[i][j])
			{
				out << "#";
			}
			else
			{
				out << ".";
			}
		}
		out << endl;
	}

	*/

	for (int yh = 0; yh < vec.size(); yh = yh + cellheight)					//main vector is logically vec[y][x]
	{
		for (int xw = 0; xw < vec[0].size(); xw = xw + cellwidth)
		{
			cellvec.clear();
			for (int ch = 0; ch < cellheight; ch++)
			{
				cellrowvec.clear();
				for (int cw = 0; cw < cellwidth; cw++)
				{
					cellrowvec.push_back(vec[yh + ch][xw + cw]);
				}
				cellvec.push_back(cellrowvec);
			}
			drawCell();													//do something upon completion of a cell
		}
		wout << nls;													//prints a newline in the output file at the end of each row
	}
	cout	
		<< "\n\nDONE.\n\n"
		<< "***NOTE***\n"
		<< "The output file will be named imgname.filetype.txt, and will be located beside the image.\n"
		<< "You will likely have to go through and fix some strange spacing in the output file,\n"
		<< "especially if the image is particularly wide, it'll likely have a ''wavey'' effect.\n"
		<< "It is recommended that you use as many BLANK BRAILLE PATTERNS as possible,\n"
		<< "these are DIFFERENT from spaces, and are found in the blank areas in the output file.\n"
		<< "You can highlight one and ctrl+c/ctrl+v them in the places that need improved spacing.\n"
		<< "You can use spaces too, but some sites, Steam for example, disallow using multiple\n"
		<< "spaces in a row for ascii art, causing it to look different between your text editor\n"
		<< "and the Steam page itself after you post it.\n\n";
	return 0;
}
