//
//  Overview.h
//  TableView01
//
//  Created by MAEDAHAJIME on 2015/02/18.
//
//

#ifndef __TableView01__Overview__
#define __TableView01__Overview__

#include <iostream>
#include "cocos2d.h"
#include <extensions/cocos-ext.h>

USING_NS_CC;
using namespace extension;

class Overview : public Layer,
public TableViewDataSource,
public TableViewDelegate
{
    Size window_size;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //TableViewDataSourceの抽象メソッド
    virtual Size cellSizeForTable(TableView* table);
    virtual TableViewCell* tableCellAtIndex(TableView* table,ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(TableView* table);
    
    //TableViewDelegateの抽象メソッド
    virtual void tableCellTouched(TableView* table,TableViewCell* cell);
    
    //TableViewDelegateが継承しているScrollViewの抽象メソッド
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
    
    CREATE_FUNC(Overview);
    
};

#endif /* defined(__TableView01__Overview__) */
