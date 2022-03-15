#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"
#include "../core/donnees.h"
#include "../clustering/kmeans.h"
#include "../clustering/kmedians.h"
#include "../clustering/pam.h"
#include "../clustering/hierarchical.h"
#include "../clustering/dbscan.h"
#include "../clustering/kmeannotes.h"
#include "../clustering/kmediannotes.h"
#include "../clustering/hierarchicalnotes.h"
#include "../core/notes.h"
#include "../core/note.h"
#include "data_science/acpNotes.h"

#include <QMainWindow>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QShortcut>
#include <QFileDialog>
#include <QFile>

#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private :
        Donnees* donnees;

        QWidget* principal;
        Scene* scene;
        QWidget* menu;

        // shortcuts
        QShortcut *openShortcut;

        // Les paramètres
        QGroupBox* generation;
        QWidget* widget_dimensions;
        QPushButton* bouton_2D;
        QPushButton* bouton_3D;
        QComboBox* choix_generation;
        QSpinBox* choix_nb_sommets;
        QPushButton* bouton_generation;
        QPushButton* bouton_clear;
        QLabel* texte_distance;
        QComboBox* choix_distance;

        // Clustering
        QGroupBox* algos_clustering;
        QLabel* texte_nb_classes;
        QSpinBox* choix_nb_classes;
        QPushButton* bouton_kmeans;
        QPushButton* bouton_kmedians;
        QPushButton* bouton_PAM;
        QPushButton* bouton_hierarchical;
        QPushButton* bouton_dbscan;

        // Data Science
        QGroupBox* algos_data_science;
        QPushButton* bouton_acp;

        // Les layouts
        QHBoxLayout* layout_principal;
        QVBoxLayout* layout_menu;
        QVBoxLayout* layout_generation;
        QHBoxLayout* layout_dimensions;
        QVBoxLayout* layout_data_science;
        QVBoxLayout* layout_clustering;

    private :
        void init_components ();
        void init_layouts ();
        void init_slots ();

    public :
        MainWindow(Donnees* d, QWidget *parent = nullptr);
        ~MainWindow();

    public slots :
        void clic_genere_donnees ( void );
        void clic_clear ( void );
        void clic_kmeans ( void );
        void clic_kmedians ( void );
        void clic_PAM ( void );
        void clic_hierarchical ( void );
        void clic_dbscan ( void );
        void clic_2D ( void );
        void clic_3D ( void );
        void openFile( void );
};
#endif // MAINWINDOW_H
