#include "vmt.hpp"
#include "utilities.hpp"

protect_guard::protect_guard(void* base, std::size_t length, std::uint32_t flags)
{
	this->base = base;
	this->length = length;

	if (!VirtualProtect(this->base, this->length, flags, (unsigned long*)&this->old))
	{
		throw std::runtime_error(
			utilities::get().format(
				"failed to protect region of size %ul at 0x%8X...",
				(long)this->length,
				(long)this->base
			)
		);
	}
}

protect_guard::~protect_guard()
{
	VirtualProtect(this->base, this->length, this->old, (unsigned long*)&this->old);
}

size_t vmt_hook::estimate_table_length(std::uintptr_t* table_start)
{
	MEMORY_BASIC_INFORMATION memory_info = { 0 };

	size_t size = -1;
	do
	{
		size++;
		VirtualQuery(reinterpret_cast<void*>(table_start[size]), &memory_info, sizeof(memory_info));

	} while (memory_info.Protect == PAGE_EXECUTE_READ || memory_info.Protect == PAGE_EXECUTE_READWRITE);

	return size;
}

void vmt_hook::setup(void* class_base)
{
	this->class_base = class_base;
	this->old_table = *(std::uintptr_t**)class_base;

	this->table_length = this->estimate_table_length(this->old_table) * sizeof(std::uintptr_t);

	if (this->table_length == 0)
		return;

	this->new_table = new uintptr_t[this->table_length + 1]();
	std::memcpy(&this->new_table[1], this->old_table, this->table_length);

	this->is_allocated = true;

	try
	{
		auto guard = protect_guard(this->class_base, sizeof(std::uintptr_t), 4);

		this->new_table[0] = this->old_table[-1];
		*(uintptr_t**)this->class_base = &this->new_table[1];
	}
	catch (...)
	{
		this->is_allocated = false;
		delete[] this->new_table;
	}
}

void vmt_hook::release()
{
	if (this->is_allocated)
	{
		try
		{
			if (this->old_table)
			{
				auto guard = protect_guard { this->class_base, sizeof uintptr_t, 4 };

				*(uintptr_t**)this->class_base = this->old_table;
				this->old_table = nullptr;
			}
		}
		catch (...) {}

		delete[] this->new_table;
		this->is_allocated = false;
	}
}