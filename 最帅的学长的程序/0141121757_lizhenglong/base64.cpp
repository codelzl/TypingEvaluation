#include "StdAfx.h"
#include "base64.h"


#include <iostream>  

static const std::string base64_chars =   
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"  
	"abcdefghijklmnopqrstuvwxyz"  
	"0123456789+/";  
// Base64编码要求把3个8位字节（3*8=24）转化为4个6位的字节（4*6=24），之后在6位的前面补两个0，形成8位一个字节的形式。 
//顺序选6个出来之后再把这6二进制数前面再添加两个0，就成了一个新的字节。之后再选出6个来，再添加0，依此类推，直到24个二进制数全部被选完。 


static inline bool is_base64(unsigned char c)
{  
	return (isalnum(c) || (c == '+') || (c == '/'));  
}  

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{  
	std::string ret;  
	int i = 0;  
	int j = 0;  
	unsigned char char_array_3[3];  
	unsigned char char_array_4[4];  

	while (in_len--) {  
		char_array_3[i++] = *(bytes_to_encode++);  
		if (i == 3) {  
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;  
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);  
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);  
			char_array_4[3] = char_array_3[2] & 0x3f;  

			for(i = 0; (i <4) ; i++)  
				ret += base64_chars[char_array_4[i]];  
			i = 0;  
		}  
	}  

	if (i)  
	{  
		for(j = i; j < 3; j++)  
			char_array_3[j] = '\0';  

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;  
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);  
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);  
		char_array_4[3] = char_array_3[2] & 0x3f;  

		for (j = 0; (j < i + 1); j++)  
			ret += base64_chars[char_array_4[j]];  

		while((i++ < 3))  
			ret += '=';  

	}  

	return ret;  

}  

std::string base64_decode(std::string const& encoded_string) {  
	int in_len = encoded_string.size();  
	int i = 0;  
	int j = 0;  
	int in_ = 0;  
	unsigned char char_array_4[4], char_array_3[3];  
	std::string ret;  

	while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {  
		char_array_4[i++] = encoded_string[in_]; in_++;  
		if (i ==4) {  
			for (i = 0; i <4; i++)  
				char_array_4[i] = base64_chars.find(char_array_4[i]);  

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);  
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);  
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];  

			for (i = 0; (i < 3); i++)  
				ret += char_array_3[i];  
			i = 0;  
		}  
	}  

	if (i) {  
		for (j = i; j <4; j++)  
			char_array_4[j] = 0;  

		for (j = 0; j <4; j++)  
			char_array_4[j] = base64_chars.find(char_array_4[j]);  

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);  
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);  
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];  

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];  
	}  

	return ret;  
}  
