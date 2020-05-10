#pragma once

#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include <iostream>
#include <iomanip>

using namespace std;

template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	int size;
	int startindex;
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v);
	~TVector();
	int GetSize() { return size; }
	int GetStartIndex() { return startindex; }
	ValType& operator[](int ind);
	ValType& elem(int ind, ValType k = 0);
	bool operator==(const TVector& v) const;
	bool operator!=(const TVector& v) const;
	TVector& operator=(const TVector& v);


	TVector  operator+(const ValType& num);
	TVector  operator-(const ValType& num);
	TVector  operator*(const ValType& num);
	TVector  operator/(const ValType& num);


	TVector  operator+(const TVector& v);
	TVector  operator-(const TVector& v);
	ValType  operator*(const TVector& v);


	friend istream& operator >> (istream& is, TVector& v)
	{
		for (int i = 0; i < v.size; i++)
		{
			is >> v.pVector[i];
		}
		return is;
	}
	friend ostream& operator<<(ostream& os, const TVector& v)
	{
		for (int i = 0; i < v.startindex; i++)
		{
			cout << "0" << setw(3);
		}
		for (int i = 0; i < v.size; i++)
		{
			os << v.pVector[i] << setw(3);
		}
		os << "\n";
		return os;
	}
	friend class Object;
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	size = s;
	startindex = si;
	pVector = new ValType[size];
	//for (int i = 0; i < size; i++)
	//	pVector[i] = a;
}

template <class ValType>
TVector<ValType>::TVector(const TVector<ValType>& v)
{
	size = v.size;
	startindex = v.startindex;
	pVector = new ValType[size];
	for (int i = 0; i < size; i++)
		pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[]pVector;
}

template <class ValType>
ValType& TVector<ValType>::operator[](int ind)
{
	return pVector[ind - startindex];
}

template <class ValType>
ValType& TVector<ValType>::elem(int ind, ValType k)
{
	if (((ind - startindex) >= 0) && ((ind - startindex) < size))
		return pVector[ind - startindex];
	else return k;
}

template <class ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& v) const
{
	if ((size != v.size) || (startindex != v.startindex))
		return false;
	for (int i = 0; i < size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;
}

template <class ValType>
bool TVector<ValType>::operator!=(const TVector<ValType>& v) const
{
	if ((size != v.size) || (startindex != v.startindex))
		return true;
	for (int i = 0; i < size; i++)
		if (pVector[i] != v.pVector[i])
			return true;
	return false;
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType>& v)
{
	if (this != &v)
	{
		if (size != v.size)
		{
			delete[]pVector;
			pVector = new ValType[v.size];
		}
		size = v.size;
		startindex = v.startindex;
		for (int i = 0; i < size; i++)
		{
			pVector[i] = v.pVector[i];
		}
	}
	return *this;
}



template <class ValType>
TVector<ValType>  TVector<ValType>::operator+(const ValType& num)
{
	TVector Rez(size, startindex);
	for (int i = 0; i < size; i++)
	{
		Rez.pVector[i] = pVector[i] + num;
	}
	return Rez;

}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator-(const ValType& num)
{
	TVector Rez(size, startindex);
	for (int i = 0; i < size; i++)
	{
		Rez.pVector[i] = pVector[i] - num;
	}
	return Rez;
}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator*(const ValType& num)
{
	TVector Rez(size, startindex);
	for (int i = 0; i < size; i++)
	{
		Rez.pVector[i] = pVector[i] * num;
	}
	return Rez;
}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator/(const ValType& num)
{
	TVector Rez(size, startindex);
	if (num != 0)
	{
		for (int i = 0; i < size; i++)
		{
			Rez.pVector[i] = pVector[i] / num;
		}
	}
	else if (num == 0)
	{
		for (int i = 0; i < size; i++)
		{
			Rez.pVector[i] = 0;
		}
	}
	return Rez;
}



template <class ValType>
TVector<ValType>  TVector<ValType>::operator+(const TVector<ValType>& v)
{
	TVector Rez(size, startindex);
	for (int i = 0; i < size; i++)
	{
		Rez.pVector[i] = pVector[i] + v.pVector[i];
	}
	return Rez;
}

template <class ValType>
TVector<ValType>  TVector<ValType>::operator-(const TVector<ValType>& v)
{
	TVector Rez(size, startindex);
	for (int i = 0; i < size; i++)
	{
		Rez.pVector[i] = pVector[i] - v.pVector[i];
	}
	return Rez;
}

template <class ValType>
ValType  TVector<ValType>::operator*(const TVector<ValType>& v)
{
	ValType f = 0;
	for (int i = 0; i < size; i++)
	{
		f = f + pVector[i] * v.pVector[i];
	}
	return f;
}



template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);
	TMatrix(const TVector<TVector<ValType> >& mt);
	bool operator==(const TMatrix& mt) const;
	bool operator!=(const TMatrix& mt) const;
	TMatrix& operator= (const TMatrix& mt);
	TMatrix  operator+ (const TMatrix& mt);
	TMatrix  operator- (const TMatrix& mt);
	TMatrix  operator* (const TMatrix& mt);

	friend istream& operator >> (istream& is, TMatrix& mt)
	{
		for (int i = 0; i < mt.size; i++)
		{
			is >> mt.pVector[i];
		}
		return is;
	}


	friend ostream& operator<<(ostream& os, const TMatrix& mt)
	{
		for (int i = 0; i < mt.size; i++)
		{
			os << mt.pVector[i];
		}
		os << "\n";
		return os;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector< TVector<ValType> >(s)
{
	for (int i = 0; i < s; i++)
	{
		TMatrix::pVector[i] = TVector<ValType>(s - i, i);
	}
}

template <class ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :TVector<TVector<ValType> >(mt)
{

}

template <class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :TVector<TVector<ValType> >(mt)
{

}

template <class ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType> >::operator==(mt);
}

template <class ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
	return TVector<TVector<ValType> >::operator!=(mt);
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator= (const TMatrix<ValType>& mt)
{
	if (this != &mt)
	{
		if (TMatrix::size != mt.size)
		{
			delete[]TMatrix::pVector;
			TMatrix::pVector = new TVector<ValType>[mt.size];
		}
		TMatrix::size = mt.size;
		TMatrix::startindex = mt.startindex;
		for (int i = 0; i < TMatrix::size; i++)
		{
			TMatrix::pVector[i] = mt.pVector[i];
		}
	}
	return *this;
}

template <class ValType>
TMatrix<ValType>  TMatrix<ValType>::operator+ (const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType> >::operator+(mt);
}

template <class ValType>
TMatrix<ValType>  TMatrix<ValType>::operator- (const TMatrix<ValType>& mt)
{
	return TVector<TVector<ValType> >::operator-(mt);
}


template <class ValType>
TMatrix<ValType>  TMatrix<ValType>::operator* (const TMatrix<ValType>& mt)
{
	int f = 0;
	TMatrix Rez(TMatrix::size);
	for (int i = 0; i < TMatrix::size; i++)
	{
		for (int j = i; j < TMatrix::size; j++)
		{
			Rez[i][j] = 0;
			f = j + 1;
			for (int t = i; t < f; t++)
			{
				Rez[i][j] = Rez[i][j] + mt.pVector[t][j] * (*this)[i][t];
			}
		}
	}
	return Rez;
}

#endif