#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

template <class T> class SmartPointer {
	T* ref{nullptr};
	unsigned* ref_count{nullptr};
public:
	SmartPointer(T * ptr) {
		reset(ptr);
	}

	SmartPointer(SmartPointer<T> & sptr) {
		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
	}

	SmartPointer<T> & operator=(SmartPointer<T> & sptr) {
		if (this == &sptr)
			return *this;

		if (ref_count && *ref_count > 0)
			remove();

		ref = sptr.ref;
		ref_count = sptr.ref_count;
		++(*ref_count);
		return *this;
	}

	~SmartPointer() {
		remove();
	}

	void reset() noexcept {
		remove();
	}

	template <class U>
	void reset(U* p) {
    if (ref) {
      remove();
    }
		ref = p;
    ref_count = static_cast<unsigned int*>(::operator new(sizeof(unsigned)));
		*ref_count = 1;
	}


	T getValue() {
		return *ref;
	}

	T & operator*() const noexcept {
		return *ref;
	}

	T* operator->() const noexcept {
		return ref;
	}

protected:
	void remove() {
		--(*ref_count);
		if (*ref_count == 0) {
			delete ref;
			delete ref_count;
			ref = nullptr;
			ref_count = nullptr;
		}
	}
};

#endif
