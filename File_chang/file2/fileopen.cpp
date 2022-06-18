#include<stdio.h>
#include<cstring>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

struct wav_header_t{
	char chunkID[4];
	unsigned long chunkSize;
	char format[4];
	char subchunk1ID[4];
	unsigned long subchunk1Size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned long sampleRate;
	unsigned long byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
};
struct FileInfo {
	wav_header_t header;
	std::vector<char> HeadInfo;
	unsigned long size;
	short int* value;
};
int* MakeArr(System::String^ UserStringForExc) {
	array<wchar_t>^ id = {'.',' ',','};
	array<System::String^>^ Arr = UserStringForExc->Split(id);
	int* Ans = new int[Arr->Length];
	for (int i = 0; i < Arr->Length; i++) {
		Ans[i] = System::Int32::Parse(Arr[i]);
	}
	return Ans;
}
FileInfo MakeFileInfo(System::String^ FileName) {
	array<wchar_t>^ a = FileName->ToCharArray();
	char* File = new char[a->Length];
	for (int i = 0; i < a->Length; i++) {
		File[i] = (char)a[i];
	}
	File[a->Length] = '\0';
	FILE* fin = fopen(File, "rb");
	wav_header_t header;
	fread(&header, sizeof(header), 1, fin);
	std::vector<char> HeadInfo;
	int sizeinfo = 4;
	for (int i = 0; i < 4; i++) {
		char New;
		fscanf_s(fin, "%c", &New);
		HeadInfo.push_back(New);
	}
	int i = 0;
	unsigned long size;
	while (true)
	{
		char Str[4];
		for (int j = i; j < i + 4; j++) {
			Str[j - i] = HeadInfo[j];
		}
		if (Str[0] == 'd' && Str[1] == 'a' && Str[2] == 't' && Str[3] == 'a') {
			fread(&size, sizeof(size), 1, fin);
			break;
		}
		sizeinfo++;
		i++;
		char New;
		fscanf_s(fin, "%c", &New);
		HeadInfo.push_back(New);
	}
	int sample_size = header.bitsPerSample / 8;
	int samples_count = size * 8 / header.bitsPerSample;
	short int* value = new short int[samples_count];
	memset(value, 0, sizeof(short int) * samples_count);
	for (int i = 0; i < samples_count; i++)
	{
		fread(&value[i], sample_size, 1, fin);
	}
	fclose(fin);
	FileInfo Ans;
	Ans.header = header;
	Ans.HeadInfo = HeadInfo;
	Ans.size = size;
	Ans.value = value;
	return Ans;
}
void MakeFiles(System::String^ FileName, System::String^ Road) {
	FileInfo NewFile = MakeFileInfo(FileName);
	array<wchar_t>^ a =Road->ToCharArray();	
	for (int k = 0; k < 2; k++) {
		char* File = new char[a->Length + 7];
		for (int i = 0; i < a->Length; i++) {
			File[i] = (char)a[i];
		}
		File[a->Length]='\\';
		File[a->Length + 1] = '0';
		File[a->Length + 2] = (char)k + '0';
		File[a->Length + 3] = '.';
		File[a->Length + 4] = 'w';
		File[a->Length + 5] = 'a';
		File[a->Length + 6] = 'v';
		File[a->Length + 7] = '\0';
		FILE* fout;
		fopen_s(&fout, File, "wb+");
		fwrite(&NewFile.header, sizeof(NewFile.header), 1, fout);
		int sizeinfo = NewFile.HeadInfo.size();
		for (auto it = 0; it < sizeinfo; it++) {
			fwrite(&NewFile.HeadInfo[it], sizeof(NewFile.HeadInfo[it]), 1, fout);
		}
		int size = NewFile.size/2;
		fwrite(&size, sizeof(size), 1, fout);
		int sample_size = NewFile.header.bitsPerSample / 8;
		int samples_count = size * 8 / NewFile.header.bitsPerSample;
		for (int i = k* samples_count; i < (k+1) *samples_count; i++)
		{
			fwrite(&NewFile.value[i], sizeof(NewFile.value[i]), 1, fout);
		}
		fclose(fout);
	}
}