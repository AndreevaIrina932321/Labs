#pragma once


class BoolVector
{
public:
    class Rank;

public:
    using Cell = unsigned char;
	static const int CellSize = 8; // sizeof(Cell) * 8

	BoolVector(int length = CellSize);
	BoolVector(int length, bool value);
	BoolVector(const char *sample, const int sampleSize);
	BoolVector(const BoolVector &other);
	~BoolVector();

    int length() const { return m_length; }
    bool bitValue(int index) const;
	void setBitValue(int index, bool value);

    void swap(BoolVector &other) noexcept;
    void print() const;
    void input();

    void invertAll();
    bool invert(const int index);
    int getWeight() const;
    void setBits(int index, int amount, bool value);
    void setAll(bool value);



	BoolVector &operator=(const BoolVector &other);
	Rank operator[](int index);
	BoolVector operator&(const BoolVector &other) const;
	BoolVector &operator&=(const BoolVector &other);
	BoolVector operator|(const BoolVector &other) const;
	BoolVector &operator|=(const BoolVector &other);
	BoolVector operator^(const BoolVector &other) const;
	BoolVector &operator^=(const BoolVector &other);
	BoolVector operator<<(int position) const;
	BoolVector &operator<<=(int position);
	BoolVector operator>>(int position) const;
	BoolVector &operator>>=(int position);
	BoolVector operator~() const;

private:
	int _excessRankCount() const;
	static Cell _mask(int index);

private:
	Cell* m_cells = nullptr;
	int m_cellCount = 0;
	int m_length = 0;
};

class BoolVector::Rank
{
public:
    Rank() = default;
    Rank(Cell* cell, Cell mask);

    void swap(Rank &other) noexcept;

    Rank &operator=(const Rank &other);
    Rank &operator=(const bool value);

    operator bool() const;

private:
    Cell* m_cell = nullptr;
    Cell m_mask = 0;
};
