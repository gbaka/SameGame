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
	// ������� ������� ����, ���� ��� �� ����
	if (!m_arr_board)
	{
		CreateBoard();
	}

	// ������������� ������� ����� ��������� ����
	for (int row = 0; row < m_rows; ++row)
	{
		for (int col = 0; col < m_cols; ++col)
		{
			m_arr_board[row][col] = (rand() % 3) + 1;
		}
	}

	// ������������� ���������� ���������� ������
	m_remaining = m_rows * m_cols;
}

COLORREF CSameGameBoard::GetBoardSpace(int p_row, int p_col)
{
	if (p_row < 0 || p_row >= m_rows || p_col < 0 || p_col >= m_cols)	
	{
		// ���� ������� ������� �� ������� �������� ���� - ���������� ���� ����
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
	// ���� ������� ���� �� ����� - ������� ���
	if (m_arr_board) {
		DeleteBoard();
	}
	m_arr_board = new int*[m_rows];
	for (int row = 0; row < m_rows; ++row)
	{
		// ������� ������� � � ������� uniform-������������� �������� ��� (0 - ��� ����� ����)
		m_arr_board[row] = new int[m_cols] {};
	}
}

int CSameGameBoard::DeleteBlocks(int p_row, int p_col)
{
	// ��������� �� ������������ ������� ������ � �������
	if (p_row < 0 || p_row >= m_rows || p_col < 0 || p_col >= m_cols)
		return -1;

	// ���� ���� ��� ����� ���� ����, �� ������� ��� �� ���������
	int n_color = m_arr_board[p_row][p_col];
	if (n_color == 0)
		return -1;

	// ������� ���������, ���� �� ����������� ����� � ��� �� ������
	int n_count = -1;
	if ((p_row - 1 >= 0 && m_arr_board[p_row - 1][p_col] == n_color) ||
		(p_row + 1 < m_rows && m_arr_board[p_row + 1][p_col] == n_color) ||
		(p_col - 1 >= 0 && m_arr_board[p_row][p_col - 1] == n_color) ||
		(p_col + 1 < m_cols && m_arr_board[p_row][p_col + 1] == n_color))
	{
		// ����� ���������� �������� ������� ��� �������� ����������� ������ ������ �����...    
		m_arr_board[p_row][p_col] = 0;
		n_count = 1;

		// ...������...
		n_count +=
			DeleteNeighborBlocks(p_row - 1, p_col, n_color, DIRECTION_DOWN);

		// ...�����...
		n_count +=
			DeleteNeighborBlocks(p_row + 1, p_col, n_color, DIRECTION_UP);

		// ...�����...
		n_count +=
			DeleteNeighborBlocks(p_row, p_col - 1, n_color, DIRECTION_RIGHT);

		// ...������
		n_count +=
			DeleteNeighborBlocks(p_row, p_col + 1, n_color, DIRECTION_LEFT);

		// � ����� ��������� ������� ����� ������� �����
		CompactBoard();

		// �������� ����� ��������� ������ �� ������ ���������� ������
		m_remaining -= n_count;
	}
	// ���������� ���������� ��������� ������
	return n_count;
}

int CSameGameBoard::DeleteNeighborBlocks(int p_row, int p_col, int p_color, Direction p_direction)
{
	// ��������� �� ������������ ������� ������ � �������
	if (p_row < 0 || p_row >= m_rows || p_col < 0 || p_col >= m_cols)
		return 0;

	// �������� �� ��, ��� ���� ����� ��� �� ����
	if (m_arr_board[p_row][p_col] != p_color)
		return 0;
	int n_count = 1;
	m_arr_board[p_row][p_col] = 0;

	// ��������� �������� �����������

	if (p_direction != DIRECTION_UP)
		n_count += DeleteNeighborBlocks(p_row - 1, p_col, p_color, DIRECTION_DOWN);
	if (p_direction != DIRECTION_DOWN)
		n_count += DeleteNeighborBlocks(p_row + 1, p_col, p_color, DIRECTION_UP);
	if (p_direction != DIRECTION_LEFT)
		n_count += DeleteNeighborBlocks(p_row, p_col - 1, p_color, DIRECTION_RIGHT);
	if (p_direction != DIRECTION_RIGHT)
		n_count += DeleteNeighborBlocks(p_row, p_col + 1, p_color, DIRECTION_LEFT);

	// ���������� ����� ���������� ��������� ������
	return n_count;
}


void CSameGameBoard::CompactBoard()
{
	// ������� �� �� �������� ����
	for (int col = 0; col < m_cols; col++)
	{
		int n_next_empty_row = m_rows - 1;
		int n_next_occupied_row= n_next_empty_row;
		while (n_next_occupied_row>= 0 && n_next_empty_row >= 0)
		{
			// ������� ������ ������
			while (n_next_empty_row >= 0 &&
				m_arr_board[n_next_empty_row][col] != 0)
				n_next_empty_row--;
			if (n_next_empty_row >= 0)
			{
				// ����� ������� ������� ������, ������������� ������ �� ������
				n_next_occupied_row= n_next_empty_row - 1;
				while (n_next_occupied_row>= 0 &&
					m_arr_board[n_next_occupied_row][col] == 0)
					n_next_occupied_row--;
				if (n_next_occupied_row>= 0)
				{
					// ������ ���������� ����� � ������� ������ �� ������
					m_arr_board[n_next_empty_row][col] =
						m_arr_board[n_next_occupied_row][col];
					m_arr_board[n_next_occupied_row][col] = 0;
				}
			}
		}
	}
	// ����� ��, ��� ��������� ������, ������� �����
	int n_next_empty_col = 0;
	int n_next_occupied_col = n_next_empty_col;
	while (n_next_empty_col < m_cols && n_next_occupied_col < m_cols)
	{
		// ������� ������ �������
		while (n_next_empty_col < m_cols &&
			m_arr_board[m_rows - 1][n_next_empty_col] != 0)
			n_next_empty_col++;
		if (n_next_empty_col < m_cols)
		{
			// ����� ������� ������� �������, ������������� ������ �� ������
			n_next_occupied_col = n_next_empty_col + 1;
			while (n_next_occupied_col < m_cols &&
				m_arr_board[m_rows - 1][n_next_occupied_col] == 0)
				n_next_occupied_col++;
			if (n_next_occupied_col < m_cols)
			{
				// �������� ���� ������� �����
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
	// ��������� ������� �� �������� (�����-�������)
	for (int col = 0; col < m_cols; col++)
	{
		// ������ �� ������� (�����-�����)
		for (int row = m_rows - 1; row >= 0; row--)
		{
			int n_color = m_arr_board[row][col];

			// ���� �� ������ �� ������ � ������ ����, �� ��� ������, ��� ������� ��� ���������
			if (n_color == 0)
				break;
			else
			{
				// ��������� ������ � ������
				if (row - 1 >= 0 &&
					m_arr_board[row - 1][col] == n_color)
					return false;
				else if (col + 1 < m_cols &&
					m_arr_board[row][col + 1] == n_color)
					return false;
			}
		}
	}
	// ���� ����������� ������ �� ����������, ��
	return true;
}

