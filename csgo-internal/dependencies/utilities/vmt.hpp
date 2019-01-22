#pragma once

#include <winerror.h>

class vmt_hook
{
public:
	void setup(void* class_pointer)
	{
		this->table_pointer = reinterpret_cast<std::uintptr_t**>(class_pointer);
		
		while (static_cast<std::uintptr_t*>(*this->table_pointer)[this->estimated_size])
			++this->estimated_size;

		const std::size_t size_table = this->estimated_size * sizeof(std::uintptr_t);

		this->original_table = *this->table_pointer;
		this->new_table = std::make_unique<std::uintptr_t[]>(this->estimated_size);

		std::memcpy(this->new_table.get(), this->original_table, size_table);
		*this->table_pointer = this->new_table.get();
	}

	template <typename t>
	HRESULT hook(const std::size_t index, t function)
	{
		if (index > this->estimated_size)
			return E_INVALIDARG;

		this->new_table[index] = reinterpret_cast<std::uintptr_t>(function);
		return S_OK;
	}

	HRESULT unhook(const std::size_t index)
	{
		if (index > this->estimated_size)
			return E_INVALIDARG;

		this->new_table[index] = this->original_table[index];
		return S_OK;
	};

	void release()
	{
		*this->table_pointer = this->original_table;
	}

	template <typename t>
	t original(const std::size_t index)
	{
		return reinterpret_cast<t>(this->original_table[index]);
	}
private:
	std::unique_ptr<std::uintptr_t[]> new_table;
	std::uintptr_t** table_pointer;
	std::uintptr_t* original_table;
	std::size_t estimated_size;
};
