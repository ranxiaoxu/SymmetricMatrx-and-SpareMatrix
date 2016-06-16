#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<vector>
using namespace std;

template<typename T>
class SymmetricMatrix{
private:
	T *_array;
	int _n;        //对称矩阵的规模
public:
	SymmetricMatrix(T *array,int n)
		:_array(new T[n*(n+1)/2])
		,_n(n)
	{
		for(int i = 0;i < _n;i++){
			for(int j = 0;j < _n;j++){
				if(i >= j){
					_array[i*(i+1)/2+j] = array[i*_n+j];
				}else{               //能少遍历几次
					break;
				}
			}
		}
	}
	void Print()
	{
		for(int i = 0;i < _n;i++){
			for(int j = 0;j < _n;j++){
				if(i >= j){
					cout<<_array[i*(i+1)/2+j]<<" ";
				}else{             
					cout<<_array[j*(j+1)/2+i]<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
	T &AcceseeNum(int i,int j)
	{
		assert(i >= 0 && i < _n);
		assert(j >= 0 && j < _n);
		if(i > j){
			swap(i,j);
		}
		return _array[i*(i+1)/2];
	}
};

template<typename T>
struct Trituple
{
	int _row;
	int _col;
	T _value;

	Trituple()
		:_row(0)
		,_col(0)
		,_value(NULL)
	{}
};
template<typename T>
class SparseMatrix{
private:
	vector<Trituple<T>> _array;
	int _rowsize;
	int _colsize;
	T _invalue;    //无效的值
public:
	SparseMatrix()
		:_rowsize(0)
		,_colsize(0)
		,_invalue(NULL)
	{}
	SparseMatrix(T *a,int rowsize,int colsize,const T & invalue)
		:_rowsize(rowsize)
		,_colsize(colsize)
		,_invalue(invalue)
	{
		for(int i = 0;i < rowsize;i++){
			for(int j = 0;j < colsize;j++){
				if(_invalue != a[i*_colsize+j]){
					Trituple<T> t;
					t._row = i;
					t._col = j;
					t._value = a[i*_colsize+j];
					_array.push_back(t);
				}
			}
		}
	}
	void Display()
	{
		size_t index = 0;
		for(int i = 0;i < _rowsize;i++){
			for(int j = 0;j < _colsize;j++){
				if(index < _array.size() && _array[index]._row == i && _array[index]._col == j){
					cout<<_array[index++]._value<<" ";
				}else{
					cout<<_invalue<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
	SparseMatrix <T> Transpose()
	{
		SparseMatrix <T> sm;
		sm._colsize = _colsize;
		sm._rowsize = _rowsize;
		sm._invalue = _invalue;
		for(int i = 0;i < _colsize;i++){
			size_t index = 0;
			while(index < _array.size()){
				if( _array[index]._col == i){
					Trituple<T> t;
					t._row = _array[index]._col;
					t._col = _array[index]._row;
					t._value = _array[index]._value;
					sm._array.push_back(t);
				}
				index++;
			}
		}
		return sm;
	}
	SparseMatrix <T> QuickTranspose()
	{
		SparseMatrix <T> sm;
		sm._colsize = _colsize;
		sm._rowsize = _rowsize;
		sm._invalue = _invalue;
		int *rowCounts = new int[_colsize];
		int *newStart = new int[_colsize];
		memset(rowCounts,0,sizeof(int)*_colsize);
		memset(newStart,0,sizeof(int)*_colsize);
		size_t index = 0;
		while(index < _array.size()){
			rowCounts[_array[index]._col]++; 
			index++;
		}
		newStart[0] = 0;
		for(int i = 1;i < _colsize;i++){
			newStart[i] = newStart[i-1] + rowCounts[i-1];
		}
		sm._array.resize(_array.size());
		index = 0;
		while(index < _array.size()){
			int tmp = _array[index]._col;
			int k = newStart[tmp]; 
			Trituple<T> t;
			t._row = _array[index]._col;
			t._col = _array[index]._row;
			t._value = _array[index]._value;

	        sm._array[k] = t; 
			++newStart[tmp];
			index++;
		}
		return sm;
	}
};
void test()
{
	int a[5][5] = {{0,1,2,3,4},{1,0,1,2,3},{2,1,0,1,2},{3,2,1,0,1},{4,3,2,1,0}};
	SymmetricMatrix<int> s((int *)a,5);
	s.Print();
	cout<<s.AcceseeNum(2,1)<<endl;
}

void test1()
{
	int a[5][5] = {{0,1,0,2,0},{0,0,0,0,0},{0,3,0,4,0},{0,0,0,0,0},{0,5,0,6,0}};
	SparseMatrix<int> s((int *)a,5,5,0);
	s.Display();
	SparseMatrix<int> s1;
	s1 = s.QuickTranspose();
	s1.Display();

}
int main()
{
	//test();
	test1();
	system("pause");
	return 0;
}