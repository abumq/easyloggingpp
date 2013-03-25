/**
 * building-blocks v1.0
 *
 * @author mkhan3189
 * http://www.icplusplus.com
 * https://www.github.com/mkhan3189/building-blocks
 * https://www.github.com/mkhan3189/building-blocks-engine
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, version 3 of the License.
 */

#include "gameplay.hh"
#include "engine/engine.hh"
#include "engine/easylogging++.h"
#include "engine/internal/player.hh"

#include <QApplication>
#include <QLabel>
#include <QPushButton>

namespace buildingblocks {

GamePlay::GamePlay(engine::Engine *gameEngine_) :
    QMainWindow(NULL)
{
    init(gameEngine_, NULL);
}

GamePlay::GamePlay(buildingblocks::engine::Engine* gameEngine_, buildingblocks::GameBoard *gameBoard_) :
    QMainWindow(NULL)
{
    init(gameEngine_, gameBoard_);
}

void GamePlay::init(engine::Engine *gameEngine_, GameBoard *gameBoard_)
{
    setupUi();
    this->gameEngine_ = gameEngine_;
    this->gameBoard_ = gameBoard_;
    if (gameBoard() == NULL) {
        int totalPoints = 5;
        this->gameBoard_ = new buildingblocks::GameBoard(centralWidget, totalPoints, totalPoints, centralWidget->width(), centralWidget->height(), 0);

        QObject::connect(this->gameBoard_, SIGNAL(updated(buildingblocks::engine::internal::Player*)), this, SLOT(boardUpdated(buildingblocks::engine::internal::Player*)));
        // Manually trigger slot once
        boardUpdated(this->gameBoard_->currentPlayer());
    }

}

GamePlay::~GamePlay()
{
    DELETE(gameEngine_);
    DELETE(gameBoard_);
    DELETE(centralWidget);
}

void GamePlay::setupUi(void)
{
    if (objectName().isEmpty())
    {
        setObjectName(QString::fromUtf8("GamePlay"));
    }
    resize(800, 855);
    playerTurnLabel = new QLabel(this);
    playerTurnLabel->setObjectName(QString::fromUtf8("playerTurnLabel"));;
    playerTurnLabel->setGeometry(10, 5, width() / 3, 15);
    playerTurnLabel->setText("Player: ");
    playerTurnLabel->show();

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    centralWidget->setGeometry(0, 40 + playerTurnLabel->height(), width(), height() - playerTurnLabel->height() - 40);
    centralWidget->show();

    resetButton = new QPushButton(this);
    resetButton->setObjectName(QString::fromUtf8("resetButton"));
    resetButton->setGeometry(width() - (width() / 6), 5, width() / 6, 45);
    resetButton->setText("Reset");
    resetButton->show();
    QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));

    player1Legend = new QLabel(this);
    player1Legend->setObjectName(QString::fromUtf8("player1Legend"));;
    player1Legend->setGeometry(width() / 6, 5, width() / 6, 22);
    player1Legend->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    player1Legend->setText("Player 1 Legend");
    player1Legend->show();

    player2Legend = new QLabel(this);
    player2Legend->setObjectName(QString::fromUtf8("player2Legend"));;
    player2Legend->setGeometry(width() / 6, 5 + player1Legend->height(), width() / 6, 22);
    player2Legend->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    player2Legend->setText("Player 2 Legend");
    player2Legend->show();

    selectionLegend = new QLabel(this);
    selectionLegend->setObjectName(QString::fromUtf8("selectionLegend"));;
    selectionLegend->setGeometry((width() / 6) + player1Legend->width(), player1Legend->y(), width() / 6, 22);
    selectionLegend->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    selectionLegend->setText("Selection");
    selectionLegend->show();
    QString styleSheetStart = "QLabel { background-color :";
    QString styleSheetEnd = "}";
    selectionLegend->setStyleSheet(styleSheetStart + "yellow" + styleSheetEnd);
}

void GamePlay::retranslateUi(void)
{
    setWindowTitle(QApplication::translate("GamePlay", "GamePlay", 0, QApplication::UnicodeUTF8));
}

void GamePlay::boardUpdated(buildingblocks::engine::internal::Player* player) {
    playerTurnLabel->setText("Turn: " + QString::fromStdString(player->name()));
    QString styleSheetStart = "QLabel { background-color :";
    QString styleSheetEnd = "}";
    buildingblocks::engine::internal::Player* player1 = this->gameBoard_->players().at(0);
    QColor color = this->gameBoard_->getPlayerQColor(player1);
    player1Legend->setStyleSheet(styleSheetStart + color.name() + styleSheetEnd);
    player1Legend->setText(QString::fromStdString(player1->name()));
    buildingblocks::engine::internal::Player* player2 = this->gameBoard_->players().at(1);
    color = this->gameBoard_->getPlayerQColor(player2);
    player2Legend->setStyleSheet(styleSheetStart + color.name() + styleSheetEnd);
    player2Legend->setText(QString::fromStdString(player2->name()));
}

void GamePlay::reset(void)
{
    gameBoard()->reset();
}

buildingblocks::engine::Engine* GamePlay::gameEngine(void) const
{
    return gameEngine_;
}

GameBoard *GamePlay::gameBoard() const
{
    return gameBoard_;
}

void GamePlay::paintEvent(QPaintEvent *)
{
    gameBoard_->setGeometry(0, 0, gameBoard_->boardWidth(), gameBoard_->boardHeight());
}

} // namespace buildingblocks
