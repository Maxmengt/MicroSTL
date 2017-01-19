#include "micro_alloc.h"

namespace MicroSTL {
	char* Alloc::start_free = 0;
	char* Alloc::end_free = 0;
	size_t Alloc::heap_size = 0;

	Alloc::obj* Alloc::free_list[Alloc::NFREELISTS_] = { 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	void* Alloc::allocate(size_t bytes) {
		if( bytes > (size_t)MAX_BYTES_ ) {
			return malloc(bytes);
		}
		size_t index = FREELIST_INDEX(bytes);
		obj* appropriate_list = free_list[index];
		if( !appropriate_list ){
			return refill(ROUND_UP(bytes));
		}
		free_list[index] = appropriate_list->next_node;
		return appropriate_list;
	}

	void Alloc::deallocate(void* place_address, size_t bytes) {
		if( bytes > (size_t)MAX_BYTES_ ){
			free(place_address);
		}
		else {
			size_t index = FREELIST_INDEX(bytes);
			obj* node = static_cast<obj*>(place_address);
			node->next_node = free_list[index];
			free_list[index] = node;
		}
	}

	void* Alloc::reallocate(void* place_address, size_t old_sz, size_t new_sz) {
		deallocate(place_address, old_sz);
		place_address = allocate(new_sz);
		return place_address;
	}

	void* Alloc::refill(size_t bytes) {
		int nobjs = NOBJS_;
		char* chunk = chunk_alloc(bytes, nobjs);
		if( nobjs == 1 ) return chunk;
		size_t index = FREELIST_INDEX(bytes);
		obj* head_node = free_list[index] = (obj*)(chunk + bytes);
		for( int i = 2; i < nobjs; ++ i ){
			if( i == nobjs - 1 ) {
				head_node->next_node = 0;
			}
			else {
				head_node->next_node = (obj*)(chunk + i * bytes);
				head_node = head_node->next_node;
			}
		}
		return (obj*)chunk;
	}

	char* Alloc::chunk_alloc(size_t bytes, int& nobjs) {
		char* result = start_free;
		size_t total_bytes = bytes * nobjs;
		size_t bytes_left = end_free - start_free;
		if( bytes_left >= total_bytes ){
			start_free += total_bytes;
			return result;
		}
		else if( bytes_left >= bytes ){
			nobjs = static_cast<int>(bytes_left / bytes);
			start_free += bytes * nobjs;
			return result;
		}
		else {
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			if( bytes_left > 0 ){
				size_t index = FREELIST_INDEX(bytes_left);
				obj* node = (obj*)start_free;
				node->next_node = free_list[index];
				free_list[index] = node;
			}
			start_free = (char*)malloc(bytes_to_get);
			if( !start_free ) {
				end_free = 0;
				for( int i = static_cast<int>(bytes) + ALIGN_; i <= MAX_BYTES_; i += ALIGN_ ) {
					size_t index = FREELIST_INDEX(i);
					if( free_list[index] ) {
						result = (char*)free_list[index];
						free_list[index] = free_list[index]->next_node;
						nobjs = i / static_cast<int>(bytes);
						return result;
					}
				}
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return result = start_free;
		}
	}
}