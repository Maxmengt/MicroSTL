#ifndef _MICRO_ALLOC_H_
#define _MICRO_ALLOC_H_

#include <cstdlib>

namespace MicroSTL {
	class Alloc {
	public:
		static void* allocate(size_t bytes);
		static void deallocate(void* place_address, size_t bytes);
		static void* reallocate(void* place_address, size_t old_sz, size_t new_sz);

	private:
		enum { ALIGN_ = 8 };
		enum { MAX_BYTES_ = 128 };
		enum { NFREELISTS_ = MAX_BYTES_ / ALIGN_ };
		enum { NOBJS_ = 20 };

		union obj {
			union obj* next_node;
			char client_data[1];
		};
		static obj* free_list[NFREELISTS_];
		
		static size_t FREELIST_INDEX(size_t bytes) {
			return (bytes + ALIGN_ - 1) / ALIGN_ - 1;
		}

		static size_t ROUND_UP(size_t bytes) {
			return (bytes + ALIGN_ - 1) & ~(ALIGN_ - 1);
		}

		static void* refill(size_t bytes);
		static char* chunk_alloc(size_t bytes, int &nobjs);

		static char* start_free;
		static char* end_free;
		static size_t heap_size;
	};
}

#endif // !_MICRO_ALLOC_H_
