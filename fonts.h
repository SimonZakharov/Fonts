#ifndef FONTS_H
#define FONTS_H

#define MAX_FONT_DATA 10000
#define V564_COMPILED_FONT_FILE "FONT.CPL"
#define COMPILED_FONT_FILE "FONT.FNT"
#define COMPILED_FONT_FILE_EXT ".FNT"

#define MAX_FONT_CHARS 256
#define _USE_MATH_DEFINES

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QFile>

namespace Ui {
class Fonts;
}

class Fonts : public QMainWindow
{
    Q_OBJECT

public slots:
	void symbolChanged(int x, int y);
	void displayTransparentChanged(int state);
	void setMeshSize();

public:
    explicit Fonts(QWidget *parent = nullptr);
    ~Fonts();

	void createSymbolsTable();
	void paintLetter(char letter);

	struct FONT_INDEX {
		int i;      /* index into font data array of start of data */
		int n;      /* total number of entries used by this element in data array */
	};
	
	struct COMPILED_FONT_HEADER {
		int check;
		int version;
		unsigned char pad[128 - 2 * sizeof(int)];
	};

	struct FONT {
		double x;
		double y;
	};

	struct FONT_INDEX f_index[MAX_FONT_CHARS];
	signed char f_data[MAX_FONT_DATA];      /* font data array */
	struct FONT f_dir[16];

	int ascii_read_compiled_font(void);

private:
    Ui::Fonts *ui;
	QWidget *widget;
	bool displayTransparentLines = false;
	int maxX = 420, maxY = 420;
	int step = 20;
	char selectedChar = ' ';
};

#endif // FONTS_H
