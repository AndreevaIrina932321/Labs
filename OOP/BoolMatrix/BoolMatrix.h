#pragma once
#include "../BoolVector/BoolVector.h"
#include "../Array/Array.h"

class BoolMatrix
{

public:
    using Cell = unsigned char;
	static const int CellSize = 8; // sizeof(Cell) * 8

	BoolMatrix(const int rowsCount = CellSize, const int columnCount = CellSize, const bool value = false);
	BoolMatrix(char **sample, const int rowsCount, const int length);
	BoolMatrix(const BoolMatrix &other);

    int getColumnsNumber() const { return m_columnsCount; }
    int getRowsNumber() const { return m_rowsCount; }

    void swap(BoolMatrix &other) noexcept;

    void print() const;
    void input();

    int getWeight() const;
    int rowWeight(int rowIndex) const;
    int collumnWeight(int collumnIndex) const;

    BoolVector rowsConjunction() const;
    BoolVector rowsDisjunction() const;

    void setBit(const int rowIndex, const int columnIndex, const bool value);
    void setSequence(const int rowIndex, const int columnIndex, const int amount, const bool value);

    bool invertBit(const int rowIndex, const int columnIndex);
    void invertSequence(const int rowIndex, const int columnIndex, const int amount);

	BoolMatrix &operator=(const BoolMatrix &other);
	BoolVector &operator[](int index);
	const BoolVector &operator[](const int index) const;
	BoolMatrix operator&(const BoolMatrix &other) const;
	BoolMatrix &operator&=(const BoolMatrix &other);
	BoolMatrix operator|(const BoolMatrix &other) const;
	BoolMatrix &operator|=(const BoolMatrix &other);
	BoolMatrix operator^(const BoolMatrix &other) const;
	BoolMatrix &operator^=(const BoolMatrix &other);
	BoolMatrix operator~() const;

	friend std::ostream& operator<<(std::ostream &out, const BoolMatrix &bm);
    friend std::istream& operator>>(std::istream &in, BoolMatrix &bm);

private:
	int m_columnsCount = 0;
	int m_rowsCount = 0;
	Array<BoolVector> m_rows;
};
