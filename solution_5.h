#pragma once
#ifndef	_SOLUTION_5_H
#define _SOLUTION_5_H
#include<iostream>
#include<cmath>
using namespace std;

class solution5_1_1 {
public:
	void operator()() {
		cout << "����̫����Ŀ��˼"
			<< endl;
	}
};

class solution5_1_2 {
public:
	void operator()() {
		cout << "random(0,1)*(b-a)+a"////////////////////
			<< endl;
	}
};

class solution5_1_3 {
public:
	void operator()() {
		cout << ""/////////////////////////////
			<< endl;
	}
};

class solution5_2_1 {
public:
	void operator()() {
		cout << "����һ��ˮƽ��ߵ��˵�һ�����ԣ���������������,Pr{X=1}=(n-1)!/n!=1/n    \n"
			<<"��Ӷn��ˮƽ�ʵ������У�Pr(X=n)=1/n!"
			<< endl;
	}
};

class solution5_2_2 {
public:
	void operator()() {
		cout << "��һ���˲���ˮƽ���һ���ᱻ���ã������һ���˵�ˮƽ���Ϊ1���򲻿��ܹ������� \n"
			<< "��һ����ˮƽΪ2,1�����ں������������(n-1)!�ֿ��� \n"
			<< "��һ����ˮƽΪ3��2������1�ĺ��棬��C(n-1,2)(n-3)! \n"
			<< "��һ����ˮƽΪ4��2,3������1�ĺ����ҿ��������У���C(n-1,3)(n-4)!2! ...... \n"
			<< "��һ����ˮƽΪn,1�������ڵ�2λ����(n-2)!,�Դ˵õ������С�(n-1,k)*(n-k-1)!(k-1)!,k=1...n-1  \n"
			<< "�����(n-1)!��(1/k)=(n-1)!*ln(n-1)+O(1),��Ϊһ����n!�ֿ��ܣ�Pr{X=2)=((n-1)!*ln(n-1)+O(1))/n! \n"
			<< "=(1/n)*(ln(n-1)+O(1)) \n"
			<< "���������Լ�������������������˵ģ�\n"
			<< "��һ��ˮƽΪi�ı���Ӷ�ĸ���Ϊ1/n,����ˮƽ�ߵĻ���i-1λ��ˮƽ��ߵ�1�ض���i-1λ֮���ұ���������λ \n"
			<< "����Ϊ1/(i-1),Pr{X=2}=��(1/n)*1/(i-1),i=2....n,=1/n��1/k,k=1...n-1,=(1/n)(ln(n-1)+O(1))"
			<< endl;
	}
};

class solution5_2_3 {
public:
	void operator()() {
		cout << "ָʾ���������X(i)��Ӧ1�����ӳ��ֵ���i���¼���1������֮�͵�����E(X)=��X(i)*Pr{i}=21/6,i=1...6"
			<< "n�����ӵ�����֮��E(��X";
	}///////////////////////////////////////
};

class solution5_2_4 {
public:
	void operator()() {
		cout << "ָʾ���������X(i)��Ӧ��i���˿��õ��Լ�ñ�ӵ� \n"
			<< "�������X��ʾ�õ��Լ�ñ�ӵ�������		\n"
			<< "E(X)=E��(X(i))=��E(X(i))=n*1/n=1,����i=1...n"
			<< endl;
	}
};

class solution5_2_5 {
public:
	void operator()() {
		cout << "";////////////////////////
	}
};

class solution5_3_3 {
public:
	void operator()() {
		cout << "���ܣ�";///////////////////////
	}
};

class solution5_4_1 {
public:
	void operator()() {
		cout << "1.k������û���˺����������ͬ�ĸ���((n-1)/n)^k,1-((n-1)/n)^k>=1/2,����n=356�����k>=253 \n"
			<< "2.û���˵�����Ϊ7.4�ĸ���Ϊ((n-1)/n)^k,ֻ��һ���˵�����Ϊ7.4�ĸ���Ϊk/n*((n-1)/n)^(k-1) \n"
			<< "1-(((n-1)/n)^k+k/n*((n-1)/n)^(k-1))>=1/2 ,k>=613 "
			<< endl;
	}
};

class solution5_4_2 {
public:
	void operator()() {
		cout << "�������������"
			<< endl;
	}
};

class solution5_4_3 {
public:
	void operator()() {//�н��
		cout << "1.�����Ǳ���ģ��������ַ����������������ԣ����������㹻������ֻ������������"
			<< endl;
	}
};

class solution5_4_4 {
public:
	void operator()() {
		cout << "������Ϊ�ض�ĳ������յĸ���Ϊ1/n^3,��һ����n�֣�E({Xi>=3))=C(k,3)*1/n^3*n>=1,����������1ʱ���������� \n"
			<< "���˵�������ͬ�����k=94"
			<< endl;
	}
};

class solution5_4_5 {
public:
	void operator()() {
		cout << "ÿ���ַ�����n�ֿ��ܣ�k���ַ�����n^k�ֿ��ܣ����а����ظ���k���в������ظ������ܵ�������A(n,k)�� \n"
			<< "Pr{X(k)}=(n!)/((n-k)!*n^k),������������⻥��"
			<< endl;
	}
};

class solution5_4_6 {
public:
	void operator()() {
		cout << "1.Ͷ��һ�����ӵĸ�����1/n,Ͷ���еĸ���Ϊ1-1/n,n�ζ�ûͶ�еĸ���Ϊ(1-1/n)^n, \n"
			<< "һ����n�����ӣ�E=n*(1-1/n)^n=n/e  \n"
			<< "2.һ������ֻ��һ�����������n��ֻ��һ��Ͷ�У�n*1/n*(1-1/n)^(n-1)=1/e,  \n"
			<< "һ����n�����ӣ�E=n/e"
			<< endl;
	}
};

class solution5_4_7 {
public:
	void operator()() {
		cout << ""//////////////////////////////////
			<< endl;
	}
};

//˼����


#endif //_SOLUTION_5_H
