#include <iostream>
#include <cstdio>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>

using Bits = std::vector<char>;

std::ostream& operator<<(std::ostream& s, const Bits& bits)
{
	for (auto b : bits)
	{
		s << b;
	}
	return s;
}

template <typename Callable>
void repeat(unsigned n, Callable f)
{
	for (unsigned i = 0; i < n; ++i)
	{
		f(i);
	}
}

void cexit(char c)
{
	if (c == 'N') exit(1);
}

char readbit(size_t n)
{
	char c;
	std::cout << (n+1) << std::endl;
	std::cin >> c;
	cexit(c);
	return c;
}

void readbit_to(size_t n, Bits* bits)
{
	char c = readbit(n);
	// std::cerr << c << " -> [" << n << "]" << std::endl;
	(*bits)[n] = c;
}

void readpair_to(size_t n, Bits* bits)
{
	const size_t bit_count = bits->size();
	readbit_to(n, bits);
	readbit_to(bit_count - n - 1, bits);
}

Bits simple_read_bits(size_t bit_count)
{
	Bits bits(bit_count, '.');
	repeat(bit_count, [&](unsigned n)
	{
		readbit_to(n, &bits);
	});
	return bits;
}

struct Idx
{
	size_t i;
	bool b;
};

bool eq(char x, char y)
{
	return x != '.' and y != '.' and x == y;
}

bool ne(char x, char y)
{
	return x != '.' and y != '.' and x != y;
}

Idx find_si(const Bits& bits)
{
	auto size = bits.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (eq(bits[i], bits[size - i - 1]))
		{
			return {i, true};
		}
	}
	std::cerr << "no si" << std::endl;
	std::cerr << bits << std::endl;
	return {0, false};
}

Idx find_di(const Bits& bits)
{
	auto size = bits.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (ne(bits[i], bits[size - i - 1]))
		{
			return {i, true};
		}
	}
	std::cerr << "no di" << std::endl;
	std::cerr << bits << std::endl;
	return {0, false};
}

char cpl(char c)
{
	if (c == '0') return '1';
	if (c == '1') return '0';
	// std::cerr << "inv input " << c << std::endl;
	// exit(1);
	return c;
}

void cpl_bits(Bits* b)
{
	std::transform(b->begin(), b->end(), b->begin(), [](char c)
	{
		return cpl(c);
	});
}

void rev_bits(Bits* b)
{
	std::reverse(b->begin(), b->end());
}

struct Idxs
{
	size_t si;
	size_t di;
	bool sb;
	bool db;
};

void detect(Bits* bits, Idxs idxs)
{
	const bool db = idxs.db;
	const bool sb = idxs.sb;
	const size_t di = idxs.di;
	const size_t si = idxs.si;
	const size_t d2 = bits->size() - di - 1;
	const size_t s2 = bits->size() - si - 1;
	const char cd = readbit(di);
	const char cs = readbit(si);
	const char cd2 = readbit(d2);
	const char cs2 = readbit(s2);
	auto deq = [db](char x, char y)
	{
		return db ? x == y : true;
	};
	auto seq = [sb](char x, char y)
	{
		return sb ? x == y : true;
	};
	if (deq(cd, (*bits)[di]) and seq(cs, (*bits)[si]) and deq(cd2, (*bits)[d2]) and seq(cs2, (*bits)[s2]))
	{
		std::cerr << "no change" << std::endl;
		return;
	}
	if (deq(cd, cpl((*bits)[di])) and seq(cs, cpl((*bits)[si])) and deq(cd2, cpl((*bits)[d2])) and seq(cs2, cpl((*bits)[s2])))
	{
		std::cerr << "cpl" << std::endl;
		cpl_bits(bits);
		return;
	}
	if (deq(cd, (*bits)[d2]) and seq(cs, (*bits)[s2]) and deq(cd2, (*bits)[di]) and seq(cs2, (*bits)[si]))
	{
		std::cerr << "rev" << std::endl;
		rev_bits(bits);
		return;
	}
	if (deq(cd, cpl((*bits)[d2])) and seq(cs, cpl((*bits)[s2])) and deq(cd2, cpl((*bits)[di])) and seq(cs2, cpl((*bits)[si])))
	{
		std::cerr << "rev n cpl" << std::endl;
		rev_bits(bits);
		cpl_bits(bits);
		return;
	}
	std::cerr << "unknown change" << std::endl;
	std::cerr << "di: " << cd << ' ' << (*bits)[di] << std::endl;
	std::cerr << "si: " << cs << ' ' << (*bits)[si] << std::endl;
	std::cerr << "d2: " << cd2 << ' ' << (*bits)[d2] << std::endl;
	std::cerr << "s2: " << cs2 << ' ' << (*bits)[s2] << std::endl;
	std::cerr << (*bits) << std::endl;
}

Idxs find_idxs(Bits* bits)
{
	const auto size = bits->size();
	for (size_t pos = 0; pos < size / 2; pos += 5)
	{
		std::cerr << "idxs " << pos << std::endl;
		for (size_t i = pos; i < pos + 5; ++i)
		{
			readpair_to(i, bits);
		}
		const Idx didx = find_di(*bits);
		const Idx sidx = find_si(*bits);
		if ((didx.b and sidx.b) or pos == size / 2 - 5)
		{
			return {sidx.i, didx.i, sidx.b, didx.b};
		}
	}
	std::cerr << "idxs not found" << std::endl;
	std::cerr << (*bits) << std::endl;
	exit(1);
}

Bits mar_reader(size_t bit_count)
{
	Bits bits(bit_count, '.');
	auto idxs = find_idxs(&bits);
	// const size_t di = idxs.di;
	// const size_t si = idxs.si;
	size_t pos = 0;
	while (true)
	{
		detect(&bits, idxs);
		readpair_to(pos++, &bits);
		readpair_to(pos++, &bits);
		readpair_to(pos++, &bits);
		if (pos >= bit_count / 2)
		{
			break;
		}
	}
	return bits;
}

void runner(size_t n, size_t bit_count)
{
	switch (bit_count)
	{
		case 10:
			repeat(n, [=](size_t)
			{
				Bits bits = simple_read_bits(bit_count);
				std::cout << bits << std::endl;
				char c;
				std::cin >> c;
				cexit(c);
			});
			break;
		case 20:
		case 100:
		default:
			repeat(n, [=](size_t k)
			{
				std::cerr << "Case " << (k+1) << std::endl;
				Bits bits = mar_reader(bit_count);
				std::cerr << bits << std::endl;
				std::cout << bits << std::endl;
				char c;
				std::cin >> c;
				cexit(c);
			});
			break;
	}
}

int main()
{
	size_t n, bit_count;
	std::cin >> n >> bit_count;
	runner(n, bit_count);
}
