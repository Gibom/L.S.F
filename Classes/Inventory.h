#ifndef __INVENTORY__
#define __INVENTORY__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "CustomTableViewCell.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class Inventory 
	: public cocos2d::LayerColor
	, public cocos2d::extension::TableViewDataSource
	, public cocos2d::extension::TableViewDelegate

{
public:
	virtual bool init();
	
	Size winSize;
	TableView* inventory;
	TableView* CreateTable(int row);
	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView*table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView* table);
};

#endif // __INVENTORY__
