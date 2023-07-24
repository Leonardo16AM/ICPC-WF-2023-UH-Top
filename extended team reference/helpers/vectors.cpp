
template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	os << "[";
	for (int i = 0; i < v.size(); os << v[i++])
		if (i > 0) os << " ";
	os << "]";
	return os;
}

template<class T>
ostream &operator<<(ostream &os, const vector<vector<T>> &v)
{
	os << "[";
	for (int i = 0; i < v.size(); os << v[i++])
		if (i > 0) os << endl << " ";
	os << "]";
	return os;
}
