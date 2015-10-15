#pragma once
#include "../RBMath/Inc/Vector4.h"
#include "VertexFormat.h"
#include <vector>

struct SrTriangle
{
	VertexP3N3T2 v[3];

	SrTriangle(VertexP3N3T2 v1, VertexP3N3T2 v2, VertexP3N3T2 v3)
	{
		v[0] = v1;
		v[1] = v2;
		v[2] = v3;
	}
};


struct SrFragment
{
	std::vector<VertexP3N3T2> frag;
};

//��Ļ�ռ�buffer��ר�����ڴ�������Ļ�ռ���ص�����
//���½�ԭ��
template <class T>
struct SrSSBuffer
{
	SrSSBuffer()
	{
		w = 0;
		h = 0;
		offset = 0;
		size = 0;
	}

	void init(int w,int h)
	{
		this->w = w;
		this->h = h;
		_buffer.resize(w*h);
		offset = w*sizeof(T);
		size = w*h*sizeof(T);
	}

	void set_vals(T v)
	{
		for (auto& i : _buffer)
		{
			i = v;
		}
	}

	void set_data(int x,int y,T data)
	{
		int index = y*w + x;
		if (index<_buffer.size())
		{
			_buffer[index] = data;
		}
	}

	T get_data(int x,int y)
	{
		int index = y*w + x;
		if (index < _buffer.size())
			return _buffer[index];
		else
			return _buffer[_buffer.size()-1];
	}

	void clear()
	{
		_buffer.clear();
	}

	~SrSSBuffer()
	{
		std::vector<T>().swap(_buffer);
	}

	std::vector<T>& get_buffer()
	{
		return _buffer;
	}

	int w;
	int h;
	int offset;
	unsigned int size;

private:
	std::vector<T> _buffer;
};