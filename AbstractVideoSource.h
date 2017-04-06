#ifndef ABSTRACTVIDEOSOURCE_H
#define ABSTRACTVIDEOSOURCE_H
#include <QObject>

class AbstractVideoSource : public QObject
{
    Q_OBJECT
public:
    explicit AbstractVideoSource(QObject* parent = nullptr);


private:

};

#endif // ABSTRACTVIDEOSOURCE_H
