#ifndef rgb_hsiH
#define rgb_hsiH

#include <math.h>
#include <algorithm>

// HIS 컬러 모델은 색상(Hue), 채도(Saturation), 명도(Intensity)


//inline void HSI2RGB(double h, double s, double i, double* r, double* g, double* b)
//{
//	double x = i * (1 - s);
//	if(h < 2 * M_PI / 3)
//	{
//		double y = i * (1 + (s * cos(h)) / (cos(M_PI / 3 - h)));
//		double z = 3 * i - (x + y);
//		*b = x; *r = y; *g = z;
//	}
//	else if(h < 4 * M_PI / 3)
//	{
//		double y = i * (1 + (s * cos(h - 2 * M_PI / 3)) / (cos(M_PI / 3 - (h  - 2 * M_PI / 3))));
//		double z = 3 * i - (x + y);
//		*r = x; *g = y; *b = z;
//	}
//	else
//	{
//		double y = i * (1 + (s * cos(h - 4 * M_PI / 3)) / (cos(M_PI / 3 - (h  - 4 * M_PI / 3))));
//		double z = 3 * i - (x + y);
//		*r = z; *g = x; *b = y;
//	}
//}
//
//inline void RGB2HSI(double r, double g, double b, double* h, double* s, double* i)
//{
//   	*i = (r + g + b) / 3.0;
//
//	double rn = r / (r + g + b);
//	double gn = g / (r + g + b);
//	double bn = b / (r + g + b);
//
//	*h = acos((0.5 * ((rn - gn) + (rn - bn))) / (sqrt((rn - gn) * (rn - gn) + (rn - bn) * (gn - bn))));
//	if(b > g)
//	{
//		*h = 2 * M_PI - *h;
//	}
//
//	*s = 1 - 3 * std::min(rn, std::min(gn, bn));
//}

#define RINT(x)	( (x)-floor(x)>0.5? ceil(x) : floor(x) )

inline void RGB_to_HSI(double R, double G, double B, double &H, double &S, double &I)
{
    if (R < 0 || R > 255 || G < 0 || G > 255 || B < 0 || B > 255) {
        return;
    }

    // find out the min, mid, and max of R, G, B
    double dMin, dMid, dMax;
    if (R > G && R > B) {
        dMax = R;
        dMid = std::max(G, B);
        dMin = std::min(G, B);
    }
    else {
        if (G > B) {
            dMax = G;
            dMid = std::max(R, B);
            dMin = std::min(R, B);
        }
        else {
            dMax = B;
            dMid = std::max(R, G);
            dMin = std::min(R, G);
        }
    }

    I = dMax / 255;
    S = 0;
    H = 0;
    if (I == 0 || dMax == dMin) {
        // this is a black image or grayscale image
        S = 0;
        H = 0;
    }
    else {
        S = (I - dMin / 255) / I;
        // domains are 60 degrees of
        // red, yellow, green, cyan, blue or magenta
        double domainBase = 0.0;
        double oneSixth = 1.0 / 6.0;
        double domainOffset = ((dMid - dMin) / (dMax - dMin)) / 6.0;

        if (R == dMax) {
            if (dMid == G) { // green is ascending
                domainBase = 0; // red domain
            }
            else { // blue is descending
                domainBase = 5.0 / 6.0; // magenta domain
                domainOffset = oneSixth - domainOffset;
            }
        }
        else {
            if (G == dMax) {
                if (dMid == B) { // blue is ascending
                    domainBase = 2.0 / 6.0; // green domain
                }
                else { // red is ascending
                    domainBase = 1.0 / 6.0; // yellow domain
                    domainOffset = oneSixth - domainOffset;
                }
            }
            else {
                if (dMid == R) { // red is ascending
                    domainBase = 4.0 / 6.0; // blue domain
                }
                else { // green is descending
                    domainBase = 3.0 / 6.0; // cyan domain
                    domainOffset = oneSixth - domainOffset;
                }
            }
        }
        H = domainBase + domainOffset;
    }
}

inline void HSI_to_RGB(double H, double S, double I, double &R, double &G, double &B)
{
    // HSI to RGB
    if (H < 0 || H > 1 || S < 0 || S > 1) {
        return;
    }

    if (I == 0.0) {
        // black image
        R = G = B = 0;
    }
    else {
        if (S == 0.0) {
            // grayscale image
            R = G = B = I;
        }
        else {
            double domainOffset = 0.0;
            if (H < 1.0 / 6.0) { // red domain; green acending
                domainOffset = H;
                R = I;
                B = I * (1 - S);
                G = B + (I - B) * domainOffset * 6;
            }
            else {
                if (H < 2.0 / 6) { // yellow domain; red acending
                    domainOffset = H - 1.0 / 6.0;
                    G = I;
                    B = I * (1 - S);
                    R = G - (I - B) * domainOffset * 6;
                }
                else {
                    if (H < 3.0 / 6) { // green domain; blue descending
                        domainOffset = H - 2.0 / 6;
                        G = I;
                        R = I * (1 - S);
                        B = R + (I - R) * domainOffset * 6;
                    }
                    else {
                        if (H < 4.0 / 6) { // cyan domain, green acsending
                            domainOffset = H - 3.0 / 6;
                            B = I;
                            R = I * (1 - S);
                            G = B - (I - R) * domainOffset * 6;
                        }
                        else {
                            if (H < 5.0 / 6) { // blue domain, red ascending
                                domainOffset = H - 4.0 / 6;
                                B = I;
                                G = I * (1 - S);
                                R = G + (I - G) * domainOffset * 6;
                            }
                            else { // magenta domain, blue descending
                                domainOffset = H - 5.0 / 6;
                                R = I;
                                G = I * (1 - S);
                                B = R - (I - G) * domainOffset * 6;
                            }
                        }
                    }
                }
            }
        }
    }

    R = RINT(R * 255);
    G = RINT(G * 255);
    B = RINT(B * 255);

}








#endif
