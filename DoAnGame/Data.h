#pragma once
class CData
{
private:
	//game scene
	int Level;
	int Score;
	int Life;
	int Coin;
public:
	CData();
	void SetLevel(int l) { this->Level = l; }
	void SetScore(int S) { this->Score = S; }
	void SetLife(int L) { this->Life = L; }
	void SetCoin(int c) { this->Coin = c; }

	int GetLevel() { return this->Level; }
	int GetScore() { return this->Score; }
	int GetLife() { return this->Life; }
	int GetCoin() { return this->Coin; }

	
};

