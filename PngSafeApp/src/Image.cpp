#include "Image.h"

#include <string>
#include <exception>
#include "vendor/stb/stb_image.h"
#include "vendor/stb/stb_image_write.h"
#include <iostream>


Image::Image(std::string filename)
	:path(filename)
{
	data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
	dataSize = width * height * channels;
	if (data == nullptr)
		throw std::runtime_error("Nie udalo sie zaladowac pliku!");
}

Image::~Image()
{
	stbi_image_free(data);
}

void Image::save(std::string filename)
{
	int success = stbi_write_png(filename.c_str(), width, height, channels, data, width*channels);
	if (!success)
		throw std::runtime_error("Nie udalo sie zapisac pliku!");
}

void Image::saveOffset()
{
	int n = offset;
	offset = 0;
	storeBytes(&n, sizeof(n));
	offset = n;
}

void Image::store(std::vector<unsigned char> inputData)
{
	for (unsigned char byte : inputData)
	{
		storeByte(byte);
	}
	saveOffset();
}

void Image::storeByte(unsigned char byte)
{
	storeBytes(&byte, 1);
}

void Image::storeBytes(void* bytes, int size)
{
	unsigned char* uc_bytes = reinterpret_cast<unsigned char*>(bytes);
	for (int k = 0; k < size; k++)
	{
		unsigned char byte = *uc_bytes;
		for (int i = 0; i < BITS_PER_BYTE; i++)
		{
			if (offset >= dataSize)
				throw std::runtime_error("Obraz jest zbyt maly, aby zmiescic dane");

			unsigned char bit = byte & 0x80 ? 1 : 0;
			data[offset] = (data[offset] & 0xFE) + bit;
			offset++;
			byte <<= 1;
		}
		uc_bytes++;
	}
}
std::vector<unsigned char> Image::load()
{
	std::vector<unsigned char> result;
	offset = 0;
	unsigned int limit = loadOffset();
	while (offset < limit)
	{
		result.push_back(loadByte());
	}
	return result;
}

unsigned char Image::loadByte()
{
	unsigned char result = 0;
	for (int i = 0; i < BITS_PER_BYTE; i++)
	{
		result <<= 1;
		result += data[offset] & 1;
		offset++;
	}
	return result;
}

unsigned int Image::loadOffset()
{
	unsigned int result = 0;
	for (int i = 0; i < sizeof(int); i++) {
		unsigned char byte = loadByte();
		unsigned int n = byte;
		n <<= BITS_PER_BYTE * i;
		result += n;
	}
	return result;
}