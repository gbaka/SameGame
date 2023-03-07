#include "pch.h"
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard()
	: m_arr_board(nullptr),
	m_cols(15),   m_rows(15),
	m_height(35), m_width(35),
	m_remaining(0),
	m_arr_colors
	{ 
	RGB(0,0,0), RGB(255,0,0),
	RGB(255,255,64), RGB(0,0,255)
	}
{
	SetupBoard();
}

CSameGameBoard::~CSameGameBoard()
{
	DeleteBoard();
}

void CSameGameBoard::SetupBoard()
{
	// Создаем игровое поле, если его не было
	if (!m_arr_board)
	{
		CreateBoard();
	}

	// Устанавливаем каждому блоку случайный цвет
	for (int row = 0; row < m_rows; ++row)
	{
		for (int col = 0; col < m_cols; ++col)
		{
			m_arr_board[row][col] = (rand() % 3) + 1;
		}
	}

	// Устанавливаем количество оставшихся блоков
	m_remaining = m_rows * m_cols;
}

COLORREF CSameGameBoard::GetBoardSpace(int p_row, int p_col)
{
	if (p_row < 0 || p_row >= m_rows || p_col < 0 || p_col >= m_cols)	
	{
		// Если участок выходит за пределы игрового поля - возвращаем цвет фона
		return m_arr_colors[0];
	}
	return  m_arr_colors[m_arr_board[p_row][p_col]];
}

void CSameGameBoard::DeleteBoard()
{
	if (m_arr_board)
	{
		for (int row = 0; row < m_rows; ++row)
		{
			delete[] m_arr_board[row];
			m_arr_board[row] = nullptr;
		}
		delete[] m_arr_board;
		m_arr_board = nullptr;
	}
}

void CSameGameBoard::CreateBoard()
{
	// Если игровое поле не пусто - удаляем его
	if (m_arr_board) {
		DeleteBoard();
	}
	m_arr_board = new int*[m_rows];
	for (int row = 0; row < m_rows; ++row)
	{
		// Создаем столбец и с помощью uniform-инициализации зануляем его (0 - код цвета фона)
		m_arr_board[row] = new int[m_cols] {};
	}
}

int CSameGameBoard::DeleteBlocks(int p_row, int p_col)
{
	// Проверяем на корректность индексы ячейки и столбца
	if (p_row < 0 || p_row >= m_rows || p_col < 0 || p_col >= m_cols)
		return -1;

	// Если блок уже имеет цвет фона, то удалить его не получится
	int n_color = m_arr_board[p_row][p_col];
	if (n_color == 0)
		return -1;

	// Сначала проверяем, есть ли примыкающие блоки с тем же цветом
	int n_count = -1;
	if ((p_row - 1 >= 0 && m_arr_board[p_row - 1][p_col] == n_color) ||
		(p_row + 1 < m_rows && m_arr_board[p_row + 1][p_col] == n_color) ||
		(p_col - 1 >= 0 && m_arr_board[p_row][p_col - 1] == n_color) ||
		(p_col + 1 < m_cols && m_arr_board[p_row][p_col + 1] == n_color))
	{
		// Затем рекурсивно вызываем функцию для удаления примыкающих блоков одного цвета...    
		m_arr_board[p_row][p_col] = 0;
		n_count = 1;

		// ...сверху...
		n_count +=
			DeleteNeighborBlocks(p_row - 1, p_col, n_color, DIRECTION_DOWN);

		// ...снизу...
		n_count +=
			DeleteNeighborBlocks(p_row + 1, p_col, n_color, DIRECTION_UP);

		// ...слева...
		n_count +=
			DeleteNeighborBlocks(p_row, p_col - 1, n_color, DIRECTION_RIGHT);

		// ...справа
		n_count +=
			DeleteNeighborBlocks(p_row, p_col + 1, n_color, DIRECTION_LEFT);

		// В конце выполняем «сжатие» нашей игровой доски
		CompactBoard();

		// Вычитаем число удаленных блоков из общего количества блоков
		m_remaining -= n_count;
	}
	// Возвращаем количество удаленных блоков
	return n_count;
}

int CSameGameBoard::DeleteNeighborBlocks(int p_row, int p_col, int p_color, Direction p_direction)
{
	// Проверяем на корректность индексы ячейки и столбца
	if (p_row < 0 || p_row >= m_rows || p_col < 0 || p_col >= m_cols)
		return 0;

	// Проверка на то, что блок имеет тот же цвет
	if (m_arr_board[p_row][p_col] != p_color)
		return 0;
	int n_count = 1;
	m_arr_board[p_row][p_col] = 0;

	// Выполняем проверку направлений

	if (p_direction != DIRECTION_UP)
		n_count += DeleteNeighborBlocks(p_row - 1, p_col, p_color, DIRECTION_DOWN);
	if (p_direction != DIRECTION_DOWN)
		n_count += DeleteNeighborBlocks(p_row + 1, p_col, p_color, DIRECTION_UP);
	if (p_direction != DIRECTION_LEFT)
		n_count += DeleteNeighborBlocks(p_row, p_col - 1, p_color, DIRECTION_RIGHT);
	if (p_direction != DIRECTION_RIGHT)
		n_count += DeleteNeighborBlocks(p_row, p_col + 1, p_color, DIRECTION_LEFT);

	// Возвращаем общее количество удаленных блоков
	return n_count;
}


void CSameGameBoard::CompactBoard()
{
	// Сначала мы всё сдвигаем вниз
	for (int col = 0; col < m_cols; col++)
	{
		int n_next_empty_row = m_rows - 1;
		int n_next_occupied_row= n_next_empty_row;
		while (n_next_occupied_row>= 0 && n_next_empty_row >= 0)
		{
			// Находим пустую строку
			while (n_next_empty_row >= 0 &&
				m_arr_board[n_next_empty_row][col] != 0)
				n_next_empty_row--;
			if (n_next_empty_row >= 0)
			{
				// Затем находим занятую строку, расположенную следом за пустой
				n_next_occupied_row= n_next_empty_row - 1;
				while (n_next_occupied_row>= 0 &&
					m_arr_board[n_next_occupied_row][col] == 0)
					n_next_occupied_row--;
				if (n_next_occupied_row>= 0)
				{
					// Теперь перемещаем блоки с занятой строки на пустую
					m_arr_board[n_next_empty_row][col] =
						m_arr_board[n_next_occupied_row][col];
					m_arr_board[n_next_occupied_row][col] = 0;
				}
			}
		}
	}
	// Затем всё, что находится справа, смещаем влево
	int n_next_empty_col = 0;
	int n_next_occupied_col = n_next_empty_col;
	while (n_next_empty_col < m_cols && n_next_occupied_col < m_cols)
	{
		// Находим пустой столбец
		while (n_next_empty_col < m_cols &&
			m_arr_board[m_rows - 1][n_next_empty_col] != 0)
			n_next_empty_col++;
		if (n_next_empty_col < m_cols)
		{
			// Затем находим занятый столбец, расположенный следом за пустым
			n_next_occupied_col = n_next_empty_col + 1;
			while (n_next_occupied_col < m_cols &&
				m_arr_board[m_rows - 1][n_next_occupied_col] == 0)
				n_next_occupied_col++;
			if (n_next_occupied_col < m_cols)
			{
				// Сдвигаем весь столбец влево
				for (int row = 0; row < m_rows; row++)
				{
					m_arr_board[row][n_next_empty_col] = m_arr_board[row][n_next_occupied_col];
					m_arr_board[row][n_next_occupied_col] = 0;
				}
			}
		}
	}
}

bool CSameGameBoard::IsGameOver() const
{
	// Проверяем столбец за столбцом (слева-направо)
	for (int col = 0; col < m_cols; col++)
	{
		// Строку за строкой (снизу-вверх)
		for (int row = m_rows - 1; row >= 0; row--)
		{
			int n_color = m_arr_board[row][col];

			// Если мы попали на ячейку с цветом фона, то это значит, что столбец уже уничтожен
			if (n_color == 0)
				break;
			else
			{
				// Проверяем сверху и справа
				if (row - 1 >= 0 &&
					m_arr_board[row - 1][col] == n_color)
					return false;
				else if (col + 1 < m_cols &&
					m_arr_board[row][col + 1] == n_color)
					return false;
			}
		}
	}
	// Если примыкающих блоков не обнаружено, то
	return true;
}

