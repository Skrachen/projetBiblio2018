#ifndef JEU_H
#define JEU_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include "opencv2/opencv.hpp"
#include <QDebug>
#include <QColor>
#include "brique.h"
#include "mur.h"
#include "palet.h"

class Jeu : public QGLWidget
{
    Q_OBJECT

public:
    explicit Jeu(QWidget *parent = 0);
    void setPos(cv::Point v){ posX = v.x; posY = v.y; qInfo() << "setVect de jeu.h: "<<posX<<" , "<<posY; }

public slots:

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent * event);

private:
    int posX;
    int posY;
    std::vector<brique*> tabBrique;
    palet* barre;
    std::vector<mur*> tabMur;
    QColor couleur;
    float posCamX_;
    float posCamY_;
    float posCamZ_;

};
#endif // JEU_H
