/**********************************************************************************
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#include "ofxUISortableList.h"
#include "ofxUI.h"

// TODO easing

ofxUISortableList::ofxUISortableList(string _name, vector<string> items, float w, float h, float x, float y, int _size) : ofxUIButton(_name, false, w, h, x, y, _size)
{
    init(_name, items, w, x, y, _size);
}

void ofxUISortableList::init(string _name, vector<string> items, float w, float x, float y, int _size)
{
    itemHeight = 30;
    padding = 2;
    int height = items.size() * itemHeight + (padding*items.size() + padding);
    rect->setHeight(height);
    name = string(_name);
    kind = OFX_UI_WIDGET_SORTABLELIST;
    autoSize = false;
    
    label->setVisible(false);
    drawLabel = false;
    bLabelRight = false;
    
    activeWidget = 0;
    activeWidgetIndex = -1;
    initDragableElements(items, _size);
}

vector<ofxUIDraggableLabelButton*> ofxUISortableList::getListItems()
{
    return listItems;
}

void ofxUISortableList::reshuffle(std::vector<string> ordering)// reshuffle based on saved ordering
{
    for (int i = 0; i < ordering.size(); i++)
    {
        ofxUIDraggableLabelButton* listItem =  listItems[i];
        if(listItem->getSortID()!=ordering.at(i))
        {
            for(int j = 0; j< listItems.size(); j++)
            {
                ofxUIDraggableLabelButton* _listItem =  listItems[j];
                if(_listItem->getSortID()==ordering.at(i))
                {
                    // swap i, j
                    swapListItems(i, j);
                }
            }
        }
    }
    refreshPositions();
}

void ofxUISortableList::swapListItems(int swapA, int swapB)
{
    std::swap(listItems[swapA], listItems[swapB]);
}

void ofxUISortableList::mouseDragged(int x, int y, int button)
{
    if(activeWidget)
    {
        ofxUIDraggableLabelButton* above;
        ofxUIDraggableLabelButton* below;
        int activeYPos = activeWidget->getY();
        bool isDirectionDown = lastActiveY < activeYPos;
        bool isDirectionUp = lastActiveY > activeYPos;
        lastActiveY = activeWidget->getY();
        
        if(isDirectionUp || isDirectionDown)// if there is change...
        {
            if(activeWidgetIndex>0 && (activeWidgetIndex < (listItems.size() - 1)))
            {
                above = listItems.at(activeWidgetIndex - 1);
                below = listItems.at(activeWidgetIndex + 1);
                //call based on direction of travel
                if(isDirectionUp && isInSwapZone(above))
                {
                    goingUp();
                }
                if(isDirectionDown && isInSwapZone(below))
                {
                    goingDown();
                }
            }
            else if(activeWidgetIndex==0 || activeWidgetIndex==(listItems.size()-1))
            {
                below = listItems.at(1);
                above = listItems.at(listItems.size() - 1);
                if(isDirectionDown && isInSwapZone(below))
                {
                    goingDown();
                }
                if(isDirectionUp &&  isInSwapZone(above))
                {
                    goingUp();
                }
            }
        }
    }
}

void ofxUISortableList::mousePressed(int x, int y, int button)
{
    activeWidget = getActiveWidget(x, y);
    if(activeWidget)
    {
        // save the position from where it was dragged (in case we need to put it back there)
        int activeWidgetRectY = activeWidget->getRect()->getY();
        int rectY = getRect()->getY();
        saveY = activeWidgetRectY - rectY;
        lastActiveY = saveY;
    }
}

void ofxUISortableList::mouseReleased(int x, int y, int button)
{
    activeWidgetIndex = -1;
    refreshPositions();
    activeWidget = 0;
}

void ofxUISortableList::initDragableElements(vector<string> &items, int _size)// build draggable widgets for the sortable items
{
    float ty = padding;
    int width = rect->getWidth() - padding*2;
    for(int i = 0; i < items.size(); i++)
    {
        stringstream index;
        index << i;
        string tname = items[i];
        ofxUIDraggableLabelButton* listItem;
        listItem = new ofxUIDraggableLabelButton(tname, "", width, itemHeight, padding, ty, _size);
        listItem->setVisible(true);
        listItem->setLabelVisible(true);
        addEmbeddedWidget(listItem);
        listItem->setSortID(tname + index.str());
        listItems.push_back(listItem);
        ty+=(itemHeight+padding);
    }
}

bool ofxUISortableList::isInSwapZone(ofxUIDraggableLabelButton* swapCandidate)// the "swapZone" is the area that extends from adjacent elements, in which the active widget can be bumped up or down the list
{
    int swapZoneHeight = activeWidget->getRect()->getHeight();
    
    int activeYPos = activeWidget->getY();
    int activeYBottom = activeWidget->getY() + swapZoneHeight;
    
    int candidateYPos = swapCandidate->getMidY();
    int candidateSwapZoneTop = candidateYPos - swapZoneHeight;
    int candidateSwapZoneBottom = candidateYPos + swapZoneHeight;
    
    if(activeYPos<candidateYPos && activeYPos>candidateSwapZoneTop)// if the top y position is in the swap zone
    {
        return true;
    }
    else if(activeYBottom>candidateYPos && activeYBottom<candidateSwapZoneBottom)// if the bottom y position is in the swap zone
    {
        return true;
    }
    return false;
}

void ofxUISortableList::goingUp()// what to do if the active widget is getting bumped up the list order
{
    int swapIndex = activeWidgetIndex - 1;
    swapListItems(activeWidgetIndex, swapIndex);
    activeWidgetIndex--;
    refreshPositions();
}

void ofxUISortableList::goingDown()// what to do if the active widget is getting bumped down the list order
{
    int swapIndex = activeWidgetIndex + 1;
    swapListItems(activeWidgetIndex, swapIndex);
    activeWidgetIndex++;
    refreshPositions();
}

void ofxUISortableList::refreshPositions()// if the ordering changes - reflect it visually
{
    float ty = padding;
    for (int i = 0; i < listItems.size(); i++)
    {
        if(activeWidgetIndex != i)
        {
            listItems.at(i)->setPos(padding, ty);
        }
        ty+=(itemHeight+padding);
    }
}

ofxUIDraggableLabelButton* ofxUISortableList::getActiveWidget(int x, int y)
{
    for (int i = 0; i < listItems.size(); i++)
    {
        if(listItems.at(i)->isHit(x, y))
        {
            activeWidgetIndex = i;
            return listItems.at(i);
        }
    }
    activeWidgetIndex = -1;
    return 0;
}