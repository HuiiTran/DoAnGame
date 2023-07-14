#pragma once
class CData
{
private:
	//game scene
	int Level;
	int Score;
	int Life;
	int Coin;
	int Card_1;
	int Card_2;
	int Card_3;
public:
	CData();
	void SetLevel(int l) { this->Level = l; }
	void SetScore(int S) { this->Score = S; }
	void SetLife(int L) { this->Life = L; }
	void SetCoin(int c) { this->Coin = c; }
	void SetCard_1(int card) { this->Card_1 = card; }
	void SetCard_2(int card) { this->Card_2 = card; }
	void SetCard_3(int card) { this->Card_3 = card; }

	int GetLevel() { return this->Level; }
	int GetScore() { return this->Score; }
	int GetLife() { return this->Life; }
	int GetCoin() { return this->Coin; }
	int GetCard_1() { return this->Card_1; }
	int GetCard_2() { return this->Card_2; }
	int GetCard_3() { return this->Card_3; }

	void ResetGame();
};

