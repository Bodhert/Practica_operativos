#include <bits/stdc++.h>

using namespace std;

void read_binary(string file_name)

ifstream file_to_open(file_name.c_str(),ios::binary);
ifstream file_to_write("output.txt");
float value;

if(file_to_open.is_open()){
	while(!file_to_open.eof()){
		file_to_open.read((char *)&value,sizeof(float));
		file_to_write<<value;
	}
}

int main{

	file_to_binary("file1");
	read_binary("mytest1.dat");
	return 0;

}
