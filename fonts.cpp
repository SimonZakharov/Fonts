#include "fonts.h"
#include "ui_fonts.h"

void Fonts::symbolChanged(int x, int y)
{
	QString letter = ui->symbolsTW->item(x, y)->text();
	ui->label->setText("Letter " + letter);
	selectedChar = letter.at(0).toLatin1();
	paintLetter(selectedChar);
}

void Fonts::displayTransparentChanged(int state)
{
	displayTransparentLines = state != 0;
	paintLetter(selectedChar);
}

void Fonts::setMeshSize()
{
	step = ui->meshSizeSpin->value();
	while (maxX % step)
	{
		maxX++; maxY++;
	}
	paintLetter(selectedChar);
}

Fonts::Fonts(QWidget *parent) : QMainWindow(parent), ui(new Ui::Fonts)
{
    ui->setupUi(this);
	ui->fontSelectCB->addItem("FONT.FNT");
	ui->fontSelectCB->addItem("FONT_S.FNT");
	ui->meshSizeSpin->setValue(step);
	createSymbolsTable();
	if (ascii_read_compiled_font() == 0)
	{
		ui->label->setText("FONT LOADED");
	}
	else
	{
		ui->label->setText("FONT NOT LOADED");
	}
	connect(ui->fontSelectCB, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) 
	{
		ui->label->setText(ui->fontSelectCB->currentText());
		QString path = ui->fontSelectCB->currentText();
		if (ascii_read_compiled_font() == 0)
		{
			ui->label->setText("FONT LOADED");
			paintLetter(selectedChar);
		}
		else
		{
			ui->label->setText("FONT NOT LOADED");
		}
	});
	connect(ui->symbolsTW, SIGNAL(cellClicked(int, int)), this, SLOT(symbolChanged(int, int)));
	connect(ui->displayTransparentCB, SIGNAL(stateChanged(int)), this, SLOT(displayTransparentChanged(int)));
	connect(ui->setMeshButton, SIGNAL(clicked()), this, SLOT(setMeshSize()));
}

Fonts::~Fonts()
{
    delete ui;
}

void Fonts::createSymbolsTable()
{
	int itemWidth = ui->symbolsTW->width() / 16;
	int itemHeight = ui->symbolsTW->height() / 16;
	for (int row = 0; row < ui->symbolsTW->rowCount(); row++)
	{
		ui->symbolsTW->setRowHeight(row, itemWidth);
		ui->symbolsTW->setColumnWidth(row, itemHeight);
		for (int col = 0; col < ui->symbolsTW->columnCount(); col++)
		{
			QTableWidgetItem *item = new QTableWidgetItem();
			item->data(Qt::TextDate);
			char code = (char)(row * 16 + col);
			QString s = ""; s += code;
			item->setText(s);
			ui->symbolsTW->setItem(row, col, item);
		}
	}
	
}

void Fonts::paintLetter(char c)
{
	QPixmap pixmap(maxX, maxY);
	pixmap.fill(QColor("white"));
	QPainter painter(&pixmap);
	QPen pen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap);
	painter.setPen(pen);
	for (int x = 0; x <= maxX; x += step)
	{
		painter.drawLine(x, 1, x, maxY);
	}
	for (int y = 0; y <= maxY; y += step)
	{
		painter.drawLine(1, y, maxX, y);
	}
	pen.setColor(Qt::red);
	pen.setWidth(2);
	painter.setPen(pen);
	double x1 = step, y1 = step, scale = step;
	double sin_ran = sin(0), cos_ran = cos(0);
	double x2 = x1, y2 = y1;
	int i = (int)c;

	signed char *dp = &f_data[f_index[i].i];
	int count = f_index[i].n;
	register int low, high;
	while (count-- > 0)
	{
		low = (*dp) & 0x0f;
		high = ((*dp++) & 0xf0) >> 4;
		if (high == 0) {
			switch (low) {
			case 8:    /* relative move */
				x2 = x1 + (((*dp)*cos_ran - (*(dp + 1))*sin_ran) * scale);
				y2 = y1 + (((*dp)*sin_ran + (*(dp + 1))*cos_ran) * scale);
				dp += 2;
				count -= 2;
				painter.drawLine(x1, -y1 + maxY, x2, -y2 + maxY);
				x1 = x2;
				y1 = y2;
				painter.drawEllipse(x1 - 5, -y1 + maxY - 5, 10, 10);
				break;
			case 9:    /* lots of relative moves */
				while (count > 0) {
					dp += 2;
					count -= 2;
					if (((dp - 2) == 0) && ((dp - 1) == 0))
						break;
					x2 = x1 + (((*(dp - 2))*cos_ran - (*(dp - 1))*sin_ran) * scale);
					y2 = y1 + (((*(dp - 2))*sin_ran + (*(dp - 1))*cos_ran) * scale);
					painter.drawLine(x1, -y1 + maxY, x2, -y2 + maxY);
					x1 = x2;
					y1 = y2;
				}
				painter.drawEllipse(x1 - 5, -y1 + maxY - 5, 10, 10);
				break;
			case 2:    /* pen up */
				if (displayTransparentLines)
				{
					pen.setColor(Qt::green); painter.setPen(pen);
				}
				else
				{
					pen.setColor(Qt::transparent); painter.setPen(pen);
				}
				break;
			case 1:    /* pen down */
				pen.setColor(Qt::red); painter.setPen(pen);
				break;
			case 0:    /* end of data */
				count = 0;
				break;
			}
		}
		else
		{
			struct FONT *pp = &f_dir[low];
			x2 = x1 + ((pp->x*cos_ran - pp->y*sin_ran) * high * scale);
			y2 = y1 + ((pp->x*sin_ran + pp->y*cos_ran) * high * scale);
			x1 = x2;
			y1 = y2;
		}
	}

	ui->paintQL->setPixmap(pixmap);
}

int Fonts::ascii_read_compiled_font(void)
{
	QByteArray ba = ui->fontSelectCB->currentText().toLatin1();
	const char *font_file1 = ba.data();
	int check;
	int i, temp;
	FILE *stream;
	struct COMPILED_FONT_HEADER cfh1;

	/* initialize font array */
	for (i = 0; i < MAX_FONT_CHARS; i++) {
		f_index[i].i = 0;
		f_index[i].n = 0;
	}
	int f_cnt = 0;
	/* tell rest of software that font is not loaded */
	int c_ascii_font_ready = 0;
	stream = fopen(font_file1, "rb");
	if (stream == NULL) {
		printf("ERROR OPENING COMPILED FONT FILE : \"%s\"", font_file1);
		return(1);
	}
	/* read file header */
	if (fread((char *)&cfh1, sizeof(cfh1), 1, stream) != 1)
		goto f_o_o_abort;

	/* read compiled font index */
	if (fread((char *)&check, sizeof(int), 1, stream) != 1)
		goto f_o_o_abort;

	temp = 0;
	if (fread((char *)&temp, sizeof(int), 1, stream) != 1)
		goto f_o_o_abort;
	if (temp > (int) sizeof(f_index)) {
		printf("COMPILED FONT INDEX IS TOO LARGE");
		goto f_o_o_msg_abort;
	}
	if (fread((char *)&f_index[0], temp, 1, stream) != 1)
		goto f_o_o_abort;

	/* read compiled font data */
	if (fread((char *)&check, sizeof(int), 1, stream) != 1)
		goto f_o_o_abort;

	temp = 0;
	if (fread((char *)&temp, sizeof(int), 1, stream) != 1)
		goto f_o_o_abort;
	if (temp > (int) sizeof(f_data)) {
		printf("COMPILED FONT DATA IS TOO LARGE");
		goto f_o_o_msg_abort;
	}
	if (fread((char *)&f_data[0], temp, 1, stream) != 1)
		goto f_o_o_abort;
	f_cnt = temp;

	fclose(stream);
	
	f_dir[0].x = 1.0;
	f_dir[1].x = 1.0;
	f_dir[2].x = 1.0;
	f_dir[3].x = 0.5;
	f_dir[4].x = 0.0;
	f_dir[5].x = -0.5;
	f_dir[6].x = -1.0;
	f_dir[7].x = -1.0;
	f_dir[8].x = -1.0;
	f_dir[9].x = -1.0;
	f_dir[10].x = -1.0;
	f_dir[11].x = -0.5;
	f_dir[12].x = 0.0;
	f_dir[13].x = 0.5;
	f_dir[14].x = 1.0;
	f_dir[15].x = 1.0;
	f_dir[0].y = 0.0;
	f_dir[1].y = 0.5;
	f_dir[2].y = 1.0;
	f_dir[3].y = 1.0;
	f_dir[4].y = 1.0;
	f_dir[5].y = 1.0;
	f_dir[6].y = 1.0;
	f_dir[7].y = 0.5;
	f_dir[8].y = 0.0;
	f_dir[9].y = -0.5;
	f_dir[10].y = -1.0;
	f_dir[11].y = -1.0;
	f_dir[12].y = -1.0;
	f_dir[13].y = -1.0;
	f_dir[14].y = -1.0;
	f_dir[15].y = -0.5;

	c_ascii_font_ready = 1;
	return(0);

f_o_o_abort:
	printf("ERROR READING COMPILED FONT FILE : \"%s\"", font_file1);
f_o_o_msg_abort:
	fclose(stream);
	/* initialize font array */
	for (i = 0; i < MAX_FONT_CHARS; i++) {
		f_index[i].i = 0;
		f_index[i].n = 0;
	}
	f_cnt = 0;
	/* tell rest of software that font is not loaded */
	c_ascii_font_ready = 0;
	return(1);
}