// des3.0.cpp : 定义控制台应用程序的入口点。
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
bitset<64> key;  //bitset从右到左0-63
bitset<48> secretkey[16];



//字符串转换为二进制
bitset<64> stringToBit(const char s[8])
{
	bitset<64> bits;
	for (int i = 0; i<8; ++i)
	for (int j = 0; j<8; ++j)
		bits[i * 8 + j] = ((s[i] >> j) & 1);

	return bits;
}

//循环左移
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
//创建密钥
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
		//循环左移
		left = leftshows(left, shiftBits[round]);
		right = leftshows(right, shiftBits[round]);
		//合并
		for (int i = 28; i < 56; i++)
			realkey[i] = left[i - 28];
		for (int i = 0; i < 28; i++)
			realkey[i] = right[i];
		//pc_2置换
		for (int i = 0; i < 48; i++)
			outkey[47 - i] = realkey[56 - PC_2[i]];
		secretkey[round] = outkey;
	}

}


bitset<32> f(bitset<32> R, bitset<48> K){
	bitset<48> expand;
	bitset<32> output;
	bitset<32> temp;
	//E扩展，扩展为48位
	for (int i = 0; i < 48; i++)
		expand[47 - i] = R[32 - E[i]];

	//异或运算
	expand = expand^K;
	//S盒运算
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

	//尾部P置换
	temp = output;
	for (int i = 0; i < 32; i++)
		output[31 - i] = temp[32 - P[i]];
	return output;
}

//加密
bitset<64>  encrypt(bitset<64>& plain){

	bitset<64> secretText;
	bitset<64> ip_result;
	bitset<32> left;
	bitset<32> right;
	bitset<32> temp;

	//初始ip置换
	for (int i = 0; i < 64; i++)
		ip_result[63 - i] = plain[64 - IP[i]];
	//分为left和right
	for (int i = 32; i < 64; i++)
		left[i - 32] = ip_result[i];
	for (int i = 0; i < 32; i++)
		right[i] = ip_result[i];

	//16轮迭代
	for (int round = 0; round < 16; round++){
		temp = right;
		right = left^f(right, secretkey[round]);
		left = temp;
	}
	//合并为Right-Left
	for (int i = 32; i < 64; i++)
		secretText[i] = right[i - 32];
	for (int i = 0; i < 32; i++)
		secretText[i] = left[i];
	//尾置换
	ip_result = secretText;
	for (int i = 0; i < 64; i++)
		secretText[63 - i] = ip_result[64 - IP_1[i]];
	//返回密文
	return secretText;


}

//解密
bitset<64> decrypt(bitset<64>& secret){

	bitset<64> plainText;
	bitset<64> ip_result;
	bitset<32> left;
	bitset<32> right;
	bitset<32> temp;

	//初始ip置换
	for (int i = 0; i < 64; i++)
		ip_result[63 - i] = secret[64 - IP[i]];
	//分为left和right
	for (int i = 32; i < 64; i++)
		left[i - 32] = ip_result[i];
	for (int i = 0; i < 32; i++)
		right[i] = ip_result[i];

	//16轮逆变换
	for (int round = 0; round < 16; round++){
		temp = right;
		right = left^f(right, secretkey[15 - round]);
		left = temp;
	}
	for (int i = 0; i<32; ++i)
		plainText[i] = left[i];
	for (int i = 32; i<64; ++i)
		plainText[i] = right[i - 32];
	// 尾置换IP-1
	ip_result = plainText;
	for (int i = 0; i<64; ++i)
		plainText[63 - i] = ip_result[64 - IP_1[i]];
	// 返回明文
	return plainText;

}
//转换为十六进制
char tohex(int i){
	if (i<10)
		return '0' + i;
	else
		return 'A' + i - 10;
}
//十六进制转换为二进制流
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
	key = stringToUnit64(k.c_str());//转换为二进制流
	//创建密钥
	keycreate();
	secretText = encrypt(plain);

	string result = "";
	//cout << "二进制为：" << b << endl;
	for (int i = 63; i>0; i = i - 4){
		int temp = 0;
		for (int j = i; j>i - 4; j--){
			temp = temp * 2;
			if (secretText[j])
				temp = temp + 1;
		}
		result = result + tohex(temp);
	}
	//cout << "十六进制为：" << result << endl;
	//system("pause");

    return result;
	//cout << "secret=" << (char*)&secretText << endl;
	//加密字符串
	/*fstream file1;
	file1.open("D://a.txt", ios::binary | ios::out);
	file1.write((char*)&secretText, sizeof(secretText));
	file1.close();
	*/

}
string dencryptString(string s,string k){

	//string k;
	//k = "12345678";
	key = stringToUnit64(k.c_str());//转换为二进制流
	keycreate();

	bitset<64> secret = stringToUnit64(s.c_str());
	bitset<64> temp_plain = decrypt(secret);

	string result = "";
	//cout << "二进制为：" << b << endl;
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
	// 解密，并写入文件 b.txt
	//bitset<64> temp_plain = decrypt(temp);
	/*file1.open("D://b.txt", ios::binary | ios::out);
	file1.write((char*)&temp_plain, sizeof(temp_plain));
	file1.close();
	*/
}

void encyptFile(string inputfile,string k,string outfile){

	//string k = "12345678";
	key = stringToUnit64(k.c_str());
	keycreate();  // 生成16个子密钥
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
		plain.reset();  // 置0
	}
	in.close();
	
}

void dencryptFile(string inputfile, string k, string outfile){
	//string k = "12345678";
	key = stringToUnit64(k.c_str());
	keycreate();  // 生成16个子密钥
	//cout << "key=" << secretkey[1] << endl;
	// 将文件 flower.jpg 加密到 cipher.txt 中
	ifstream in;
	ofstream out;
	bitset<64> plain;

	// 解密 cipher.txt，并写入图片 flower1.jpg
	in.open(inputfile, ios::binary);
	out.open(outfile, ios::binary);
	while (in.read((char*)&plain, sizeof(plain)))
	{
		bitset<64> temp = decrypt(plain);
		out.write((char*)&temp, sizeof(temp));
		plain.reset();  // 置0
	}
	in.close();
	out.close();

}


