#pragma once
#include "..\Lab2_GUI\gui.hpp"
class QPushButton;
class gui_l3 : public gui {
	Q_OBJECT
public:
	gui_l3(QWidget *parent = Q_NULLPTR);
	virtual ~gui_l3();
protected:
	QPushButton *m_b;
};