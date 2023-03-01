#pragma once
class CSameGameBoard
{
private:
	// ”казатель на двумерный массив, характеризующий состо€ние игрового пол€
	int** m_arr_board;

	// —писок цветов: 0 Ц это цвет фона, 1-3 Ц это цвета блоков
	COLORREF m_arr_colors[4];

	int m_width;
	int m_height;
	int m_cols;
	int m_rows;

private:
	// ‘ункци€ дл€ создани€ игрового пол€ и выделени€ пам€ти под него
	void CreateBoard();

public:
	CSameGameBoard();

	~CSameGameBoard();

	// ћетод дл€ рандомной расстановки блоков в начале игры
	void SetupBoard();

	// ћетод дл€ получени€ цвета определенной клетки игрового пол€
	COLORREF GetBoardSpace(int p_row, int p_col);

	// √еттеры дл€ получени€ информации о параметрах игрового пол€
	int GetWidth()   const { return m_width;  }
	int GetHeight()  const { return m_height; }
	int GetCols()    const { return m_cols;   }
	int GetRows()    const { return m_rows;   }

	// ћетод дл€ удалени€ игрового пол€ и освобождени€ пам€ти
	void DeleteBoard();
};

