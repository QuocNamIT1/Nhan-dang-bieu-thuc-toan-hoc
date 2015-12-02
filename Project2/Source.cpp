#define _CRT_SECURE_NO_WARNINGS
#include"Xulyanh.h"
#include<fstream>
#include<stack>
#include"NeuralNetwork.h"
#include"TinhToanBieuThuc.h"
#include<ctime>
typedef int Matrix[15][10];
typedef int ArrayChar[16];
#define Image_count 360
void ConvertToChar_(int &char_, int bytechar[])
{
	for (int i = 0; i < 16; i++)
	{
		char_ += bytechar[i] * std::pow(2, 15 - i);
	}
}
void ConvertToByte(int char_, int bytechar[])
{
	std::stack<int> stBinary;
	while (char_)
	{
		stBinary.push(char_ % 2);
		char_ /= 2;
	}
	int n = stBinary.size();
	for (int i = 0; i < 16-n; i++)
	{
		bytechar[i] = 0;
	}
	for (int i = 16-n; i < 16; i++)
	{
		bytechar[i] = stBinary.top();
		stBinary.pop();
	}
}
void ConvertToMatrix(Mat input, INPUTLAYER &temp_)
{
	for (int z = 0; z < 15; z += 1)
	{
		for (int j = 0; j < 10; j += 1)
		{
			int temp1 = 0;
			for (int x = 0; x < 5; x++)
			{
				for (int y = 0; y < 5; y++)
				{
					if (j * 5 == 20)
					{
						int a = 2;
					}
					Scalar colour = input.at<uchar>(Point(j * 5 + x, z * 5 + y));
					temp1 += colour.val[0];
				}
			}
			temp1 /= 25;
			if (temp1 > 200)
			{
				temp_[z*10+j] = 0;
			}
			else
			{
				temp_[z * 10 + j] = 1;
			}
		}
	}
}
void CopyArray(ArrayChar input, ArrayChar output)
{
	for (int i = 0; i < 16; i++)
	{
		output[i] = input[i];
	}
}
void tool()
{
	Xulyanh xuly("C:\\Users\\WinDown\\Desktop\\ghjk.png");
	xuly.Cat_anh();
	xuly.ResizeImage();

	std::vector<Mat> listNumber;//lưu ảnh các số trong thư mục Data
	INPUTLAYER ListMatrix[Image_count];//lưu lại các ma trận đã được chuyển đổi từ ảnh trong thư mục data
	//đọc các file ảnh tử thư mục data
	string link = "Data\\1-0";
	string link_temp = "Data\\1-A";
	for (int i = 0; i < Image_count; i++)
	{
		if (i % 260==0 && i!=0)
		{
			link_temp += "A";
		}
		if (i % 10 == 0&&i!=0)
		{
			link_temp[link_temp.length() - 1] += 1;
		}

		Mat tam;
		char s[1];
		s[0] = char(i % 10 + 48);
		string temp;
		temp.assign(s, 1);
		temp += ".jpg";
		link = link_temp + temp;
		tam = imwrite(link, xuly.listNumberCurrent[i]);
	}

}
string nhandang()
{
	Xulyanh xuly("C:\\Users\\WinDown\\Desktop\\asd1.png");
	xuly.Cat_anh();
	xuly.ResizeImage();
	NeuralNetwork neuralNet = NeuralNetwork();
	neuralNet.DocTrongSo();
	char *dayso = new char[xuly.listNumberCurrent.size()];
	for (int i = 0; i < xuly.listNumberCurrent.size(); i++)
	{
		INPUTLAYER input1;
		ArrayChar out;
		ConvertToMatrix(xuly.listNumberCurrent[i], input1);
		neuralNet.setinput(input1);
		neuralNet.nhandang();
		CopyArray(neuralNet.out, out);
		int char_ = 0;
		ConvertToChar_(char_, out);
		dayso[i] = char_;
	}
	string daysotemp;
	daysotemp.assign(dayso, xuly.listNumberCurrent.size());
	imshow("anh goc", xuly.source);
	return daysotemp;
}

void trainning()
{
	std::ifstream in;
	in.open("Data\\data.txt", std::ios::in);
	std::vector<std::string> listchar;
	while (!in.eof())
	{
		std::string temp;
		std::getline(in, temp);
		listchar.push_back(temp);
	}
	ArrayChar arrayBinary[18];
	for (int i = 0; i < listchar.size(); i++)
	{
		ArrayChar temp_;
		ConvertToByte((int)listchar[i][0], temp_);
		for (int j = 0; j < 16; j++)
		{
			arrayBinary[i][j] = temp_[j];
		}
	}


	std::vector<Mat> listNumber;//lưu ảnh các số trong thư mục Data
	INPUTLAYER ListMatrix[Image_count];//lưu lại các ma trận đã được chuyển đổi từ ảnh trong thư mục data
	//đọc các file ảnh tử thư mục data
	string link = "Data\\1-0";
	string link_temp = "Data\\1-A";
	for (int i = 0; i < Image_count; i++)
	{
		if (i % 260 == 0 && i != 0)
		{
			link_temp += "A";
		}
		if (i % 10 == 0 && i != 0)
		{
			link_temp[link_temp.length() - 1] += 1;
		}
		char s[1];
		Mat tam;
		s[0] = char(i%10 +48);
		string temp;
		temp.assign(s, 1);
		temp += ".jpg";
		link =link_temp+ temp;
		tam = imread(link,CV_LOAD_IMAGE_GRAYSCALE);
		listNumber.push_back(tam);
		INPUTLAYER temp_;
		ConvertToMatrix(listNumber[i], temp_);
		NeuralNetwork::CopyMatrix(ListMatrix[i], temp_);
	}
	double min = 0.09;
	for (int i = 800; i <= 800; i += 10)
	{
		NeuralNetwork neuralNet = NeuralNetwork(i);
		double _error;
		std::cout << "So lop an: " << i << std::endl;
		_error = neuralNet.training(Image_count, ListMatrix, arrayBinary);
		std::cout << "Ti le loi:" << _error << std::endl;
		if (_error < min)
		{
			neuralNet.GhiTrongSo();
			min = _error;
		}
	}
}
int main()
{
	clock_t start, end;
	start = clock();
	//tool cắt và lưu các chữ cái cần trainning
	//tool();
	//tranning bộ dữ liệu với số lớp ẩn tắng dna62 từ 190 -> 800
	//trainning();
	//nhận dạng biểu thức
	string daysotemp = nhandang();
	std::cout << daysotemp << " = ";
	///////Tính toán biểu thức
	//TinhToanBieuThuc ttbt(daysotemp);
	//std::cout << ttbt.tinhbieuthuc() << std::endl;
	end = clock();
	std::cout <<"Thoi gian chay:"<< (end - start)/1000.0 <<"s"<< std::endl;
	cvWaitKey();
system("pause");
	return 1;
}


