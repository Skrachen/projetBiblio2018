#include "jeu.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFont>


// Constructeur
Jeu::Jeu(QWidget *parent) : QGLWidget(parent) {

    // Reglage de la taille/position
    setFixedSize(700, 300);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());


    posCamX_=0;
    posCamY_=0;
    posCamZ_=1.1f;

    vitessePalet = 0;

}

// Fonction d'initialisation
void Jeu::initializeGL()
{
    couleur.setRgb(200, 150, 50);
    glClearColor(0.5,0.5,0.5,1);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
    // Réglage de la lampe (en position 0,0,0, emettant dans toutes les directions, avec une couleur ambiante et diffuse blanche)
    GLfloat Light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, Light);
    GLfloat positionLight[] = {0.0f, 0.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);

    //Activation de la lumiere dans OpenGL et de la lampe
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);



    for(int j=0;j<8;j++){
        for(int i=0;i<10;i++){
           tabBrique.push_back(new brique(-155+30*i,65-j*10,0,0.0f,30,0.0f,10));
        }
    }
    tabMur.push_back(new mur(murGauche,murHaut-2,0,true));
    tabMur.push_back(new mur(murDroite,murHaut-2,0,true));
    tabMur.push_back(new mur(murGauche,murHaut,0,false));
    tabMur.push_back(new mur(murGauche,murBas,0,false,true));
    barre =new palet(0,-75,0);
    fond_=new fond(0,-65,0,murGauche,murDroite+10,-10,147.0f);
    current_balle=new balle(0,-65,0,5);

    vitesseBalleY = 5;
    vitesseBalleX = rand()%5-2.5;
    m_TexteLevel = QString("Niveau: %1").arg(QString::fromStdString("1"));
    m_TexteScore = QString("Score: %1").arg(QString::fromStdString("1"));
    m_TexteNbBalle = QString("Nombre de balle(s) restante(s): %1").arg(QString::fromStdString("1"));
    if(vitesseBalleX==0){vitesseBalleX+=1;}
}


// Fonction de redimensionnement
void Jeu::resizeGL(int width, int height)
{
    // Définition du viewport
    glViewport(0,0,700,300);

    // Définition de la matrice de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-350.0f * (16/9), 350.0f * (16/9), -150.0f, 150.0f, -50.0f,50.0f);

}

// Fonction d'affichage
void Jeu::paintGL()
{
    glClearColor(1,1,1,1); // Couleur à utiliser lorsqu’on va nettoyer la fenetre ( = le fond)

    // Réinitialisation du tampon de couleur
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Réinitialisation de la matrice courante
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posCamX_,posCamY_,posCamZ_,0,0,0,0,1,0);
    glScalef(1.25f,1.25f,1.0f);
    for(int i=0;i<tabBrique.size();i++){
       tabBrique[i]->displayBrique();
    }
    for(int i=0;i<tabMur.size();i++){
       tabMur[i]->displayMur();
    }
    barre->displayPalet();
    fond_->displayFond();
    current_balle->displayBalle();
    glColor3f(0,0,0);
    renderText(270, 35, "Casse brique", QFont( "Helvetica", 20, QFont::Bold, TRUE ));
    renderText(0, 275, m_TexteNbBalle, QFont( "lucida", 10, QFont::Bold, TRUE ));
    renderText(325, 275, m_TexteLevel, QFont( "lucida", 10, QFont::Bold, TRUE ));
    renderText(575, 275, m_TexteScore, QFont( "lucida", 10, QFont::Bold, TRUE ));

}

void Jeu::animation(){

    // Mouvement du palet
    if(vitessePalet > 0){vitessePalet -= 2; }else{ vitessePalet += 2; }
    vitessePalet +=vX;
    if(vitessePalet > 25){ vitessePalet = 25; }else if(vitessePalet < -25){ vitessePalet = -25; }
    if(( barre->getXPalet()-30+vitessePalet <= murGauche )||( barre->getXPalet()+30+vitessePalet >= murDroite )){
        vitessePalet = -vitessePalet;
    }
    barre->movePalet(vitessePalet);

    // Mouvement de la balle
    float xBalle = current_balle->getXBalle();
    float yBalle = current_balle->getYBalle();
    float xPalet = barre->getXPalet();
    xBalle += vitesseBalleX;
    yBalle += vitesseBalleY;
    // Collisions de la balle avec les murs, le palet et les briques
    if( yBalle+5 >= murHaut-5 ){ vitesseBalleY = -vitesseBalleY; }
    if( xBalle+5 >= murDroite ){ vitesseBalleX = -vitesseBalleX; }
    if( xBalle-5 <= murGauche+10 ){ vitesseBalleX = -vitesseBalleX; }
    if( yBalle-5 <= -70 && yBalle-5 >= -71 && xPalet-xBalle<35 && xPalet-xBalle>-35 && vitesseBalleY<0 ){
        vitesseBalleY = -vitesseBalleY;
        vitesseBalleX += (xBalle-xPalet)*0.5;
    }
    //TODO - collision avec les briques
    current_balle->setXBalle(xBalle);
    current_balle->setYBalle(yBalle);

}

void Jeu::rebondPalet(float xPalet, float xBalle){
    float vitesseAbsBalle = sqrt(vitesseBalleX*vitesseBalleX+vitesseBalleY*vitesseBalleY);
    float angleBalle = atan(vitesseBalleX/vitesseBalleY);
    float angleRebondBalle = -angleBalle+atan(1)*(xBalle-xPalet);
    vitesseBalleY = sqrt(vitesseAbsBalle*vitesseAbsBalle/(1+tan(angleRebondBalle)*tan(angleRebondBalle)));
    vitesseBalleX = sqrt(vitesseAbsBalle*vitesseAbsBalle-vitesseBalleY*vitesseBalleY);
}



