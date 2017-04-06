#ifndef FILEVIDEOSOURCE_H
#define FILEVIDEOSOURCE_H

#include "AbstractVideoSource.h"

class FileVideoSource : public AbstractVideoSource
{
    Q_OBJECT
public:
    FileVideoSource(QObject* parent = nullptr);
};

#endif // FILEVIDEOSOURCE_H
