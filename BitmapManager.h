#pragma once
class BitmapManager
{
public:
	BitmapManager();
	virtual ~BitmapManager();

	BitmapManager(const BitmapManager&) = delete;
	BitmapManager& operator=(const BitmapManager&) = delete;

	Bitmap* LoadBitmap(const String& fileNameRef);

private:
	static const int SIZE = 10;
	Bitmap* m_BmpPtrArr[SIZE];
	String m_FileNameArr[SIZE];
	int m_NumberOfStoredBitmaps = 0;
};

