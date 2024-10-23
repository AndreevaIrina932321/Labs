#pragma once


class BoolVector
{
	using Cell = unsigned int;
	static const int CellSize = 8; // sizeof(Cell) * 8

public:
	BoolVector(int length = CellSize);
	BoolVector(int length, bool value);
	~BoolVector();

	bool bitValue(int index) const;
	void setBitValue(int index, bool value);

	BoolVector& operator=(const BoolVector& other);
	//bool operator[](int index); // TODO: implement

private:
	int _excessRankCount() const;

private:
	Cell* m_cells = nullptr;
	int m_cellCount = 0;
	int m_length = 0;
};
