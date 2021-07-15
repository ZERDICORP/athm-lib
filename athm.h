// athm.h

#include <cmath>
#include <random.h>
#include <str.h>

#define mPi 3.14159265359
#define mDoublePi mPi * 2
#define mG 6.674184 * pow(10, -11)

#ifndef ZER__ATHM_MODEL
	#define ZER__ATHM_MODEL
		namespace zer
		{
			namespace athm
			{
				inline char controlCharToChar(char cControlChar);

				inline std::string repetitionInterpretation(std::string s);
				inline std::string reverseRepetitionInterpretation(std::string s);

				struct Separator
				{
					std::string sDot =  "[";
					std::string sIntCode = "]";
					std::string sGlobalSep = "|";
				};
				
				inline std::string encrypt(std::string sText, unsigned long ulKey, Separator separator);
				inline std::string decrypt(std::string sCode, int iKey, Separator separator);

				struct Dist
				{
					float fHorizontal;
					float fVertical;
				};

				inline Dist dda(int iPlayerY, int iPlayerX, float fAlpha, int iSqW);

				inline double gravityForce(long double ldM1, long double ldM2, long double ldR) {return mG * ((ldM1 * ldM2) / pow(ldR, 2));}

				inline float getDistanceToFirstVerticalIntersection(int iPX, int iMX, float fCosAlpha, int iSqW);
				inline float getDistanceToFirstHorizontalIntersection(int iPY, int iMY, float fSinAlpha, int iSqW);
				inline float toRadians(float fDegree) {return fDegree * (mPi / 180);}
				inline float toDegrees(float fRadians) {return fRadians / (mPi / 180);}
				inline float getAngleToPoint(float fY1, float fX1, float fY2, float fX2) {return toRadians(180 / mPi * atan2f(fX1 - fX2, fY1 - fY2)) + toRadians(90);}
				inline float getHypot(float iFromY, float iFromX, float iToY, float iToX) {return sqrt(pow(abs(iFromY - iToY), 2) + pow(abs(iFromX - iToX), 2));}
				inline float sign(float f) {return f / abs(f);}

				inline bool isInt(char chr);
				inline bool isNumber(std::string str);
				inline bool pointInside2dMatrix(int fMatrixHeight, int fMatrixWidth, float fY, float fX) {return ((fY >= 0 && fY < fMatrixHeight) && (fX >= 0 && fX < fMatrixWidth));}

				#include "athm.inl"
			};
		};
#endif