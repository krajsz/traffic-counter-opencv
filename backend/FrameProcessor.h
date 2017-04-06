#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QObject>

class FrameProcessor : public QObject
{
    Q_OBJECT
public:
    explicit FrameProcessor(QObject *parent = 0);

signals:

public slots:
};

#endif // FRAMEPROCESSOR_H