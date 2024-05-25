#include "Cpu.h"
#include <memory>
#include "Memory.h"
#include "Instruction.h"
#include <sstream>

void CPU::Reset(Memory& memory)
{
	memset(&R0, 0, 13 * sizeof(CPU::Dword));

	memset(&st, 0xFFFFFFFF, sizeof(CPU::Dword));
}

void CPU::Dispatch(Memory& mem)
{

}

void CPU::Fetch(Memory& memory)
{
	CPU::Dword op = memory[IP++];

	Instruction in = static_cast<Instruction>(op & 0x00FF);

	CPU::Byte p = (op & 0xFF00) >> 8;

	std::array<Params, 2> params = { static_cast<Params>(p & 0x0F), static_cast<Params>((p & 0xF0) >> 4) };

	Execute(op, in, params, memory);
}

void CPU::Execute(const CPU::Dword& opcode, const Instruction& inst, const std::array<Params, 2>& params, Memory& memory)
{
	Dword res = -1;
	switch (inst)
	{
	case (NOP):
		return;
	case (MOVR | JMP):
		if (params[0] != Data) 
			memcpy(&st + params[1], &st + params[0], sizeof(Dword));
		else 
		{
			CPU::Dword data = opcode >> 16;
			memcpy(&st + params[1], &data, sizeof(Dword));
		}
		break;
	case (MOVS):
		if (params[0] != Data)
			memcpy((void*)*(&st + params[1]), &st + params[0], sizeof(Dword));
		else
		{
			CPU::Dword data = opcode >> 16;
			memcpy((void*)*(&st + params[1]), &data, sizeof(Dword));
		}
		break;
	case (MOVD):
		if (params[0] != Data)
			memcpy(&st + params[1], (void*)*(& st + params[0]), sizeof(Dword));
		else
		{
			CPU::Dword data = opcode >> 16;
			memcpy(&st + params[1], (void*)*&data, sizeof(Dword));
		}
		break;
	case (JZ):
		if (FLAGS.test(1)) {
			memcpy(&st + params[1], &st + params[0], sizeof(Dword));
		}
		break;
	case (PUSH):
		if (params[0] != Data)
		{
			memcpy(&SP, &st + params[0], sizeof(Dword));
			SP--;
		}
		else
		{
			CPU::Dword data = opcode >> 16;
			memcpy(&SP, &st + params[0], sizeof(Dword));
			SP--;
		}
		break;
	case (POP):
		if (params[0] != Data)
		{
			SP++;
			memcpy(&st + params[1], &SP, sizeof(Dword));
		}
		break;
	case (IN):
	case (OUT):
		break;

	case (ADD):
		res = *(&st + params[1]) + *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (SUB | CMP):
		res = *(&st + params[1]) - *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (AND):
		res = *(&st + params[1]) & *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (OR):
		res = *(&st + params[1]) | *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (XOR):
		res = *(&st + params[1]) ^ *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (LSL):
		res = *(&st + params[1]) < *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (LSR):
		res = *(&st + params[1]) > *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (INC):
		res = *(&st + params[1]) + 1;
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (MUL):
		res = *(&st + params[1]) * *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (DIV):
		res = *(&st + params[1]) / *(&st + params[0]);
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;
	case (DEC):
		res = *(&st + params[1]) - 1;
		memcpy(&st + params[1], &res, sizeof(Dword));
		break;		
	}

	FLAGS.set(1, res == 0);

}

std::string CPU::ToString()
{
	std::stringstream ss;

	ss << "Текущее состояние микропроцессора: \n";

	ss << "Регистры общего назначения: \n";

	ss << "\tR0 = " << std::to_string(R0) << "\n";
	ss << "\tR1 = " << std::to_string(R1) << "\n";
	ss << "\tR2 = " << std::to_string(R2) << "\n";
	ss << "\tR3 = " << std::to_string(R3) << "\n";
	ss << "\tR4 = " << std::to_string(R4) << "\n";
	ss << "\tR5 = " << std::to_string(R5) << "\n";
	ss << "\tR6 = " << std::to_string(R6) << "\n";
	ss << "\tR7 = " << std::to_string(R7) << "\n";
	ss << "\tR8 = " << std::to_string(R8) << "\n";

	ss << "Регистры специального назначения: \n";

	ss << "\tIP = " << std::to_string(IP) << "\n";
	ss << "\tSP = " << std::to_string(SP) << "\n";
	ss << "\tRP = " << std::to_string(RP) << "\n";

	ss << "Текущее состояние флагов: \n";

	ss << "\tФлаг Zero = 0 \n";
	ss << "\tФлаг StackOverflow = 0 \n";
	ss << "\tФлаг Carry = 0 \n";
	ss << "\tФлаг DivisionByZero = 0 \n";
	ss << "\tФлаг SumOverflow = 0 \n";

	return ss.str();
}
