#pragma once
class CSameGameBoard
{
private:
	// Указатель на двумерный массив, характеризующий состояние игрового поля
	int** m_arr_board;

	// Список цветов: 0 – это цвет фона, 1-7 – это цвета блоков
	COLORREF m_arr_colors[8];

	// Количество оставшихся блоков
	int m_remaining;

	int m_colors;
	int m_width;
	int m_height;
	int m_cols;
	int m_rows;

private:
	// Функция для создания игрового поля и выделения памяти под него
	void CreateBoard();

	// Перечисление с вариантами направления (откуда мы пришли) потребуется для
	// корректной работы функции удаления блоков
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	// Вспомогательная рекурсивная функция для удаления примыкающих блоков
	int DeleteNeighborBlocks(int p_row, int p_col, int p_color, Direction p_direction);

	// Функция для сжатия доски после того, как были удалены блоки
	void CompactBoard();

public:
	CSameGameBoard();

	~CSameGameBoard();

	// Метод для рандомной расстановки блоков в начале игры
	void SetupBoard();

	// Метод для получения цвета определенной клетки игрового поля
	COLORREF GetBoardSpace(int p_row, int p_col);

	// Геттеры для получения информации о параметрах игрового поля
	int GetWidth()   const { return m_width;  }
	int GetHeight()  const { return m_height; }
	int GetCols()    const { return m_cols;   }
	int GetRows()    const { return m_rows;   }

	// Сеттеры для изменения параметров игрового поля
	void SetWidth(int p_width)   { m_width = (p_width >= 3) ? p_width : 3;    }
	void SetHeight(int p_height) { m_height = (p_height >= 3) ? p_height : 3; }
	void SetColumns(int p_cols)  { m_cols = (p_cols >= 5) ? p_cols : 5;       }
	void SetRows(int p_rows)     { m_rows = (p_rows >= 5) ? p_rows : 5;       }

	// Мы закончили игру?
	bool IsGameOver() const;

	// Подсчет количества оставшихся блоков
	int GetRemainingCount() const { return m_remaining; }

	// Функция для удаления всех примыкающих блоков
	int DeleteBlocks(int p_row, int p_col);

	// Метод для удаления игрового поля и освобождения памяти
	void DeleteBoard();

	// Гетеры и cеттеры для количества цветов
	int GetNumColors() { return m_colors; }

	void SetNumColors(int p_colors)
	{
		m_colors = (p_colors >= 3 && p_colors <= 7) ? p_colors : m_colors;
	}
};

