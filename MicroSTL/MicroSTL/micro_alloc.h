#ifndef _MICRO_ALLOC_H_
#define _MICRO_ALLOC_H_

namespace MicroSTL {
	class Alloc {
	public:
		static void* allocate(size_t n);
		static void deallocate(void* place_address, size_t n);
		static void* reallocate(void* place_address, size_t old_sz, size_t new_sz);

	private:
		enum { ALIGN_ = 8 };
		enum { MAX_BYTES_ = 128 };
		enum { NFREELISTS_ = MAX_BYTES_ / ALIGN_ };

		union obj {
			union obj* next_free_node;
			char client_data[1];
		};
		static obj* free_list[NFREELISTS_];
		
		static int FREELIST_INDEX(size_t bytes) {
			return (bytes + ALIGN_ - 1) / ALIGN_ - 1;
		}

		static size_t ROUND_UP(size_t bytes) {
			return (bytes + ALIGN_ - 1) & ~(ALIGN_ - 1);
		}

		static void* refill(size_t n);
		static char* chunk_alloc(size_t size, int &nobjs);

		static char* start_free;
		static char* end_free;
		static size_t heap_size;
	};
}

#endif // !_MICRO_ALLOC_H_
