// athm.inl

char controlCharToChar(char cControlChar)
{
	switch (cControlChar)
	{
		case '\n':
			return 'n';
		case '\t':
			return 't';
		case '\a':
			return 'a';
		case '\0':
			return '0';
		case '\b':
			return 'b';
		case '\v':
			return 'v';
		case '\f':
			return 'f';
		case '\r':
			return 'r';
		case '\"':
			return '"';
	}
}

std::string repetitionInterpretation(std::string s)
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

std::string reverseRepetitionInterpretation(std::string s)
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

std::string encrypt(std::string sText, unsigned long ulKey, Separator separator)
{
	int iKeyLength = std::to_string(ulKey).size();

	std::string sResult;

	for (int i = 0; i < sText.size(); ++i)
	{
		int iCodeNumber = (int)sText[i];
		int iStartFake = zer::rnd::randi(1, 9);
		int iEndFake = zer::rnd::randi(0, 9);
		
		unsigned long ul = iCodeNumber * ulKey;
		unsigned long ul2 = ul / iKeyLength;
		unsigned long ul3 = (ul2 + (iEndFake * iKeyLength - iEndFake)) * iStartFake + ul % ul2;

		std::string sRes = std::to_string(iStartFake) + std::to_string(ul3) + std::to_string(abs(iEndFake - iStartFake));
		std::string sIntCode;

		for (int j = 0; j < sRes.size(); ++j)
		{
			for (int k = 0; k < stoi(std::string(1, sRes[j])); ++k, sIntCode += separator.sDot);
			sIntCode += separator.sIntCode;
		}

		sIntCode.erase(sIntCode.size() - 1, 1);

		sResult += sIntCode + separator.sGlobalSep;
	}

	sResult.erase(sResult.size() - 1, 1);

	return sResult;
}

std::string decrypt(std::string sCode, int iKey, Separator separator)
{
	int iKeyLength = std::to_string(iKey).size();

	std::string sResult;
	zer::row<std::string> rIntCodes = zer::str::split(sCode, separator.sGlobalSep);

	for (int i = 0; i < rIntCodes.len(); ++i)
	{
		zer::row<std::string> rDots = zer::str::split(rIntCodes[i], separator.sIntCode);
		
		std::string sNumber;
		for (int j = 0; j < rDots.len(); ++j)
			sNumber += std::to_string(rDots[j].size());

		int iStartFake = stoi(std::string(1, sNumber[0]));
		int iEndFake = stoi(std::string(1, sNumber[sNumber.size() - 1])) + iStartFake;

		sNumber.erase(0, 1);
		sNumber.erase(sNumber.size() - 1, 1);
		
		double dNumber = stod(sNumber);
		int iRes = round((((dNumber - (iEndFake * iKeyLength - iEndFake)) * iKeyLength) / iKey) / iStartFake);
		
		sResult += (char)iRes;
	}

	return sResult;
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