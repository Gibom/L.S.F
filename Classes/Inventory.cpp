#include "Inventory.h"

USING_NS_CC;


bool Inventory::init()
{
	/////////////////////////////

	return true;
}

TableView* Inventory::CreateTable(int row)
{
	winSize = Director::getInstance()->getWinSize();

	inventory = TableView::create(this, Size(640, 60));
	inventory->setDirection(ScrollView::Direction::HORIZONTAL);
	inventory->setPosition(Vec2(43, (winSize.height - 318) - (64 * row)));
	inventory->setDelegate(this);
	inventory->setTag(row);

	inventory->reloadData();

	return inventory;
}

void Inventory::tableCellTouched(TableView* table, TableViewCell* cell)
{
	LSFSingleton::getInstance()->tableTag = table->getTag();
	LSFSingleton::getInstance()->cellIdx = cell->getIdx();
	LSFSingleton::getInstance()->cellTag = cell->getTag();
	
	log("Table Tag : %d\nCell touched at index : %ld\nSprite Tag :%d",
		table->getTag(), cell->getIdx(), cell->getTag());
	
	
	log("LSFSingleton::getInstance()->tableTag = table->getTag() %d", LSFSingleton::getInstance()->tableTag);
	log("LSFSingleton::getInstance()->cellIdx = cell->getIdx() %d", LSFSingleton::getInstance()->cellIdx);
	log("LSFSingleton::getInstance()->cellTag = cell->getTag() %d", LSFSingleton::getInstance()->cellTag);
}

Size Inventory::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
	/*if (idx == 2)
	{
		return Size(100, 100);
	}*/
	return Size(64, 60);
}

TableViewCell* Inventory::tableCellAtIndex(TableView* table, ssize_t idx)
{
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell* cell = table->dequeueCell();
	if (!cell)
	{
		cell = new CustomTableViewCell();
		cell->autorelease();
		auto sprite = Sprite::create("Sprites/Icon.png");
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
		sprite->setTag(0);
		cell->addChild(sprite);
	}
	else
	{
		/*auto label = (LabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());*/
	}

	return cell;
}

ssize_t Inventory::numberOfCellsInTableView(TableView* table)
{
	return 10;
}