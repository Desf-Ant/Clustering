#include "mainwindow.h"

MainWindow::MainWindow(Donnees* d, QWidget *parent) : QMainWindow(parent)
{
    this->donnees = d;
    this->scene = new Scene( this->donnees );
    this->init_components();
    this->init_layouts();
    this->init_slots();
}

void MainWindow::init_components ( void )
{
    this->principal = new QWidget();
    this->menu = new QWidget();

    this->generation = new QGroupBox( "Génération" );
    this->choix_nb_sommets = new QSpinBox();
    this->choix_nb_sommets->setMinimum(1);
    this->choix_nb_sommets->setMaximum(1000);
    this->widget_dimensions = new QWidget();
    this->bouton_2D = new QPushButton ( "2D" );
    this->bouton_3D = new QPushButton ( "3D" );
    this->bouton_2D->setCheckable(true);
    this->bouton_3D->setCheckable(true);
    this->bouton_2D->setChecked(true);
    this->texte_distance = new QLabel ( "Choix de la distance :" );
    this->choix_distance = new QComboBox();
    this->choix_distance->addItem( "Manhattan (1)" );
    this->choix_distance->addItem( "Euclidienne (2)" );
    this->choix_distance->addItem( "Chebyshev (infinie)" );
    this->choix_distance->addItem( "Cosinus" );
    this->choix_distance->setCurrentIndex(1); // euclidienne par défaut
    this->choix_generation = new QComboBox();
    this->choix_generation->addItem( "Random" );
    this->choix_generation->addItem( "Eparpillés" );
    this->choix_generation->addItem( "Carré" );
    this->choix_generation->addItem( "Rectangle" );
    this->choix_generation->addItem( "Disque" );
    this->choix_generation->addItem( "Ellipse" );
    this->bouton_generation = new QPushButton ( "Génère sommets" );
    this->bouton_clear = new QPushButton ( "Clear scène" );

    this->algos_clustering = new QGroupBox( "Clustering" );
    this->texte_nb_classes = new QLabel ( "Nombre de classes :" );
    this->choix_nb_classes = new QSpinBox( );
    this->choix_nb_classes->setMinimum(2);
    this->choix_nb_classes->setMaximum(8);
    this->bouton_kmeans = new QPushButton ( "K-means" );
    this->bouton_kmedians = new QPushButton ( "K-medians" );
    this->bouton_PAM = new QPushButton ( "PAM" );
    this->bouton_hierarchical = new QPushButton ( "Hierarchical" );
    this->bouton_dbscan = new QPushButton ( "DBSCAN" );

    this->algos_data_science = new QGroupBox( "Data Science" );
    this->bouton_acp = new QPushButton ( "ACP" );
}

void MainWindow::init_layouts ( void )
{
    this->setCentralWidget( this->principal );
    this->layout_principal = new QHBoxLayout();
    this->layout_menu = new QVBoxLayout();
    this->layout_generation = new QVBoxLayout();
    this->layout_dimensions = new QHBoxLayout();
    this->layout_data_science = new QVBoxLayout();
    this->layout_clustering = new QVBoxLayout();

    this->principal->setLayout( this->layout_principal );
    this->layout_principal->addWidget( this->scene );
    this->layout_principal->addWidget( this->menu );
    this->menu->setLayout( this->layout_menu );

    this->layout_menu->addWidget( this->generation );
    this->generation->setLayout( this->layout_generation );
    this->layout_generation->addWidget( this->widget_dimensions );
    this->widget_dimensions->setLayout( this->layout_dimensions );
    this->layout_dimensions->addWidget( this->bouton_2D );
    this->layout_dimensions->addWidget( this->bouton_3D );
    this->layout_generation->addWidget( this->choix_nb_sommets );
    this->layout_generation->addWidget( this->texte_distance );
    this->layout_generation->addWidget( this->choix_distance );
    this->layout_generation->addWidget( this->choix_generation );
    this->layout_generation->addWidget( this->bouton_generation );
    this->layout_generation->addWidget( this->bouton_clear );

    // Clustering
    this->layout_menu->addWidget( this->algos_clustering );
    this->algos_clustering->setLayout( this->layout_clustering );
    this->layout_clustering->addWidget( this->texte_nb_classes );
    this->layout_clustering->addWidget( this->choix_nb_classes );
    this->layout_clustering->addWidget( this->bouton_kmeans );
    this->layout_clustering->addWidget( this->bouton_kmedians );
    this->layout_clustering->addWidget( this->bouton_PAM );
    this->layout_clustering->addWidget( this->bouton_hierarchical );
    this->layout_clustering->addWidget( this->bouton_dbscan );

    // Data Science
    this->layout_menu->addWidget( this->algos_data_science );
    this->algos_data_science->setLayout( this->layout_data_science );
    this->layout_data_science->addWidget( this->bouton_acp );
}

void MainWindow::init_slots ( void )
{
    connect ( this->bouton_generation, SIGNAL(clicked()), this, SLOT(clic_genere_donnees()) );
    connect ( this->bouton_clear, SIGNAL(clicked()), this, SLOT(clic_clear()) );
    connect ( this->bouton_kmeans, SIGNAL(clicked()), this, SLOT(clic_kmeans()) );
    connect ( this->bouton_kmedians, SIGNAL(clicked()), this, SLOT(clic_kmedians()) );
    connect ( this->bouton_PAM, SIGNAL(clicked()), this, SLOT(clic_PAM()) );
    connect ( this->bouton_hierarchical, SIGNAL(clicked()), this, SLOT(clic_hierarchical()) );
    connect ( this->bouton_dbscan, SIGNAL(clicked()), this, SLOT(clic_dbscan()) );
    connect ( this->bouton_2D, SIGNAL(clicked()), this, SLOT(clic_2D()) );
    connect ( this->bouton_3D, SIGNAL(clicked()), this, SLOT(clic_3D()) );
}

MainWindow::~MainWindow()
{

}

void MainWindow::clic_genere_donnees ( void )
{
    this->donnees->setNbDonnees( this->donnees->getDonnees()->size() + this->choix_nb_sommets->value() );
    this->donnees->setDimension( this->bouton_2D->isChecked() );
    this->donnees->setTypeDistance( (type_dist)(this->choix_distance->currentIndex()) );

    switch ( this->choix_generation->currentIndex() )
    {
        case 0 : this->donnees->genere_random(); break;
        case 1 : this->donnees->genere_eparpilles(); break;
        case 2 : this->donnees->genere_carre(); break;
        case 3 : this->donnees->genere_rectangle(); break;
        case 4 : this->donnees->genere_disque(); break;
        case 5 : this->donnees->genere_ellipse(); break;
        default : this->donnees->genere_random(); break;
    }
    this->scene->recharge();
}

void MainWindow::clic_clear ( void )
{
    this->donnees->getDonnees()->clear();
    this->donnees->getGraines()->clear();
    this->donnees->setNbDonnees(0);
    this->scene->recharge();
}

void MainWindow::clic_kmeans ( void )
{
    unsigned int nb_classes = this->choix_nb_classes->value();
    type_dist type = (type_dist)(this->choix_distance->currentIndex());
    Kmeans km ( this->donnees, nb_classes, type );
    km.execute();
    this->scene->recharge();
}

void MainWindow::clic_kmedians ( void )
{
    unsigned int nb_classes = this->choix_nb_classes->value();
    type_dist type = (type_dist)(this->choix_distance->currentIndex());
    Kmedians km ( this->donnees, nb_classes, type );
    km.execute();
    this->scene->recharge();
}

void MainWindow::clic_PAM ( void )
{
    unsigned int nb_classes = this->choix_nb_classes->value();
    type_dist type = (type_dist)(this->choix_distance->currentIndex());
    PAM pam ( this->donnees, nb_classes, type );
    pam.execute();
    this->scene->recharge();
}

void MainWindow::clic_hierarchical ( void )
{
    unsigned int nb_classes = this->choix_nb_classes->value();
    type_dist type = (type_dist)(this->choix_distance->currentIndex());
    Hierarchical h ( this->donnees, nb_classes, type );
    h.execute();
    this->scene->recharge();
}

void MainWindow::clic_dbscan ( void )
{
    type_dist type = (type_dist)(this->choix_distance->currentIndex());
    DBSCAN db ( this->donnees, type );
    db.execute();
    this->scene->recharge();
}

void MainWindow::clic_2D ( void )
{
    this->bouton_2D->setChecked(true);
    this->bouton_3D->setChecked(false);
}

void MainWindow::clic_3D ( void )
{
    this->bouton_2D->setChecked(false);
    this->bouton_3D->setChecked(true);
}
