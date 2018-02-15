Data<int> readElems(const char* crFile) {
 	Data<int> res;
	std::ifstream s(crFile);
	while (s) {
		int i;
		s >> i;
		if (s) {
			res.insert(i);
		}
	}
	return res;
}

Data<int> deleteElems(const char* crFile,Data<int>& crRes) {
	std::ifstream s(crFile);
	Data<int> res(crRes);
	while (s) {
		int i;
		s >> i;
		if (s)
            res.erase(i);
	}
	return res;
}
