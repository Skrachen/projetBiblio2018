#ifndef JEU_H
#define JEU_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include "opencv2/opencv.hpp"
#include <QDebug>
#include <QColor>
#include <cassebrique.h>
class Jeu : public QGLWidget
{
    Q_OBJECT

public:
    explicit Jeu(QWidget *parent = 0);
    void setPos(cv::Point v){ vX =(float) v.x; vY = v.y;}


    cassebrique* getJeuCasseBrique(){return jeuCasseBrique;}
public slots:

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();



private:
    void rebondPalet(float xPalet, float xBalle);
    // Timer d'animation
    float m_Time { 0.0f };
    float vX;
    float vY;
    cassebrique* jeuCasseBrique;
    QString m_TexteLevel = "";
    QString m_TexteScore = "";
    QString m_TexteNbBalle = "";

    QColor couleur;
    float posCamX_;
    float posCamY_;
    float posCamZ_;

    float murGauche = -165;
    float murDroite =  145;
    float murHaut   =  75;
    float murBas=-80;
    float vitessePalet;
    float vitesseBalleX;
    float vitesseBalleY;

};
#endif // JEU_H
