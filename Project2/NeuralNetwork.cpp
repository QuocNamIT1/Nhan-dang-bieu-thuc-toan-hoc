#include "NeuralNetwork.h"
Neural::Neural(){}
Neural::~Neural(){}
double e = std::exp(1.0);
void NeuralNetwork::CopyMatrix(INPUTLAYER &output, INPUTLAYER input)
{
	for (int i = 0; i < 150; i++)
	{
		output[i] = input[i];
	}
}
NeuralNetwork::NeuralNetwork()
{
}
NeuralNetwork::NeuralNetwork(int _Count_hideLayer)
{
	Count_hideLayer = _Count_hideLayer;
	srand(time(NULL));
	for (int i = 0; i < this->Count_hideLayer; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			int weight;
			do
			{
				weight = (rand() % 60 - 30);
			} while (!weight);
			m_hideWeight[j][i] =  weight;
		}
	}
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < this->Count_hideLayer; j++)
		{
			int weight;
			do
			{
				weight = (rand() % 60 - 30);
			} while (!weight);
		 	m_outWeight[j][i]= (weight);
		}
	}
}
void NeuralNetwork::GhiTrongSo()
{
	std::ofstream os("Data\\Test.txt");
	os << Count_hideLayer << std::endl;
	for (int i = 0; i < 150; i++)
	{
		for (int j = 0; j < Count_hideLayer; j++)
		{
			os << m_hideWeight[i][j]<<" ";
		}
		os << std::endl;
	}
	for (int i = 0; i <	Count_hideLayer; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			os << m_outWeight[i][j] << " ";
		}
		os << std::endl;
	}
}
void NeuralNetwork::DocTrongSo()
{
	std::ifstream os("Data\\Test.txt");
	os >> Count_hideLayer;
	for (int i = 0; i < 150; i++)
	{
		for (int j = 0; j < Count_hideLayer; j++)
		{
			os >> m_hideWeight[i][j];
		}
	}
	for (int i = 0; i < Count_hideLayer; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			os >> m_outWeight[i][j];
		}
	}
}
double NeuralNetwork::training(int count_image, INPUTLAYER input_layer[], ArrayChar arrayBinary[])
{
	double total_error;
	//số vòng huấn luyện
	for (int i = 0; i < 600; ++i)
	{
		double error ;
		total_error = 0;
		//duyệt qua list các ảnh dữ liệu
		for (int j = 0; j < count_image; ++j)
		{
			double total_weight1 = 0;
			double total_weight;
			error = 0;
			if (i==599&&j==179)
			{
				int a = 2;
			}
			//duyệt trong 250 neural ẩn
			for (int m = 0; m < this->Count_hideLayer; ++m)
			{
				total_weight = -30;
				for (int k = 0; k < 150; ++k)
				{
					total_weight += input_layer[j][k] * m_hideWeight[k][m];
				}
				//total_weight -= 30;
				//sau khi tính tổng các input voi trong so tai neural m thì tính đầu ra tại neural này
				m_hideOut[0][m] = 1.0 / (1.0 + std::pow(e, -0.014*total_weight));
			}//end lớp ẩn
			//duyệt qua 16 neural lớp ra
			for (int n = 0; n < 16; ++n)
			{
				total_weight1 = -30;
				for (int l = 0; l < this->Count_hideLayer; ++l)
				{
					total_weight1 += m_outWeight[l][n] * m_hideOut[0][l];
				}
				//total_weight1 -= 30;
				m_outOut[0][n] = 1.0 / (1.0 + std::pow(e, -0.014 * total_weight1));
				error += 1.0 / 2 * std::pow((arrayBinary[j%18][n] - m_outOut[0][n]), 2);
				float daoham1 = 0.014* m_outOut[0][n] * (1 - m_outOut[0][n]);
				m_outError[n] = (arrayBinary[j%18][n] - m_outOut[0][n])*daoham1;
			}//end lớp ra
			//cập nhật trọng số cho lớp ra
			total_error += error;
			if (error >= 0.0002)
			{
				//tính hệ số lỗi cho lớp ẩn
				for (int m = 0; m < this->Count_hideLayer; ++m)
				{
					float daoham = 0.014*(1 - m_hideOut[0][m])*m_hideOut[0][m];
					double delta = 0;
					for (int n = 0; n < 16; ++n)
					{
						m_outWeight[m][n] += 150 * m_outError[n] * m_hideOut[0][m];
						delta += m_outError[n] * m_outWeight[m][n];
					}	//duyệt trong 250 neural ẩn
					m_hideError[m] = daoham*delta;
				}//end hệ số lỗi

				double totaltemp = 0;
				//cập nhật trọng số ch lớp ẩn
				for (int n = 0; n < this->Count_hideLayer; ++n)
				{
					for (int k = 0; k < 150; ++k)
					{
						m_hideWeight[k][n] += 150 * input_layer[j][k] * m_hideError[n];
					}
				}

			}
		}
	}
	return total_error;
}
double NeuralNetwork::nhandang()
{
	double total_weight1 = 0;
	double total_weight;
	double error = 0;
	for (int m = 0; m < this->Count_hideLayer; m++)
	{
		total_weight = -30;
		for (int k = 0; k < 150; k++)
		{
			total_weight += input[k] * m_hideWeight[k][m];
		}
		//total_weight -= 30;
		//sau khi tính tổng các input voi trong so tai neural m thì tính đầu ra tại neural này
		m_hideOut[0][m] = 1.0 / (1.0 + std::pow(e, -0.014*total_weight));
	}//end lớp ẩn
	for (int n = 0; n < 16; n++)
	{
		total_weight1 = -30;
		for (int l = 0; l < this->Count_hideLayer; l++)
		{
			total_weight1 += m_outWeight[l][n] * m_hideOut[0][l];
		}
		//total_weight1 -= 30;
		m_outOut[0][n] = 1.0 / (1.0 + std::pow(e, -0.014 * total_weight1));

		if (m_outOut[0][n] > 0.5)
		{
			this->out[n] = 1;
		}
		else
		{

			this->out[n] = 0;
		}
	}
	return 0;
}
NeuralNetwork::~NeuralNetwork()
{

}
