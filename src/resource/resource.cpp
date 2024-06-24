#include "resource.h"
#include <QResource>

void Resource::registerResource()
{
    QResource::registerResource(":/image.res");
    QResource::registerResource(":/shader.res");
}
