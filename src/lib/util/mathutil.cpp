#include "mathutil.h"
#include <QVector2D>
#include <QVector2D>

int MathUtil::compare(double d1, double d2, double dEsp)
{
    if (d1 > d2 + dEsp)
        return 1;
    else if (d2 > d1 + dEsp)
        return -1;
    return 0;
}

bool MathUtil::compare(const QPointF& pt1, const QPointF& pt2, double dEsp)
{
    if (compare(pt1.x(), pt2.x(), dEsp) != 0)
        return false;
    if (compare(pt1.y(), pt2.y(), dEsp) != 0)
        return false;
    return true;
}

QRect MathUtil::buildRect(const QPointF& pt1, const QPointF& pt2)
{
    double minX = std::min(pt1.x(), pt2.x());
    double minY = std::min(pt1.y(), pt2.y());
    double maxX = std::max(pt1.x(), pt2.x());
    double maxY = std::max(pt1.y(), pt2.y());
    return QRect(minX, minY, maxX - minX, maxY - minY);
}

double MathUtil::getCross(QPointF p1, QPointF p2, QPointF p)
{
    return (p2.x() - p1.x()) * (p.y() - p1.y()) - (p.x() - p1.x()) * (p2.y() - p1.y());
}

bool MathUtil::isPointInMatrix(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF p)
{
    return (getCross(p1, p2, p) * getCross(p3, p4, p) >= 0) && (getCross(p2, p3, p) * getCross(p4, p1, p) >= 0);
}

double MathUtil::vectorDotProduct(QPointF pt1, QPointF pt2, QPointF basePt)
{
    return QVector2D::dotProduct(QVector2D(pt1 - basePt), QVector2D(pt2 - basePt).normalized());
}

double MathUtil::distance(const QPointF& pt1, const QPointF& pt2)
{
    return QVector2D(pt1 - pt2).length();
}
