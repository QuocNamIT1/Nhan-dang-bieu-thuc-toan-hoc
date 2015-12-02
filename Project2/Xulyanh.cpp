#include "Xulyanh.h"


Xulyanh::Xulyanh(string filename)
{
	source = imread(filename, CV_LOAD_IMAGE_COLOR);
}
Xulyanh::Xulyanh()
{
}
Mat Xulyanh::ThresholdImage()
{
	Mat grayimg(source.size(), CV_8UC1);
	Mat thresh(source.size(), CV_8UC1);

	//imshow("image", image);//ảnh gốc
	cvtColor(source, grayimg, CV_BGR2GRAY);//chuyển sang ảnh xám
	threshold(grayimg, thresh, 150, 255, CV_THRESH_BINARY);//nhị phân hóa ảnh
	//imshow("Thresh", thresh);//show ảnh
	normalize(thresh, thresh, 0, 255, CV_MINMAX);//giảm nhiễu cho ảnh


	//xử lý các diểm ảnh ngoài ý muốn
	Mat miniThresh(thresh.size(), CV_8UC1);//ảnh này dùng để xử lý
	thresh.copyTo(miniThresh);
	return miniThresh;
}
void Xulyanh::Cat_anh()
{
	Mat thresh = this->ThresholdImage();
	int xmin = 10000, ymin = 10000, xmax = -1, ymax = -1;
	//tìm xmin
	for (int i = 0; i <thresh.cols; i++)
	{
		for (int j = 0; j < thresh.rows; j++)
		{
			Scalar colour = thresh.at<uchar>(Point(i, j));
			if (colour.val[0] == 0)
			{
				xmin = i;
				break;
			}
		}
		if (xmin != 10000)
		{
			break;
		}
	}
	//tìm ymin
	for (int i = 0; i <thresh.rows; i++)
	{
		for (int j = 0; j < thresh.cols; j++)
		{
			Scalar colour = thresh.at<uchar>(Point(j, i));
			if (colour.val[0] == 0)
			{
				ymin = i;
				break;
			}
		}
		if (ymin != 10000)
		{
			break;
		}
	}


	//tìm xmax
	for (int i = thresh.cols - 1; i >= 0; i--)
	{
		for (int j = 0; j < thresh.rows; j++)
		{
			Scalar colour = thresh.at<uchar>(Point(i, j));
			if (colour.val[0] == 0)
			{
				xmax = i;
				break;
			}
		}
		if (xmax != -1)
		{
			break;
		}
	}
	//tìm ymax
	for (int i = thresh.rows - 1; i >= 0; i--)
	{
		for (int j = 0; j < thresh.cols; j++)
		{
			Scalar colour = thresh.at<uchar>(Point(j, i));
			if (colour.val[0] == 0)
			{
				ymax = i;
				break;
			}
		}
		if (ymax != -1)
		{
			break;
		}
	}


	Mat number = thresh(Rect(xmin, ymin, xmax - xmin+1, ymax - ymin+1));


	// chia cắt các dòng trong ảnh
	int x_current, y_current = 0;
	std::vector<Mat> listdongMat;
	bool dongtrang = false;
	//chia dòng
	for (int i = 0; i< number.rows; i++)
	{
		int j;
		for (j = 0; j < number.cols; j++)
		{
			Scalar colour = number.at<uchar>(Point(j, i));
			if (colour.val[0] == 0)
			{
				if (dongtrang == true)//nếu đang là dòng trắng mà gặp dòng den
				{
					y_current = i;
				}
				dongtrang = false;
				break;
			}
		}
		//nếu trong dòng này toàn màu trắng thì cắt ra 
		if (j == number.cols&&dongtrang == false)
		{

			Mat _temp = number(Rect(0, y_current, number.cols, i - y_current));
			listdongMat.push_back(_temp);
			dongtrang = true;
		}
		if (i == number.rows - 1 && dongtrang == false)
		{
			Mat _temp = number(Rect(0, y_current, number.cols, number.rows - y_current));
			listdongMat.push_back(_temp);
		}
	}
	std::vector<Mat> listNumber;
	for (int z = 0; z < listdongMat.size(); z++)
	{
		dongtrang = true;
		//chia các chữ số trong các ảnh đã cắt dòng
		for (int i = 0; i < listdongMat[z].cols; i++)
		{
			int j;
			for (j = 0; j < listdongMat[z].rows; j++)
			{
				Scalar colour = listdongMat[z].at<uchar>(Point(i, j));
				if (colour.val[0] == 0)//nếu là màu đen
				{
					if (dongtrang)
					{
						x_current = i;
						dongtrang = false;
					}
					break;
				}
			}
			if (j == listdongMat[z].rows&&dongtrang == false)
			{
				dongtrang = true;
				Mat temp = listdongMat[z](Rect(x_current, 0, i - x_current, listdongMat[z].rows));
				listNumber.push_back(temp);
			}
			if (i == listdongMat[z].cols-1&&!dongtrang)
			{
				dongtrang = true;
				Mat temp = listdongMat[z](Rect(x_current, 0, i - x_current+1, listdongMat[z].rows));
				listNumber.push_back(temp);
			}
		}
	}


	//cắt những đoạn thừa trong ảnh
	for (int i = 0; i < listNumber.size(); i++)
	{
		for (int j = 0; j < listNumber[i].rows; j++)
		{
			int z;
			for (z = 0; z < listNumber[i].cols; z++)
			{
				Scalar colour = listNumber[i].at<uchar>(Point(z, j));
				if (colour.val[0] == 0)//nếu là màu đen
				{

					y_current = j;
					break;
				}
			}
			if (z != listNumber[i].cols)
			{
				break;
			}
		}
		int y_current1;
		for (int j = listNumber[i].rows - 1; j >= 0; j--)
		{
			int z;
			for (z = 0; z < listNumber[i].cols; z++)
			{
				Scalar colour = listNumber[i].at<uchar>(Point(z, j));
				if (colour.val[0] == 0)//nếu là màu đen
				{
					y_current1 = j;
					break;
				}
			}
			if (z != listNumber[i].cols)
			{
				break;
			}
		}
		Mat temp = listNumber[i](Rect(0, y_current, listNumber[i].cols, y_current1 - y_current + 1));
		this->listNumberCurrent.push_back(temp);
	}
}
void Xulyanh::ResizeImage()
{
	for (int i = 0; i < listNumberCurrent.size(); i++)
	{
		resize(listNumberCurrent[i], listNumberCurrent[i], Size(50, 75));
	}
}
Xulyanh::~Xulyanh()
{
}
