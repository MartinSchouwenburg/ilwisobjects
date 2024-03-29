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

#ifndef RANGEITERATOR_H
#define RANGEITERATOR_H

namespace Ilwis {
template<typename OutputType, typename RangeType> class RangeIterator
{
public:
    RangeIterator(const Range* range) : _range(range), _current(0){
        quint32 temp = 0;
        RangeType::valueAt(temp, _range);
        if ( temp == iUNDEF)
            _current = iUNDEF;
    }

    RangeIterator(const RangeIterator& iter){
        _range = iter._range;
        _current = iter._current;
    }

    RangeIterator& operator=(const RangeIterator& iter){
        _range = iter._range;
        _current = iter._current;
		
		return *this;
    }

    RangeIterator& operator++(){
        ++_current;
        checkRange();
        return *this;
    }

    RangeIterator& operator--(){
        if ( isValid()){
            if ( _current > 0)
                --_current;
        }
        return *this;
    }

    RangeIterator& operator+=(int n){
        if ( isValid())
            _current += n;
        return *this;
    }

    RangeIterator& operator-=(int n){
        if ( isValid()){
            if ( _current < n)
                _current = 0;
            else
                _current -= n;
        }

        return *this;
    }

    OutputType operator[](quint32 n){
        quint32 temp = n;
        return  RangeType::valueAt(temp, _range);
    }

    QString toString() const{
        return RangeType::valueAsString(_current, _range);
    }

    bool operator>(const RangeIterator& iter){
        if ( !isValid())
            return false;

        if ( iter._range != _range)
            return false;
        return _current > iter._current;
    }

    bool operator<(const RangeIterator& iter){
        if ( !isValid())
            return false;

        if ( iter._range != _range)
            return false;
        return _current < iter._current;
    }

    bool operator>=(const RangeIterator& iter){
        if ( !isValid())
            return false;

        if ( iter._range != _range)
            return false;
        return _current >= iter._current;
    }

    bool operator<=(const RangeIterator& iter){
        if ( !isValid())
            return false;

        if ( iter._range != _range)
            return false;
        return _current <= iter._current;
    }

    bool operator==(const RangeIterator& iter){
        if ( !isValid())
            return true;

        if ( isNumericalUndef(_current) || isNumericalUndef(iter._current))
            return false;
        if ( iter._range != _range)
            return false;
        if ( _current >= iter._range->count()) // end condition
            return true;
        return _current == iter._current;
    }

    bool operator!=(const RangeIterator& iter){
        return !operator==(iter);
    }

    bool isValid() const{
        return _current != iUNDEF;
    }
    OutputType operator*() const{
        return RangeType::valueAt(_current, _range);
    }

    OutputType operator*() {
        return RangeType::valueAt(_current, _range);
    }

    quint32 current() const{
        return _current;
    }

private:
    const Range *_range;
    quint32 _current;

    void checkRange(){
        RangeType::valueAt(_current, _range);
    }
};
template<typename OutputType, typename RangeType>  RangeIterator<OutputType, RangeType> operator+(const RangeIterator<OutputType, RangeType>& iter, int n) {
    RangeIterator<OutputType, RangeType> iterTemp(iter);
    iterTemp += n;
    return iterTemp;
}

template<typename OutputType, typename RangeType>  RangeIterator<OutputType, RangeType> operator-(const RangeIterator<OutputType, RangeType>& iter, int n) {
    RangeIterator<OutputType, RangeType> iterTemp(iter);
    iterTemp -= n;
    return iterTemp;
}

template<typename OutputType, typename RangeType>  RangeIterator<OutputType, RangeType> operator+(int n,const RangeIterator<OutputType, RangeType>& iter) {
    RangeIterator<OutputType, RangeType> iterTemp(iter);
    iterTemp += n;
    return iterTemp;
}

template<typename OutputType, typename RangeType>  RangeIterator<OutputType, RangeType> operator-(int n,const RangeIterator<OutputType, RangeType>& iter) {
    RangeIterator<OutputType, RangeType> iterTemp(iter);
    iterTemp = n - iterTemp;
    return iterTemp;
}
}






#endif // RANGEITERATOR_H
