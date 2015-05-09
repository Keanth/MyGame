#pragma once
class DialogueTree
{
public:
	DialogueTree();
	virtual ~DialogueTree();

	DialogueTree(const DialogueTree&) = delete;
	DialogueTree& operator=(const DialogueTree&) = delete;

	void Tick(double deltaTime);
	void Paint();

private:
	void DialogueLoop();
	void Cursor(int number, double deltaTime);
	RECT2 CursorRect();

	std::vector<String> m_DialogueTreeArr;
	int m_Pointer = 0;

	//Dialogue Boxes
	enum class DialogueState
	{
		CURLYHAPPY,
		QUOTE
	};
	DialogueState m_DialogueState = DialogueState::CURLYHAPPY;

	Font* m_FontPtr = nullptr;
	Bitmap* m_BmpCurlyHappyPtr = nullptr;
	Bitmap* m_BmpQuotePtr = nullptr;

	//point thingy
	Bitmap* m_BmpCursorPtr = nullptr;
	double m_CursorCount = 0.0;
	bool m_IsCursor = false;
};

