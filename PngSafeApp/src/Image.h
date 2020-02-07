#pragma once
#include <string>
#include <vector>

class Image
{
private:
	const int BITS_PER_BYTE = 8;
	std::string path;
	unsigned char* data = nullptr;
	unsigned int dataSize;
	unsigned int offset = sizeof(int) * BITS_PER_BYTE; // Pierwsze 4 bajty koduj¹ rozmiar danych.
	int width;
	int height;
	int channels;

	void storeBytes(void* bytes, int size);
	void storeByte(unsigned char byte);
	unsigned char loadByte();
	void saveOffset();
	unsigned int loadOffset();
public:
	Image(std::string filename);
	~Image();
	void store(std::vector<unsigned char> inputData);
	std::vector<unsigned char> load();

	void save(std::string filename);
};