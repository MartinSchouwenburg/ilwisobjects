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

#ifndef COLORRANGE_H
#define COLORRANGE_H

#include <QColor>

namespace Ilwis{

class ColorItem;
class DomainItem;
class Domain;
typedef QSharedPointer<ColorItem> SPColorItem;
typedef QSharedPointer<DomainItem> SPDomainItem;
typedef IlwisData<Domain> IDomain;

struct KERNELSHARED_EXPORT LocalColor {
    quint8 _component1=0;
    quint8 _component2=0;
    quint8 _component3=0;
    quint8 _component4=0;
} ;


class KERNELSHARED_EXPORT ColorRangeBase
{
public:
    enum ColorModel{cmNONE, cmRGBA, cmHSLA, cmCYMKA, cmGREYSCALE};

    ColorRangeBase(IlwisTypes tp, ColorModel clrmodel);
    ColorModel defaultColorModel() const;
    void defaultColorModel(ColorModel m);

    static QColor toColor(quint64 clrint, ColorModel clrModel) ;
    static QColor toColor(const QVariant &v, ColorModel colormodel);
    static QString toString(const QColor& clr, ColorModel clrModel);
    static const QStringList& defaultColorNames() ;
    static QColor defaultColor(const QString& name) ;
    static QColor defaultColor(int index) ;

protected:
    void storeColor(const QColor &clr, QDataStream& stream) const;
    void loadColor(QColor &clr, QDataStream &stream);
private:
    static void init();
    IlwisTypes _valuetype;
    ColorModel _defaultModel = cmRGBA;
    static QStringList _defaultColorNames;

};

class KERNELSHARED_EXPORT ContinuousColorRange  : public Range, public ColorRangeBase{
public:
    ContinuousColorRange();
    ContinuousColorRange(const QColor& clr1, const QColor& clr2=QColor("#FFFFFF"), ColorModel colormodel=ColorRangeBase::cmRGBA);
    bool isValid() const;
    QString toString() const;
    Range *clone() const;
    QVariant ensure(const QVariant& v, bool inclusive = true) const;
    bool contains(const QVariant& v, bool inclusive = true) const;
    bool contains(const Range *v, bool inclusive = true) const;
    QVariant impliedValue(const QVariant& v) const;
    IlwisTypes valueType() const;
    static QColor valueAt(double &index, const Ilwis::Range *rng);
    static QString valueAsString(double &index, const Range *rng);
    quint32 count() const;
    QColor limitColor1() const;
    QColor limitColor2() const;
    void add(const QVariant& v);
    void store(QDataStream& stream)  const;
    void load(QDataStream& stream);
    void clear();
private:
    QColor _limit1;
    QColor _limit2;
};

class KERNELSHARED_EXPORT ColorPalette : public ItemRange, public ColorRangeBase  {
public:
    ColorPalette();
	ColorPalette(const QString& definition);

    QVariant impliedValue(const QVariant& v) const;

    SPDomainItem item(quint32 raw) const;
    SPDomainItem item(const QString &nam, int itemIndex = iUNDEF) const;
    SPDomainItem itemByOrder(quint32 index) const;
    QColor color(int index) const;
    QString toString() const;
    Range *clone() const;

    void add(DomainItem *item);
    void add(SPDomainItem item);
    void add(const QVariant& color);
    void remove(const QString& nm);
    void clear();

    bool contains(const QVariant& color, bool inclusive = true) const;
    bool contains(SPRange rng, bool inclusive=true) const;
    bool contains(Ilwis::Range *rng, bool inclusive=true) const;

    QVariant ensure(const QVariant& v, bool inclusive = true) const;
    quint32 count() const;
    IlwisTypes valueType() const;
    static QColor valueAt(quint32 index, const Ilwis::Range *rng);
    static QString valueAsString(quint32 index, const Range *rng);

    bool isValid() const;

    qint32 gotoIndex(qint32 index, qint32 step) const;
    bool alignWithParent(const IDomain &dom);
    void store(QDataStream& stream)  const;
    void load(QDataStream& stream);

private:
    std::vector<SPColorItem> _colors;

};


}

#endif // COLORRANGE_H
