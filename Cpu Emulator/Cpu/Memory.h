#pragma once
#include <memory>
#include "Cpu.h"

class Memory
{
public:
	Memory()
	{
		memset(data, 0, SIZE);
	}

	CPU::Dword operator[](CPU::Dword address) const {
		//return data[address] | data[address + 1] << 8;
		return reinterpret_cast<CPU::Dword*>(data)[address];
	}

	void SetupTest() 
	{
		int i1 = 0x20001001;
		
		memcpy(data, &i1, sizeof(i1));

		short i2 = 0x2101;

		memcpy(data + sizeof(i1), &i2, sizeof(i2));

	}

	~Memory() 
	{
		delete data;
	}

private:
	static constexpr int SIZE = 64 * 1024; //* 1024;

	CPU::Byte* data = new CPU::Byte[SIZE];
};