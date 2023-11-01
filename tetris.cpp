#include "tetris.h"

#include "ui_tetris.h"

Tetris::Tetris(QWidget *parent) : QMainWindow(parent), ui(new Ui::Tetris) {
  ui->setupUi(this);

  // Увеличиваем размер шрифта меню
  menuBar()->setStyleSheet(QString("font-size: %1px").arg(14));

  QMenu *gameMenu = menuBar()->addMenu("&Игра");

  // Создаём объект класса QAction (действие) с названием Новая игра
  QAction *startNewGame = new QAction("&Нова игра", this);

  // Добавляем QAction в пункт меню Игра
  gameMenu->addAction(startNewGame);

  // Создаем соединени между слотом начала новой игры в GameField и QAction
  connect(startNewGame, &QAction::triggered, ui->gameField,
          &GameField::StartNewGame);

  // Создаем соединени между слотом начала новой игры в классе GameField и
  // кнопкой
  connect(ui->newGameButton, &QPushButton::clicked, ui->gameField,
          &GameField::StartNewGame);
}

Tetris::~Tetris() { delete ui; }
