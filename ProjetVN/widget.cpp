#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    texteDeScene = 1;
    fondDeScene = 1;

    ui->maVue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->maVue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    maScene.setSceneRect(0,0,1000,700);
    ui->maVue->fitInView(maScene.sceneRect(),Qt::KeepAspectRatio);
    ui->maVue->setScene(&maScene);


    /*----- Definition du fond de la scene -----*/
    QString image = ":/new/IMAGES/Accueil.jpg";
    QPixmap pim(image);
    maScene.setBackgroundBrush(pim.scaled(1000,700,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    /*------------------------------------------*/
    ui->pushButtonTexte->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::lireBandeSons(int _maScene)
{
    if( _maScene==1){
        // player.setMedia(QUrl("qrc:/SONS/"+QString::number(_maScene)+".mp3"));
        player.setMedia(QUrl("qrc:/new/SONS/clocheEcole.mp3"));
        player.setVolume(50);
    }
    if( _maScene==2){
        player.setMedia(QUrl("qrc:/new/SONS/RueClassique.mp3"));
        player.setVolume(100);
    }
    if( _maScene==7 || _maScene==8){
        player.setMedia(QUrl("qrc:/new/SONS/safeZoneBar.mp3"));
        player.setVolume(100);
    }
    if( _maScene==5){
        player.setMedia(QUrl("qrc:/new/SONS/musique-dhorreur-et-de-suspens.mp3"));
        player.setVolume(100);
    }
    if( _maScene==4 && texteDeScene==101){
        player.stop();
    }

    player.play();
}

void Widget::ChangerTexte()
{
    maScene.clear();

    /*----- Definition du fond -----*/
    QString image = ":/new/IMAGES/" + QString::number(fondDeScene) + ".jpg";
    QPixmap pim(image);
    maScene.setBackgroundBrush(pim.scaled(1000,700,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    /*------------------------------*/

    /*----- Parametres de style -----*/
    QColor background(0,0,0,100);
    QFont police;
    police.setPixelSize(20);
    police.setBold(1);
    /*------------------------------*/

    /*----- Zone de texte -----*/
    QGraphicsRectItem *rectangle = new QGraphicsRectItem(20,500,960,160);
    rectangle->setBrush(background);
    rectangle->setPen(background);
    maScene.addItem(rectangle);
    rectangle->setZValue(10);
    /*-------------------------*/

    /*----- Recuperation du texte dans un fichier -----*/
    QString texteAafficher = ":/new/TEXTES/" + QString::number(texteDeScene) + ".txt";
    QString texte = "";
    QFile fichier(texteAafficher);
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "ERROR", fichier.errorString());
    }
    else
    {
        QTextStream in(&fichier);
        while(!in.atEnd()) {
            QString line = in.readLine() + "\n";
            texte += line;
        }
    }
    /*-------------------------------------------------*/

    /*----- Ajout du texte dans la zone de texte -----*/
    QGraphicsTextItem *text = maScene.addText(texte);
    text->setPos(20,500);
    text->setFont(police);
    text->setDefaultTextColor(QColor(255,255,255));
    text->setZValue(11);
    /*------------------------------------------------*/

    /*----- On incrémente le texte pour passer au texte suivant, et potentiellement au fond suivant -----*/
    texteDeScene++;
    if((texteDeScene > 3 && fondDeScene == 1) || (texteDeScene > 5 && fondDeScene == 2) || (texteDeScene == 101 && fondDeScene == 3)||
            (texteDeScene == 103 && fondDeScene == 4) || (texteDeScene == 109 && fondDeScene == 5) || (texteDeScene == 303 && fondDeScene == 6) || (texteDeScene == 311 && fondDeScene == 7))
    {
        fondDeScene++;
        lireBandeSons(fondDeScene);
    }
    if((texteDeScene == 403 && fondDeScene == 6) || (texteDeScene == 201 && fondDeScene == 3) || (texteDeScene == 312 && fondDeScene == 8))
    {
        fondDeScene = 4;

    }
    /*---------------------------------------------------------------------------------------------------*/

    /*------ On fait apparaitre la waifu si les conditions sont respectées -----*/
    if((texteDeScene > 105 && texteDeScene < 200) || (texteDeScene>299 && texteDeScene < 312))
    {
        QPixmap PersonnageFeminin(":/new/PERSONNAGES/Waifu2.png");
        PersonnageFeminin.setDevicePixelRatio(2);
        QGraphicsPixmapItem *personnage = new QGraphicsPixmapItem(QPixmap(":/new/PERSONNAGES/Waifu2.png"));
        //QBrush interieurTexture(PersonnageFeminin);
        maScene.addItem(personnage);
        personnage->setScale(0.5);
        personnage->setPos(650,165);
        //personnage->setPos(100,165);
    }
    /*--------------------------------------------------------------------------*/

    maScene.setBackgroundBrush(pim.scaled(1000,800,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
}

void Widget::on_pushButtonTexte_clicked()
{
    ChangerTexte();

    /*--------------------- Premier choix ----------------*/
    if(texteDeScene==8){
        QMessageBox choix1;
        choix1.setText("Que devrais-je faire?");
        QAbstractButton *bouton1=choix1.addButton(tr("Continuer mon chemin ?"),QMessageBox::ActionRole);
        QAbstractButton *bouton2=choix1.addButton(tr("Emprunter un autre chemin ?"),QMessageBox::ActionRole);
        choix1.exec();

        if(choix1.clickedButton()==bouton1){
            texteDeScene=100;
        }
        if(choix1.clickedButton()==bouton2){
            texteDeScene=200;
        }
        ChangerTexte();
    }
    /*----------------------------------------------------*/

    /*--------------------- Deuxieme choix ----------------*/
    if(texteDeScene==112){
        QMessageBox choix2;
        choix2.setText("Que devrais-je faire?");
        QAbstractButton *bouton3=choix2.addButton(tr("Suivre Saeko ?"),QMessageBox::ActionRole);
        QAbstractButton *bouton4=choix2.addButton(tr("Continuer seul ?"),QMessageBox::ActionRole);
        choix2.exec();

        if(choix2.clickedButton()==bouton3){
            texteDeScene=300;
        }
        if(choix2.clickedButton()==bouton4){
            texteDeScene=400;
        }
        ChangerTexte();
    }
    /*----------------------------------------------------*/

    if(texteDeScene == 405 ||  texteDeScene == 202 || texteDeScene == 313 )
    {
        ui->pushButtonTexte->setEnabled(0);
    }

    if(texteDeScene==101){
        player.setMedia(QUrl("qrc:/new/SONS/boing.mp3"));
        player.setVolume(400);
    }
}

void Widget::on_pushButtonPlay_clicked()
{
    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonTexte->setEnabled(true);

    ChangerTexte();
    lireBandeSons(fondDeScene);
    //texteDeScene++;

}

