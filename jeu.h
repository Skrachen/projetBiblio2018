#ifndef JEU_H
#define JEU_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include "opencv2/opencv.hpp"
#include <QDebug>
#include <QColor>
#include "brique.h"
#include "mur.h"
#include "palet.h"
#include "balle.h"

class Jeu : public QGLWidget
{
    Q_OBJECT

public:
    explicit Jeu(QWidget *parent = 0);
    void setPos(cv::Point v){ posX =(float) v.x; posY = v.y;}

    void animation();
public slots:

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

private:
    // Timer d'animation
    float m_Time { 0.0f };
    QTimer m_AnimationTimer;
    float posX;
    float posY;
    std::vector<brique*> tabBrique;
    palet* barre;
    balle* current_balle;
    std::vector<mur*> tabMur;
    QColor couleur;
    float posCamX_;
    float posCamY_;
    float posCamZ_;

};
#endif // JEU_H
