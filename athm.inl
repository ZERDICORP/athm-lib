// athm.inl

template<typename TKey, typename TValue>
std::vector<TKey> keys(std::map<TKey, TValue> const& map)
{
	std::vector<TKey> vec;
	for (auto const& element : map)
		vec.push_back(element.first);
	return vec;
}

template<typename TKey, typename TValue>
std::vector<TValue> values(std::map<TKey, TValue> const& map)
{
	std::vector<TValue> vec;
	for (auto const& element : map)
		vec.push_back(element.second);
	return vec;
}

void rand_init()
{
	srand(time(NULL));
}

int rand_int(int iTo)
{
	return rand() % iTo * (iTo / abs(iTo));
}

int rand_int(int iFrom, int iTo)
{
	assert(iTo > iFrom);
	return rand() % (iTo - iFrom + 1) + iFrom;
}

template <typename T>
T rand_choice(std::initializer_list<T> list, int iLen)
{
	int iRandomIndex = rand_int(iLen);
	int iCount = 0;
	for (T item : list)
	{
		if (iCount == iRandomIndex)
			return item;
		iCount++;
	}

}

int find(auto start, auto end, auto callback)
{
	for (auto ptr = start; ptr != end; ++ptr)
		if (callback(*ptr))
			return static_cast<int>(ptr - start);
	return -1;
}

void sort(auto start, auto end, auto callback)
{
	for (auto ptr1 = start; ptr1 != end; ++ptr1)
	{
		for (auto ptr2 = start; ptr2 != end; ++ptr2)
		{
			if (callback(*ptr1, *ptr2))
				{
					auto temp = *ptr1;
					*ptr1 = *ptr2;
					*ptr2 = temp;
				}
		}
	}
}

std::string getCurrentDateTime(std::string format = "%d.%m.%Y %H:%M:%S")
{
	time_t rawtime;
	int iBufferSize = 100;
	char buffer [iBufferSize];

	std::time(&rawtime);
	std::strftime(buffer, iBufferSize, format.c_str(), std::localtime(&rawtime));

	return buffer;
}

bool isFolder(std::string sPath)
{
	DWORD attrib = GetFileAttributes(sPath.c_str());
	if ((attrib & FILE_ATTRIBUTE_DIRECTORY) != 0)
		return true;
	return false;
}

std::vector<std::string> listDir(std::string sDir)
{
	std::vector<std::string> list;

	struct dirent *entry;
	DIR *dp;

	dp = ::opendir(sDir.c_str());
	if (dp == NULL)
	{
		std::cout << "[error]: path \"" << sDir << "\" not found.." << std::endl;
		abort();
	}
	while ((entry = ::readdir(dp)))
		list.push_back(entry -> d_name);
	::closedir(dp);

	delete entry;
	delete dp;

	return list;
}

std::vector<std::string> listFolders(std::string sDir)
{
	std::vector<std::string> list = listDir(sDir);
	for (int i = 0; i < list.size(); ++i)
		if (isFile(sDir + list[i]))
		{
			list.erase(list.begin() + i);
			i--;
		}
	return list;
}

std::vector<std::string> listFiles(std::string sDir)
{
	std::vector<std::string> list = listDir(sDir);
	for (int i = 0; i < list.size(); ++i)
		if (isFolder(sDir + list[i]))
		{
			list.erase(list.begin() + i);
			i--;
		}
	return list;
}

std::string getWinVersion()
{
	if (IsWindows8Point1OrGreater())
		return "8.1+";
	if (IsWindows8OrGreater())
		return "8";
	if (IsWindows7OrGreater())
		return "7";
	if (IsWindowsVistaOrGreater())
		return "Vista";
	if (IsWindowsXPOrGreater())
		return "XP";
	return "Undefined Windows Version";
}

int index(std::string sString, std::string sSubstring)
{
	int iIndex = -1;
	for (int i = 0; i < sString.size(); ++i)
	{
		std::string sSubstringCandidate = "";
		if (i < sString.size() - (sSubstring.size() - 1))
			for (int j = 0; j < sSubstring.size(); ++j)
				sSubstringCandidate += sString[i + j];
		
		if (sSubstringCandidate == sSubstring)
		{
			iIndex = i;
			break;
		}
	}
	return iIndex;
}

std::string replace(std::string sString, std::string sSubstring, std::string sReplacement)
{
	std::string sRes;
	for (int i = 0; i < sString.size(); ++i)
	{
		std::string sSubstringCandidate = "";
	
		if (i < sString.size() - (sSubstring.size() - 1))
			for (int j = 0; j < sSubstring.size(); ++j)
				sSubstringCandidate += sString[i + j];
		
		if (sSubstringCandidate == sSubstring)
		{
			sRes += sReplacement;
			if (sSubstring.size() == 1)
				continue;
			i += sSubstring.size();
		}
		sRes += sString[i];
	}
	return sRes;
}

std::vector<std::string> split(std::string sString, std::string sSeparator)
{
	std::vector<std::string> v;

	std::string sPart;
	for (int i = 0; i < sString.size(); ++i)
	{
		std::string sSeparatorCandidate = "";
		if (i < sString.size() - (sSeparator.size() - 1))
			for (int j = 0; j < sSeparator.size(); ++j)
				sSeparatorCandidate += sString[i + j];
		
		if (sSeparatorCandidate == sSeparator)
		{
			v.push_back(sPart);
			sPart = "";
			i += sSeparator.size() - 1;
		}
		else
			sPart += sString[i];
	}

	v.push_back(sPart);
	return v;
}

char controlCharToChar(char cControlChar)
{
	switch (cControlChar)
	{
		case '\n': return 'n';
		case '\t': return 't';
		case '\a': return 'a';
		case '\0': return '0';
		case '\b': return 'b';
		case '\v': return 'v';
		case '\f': return 'f';
		case '\r': return 'r';
		case '\"': return '"';
	}
}

std::string collapseReps(std::string s)
{
	std::string sRes;

	char cCurrent = s[0];

	int iRepetitions = 0;

	for (int i = 0; i < s.size(); ++i, iRepetitions++)
	{
		if (i == s.size() - 1)
		{
			if (s[i] == s[i - 1])
				sRes += std::to_string(iRepetitions + 1) + s[i];
			else
			{
				sRes += std::to_string(iRepetitions) + s[i - 1];
				sRes += s[i];
			}
			break;
		}

		if (iRepetitions > 2 && s[i] != cCurrent)
		{
			sRes += std::to_string(iRepetitions) + cCurrent;
			cCurrent = s[i];
			iRepetitions = 0;
		}
		else if (iRepetitions <= 2 && s[i] != cCurrent)
		{
			sRes += std::string(iRepetitions, cCurrent);
			cCurrent = s[i];
			iRepetitions = 0;
		}
	}

	return sRes;
}

std::string expandReps(std::string s)
{
	std::string sRes;
	std::string sNumber;

	for (int i = 0; i < s.size(); ++i)
	{
		if (zer::athm::isInt(s[i]))
			sNumber += s[i];
		else
			if (zer::athm::isInt(s[i - 1]))
			{
				sRes += std::string(stoi(sNumber), s[i]);
				sNumber = "";
			}
			else
				sRes += s[i];
	}

	return sRes;
}

float getDistanceToFirstVerticalIntersection(int iPX, int iMX, float fCosAlpha, int iSqW)
{
	int iAX = fCosAlpha >= 0 ? iMX + iSqW : iMX; // if we look right, when x > 0
	return float((iAX - iPX) / fCosAlpha);
}

float getDistanceToFirstHorizontalIntersection(int iPY, int iMY, float fSinAlpha, int iSqW)
{
	int iAY = fSinAlpha >= 0 ? iMY + iSqW : iMY; // if we look down, when y > 0
	return float((iAY - iPY) / fSinAlpha);
}

Dist dda(int iPlayerY, int iPlayerX, float fAlpha, int iSqW)
{
	float fSinAlpha = sin(fAlpha);
	float fCosAlpha = cos(fAlpha);

	int iMY = int(iPlayerY / iSqW) * iSqW;
	int iMX = int(iPlayerX / iSqW) * iSqW;

	float fFirstHorizontalIntersection = getDistanceToFirstHorizontalIntersection(iPlayerY, iMY, fSinAlpha, iSqW);
	float fFirstVerticalIntersection = getDistanceToFirstVerticalIntersection(iPlayerX, iMX, fCosAlpha, iSqW);

	return {fFirstHorizontalIntersection, fFirstVerticalIntersection};
}

bool isInt(char chr)
{
	char ints[10]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	for (int i = 0; i < 10; ++i)
		if (chr == ints[i])
			return true;
	return false;
}

bool isNumber(std::string str)
{
	if (str.size() > 1 && str[0] == '0')
		if (str[1] != '.')
			return false;

	int iDotsCount = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '.')
			iDotsCount++;
		else if (!isInt(str[i]))
			return false;
		if (iDotsCount > 1)
			return false;
	}
	return true;
}