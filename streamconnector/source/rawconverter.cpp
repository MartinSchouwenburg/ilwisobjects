/*IlwisObjects is a framework for analysis, processing and visualization of remote sensing and gis data
Copyright (C) 2018  52n North

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "ilwis.h"
#include "rawconverter.h"

using namespace Ilwis;
using namespace Stream;

RawConverter::RawConverter(double low, double high, double step, bool hasUndefs)  {
    _storeType =  minNeededStoreType(low, high, step, hasUndefs);
    _offset = determineOffset(low, high, step, _storeType);
	_scale = step; // MathHelper::roundTo3DecimalDigits(step);
    _undefined = guessUndef();
}

IlwisTypes RawConverter::minNeededStoreType(double low, double high, double step, bool hasUndefs) const{
    double minDivStep;
    double maxDivStep;
    intRange(low, high, step, minDivStep, maxDivStep );

    quint64 delta = rounding(abs(maxDivStep - minDivStep));//TODO change from quint32 to quint64 might change behaviour??
    if ( step != 0) {
        if ( delta <= 255 && !hasUndefs)
            return itUINT8;
        else if ( delta <= 65535)
            return itINT16;
        else if ( delta <= 4294967295){
            return itINT32;
        }
    }
    return itDOUBLE;

}

long RawConverter::rounding(double x) const {
    return (long)floor(x + 0.5);
}

void RawConverter::intRange(double low, double high, double step, double& minDivStep, double& maxDivStep) const {
    minDivStep = low;
    maxDivStep = high;
    if (step > 1e-30) {
        minDivStep /= step;
        maxDivStep /= step;
    }
}

double RawConverter::determineScale(double low, double high, double step) const  {
    double minDivStep;
    double maxDivStep;
    intRange(low, high, step, minDivStep, maxDivStep );
    //int r = log10(abs(maxDivStep - minDivStep)) + 1;
    // try this....
    int r = log10(rounding(abs(maxDivStep - minDivStep)));
    return pow(10,-r);

}

double RawConverter::determineOffset(double low, double high, double step, IlwisTypes st)
{
  if (st == itDOUBLE)
    return 0;
  double minDivStep;
  double maxDivStep;
  intRange(low, high, step, minDivStep, maxDivStep );

  double r0 = 0;
  double r = rounding(minDivStep / 2 + maxDivStep / 2 - 0.0001);
  r0 = r;
  switch (st) {
     case itINT32:
       if (minDivStep < -LONG_MAX || maxDivStep > LONG_MAX)
         r0 = minDivStep / 2 + maxDivStep / 2 - 0.0001;
       else
         r0 =  0;
       break;
     case itINT16:
       if (minDivStep < -SHRT_MAX || maxDivStep > SHRT_MAX)
         r0 = minDivStep / 2 + maxDivStep / 2 - 0.0001;
       else
         r0 = 0;
       break;
     case itUINT8:
       if (minDivStep < 0 || maxDivStep > 255)
         r0 = minDivStep-1;
       else
         r0 = -1;
       break;
  }
  return r0;
}


double RawConverter::guessUndef() {
    if ( _storeType == itINT16)
        return shILW3UNDEF;
    else if ( _storeType == itINT32)
        return iILW3UNDEF;
    if ( _storeType == itFLOAT)
        return flUNDEF;
    return rUNDEF;
}

