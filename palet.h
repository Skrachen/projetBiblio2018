#ifndef PALET_H
#define PALET_H


#include <GL/glu.h>
#include <QColor>
#include <QtGui/qopengl.h>
class palet
{
public:
    palet(float x, float y, float z);
    void displayPalet(float x, float y, float z);
private:
    float positionX;
    float positionY;
    float positionZ;
};

#endif // PALET_H