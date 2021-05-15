#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

template <class T> class SmartPointer {
	T* ref;
	unsigned* ref_count;
public:
	SmartPointer(T * ptr) {
		ref = ptr;
		ref_count = (unsigned *)malloc(sizeof(unsigned));
		*ref_count = 1;
	}

	SmartPointer(SmartPointer<T> & sptr) {
		red = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
	}

	SmartPointer<T> & operator=(SmartPointer<T> & sptr) {
		if (this == &sptr)
			return *this;

		if (*ref_count > 0)
			remove();

		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
		return *this;
	}

	~SmartPointer() {
		remove();
	}

	T getValue() {
		return *ref;
	}

protected:
	void remove() {
		--(*ref_count);
		if (*ref_count == 0) {
			delete ref;
			free(ref_count);
			ref = NULL;
			red_count = NULL;
		}
	}
};

#endif