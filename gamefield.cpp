#include "gamefield.h"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

GameField::GameField(QWidget *parent) : QWidget{parent} {
  setFocusPolicy(Qt::StrongFocus);

  // Устанавливаем асинхронное соединение
  connect(this, &GameField::InitialisationStarted, this, &GameField::SetCells,
          Qt::QueuedConnection);

  // Вызываем отложенный сигнал
  emit InitialisationStarted();
}

// Геттер свойства rowsCount
uint GameField::GetRowsNumber() const { return rowsCount_; }

// Сеттер свойства rowsCount
void GameField::SetRowsNumber(uint rowsCount) {
  if (rowsCount_ == rowsCount) return;

  rowsCount_ = rowsCount;
  emit RowsNumberChanged();
}

// Геттер свойства columnsCount
uint GameField::GetColumnsNumber() const { return columnsCount_; }

// Сеттер свойства columnsCount
void GameField::SetColumnsNumber(uint columnsCount) {
  if (columnsCount_ == columnsCount) return;

  columnsCount_ = columnsCount;
  emit ColumnsNumberChanged();
}

void GameField::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)

  QPainter painter(this);
  painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
  DrawCells(&painter);
}

void GameField::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    qDebug() << "space pressed";
  }
}

void GameField::SetCells() {
  // Задаем развер вектора согласно rowsCount_
  cellsColors_.resize(rowsCount_);

  for (uint i = 0; i < rowsCount_; i++) {
    // Изменяем размер вложенного вектора согласно columnsCount_
    cellsColors_[i].resize(columnsCount_);
  }

  ResetCellsColor();  // Перекрашиваем ячейки в базовый цвет
  setFixedSize(GetSize());  // Задам разер виджта по размру игровой сетки
}

void GameField::StartNewGame() {
  setFocus();  // Устанавливаем фокус на виджет
  qDebug() << "new game started";
}

void GameField::ResetCellsColor() {
  for (uint i = 0; i < rowsCount_; i++) {
    // Заполняем весь вектор базовым цветом
    cellsColors_[i].fill(kCellDefaultColor);
  }
}

// Получаем размер игровой сетки
QSize GameField::GetSize() const {
  return QSize(columnsCount_, rowsCount_) * kCellSize;
}

void GameField::DrawCells(QPainter *painter) {
  int positionX = 0;
  int positionY = 0;

  for (uint i = 0; i < rowsCount_; i++) {
    for (uint j = 0; j < columnsCount_; j++) {
      // Рисуем ячейку ее цветом, заданным в cellsColors_
      painter->setBrush(cellsColors_[i][j]);

      // Рисуем каждую ячейку со смещением
      painter->drawRect(positionX, positionY, positionX + kCellSize,
                        positionY + kCellSize);

      positionX += kCellSize;
    }

    positionX = 0;
    positionY += kCellSize;
  }
}
