#include "PlaybackActionsDock.h"
#include "ui_playbackactionsdock.h"

PlaybackActionsDock::PlaybackActionsDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PlaybackActionsDock)
{
    ui->setupUi(this);
}

PlaybackActionsDock::~PlaybackActionsDock()
{
    delete ui;
}
