#pragma once
class CSameGameBoard
{
private:
	// ��������� �� ��������� ������, ��������������� ��������� �������� ����
	int** m_arr_board;

	// ������ ������: 0 � ��� ���� ����, 1-7 � ��� ����� ������
	COLORREF m_arr_colors[8];

	// ���������� ���������� ������
	int m_remaining;

	int m_colors;
	int m_width;
	int m_height;
	int m_cols;
	int m_rows;

private:
	// ������� ��� �������� �������� ���� � ��������� ������ ��� ����
	void CreateBoard();

	// ������������ � ���������� ����������� (������ �� ������) ����������� ���
	// ���������� ������ ������� �������� ������
	enum Direction
	{
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT
	};

	// ��������������� ����������� ������� ��� �������� ����������� ������
	int DeleteNeighborBlocks(int p_row, int p_col, int p_color, Direction p_direction);

	// ������� ��� ������ ����� ����� ����, ��� ���� ������� �����
	void CompactBoard();

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

	// ������� ��� ��������� ���������� �������� ����
	void SetWidth(int p_width)   { m_width = (p_width >= 3) ? p_width : 3;    }
	void SetHeight(int p_height) { m_height = (p_height >= 3) ? p_height : 3; }
	void SetColumns(int p_cols)  { m_cols = (p_cols >= 5) ? p_cols : 5;       }
	void SetRows(int p_rows)     { m_rows = (p_rows >= 5) ? p_rows : 5;       }

	// �� ��������� ����?
	bool IsGameOver() const;

	// ������� ���������� ���������� ������
	int GetRemainingCount() const { return m_remaining; }

	// ������� ��� �������� ���� ����������� ������
	int DeleteBlocks(int p_row, int p_col);

	// ����� ��� �������� �������� ���� � ������������ ������
	void DeleteBoard();

	// ������ � c������ ��� ���������� ������
	int GetNumColors() { return m_colors; }

	void SetNumColors(int p_colors)
	{
		m_colors = (p_colors >= 3 && p_colors <= 7) ? p_colors : m_colors;
	}
};

