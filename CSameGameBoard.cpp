#include "pch.h"
#include "CSameGameBoard.h"

CSameGameBoard::CSameGameBoard()
	: m_arr_board(nullptr),
	m_cols(15),   m_rows(15),
	m_height(35), m_width(35),
	m_arr_colors
	{ 
	RGB(0,0,0), RGB(255,0,0),
	RGB(255,255,64), RGB(0,0,255)
	}
{
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
	for (int row = 0; row < m_rows; ++row)
	{
		for (int col = 0; col < m_cols; ++col)
		{
			m_arr_board[row][col] = (rand() % 3) + 1;
		}
	}
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

