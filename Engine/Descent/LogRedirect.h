struct CoutRedirect {
	std::streambuf* old;
	CoutRedirect() :old(0) {
		// empty
	}

	~CoutRedirect() {
		if (old != 0) {
			std::cout.rdbuf(old);
		}
	}

	void redirect(std::streambuf* to) {
		old = std::cout.rdbuf(to);
	}
};