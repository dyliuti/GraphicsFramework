#include "imageutil.h"
#include "fileutil.h"

#include <QCollator>
#include <QColorSpace>
#include <QColor>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QFileInfoList>
#include <QImage>
#include <QImageReader>
#include <QStandardPaths>
//#include <libPNG/png.h>
#include <math.h>

const QString c_strPngSuffix = QStringLiteral("png");

//遍历所有的png文件，修改成前缀+下划线+三位索引+.png的形式
struct StandardPngFileInfo
{
    typedef std::shared_ptr<StandardPngFileInfo> ptr;
    QString strFilePath;
    QString strFileName;
    QString strBaseName;
    int nIndex = -1;
};

QImage ImageUtil::loadFromFile(const QString& strFilePath, bool convertColorSpaceToRGB)
{
    QImage img(strFilePath);
    if (convertColorSpaceToRGB && !img.isNull())
    {
        //        const auto& oriColorSpace = img.colorSpace();
        //sRGB转换成RGB
        //        if (oriColorSpace.primaries() == QColorSpace::Primaries::SRgb)
        //        {
        //            img.setColorSpace(QColorSpace(QColorSpace::AdobeRgb));
        //        }
        img.setColorSpace(QColorSpace());
    }
    return img;
}

// FM_MAKEUP_CODING QT 美妆导入图片时,剪裁图片
QImage ImageUtil::clipImageWithEmptyPixel(QImage& src, int padding, QRect& clipRect)
{
    int left = src.width();
    int top = src.height();
    int right = 0;
    int bottom = 0;

    for (int i = 0; i < src.width(); i++)
    {
        for (int j = 0; j < src.height(); j++)
        {
            if (qAlpha(src.pixel(i, j)) > 0)
            {
                if (i < left)
                {
                    left = i;
                }
                if (j < top)
                {
                    top = j;
                }
                if (i > right)
                {
                    right = i;
                }
                if (j > bottom)
                {
                    bottom = j;
                }
            }
        }
    }

    left = static_cast<int>(fmax(0, left - padding));
    top = static_cast<int>(fmax(0, top - padding));
    right = static_cast<int>(fmin(src.width() - 1, right + padding));
    bottom = static_cast<int>(fmin(src.height() - 1, bottom + padding));

    if (right < left || bottom < top)
    {
        return QImage();
    }
    clipRect.setLeft(left);
    clipRect.setTop(top);
    clipRect.setRight(right);
    clipRect.setBottom(bottom);

    return src.copy(left, top, (right - left + 1), (bottom - top + 1));
}

QSize ImageUtil::getImageSize(const QString& imagePath)
{
    if (!QFile::exists(imagePath))
    {
        return { 0, 0 };
    }
    return QImageReader(imagePath).size();
}

QString ImageUtil::getFormat(const QString& imagePath)
{
    return QImageReader(imagePath).format();
}

bool ImageUtil::isPngFormat(const QString& imagePath)
{
    return getFormat(FileUtil::removeFilePrefix(imagePath)).compare("png", Qt::CaseInsensitive) == 0;
}


bool ImageUtil::isValidPngFile(const QString& strFilePath)
{
    if (!strFilePath.endsWith(".png", Qt::CaseInsensitive))
        return false;
    if (FileUtil::isDir(strFilePath))
        return false;
    QFileInfo fileInfo(strFilePath);
    if (fileInfo.isHidden())
        return false;
    return true;
}

QString ImageUtil::removeRedundancePngSuffix(const QString& strFileName)
{
    QString strResult = strFileName;
    static const QString& reduranceSuffix = ".png.png";
    while (strResult.endsWith(reduranceSuffix, Qt::CaseInsensitive))
    {
        strResult = strResult.left(strResult.size() - 4);
    }
    return strResult;
}

bool ImageUtil::renameImage(const QString& strImagePath, const QString& strNewPrefix)
{
    QFileInfo fileInfo(strImagePath);
    if (!fileInfo.isFile())
        return false;
    if (fileInfo.suffix().compare("png", Qt::CaseInsensitive) != 0)
        return false;
    QString strFileName = fileInfo.fileName();
    const QString& strIndexSuffix = fileInfo.completeBaseName().right(4);
    if (strIndexSuffix.size() != 4)
        return false;
    if (strIndexSuffix[0] != "_")
        return false;
    bool bFlag = false;
    int nIndex = strIndexSuffix.right(3).toInt(&bFlag);
    Q_UNUSED(nIndex)
    if (!bFlag)
        return false;
    const QString& strNewName = strNewPrefix + strIndexSuffix + ".png";
    QString strDirPath = fileInfo.dir().absolutePath();
    if (!strDirPath.endsWith("/"))
        strDirPath = strDirPath.append("/");
    const QString& strNewPath = strDirPath + strNewName;
    QFile file(strImagePath);
    return file.rename(strNewPath);
}

bool ImageUtil::renameImagesInDir(const QString& strDirPath, const QString& strNewPrefix)
{
    QFileInfo dirInfo(strDirPath);
    if (!dirInfo.isDir())
        return false;
    QDir dir(strDirPath);
    const QFileInfoList& pngFileList = dir.entryInfoList({ "*.png" }, QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    bool bFlag = true;
    for (const auto& pngFile : pngFileList)
    {
        const QString& strImagePath = pngFile.absoluteFilePath();
        auto tmpResult = renameImage(strImagePath, strNewPrefix);
        if (!tmpResult)
            bFlag = false;
    }
    return bFlag;
}

bool ImageUtil::renameImage(const QString& strImagePath, const QString& strBefore, const QString& strAfter)
{
    QFileInfo fileInfo(strImagePath);
    if (!fileInfo.isFile())
        return false;
    if (fileInfo.suffix().compare("png", Qt::CaseInsensitive) != 0)
        return false;
    QString strFileName = fileInfo.fileName();
    strFileName = strFileName.replace(strBefore, strAfter);
    QString strDirPath = fileInfo.dir().absolutePath();
    if (!strDirPath.endsWith("/"))
        strDirPath = strDirPath.append("/");
    const QString& strNewFilePath = strDirPath + strFileName;
    QFile file(strImagePath);
    return file.rename(strNewFilePath);
}

bool ImageUtil::renameImagesInDir(const QString& strDirPath, const QString& strBefore, const QString& strAfter)
{
    QFileInfo dirInfo(strDirPath);
    if (!dirInfo.isDir())
        return false;
    QDir dir(strDirPath);
    const QFileInfoList& pngFileList = dir.entryInfoList({ "*.png" }, QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    bool bFlag = false;
    for (const auto& pngFile : pngFileList)
    {
        const QString& strImagePath = pngFile.absoluteFilePath();
        auto tmpResult = renameImage(strImagePath, strBefore, strAfter);
        if (!tmpResult)
            bFlag = tmpResult;
    }
    return bFlag;
}

QStringList ImageUtil::sortImageList(const QStringList& oriImageList)
{
    QStringList resultImageList = oriImageList;
#ifdef Q_OS_OSX
    for (int i = 0; i < resultImageList.size(); ++i)
    {
        const QFileInfo& fileInfo = resultImageList[i];
        if (fileInfo.fileName() == ".DS_Store")
        {
            resultImageList.removeAt(i);
            break;
        }
    }
#endif
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(resultImageList.begin(), resultImageList.end(),
              [&collator](const QString& str1, const QString& str2) {
                  return collator.compare(str1, str2) < 0;
              });
    return resultImageList;
}

QString ImageUtil::getImagePrefix(const QString& strImagePath)
{
    QFileInfo fileInfo(strImagePath);
    if (!fileInfo.isFile())
        return "";
    if (fileInfo.suffix().compare("png", Qt::CaseInsensitive) != 0)
        return "";
    QString strFileName = fileInfo.fileName();
    const QString& strIndexSuffix = fileInfo.completeBaseName().right(4);
    if (strIndexSuffix.size() != 4)
        return "";
    if (strIndexSuffix[0] != "_")
        return "";
    bool bFlag = false;
    strIndexSuffix.right(3).toInt(&bFlag);
    if (!bFlag)
        return "";
    return strFileName.left(strFileName.size() - 4 - strIndexSuffix.size());
}

void ImageUtil::updateTextureColorSpace(const QString& filePath, bool convertToSRGB)
{
    static const unsigned char srgb_lut[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7,
        8, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18,
        19, 19, 20, 20, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32, 33, 33, 34, 35,
        35, 36, 37, 38, 39, 39, 40, 41, 42, 43, 43, 44, 45, 46, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 81, 82, 83, 84, 85,
        87, 88, 89, 90, 91, 93, 94, 95, 97, 98, 99, 100, 102, 103, 105, 106, 107, 109, 110, 111, 113, 114, 116, 117, 119, 120,
        121, 123, 124, 126, 127, 129, 130, 132, 133, 135, 137, 138, 140, 141, 143, 145, 146, 148, 149, 151, 153, 154, 156, 158, 159, 161,
        163, 165, 166, 168, 170, 172, 173, 175, 177, 179, 181, 182, 184, 186, 188, 190, 192, 194, 196, 197, 199, 201, 203, 205, 207, 209,
        211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 234, 236, 238, 240, 242, 244, 246, 248, 251, 253, 255
    };
    QString oldFilePath = filePath;
    oldFilePath.insert(oldFilePath.lastIndexOf('.'), "_rgb");
    if (convertToSRGB)
    {
        QImage png = loadFromFile(filePath);
        png.save(oldFilePath);
        QColor color;
        for (int x = 0; x < png.width(); x++)
        {
            for (int y = 0; y < png.height(); y++)
            {
                color = png.pixelColor(x, y);
                png.setPixelColor(x, y, QColor(srgb_lut[color.red()], srgb_lut[color.green()], srgb_lut[color.blue()]));
            }
        }
        png.save(filePath);
    }
    else
    {
        QImage png = loadFromFile(oldFilePath);
        png.save(filePath);
    }
}

std::vector<unsigned char> ImageUtil::readTextureFromFile(const QString& filePath)
{
    if (!QFile(filePath).exists())
    {
        std::vector<unsigned char> error;
        return error;
    }
    QImage image = QImage(filePath).mirrored(false, true);
    bool hasAlpha = (image.format() == QImage::Format_ARGB32 || image.format() == QImage::Format_RGBA8888);
    std::vector<unsigned char> imageData(image.width() * image.height() * (hasAlpha ? 4 : 3));
    QColor color;
    int index = 0;
    for (int y = 0; y < image.height(); y++)
    {
        for (int x = 0; x < image.width(); x++)
        {
            color = image.pixelColor(x, y);
            imageData[index++] = color.red();
            imageData[index++] = color.green();
            imageData[index++] = color.blue();
            if (hasAlpha)
            {
                imageData[index++] = color.alpha();
            }
        }
    }
    return imageData;
}

ImageUtil::PNGManager::PNGManager(const QString& png_path) :
    m_pngPath(png_path)
{
    //init();
}

ImageUtil::PNGManager::~PNGManager()
{
    if (m_buffer)
    {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}

//void ImageUtil::PNGManager::init()
//{
//    if (!QFile::exists(m_pngPath))
//    {
//        qCritical() << "[error][PNGManager::ReadPNG] file not exist";
//        return;
//    }

//    FILE* file = fopen(m_pngPath.toLocal8Bit().constData(), "rb");
//    if (file == nullptr)
//    {
//        qCritical() << "[error][PNGManager::ReadPNG] open failed";
//        return;
//    }

//    uchar sig[8];
//    fread(sig, 1, 8, file);
//    if (!png_check_sig(sig, 8))
//    {
//        //qCritical() << "[error][PNGManager::ReadPNG] not a png file";
//        fclose(file);
//        return;
//    }

//    png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//    if (pngPtr == nullptr)
//    {
//        qCritical() << "[error][PNGManager::ReadPNG] init error 1";
//        fclose(file);
//        return;
//    }

//    png_infop infoPtr = png_create_info_struct(pngPtr);
//    if (infoPtr == nullptr)
//    {
//        qCritical() << "[error][PNGManager::ReadPNG] init error 2";
//        fclose(file);
//        return;
//    }

//    setjmp(png_jmpbuf(pngPtr));

//    rewind(file);
//    png_init_io(pngPtr, file);
//    png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_EXPAND, 0);

//    m_channelCount = png_get_channels(pngPtr, infoPtr);
//    m_bitDepth = png_get_bit_depth(pngPtr, infoPtr);
//    m_colorType = png_get_color_type(pngPtr, infoPtr);

//    if (m_bitDepth != 8 && m_bitDepth != 16)
//    {
//        qCritical() << "[error][PNGManager::ReadPNG] unsupported bit depth";
//        png_destroy_read_struct(&pngPtr, &infoPtr, static_cast<png_infopp>(NULL));
//        fclose(file);
//        return;
//    }

//    png_bytep* row_pointers = png_get_rows(pngPtr, infoPtr);
//    m_width = png_get_image_width(pngPtr, infoPtr);
//    m_height = png_get_image_height(pngPtr, infoPtr);
//    m_size = m_width * m_height;

//    int pixelBytes = 0;
//    if (m_colorType == PNG_COLOR_TYPE_RGB)
//    {
//        pixelBytes = m_bitDepth * 3 / 8;
//        if ((m_width * pixelBytes) % 4 == 0)
//        {
//            m_bufferRowSize = m_width * pixelBytes;
//        }
//        else
//        {
//            m_bufferRowSize = ((m_width * pixelBytes) / 4 + 1) * 4;
//        }
//        m_bufferSize = m_bufferRowSize * m_height;
//    }
//    else if (m_colorType == PNG_COLOR_TYPE_RGBA)
//    {
//        pixelBytes = m_bitDepth * 4 / 8;
//        m_bufferRowSize = m_width * pixelBytes;
//        m_bufferSize = m_bufferRowSize * m_height;
//    }
//    else
//    {
//        qCritical() << "[error][PNGManager::ReadPNG] init error 3";
//        png_destroy_read_struct(&pngPtr, &infoPtr, static_cast<png_infopp>(NULL));
//        fclose(file);
//        return;
//    }

//    m_buffer = new unsigned char[m_bufferSize];
//    for (int i = 0; i < m_height; i++)
//    {
//        memcpy(m_buffer + i * m_bufferRowSize, row_pointers[m_height - i - 1], m_width * pixelBytes);
//    }

//    png_destroy_read_struct(&pngPtr, &infoPtr, static_cast<png_infopp>(NULL));
//    fclose(file);

//    m_loadSuccess = true;
//}
