#pragma once
#include<vector>
#include<ctime>
#include<math.h>
#include<fstream>
#define _HIDELAYER 800 //số lớp ẩn tối đa
class Neural
{
public:
	double *weight;
	double m_output;
	double m_error;
	Neural();
	~Neural();

private:

};
typedef float INPUTLAYER[150];//ma trận input của lớp vào
typedef float HIDELAYER_WEIGHT[150][_HIDELAYER];//ma trận trọng số lớp ẩn
typedef float HIDELAYER_OUTPUT[1][_HIDELAYER];//ma trận output lớp ẩn
typedef float OUTPUTLAYER_WEIGHT[_HIDELAYER][16];//ma trận trọng số lớp ra
typedef float OUTPUTLAYER_OUTPUT[1][16];//ma trận output lớp ra
typedef float OUTPUTERROR[16];//mảng hệ số lỗi của lớp ra
typedef float HIDEERROR[_HIDELAYER];//mảng hệ số lỗi của lớp ẩn
typedef int ArrayChar[16];
//mạng neural
class NeuralNetwork
{
	INPUTLAYER input;
	HIDELAYER_WEIGHT m_hideWeight;
	OUTPUTLAYER_WEIGHT m_outWeight;
	HIDELAYER_OUTPUT m_hideOut;
	OUTPUTLAYER_OUTPUT m_outOut;
	HIDEERROR m_hideError;
	OUTPUTERROR m_outError;
public:
	ArrayChar out;
	int Count_hideLayer;//số neural lớp ẩn
	int Count_OutLayer;//số neural lớp ra
	NeuralNetwork(int _Count_hideLayer);
	NeuralNetwork();
	double training(int count, INPUTLAYER input_layer[], ArrayChar arrayBinary[]);
	double nhandang();
	void GhiTrongSo();
	void DocTrongSo();
	void setinput(INPUTLAYER temp)
	{
		CopyMatrix(input, temp);
	}
	static void CopyMatrix(INPUTLAYER &output, INPUTLAYER input);
	~NeuralNetwork();
};

