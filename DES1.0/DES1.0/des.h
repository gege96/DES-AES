// des3.0.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"stdio.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include"time.h"
#include"table.h"

using namespace std;
bitset<64> key;  //bitset���ҵ���0-63
bitset<48> secretkey[16];



//�ַ���ת��Ϊ������
bitset<64> stringToBit(const char s[8])
{
	bitset<64> bits;
	for (int i = 0; i<8; ++i)
	for (int j = 0; j<8; ++j)
		bits[i * 8 + j] = ((s[i] >> j) & 1);

	return bits;
}

//ѭ������
bitset<28>  leftshows(bitset<28> bits, int shift){

	bitset<28> temp = bits;
	//shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	for (int i = 27; i >= 0; i--)
	{
		if (i - shift >= 0)
			bits[i] = temp[i - shift];
		else
			bits[i] = temp[i - shift + 28];
	}
	return bits;

}
//������Կ
void keycreate(){
	//bitset<64> tmp;
	bitset<28> left;
	bitset<28> right;
	bitset<56> realkey;
	bitset<48> outkey;
	//key = 0011100000110111001101100011010100110100001100110011001000110001
	for (int i = 0; i < 56; i++){
		realkey[55 - i] = key[64 - PC_1[i]];
	}
	for (int round = 0; round < 16; round++){
		//left
		for (int i = 28; i < 56; i++)
			left[i - 28] = realkey[i];
		//right
		for (int i = 0; i < 28; i++)
			right[i] = realkey[i];
		//ѭ������
		left = leftshows(left, shiftBits[round]);
		right = leftshows(right, shiftBits[round]);
		//�ϲ�
		for (int i = 28; i < 56; i++)
			realkey[i] = left[i - 28];
		for (int i = 0; i < 28; i++)
			realkey[i] = right[i];
		//pc_2�û�
		for (int i = 0; i < 48; i++)
			outkey[47 - i] = realkey[56 - PC_2[i]];
		secretkey[round] = outkey;
	}

}


bitset<32> f(bitset<32> R, bitset<48> K){
	bitset<48> expand;
	bitset<32> output;
	bitset<32> temp;
	//E��չ����չΪ48λ
	for (int i = 0; i < 48; i++)
		expand[47 - i] = R[32 - E[i]];

	//�������
	expand = expand^K;
	//S������
	int x = 0;
	for (int i = 0; i < 48; i = i + 6){

		int row = expand[47 - i] * 2 + expand[47 - i - 5];
		int col = expand[47 - i - 1] * 8 + expand[47 - i - 2] * 4 + expand[47 - i - 3] * 2
			+ expand[47 - i - 4];
		int num = S_BOX[i / 6][row][col];
		bitset<4> binary(num);
		output[31 - x] = binary[3];
		output[31 - x - 1] = binary[2];
		output[31 - x - 2] = binary[1];
		output[31 - x - 3] = binary[0];
		x += 4;
	}

	//β��P�û�
	temp = output;
	for (int i = 0; i < 32; i++)
		output[31 - i] = temp[32 - P[i]];
	return output;
}

//����
bitset<64>  encrypt(bitset<64>& plain){

	bitset<64> secretText;
	bitset<64> ip_result;
	bitset<32> left;
	bitset<32> right;
	bitset<32> temp;

	//��ʼip�û�
	for (int i = 0; i < 64; i++)
		ip_result[63 - i] = plain[64 - IP[i]];
	//��Ϊleft��right
	for (int i = 32; i < 64; i++)
		left[i - 32] = ip_result[i];
	for (int i = 0; i < 32; i++)
		right[i] = ip_result[i];

	//16�ֵ���
	for (int round = 0; round < 16; round++){
		temp = right;
		right = left^f(right, secretkey[round]);
		left = temp;
	}
	//�ϲ�ΪRight-Left
	for (int i = 32; i < 64; i++)
		secretText[i] = right[i - 32];
	for (int i = 0; i < 32; i++)
		secretText[i] = left[i];
	//β�û�
	ip_result = secretText;
	for (int i = 0; i < 64; i++)
		secretText[63 - i] = ip_result[64 - IP_1[i]];
	//��������
	return secretText;


}

//����
bitset<64> decrypt(bitset<64>& secret){

	bitset<64> plainText;
	bitset<64> ip_result;
	bitset<32> left;
	bitset<32> right;
	bitset<32> temp;

	//��ʼip�û�
	for (int i = 0; i < 64; i++)
		ip_result[63 - i] = secret[64 - IP[i]];
	//��Ϊleft��right
	for (int i = 32; i < 64; i++)
		left[i - 32] = ip_result[i];
	for (int i = 0; i < 32; i++)
		right[i] = ip_result[i];

	//16����任
	for (int round = 0; round < 16; round++){
		temp = right;
		right = left^f(right, secretkey[15 - round]);
		left = temp;
	}
	for (int i = 0; i<32; ++i)
		plainText[i] = left[i];
	for (int i = 32; i<64; ++i)
		plainText[i] = right[i - 32];
	// β�û�IP-1
	ip_result = plainText;
	for (int i = 0; i<64; ++i)
		plainText[63 - i] = ip_result[64 - IP_1[i]];
	// ��������
	return plainText;

}
//ת��Ϊʮ������
char tohex(int i){
	if (i<10)
		return '0' + i;
	else
		return 'A' + i - 10;
}
//ʮ������ת��Ϊ��������
bitset<64> stringToUnit64(string hex_key) {
	bitset<64> binary_key = 0L;
	for (int i = 0; i < hex_key.length(); i++) {
		binary_key <<= 4;
		char& c = hex_key.at(i);
		if (c >= '0' && c <= '9') {
			binary_key |= ((c - '0') & 0xfL);
		}
		else if (c >= 'a' && c <= 'f')  {
			binary_key |= ((c - 'a' + 10 & 0xfL));
		}
		else if (c >= 'A' && c <= 'F') {
			binary_key |= ((c - 'A' + 10 & 0xfL));
		}
		else {
			// throw runtime_error("key is not in hex format");
		}
	}
	return binary_key;
}
string encyptString(string s,string k)
{

	//string s;
	//string k;
	bitset<64>  secretText;

	//s = "abcdefgh";
	//k = "12345678";
	bitset<64> plain = stringToUnit64(s.c_str());
	key = stringToUnit64(k.c_str());//ת��Ϊ��������
	//������Կ
	keycreate();
	secretText = encrypt(plain);

	string result = "";
	//cout << "������Ϊ��" << b << endl;
	for (int i = 63; i>0; i = i - 4){
		int temp = 0;
		for (int j = i; j>i - 4; j--){
			temp = temp * 2;
			if (secretText[j])
				temp = temp + 1;
		}
		result = result + tohex(temp);
	}
	//cout << "ʮ������Ϊ��" << result << endl;
	//system("pause");

    return result;
	//cout << "secret=" << (char*)&secretText << endl;
	//�����ַ���
	/*fstream file1;
	file1.open("D://a.txt", ios::binary | ios::out);
	file1.write((char*)&secretText, sizeof(secretText));
	file1.close();
	*/

}
string dencryptString(string s,string k){

	//string k;
	//k = "12345678";
	key = stringToUnit64(k.c_str());//ת��Ϊ��������
	keycreate();

	bitset<64> secret = stringToUnit64(s.c_str());
	bitset<64> temp_plain = decrypt(secret);

	string result = "";
	//cout << "������Ϊ��" << b << endl;
	for (int i = 63; i>0; i = i - 4){
		int temp = 0;
		for (int j = i; j>i - 4; j--){
			temp = temp * 2;
			if (temp_plain[j])
				temp = temp + 1;
		}
		result = result + tohex(temp);
	}
	return result;
	/*
	fstream file1;
	bitset<64> temp;
	file1.open("D://a.txt", ios::binary | ios::in);
	file1.read((char*)&temp, sizeof(temp));
	file1.close();
	*/
	// ���ܣ���д���ļ� b.txt
	//bitset<64> temp_plain = decrypt(temp);
	/*file1.open("D://b.txt", ios::binary | ios::out);
	file1.write((char*)&temp_plain, sizeof(temp_plain));
	file1.close();
	*/
}

void encyptFile(string inputfile,string k,string outfile){

	//string k = "12345678";
	key = stringToUnit64(k.c_str());
	keycreate();  // ����16������Կ
	//cout << "key=" << secretkey[1] << endl;

	ifstream in;
	ofstream out;
	in.open(inputfile, ios::binary);
	out.open(outfile, ios::binary);
	//in.open("C:\\Users\\dell\\Desktop\\flower.jpg", ios::binary);
	//out.open("C:\\Users\\dell\\Desktop\\cipher.txt", ios::binary);
	bitset<64> plain;
	while (in.read((char*)&plain, sizeof(plain)))
	{
		bitset<64> cipher = encrypt(plain);
		out.write((char*)&cipher, sizeof(cipher));
		plain.reset();  // ��0
	}
	in.close();
	
}

void dencryptFile(string inputfile, string k, string outfile){
	//string k = "12345678";
	key = stringToUnit64(k.c_str());
	keycreate();  // ����16������Կ
	//cout << "key=" << secretkey[1] << endl;
	// ���ļ� flower.jpg ���ܵ� cipher.txt ��
	ifstream in;
	ofstream out;
	bitset<64> plain;

	// ���� cipher.txt����д��ͼƬ flower1.jpg
	in.open(inputfile, ios::binary);
	out.open(outfile, ios::binary);
	while (in.read((char*)&plain, sizeof(plain)))
	{
		bitset<64> temp = decrypt(plain);
		out.write((char*)&temp, sizeof(temp));
		plain.reset();  // ��0
	}
	in.close();
	out.close();

}


