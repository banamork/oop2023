#include <gtest/gtest.h>

#include <unordered_map/unordered_map.hpp>

using namespace vaa;

TEST(INSERT_ONE_INT, GetTest)
{
	unordered_map<int, int> m;
	for (int i = 0; i < 5; i++)
	{
		m.insert({ i, i });
	}
	auto it = m.begin();
	ASSERT_EQ(4, it->first);
	ASSERT_EQ(4, it->second);
	it++;
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(1, it->second);
	++it;
	ASSERT_EQ(0, it->first);
	ASSERT_EQ(0, it->second);
	it++;
	ASSERT_EQ(3, it->first);
	ASSERT_EQ(3, it->second);
	++it;
	ASSERT_EQ(2, it->first);
	ASSERT_EQ(2, it->second);
}

TEST(INSERT_ONE_CHAR, GetTest)
{
	unordered_map<char, char> map;
	for (int i = 0; i < 5; i++)
	{
		char str = i + 'a';
		map.insert({ str, str });
	}
	auto it = map.begin();
	ASSERT_EQ('e', it->first);
	ASSERT_EQ('e', it->second);
	it++;
	ASSERT_EQ('c', it->first);
	ASSERT_EQ('c', it->second);
	++it;
	ASSERT_EQ('d', it->first);
	ASSERT_EQ('d', it->second);
	it++;
	ASSERT_EQ('a', it->first);
	ASSERT_EQ('a', it->second);
	++it;
	ASSERT_EQ('b', it->first);
	ASSERT_EQ('b', it->second);
}

TEST(INSERT_TWO, GetTest)
{
	unordered_map<std::string, std::string> m;
	std::string str = "a";
	m.insert({std::move(str) , "a" });
	auto it = m.begin();
	ASSERT_EQ("a", it->first);
	ASSERT_EQ("a", it->second);
}

TEST(INSERT_THREE, GetTest)
{
	unordered_map<double, double> m;
	std::initializer_list<std::pair<double, double>> l = { {1.0, 2.3}, {4.5, 6.7} };
	m.insert(l);
	auto it = m.begin();
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(2.3, it->second);
	it++;
	ASSERT_EQ(4.5, it->first);
	ASSERT_EQ(6.7, it->second);
}

TEST(Emplace, GetTest)
{
	unordered_map<int, int> m;
	for (int i = 0; i < 5; i++)
	{
		m.emplace(i, i);
	}
	auto it = m.begin();
	ASSERT_EQ(4, it->first);
	ASSERT_EQ(4, it->second);
	it++;
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(1, it->second);
	++it;
	ASSERT_EQ(0, it->first);
	ASSERT_EQ(0, it->second);
	it++;
	ASSERT_EQ(3, it->first);
	ASSERT_EQ(3, it->second);
	++it;
	ASSERT_EQ(2, it->first);
	ASSERT_EQ(2, it->second);

	
	unordered_map<char, char> map;
	for (int i = 0; i < 5; i++)
	{
		char str = i + 'a';
		map.emplace(str, str);
	}
	auto i = map.begin();
	ASSERT_EQ('e', i->first);
	ASSERT_EQ('e', i->second);
	i++;
	ASSERT_EQ('c', i->first);
	ASSERT_EQ('c', i->second);
	++i;
	ASSERT_EQ('d', i->first);
	ASSERT_EQ('d', i->second);
	i++;
	ASSERT_EQ('a', i->first);
	ASSERT_EQ('a', i->second);
	++i;
	ASSERT_EQ('b', i->first);
	ASSERT_EQ('b', i->second);
}

TEST(FIND, GetTest)
{
	unordered_map<int, int> m;
	for (int i = 0; i < 5; i++)
	{
		m.emplace(i, i);
	}
	auto it = m.find(4);
	ASSERT_EQ(4, it->second);
	auto i = m.find(5);
	ASSERT_TRUE(i == m.end());
}

TEST(AT, GetTest)
{
	unordered_map<int, int> m;
	for (int i = 0; i < 5; i++)
	{
		m.emplace(i, i);
	}
	auto it = m.at(4);
	ASSERT_EQ(4, it);
	ASSERT_THROW(m.at(5), std::out_of_range);
}

TEST(Clear, GetTest)
{
	unordered_map<char, char> map;
	for (int i = 0; i < 5; i++)
	{
		char str = i + 'a';
		map[str] = str;
	}
	auto i = map.begin();
	ASSERT_EQ('e', i->first);
	i++;
	++i;
	ASSERT_EQ('d', i->first);
	i++;
	ASSERT_EQ('a', i->first);
	++i;
	ASSERT_EQ('b', i->first);
	unordered_map<std::string, std::string> s;
	std::string str = "a";
	s["a"] = std::move(str);
	auto it = s.cbegin();
	ASSERT_EQ("a", it->first);
	ASSERT_EQ("a", it->second);
	map.clear();
	ASSERT_EQ(0, map.size());
	ASSERT_EQ(true, map.empty());
}

TEST(operators, GetTest)
{
	unordered_map<char, char> map;
	for (int i = 0; i < 5; i++)
	{
		char str = i + 'a';
		map[str] =  str;
	}
	auto i = map.begin();
	ASSERT_EQ('e', i->first);
	i++;
	++i;
	ASSERT_EQ('d', i->first);
	i++;
	ASSERT_EQ('a', i->first);
	++i;
	ASSERT_EQ('b', i->first);
	unordered_map<std::string, std::string> s;
	std::string str = "a";
	s["a"] = std::move(str);
	auto it = s.cbegin();
	ASSERT_EQ("a", it->first);
	ASSERT_EQ("a", it->second);
}

TEST(Erase, GetTest)
{
	unordered_map<int, int> m;
	for (int i = 0; i < 5; i++)
	{
		m.insert({ i, i });
	}
	auto it = m.begin();
	ASSERT_EQ(4, it->first);
	ASSERT_EQ(4, it->second);
	it++;
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(1, it->second);
	++it;
	ASSERT_EQ(0, it->first);
	ASSERT_EQ(0, it->second);
	it++;
	ASSERT_EQ(3, it->first);
	ASSERT_EQ(3, it->second);
	++it;
	ASSERT_EQ(2, it->first);
	ASSERT_EQ(2, it->second);
	ASSERT_EQ(5, m.size());
	for (int i = 0; i < 5; i++)
	{
		m.erase(i);
	}
	ASSERT_EQ(0, m.size());
}

TEST(for_const, GetTest)
{
	unordered_map<int, int> m;
	for (int i = 0; i < 5; i++)
	{
		m.insert({ i, i });
	}
	for (auto it = m.cbegin(); it != m.cend(); it++)
	{
	}
}


TEST(Copy, GetTest)
{
	unordered_map<int, int> map;
	for (int i = 0; i < 5; i++)
	{
		map.insert({ i, i });
	}
	unordered_map<int, int> m(map);
	auto it = m.begin();
	ASSERT_EQ(4, it->first);
	ASSERT_EQ(4, it->second);
	it++;
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(1, it->second);
	++it;
	ASSERT_EQ(0, it->first);
	ASSERT_EQ(0, it->second);
	it++;
	ASSERT_EQ(3, it->first);
	ASSERT_EQ(3, it->second);
	++it;
	ASSERT_EQ(2, it->first);
	ASSERT_EQ(2, it->second);

	unordered_map<int, int> n;
	auto i = n.cbegin();
	n.insert({ 1, 3 });
	n.erase(1);
	n = m;
	auto k = n.begin();
	ASSERT_EQ(4, k->first);
	ASSERT_EQ(4, k->second);
	k++;
	ASSERT_EQ(1, k->first);
	ASSERT_EQ(1, k->second);
	++k;
	ASSERT_EQ(0, k->first);
	ASSERT_EQ(0, k->second);
	k++;
	ASSERT_EQ(3, k->first);
	ASSERT_EQ(3, k->second);
	++k;
	ASSERT_EQ(2, k->first);
	ASSERT_EQ(2, k->second);
}

TEST(Move, GetTest)
{
	unordered_map<int, int> map;
	for (int i = 0; i < 5; i++)
	{
		map.insert({ i, i });
	}
	unordered_map<int, int> m(std::move(map));
	auto it = m.begin();
	ASSERT_EQ(4, it->first);
	ASSERT_EQ(4, it->second);
	it++;
	ASSERT_EQ(1, it->first);
	ASSERT_EQ(1, it->second);
	++it;
	ASSERT_EQ(0, it->first);
	ASSERT_EQ(0, it->second);
	it++;
	ASSERT_EQ(3, it->first);
	ASSERT_EQ(3, it->second);
	++it;
	ASSERT_EQ(2, it->first);
	ASSERT_EQ(2, it->second);

	unordered_map<int, int> n;
	auto i = n.cbegin();
	n.insert({ 1, 3 });
	n.erase(1);
	n = std::move(m);
	auto k = n.begin();
	ASSERT_EQ(4, k->first);
	ASSERT_EQ(4, k->second);
	k++;
	ASSERT_EQ(1, k->first);
	ASSERT_EQ(1, k->second);
	++k;
	ASSERT_EQ(0, k->first);
	ASSERT_EQ(0, k->second);
	k++;
	ASSERT_EQ(3, k->first);
	ASSERT_EQ(3, k->second);
	++k;
	ASSERT_EQ(2, k->first);
	ASSERT_EQ(2, k->second);
}