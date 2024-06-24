#ifndef MATHUTIL_H
#define MATHUTIL_H
#include "util_global.h"
#include <QPointF>
#include <QRectF>

class UTIL_EXPORT MathUtil {
public:
    // 比较double值， d1<d2返回-1,  d1==d2返回0,  d1>d2返回1
    static int compare(double d1, double d2, double dEsp = 1e-6);
    static bool compare(const QPointF& pt1, const QPointF& pt2, double dEsp = 1e-6);
    // 两点围成的矩形
    static QRect buildRect(const QPointF& pt1, const QPointF& pt2);
    // 合并rect
    static QRectF mergeRect(const QVector<QRectF>& rects);
    static bool isPointInRect(const QPointF& pt, const QRectF& rect);
    static double getCross(QPointF p1, QPointF p2, QPointF p);
    static bool isPointInMatrix(QPointF p1, QPointF p2, QPointF p3, QPointF p4, QPointF p);
    static double vectorDotProduct(QPointF pt, QPointF linePt1, QPointF linePt2);
    // 获取两点之间的距离
    static double distance(const QPointF& pt1, const QPointF& pt2);
};

#endif // MATHUTIL_H
