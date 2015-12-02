// ClassLibrary1.h
#include "../Project2/NeuralNetwork.cpp"
#include "../Project2/NeuralNetwork.h"
#include "../Project2/Xulyanh.cpp"
#include "../Project2/Xulyanh.h"
#include "../Project2/TinhToanBieuTHuc.cpp"
#include "../Project2/TinhToanBieuTHuc.h"
#include <msclr\marshal_cppstd.h>
#include<string>
#pragma once
#include<fstream>
#include<stack>
using namespace std;
using namespace System;

namespace ClassLibrary1 {

	public ref class Class1
	{
	public:
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
			for (int i = 0; i < 16 - n; i++)
			{
				bytechar[i] = 0;
			}
			for (int i = 16 - n; i < 16; i++)
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
						temp_[z * 10 + j] = 0;
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
		static std::string toss(System::String ^ s)
		{
			// convert .NET System::String to std::string
			const char* cstr = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
			std::string sstr = cstr;
			System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)cstr));
			return sstr;
		}



		System::String^ TimChuoiDauRa(System::String^ filename)
		{
			NeuralNetwork neuralNet;
			neuralNet.DocTrongSo();
			std::string s = Class1::toss(filename);
			Xulyanh xuly(s);
			xuly.Cat_anh();
			xuly.ResizeImage();
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
			System::String^ MyString = gcnew System::String(daysotemp.c_str());
			return MyString;
		}
		 float tinh(System::String^ s)
		{
			string temp=toss(s);
			
			TinhToanBieuThuc a(temp);
			return a.tinhbieuthuc();
		}
	};
}
