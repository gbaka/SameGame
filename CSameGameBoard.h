#pragma once
class CSameGameBoard
{
private:
	// ��������� �� ��������� ������, ��������������� ��������� �������� ����
	int** m_arr_board;

	// ������ ������: 0 � ��� ���� ����, 1-3 � ��� ����� ������
	COLORREF m_arr_colors[4];

	int m_width;
	int m_height;
	int m_cols;
	int m_rows;

private:
	// ������� ��� �������� �������� ���� � ��������� ������ ��� ����
	void CreateBoard();

public:
	CSameGameBoard();

	~CSameGameBoard();

	// ����� ��� ��������� ����������� ������ � ������ ����
	void SetupBoard();

	// ����� ��� ��������� ����� ������������ ������ �������� ����
	COLORREF GetBoardSpace(int p_row, int p_col);

	// ������� ��� ��������� ���������� � ���������� �������� ����
	int GetWidth()   const { return m_width;  }
	int GetHeight()  const { return m_height; }
	int GetCols()    const { return m_cols;   }
	int GetRows()    const { return m_rows;   }

	// ����� ��� �������� �������� ���� � ������������ ������
	void DeleteBoard();
};

