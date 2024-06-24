#ifndef IMAGEUTIL_H
#define IMAGEUTIL_H
#include <QObject>
#include <QImage>


class ImageUtil : public QObject
{
    Q_OBJECT

public:
    class PNGManager;

    /*
     * 从文件中加载文件
     * strFileName : 文件的路径
     * convertSRGBToRGB : 是否从SRGB转换成RGB，QImage无法保存SRGB的图片
    */
    static QImage loadFromFile(const QString& strFilePath, bool convertColorSpaceToRGB = true);

    /*
     * 图片大小
     */
    static Q_INVOKABLE QSize getImageSize(const QString& imagePath);

    /*
     * 图片格式 png / jpeg / jpg等
     */
    static Q_INVOKABLE QString getFormat(const QString& imagePath);
    static Q_INVOKABLE bool isPngFormat(const QString& imagePath);

    /*
     * 是否是工具所用的可靠的png文件
     * 后缀为png，不能为隐藏文件
     */
    static Q_INVOKABLE bool isValidPngFile(const QString& strFilePath);

    /*
    * 去除多余的png后缀
    */
    static QString removeRedundancePngSuffix(const QString& strFileName);

    /*
     * 重命名图片的前缀，将图将图片从 aaa_000.png 重命名为 bbb_000.png
    */
    static bool renameImage(const QString& strImagePath, const QString& strNewPrefix);

    /*
     * 重命名图片文件夹下的文件前缀，图片中的aaa_000.png，重命名为bbb_000.png
    */
    static bool renameImagesInDir(const QString& strDirPath, const QString& strNewPrefix);

    /*
     * 重命名图片，替换名字中的字符串
    */
    static bool renameImage(const QString& strImagePath, const QString& strBefore, const QString& strAfter);

    /*
     * 重命名文件夹中的图片，替换名字中的字符串
    */
    static bool renameImagesInDir(const QString& strDirPath, const QString& strBefore, const QString& strAfter);

    /*
     *对搜索得到的序列帧图片进行排序
     */
    static QStringList sortImageList(const QStringList& oriImageList);

    /*
     * 获取图片文件的前缀
     */
    static QString getImagePrefix(const QString& strImagePath);

    /*
     * 从文件中加载图片
     * strFileName : 文件的路径
     * convertSRGBToRGB : 是否从SRGB转换成RGB
    */
    static void updateTextureColorSpace(const QString& filePath, bool convertToSRGB = true);
    /*
     * 从文件中读取图片的像素值
     * strFileName : 文件的路径
     * convertSRGBToRGB : 是否从SRGB转换成RGB，QImage无法保存SRGB的图片
    */
    static std::vector<unsigned char> readTextureFromFile(const QString& filePath);
};

class ImageUtil::PNGManager
{
public:
    explicit PNGManager(const QString& png_path);
    ~PNGManager();

    unsigned char* getBuffer() { return m_buffer; }
    unsigned int getBufferRowSize() const { return m_bufferRowSize; }
    int getChannelCount() const { return m_channelCount; }
    int getBitDepth() const { return m_bitDepth; }
    int getColorType() const { return m_colorType; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    bool loadSuccess() const { return m_loadSuccess; }

private:
    //void init();

private:
    QString m_pngPath;
    unsigned char* m_buffer = nullptr;
    unsigned int m_bufferSize = 0;
    unsigned int m_bufferRowSize = 0;
    int m_colorType = 0;
    int m_channelCount = 0;
    int m_bitDepth;
    int m_width = 0;
    int m_height = 0;
    int m_size = 0;
    bool m_loadSuccess = false;
};

#endif // IMAGEUTIL_H
